
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B4DetectorConstruction.cc 101905 2016-12-07 11:34:39Z gunter $
// 
/// \file B4DetectorConstruction.cc
/// \brief Implementation of the B4DetectorConstruction class

#include "B4DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Sphere.hh" // included by rp for sphere
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "MuonTree.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal 
G4GlobalMagFieldMessenger* B4DetectorConstruction::fMagFieldMessenger = nullptr; 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4DetectorConstruction::B4DetectorConstruction(MuonTree* histo)
 : G4VUserDetectorConstruction(),
   fMuonTree(histo),
   fCheckOverlaps(true)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4DetectorConstruction::~B4DetectorConstruction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B4DetectorConstruction::Construct()
{
  // Define materials 
  DefineMaterials();
  
  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4DetectorConstruction::DefineMaterials()
{ 
  // Lead material defined using NIST Manager
  auto nistManager = G4NistManager::Instance();
  nistManager->FindOrBuildMaterial("G4_AIR");
  
  // Liquid argon material
  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;  
  G4double density;
  G4int ncomponents, natoms; 
  G4Element* C = new G4Element("Carbon", "C", z=6., a=12.01*g/mole);
  G4Element* H = new G4Element("Hydrogen", "H", z=1., a=1.01*g/mole);
  G4Element* Ca = new G4Element("Calcium", "Ca", z=20., a=40.078*g/mole);
  G4Element* O = new G4Element("Oxygen", "O", z=8., a=15.999*g/mole);
  new G4Material("liquidArgon", z=18., a= 39.95*g/mole, density= 1.390*g/cm3);
         // The argon by NIST Manager is a gas with a different density
  new G4Material("iron", z=26.,a=55.850*g/mole, density=7.894*g/cm3);
  new G4Material("tungsten", z=74.,a=183.85*g/mole, density=19.3*g/cm3);
  new G4Material("copper", z=29.,a=63.54*g/mole, density=8.96*g/cm3); 
  new G4Material("lead", z=82.,a=207.19*g/mole, density=11.34*g/cm3);
  // Vacuum
  new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
                  kStateGas, 2.73*kelvin, 3.e-18*pascal);

  G4Material* Scintillator = 
	new G4Material("Scintillator", density= 1.032*g/cm3, ncomponents=2);
	Scintillator->AddElement(C, natoms=9);
	Scintillator->AddElement(H, natoms=10);
	
	Scintillator->GetIonisation()->SetBirksConstant(0.126*mm/MeV);
  // Water
  G4Element* ele_H = new G4Element("Hydrogen","H",z=1.,a = 1.01*g/mole);
  G4Element* ele_O = new G4Element("Oxygen","O",z=8.,a=16.00*g/mole);
  G4Material* H2O = new G4Material("Water",density=1.000*g/cm3,ncomponents=2);
  H2O->AddElement(ele_H, natoms=2);
  H2O->AddElement(ele_O, natoms=1);

  //Limestone
  G4Material* Limestone =
	new G4Material("Limestone", density= 2.6*g/cm3, ncomponents=3);
	Limestone->AddElement(Ca, natoms=1);
	Limestone->AddElement(C, natoms=1);
	Limestone->AddElement(O, natoms=3);

  nistManager->FindOrBuildMaterial("G4_Fe");
  nistManager->FindOrBuildMaterial("G4_Pb");
  nistManager->FindOrBuildMaterial("G4_AIR");
  nistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  nistManager->FindOrBuildMaterial("G4_H");
  nistManager->FindOrBuildMaterial("G4_C");
  nistManager->FindOrBuildMaterial("G4_O");
  nistManager->FindOrBuildMaterial("G4_Al");
  nistManager->FindOrBuildMaterial("G4_Si");
  nistManager->FindOrBuildMaterial("G4_K");
  nistManager->FindOrBuildMaterial("G4_Ca");
  nistManager->FindOrBuildMaterial("G4_Fe");
  nistManager->FindOrBuildMaterial("G4_Na");
  nistManager->FindOrBuildMaterial("G4_Mg");  
  nistManager->FindOrBuildMaterial("G4_Sc");  
 // Liquid argon material
  new G4Material("liquidArgon", z=18., a= 39.95*g/mole, density= 1.390*g/cm3);
         // The argon by NIST Manager is a gas with a different density

  // Vacuum
  new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
                  kStateGas, 2.73*kelvin, 3.e-18*pascal);


//soil-this section describes fractional compostion of soil. comment out whole section if not using the material
/*	a = 1.00794*g/mole;
	G4Element* elH = new G4Element ("Hydrogen" ,"H", 1., a);
 	
	a = 12.0107*g/mole;
	G4Element* elC  = new G4Element("Carbon","C" ,  6., a);

	a = 16.00*g/mole;
  	G4Element* elO  = new G4Element("Oxygen"  ,"O" ,  8., a);

	a = 26.981539*g/mole;
	G4Element* elAl  = new G4Element("Aluminium"  ,"Al" ,  13., a);

	a = 28.0855*g/mole;
	G4Element* elSi  = new G4Element("Silicon"  ,"Si" , 14., a); 

	a = 39.0983*g/mole;
        G4Element* elK  = new G4Element("Potasium"  ,"K" , 19., a);

	a = 40.078*g/mole;
        G4Element* elCa  = new G4Element("Calcium"  ,"Ca" , 20., a);
	
	a = 55.845*g/mole;
        G4Element* elFe  = new G4Element("Iron"  ,"Fe" , 26., a);      
	
	density = 2837.0*mg/cm3;
  
	G4Material* Soil = new G4Material("Soil",density, 8);
  	Soil->AddElement(elH, 2.1*perCent);
  	Soil->AddElement(elC, 1.6*perCent);
	Soil->AddElement(elO, 57.7*perCent);
  	Soil->AddElement(elAl, 5.0*perCent);
	Soil->AddElement(elSi, 27.1*perCent);
	Soil->AddElement(elK, 1.3*perCent);
	Soil->AddElement(elCa, 4.1*perCent);
	Soil->AddElement(elFe, 1.1*perCent);
 */

//
// Rock-this section describes fractional compostion of soil. comment out who    le section if not using the material
//


          a = 16.00*g/mole;
         G4Element* elO  = new G4Element("Oxygen"  ,"O" ,  8., a);
         
         a = 28.0855*g/mole;
         G4Element* elSi  = new G4Element("Silicon"  ,"Si" , 14., a); 
         
         a = 26.981539*g/mole;
         G4Element* elAl  = new G4Element("Aluminium"  ,"Al" ,  13., a);
         
         a = 55.845*g/mole;
         G4Element* elFe  = new G4Element("Iron"  ,"Fe" , 26., a);     
        
         a = 40.078*g/mole;
         G4Element* elCa  = new G4Element("Calcium"  ,"Ca" , 20., a);
         
         a = 22.9898*g/mole;
         G4Element* elNa  = new G4Element("Sodium"  ,"Na" , 11., a);
         
         a = 39.0983*g/mole;
         G4Element* elK  = new G4Element("Potasium"  ,"K" , 19., a);
       
       	 a = 24.305*g/mole;
         G4Element* elMg  = new G4Element("Magnesium"  ,"Mg" , 12., a);
	      
         
         density = 2680.0*mg/cm3;
   
         G4Material* Rock1 = new G4Material("Rock1",density, 8);
         Rock1->AddElement(elO, (46.60+1.41)*perCent);  // 1.41 to make total 100 percent
         Rock1->AddElement(elSi, 27.72*perCent);
         Rock1->AddElement(elAl, 8.13*perCent);
         Rock1->AddElement(elFe, 5.00*perCent);
         Rock1->AddElement(elCa, 3.63*perCent);
         Rock1->AddElement(elNa, 2.83*perCent);
         Rock1->AddElement(elK, 2.59*perCent);
         Rock1->AddElement(elMg, 2.09*perCent);

         G4Material* Rock2 = new G4Material("Rock2",density*0.9, 8);
         Rock2->AddElement(elO, (46.60+1.41)*perCent);
         Rock2->AddElement(elSi, 27.72*perCent);
         Rock2->AddElement(elAl, 8.13*perCent);
         Rock2->AddElement(elFe, 5.00*perCent);
         Rock2->AddElement(elCa, 3.63*perCent);
         Rock2->AddElement(elNa, 2.83*perCent);
         Rock2->AddElement(elK, 2.59*perCent);
         Rock2->AddElement(elMg, 2.09*perCent);

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B4DetectorConstruction::DefineVolumes()
{
  /*  G4 Gerometry Tree
     World
       - Cairn
          - Chamber
          - Passage
       - HillBottom
       - HillBottom
       - Camera  
           - Tray
           - sBar
       - RefPlane
  */

  // Geometry parameters
  G4RotationMatrix* zRot = new G4RotationMatrix; // Rotates X and Z axes only
  zRot -> rotateX(0.*rad);
  zRot -> rotateY(0.*rad);
  zRot -> rotateZ(M_PI/2.*rad);

  // Get materials
  auto defaultMaterial = G4Material::GetMaterial("G4_AIR");
  auto boxMaterial = G4Material::GetMaterial("Limestone");
  auto sBarMaterial  = G4Material::GetMaterial("Scintillator");
  // auto carinMaterial = G4Material::GetMaterial("Rock2");  // Rock2 or G4_AIR
  // auto hillMaterial = G4Material::GetMaterial("Rock1");   // Rock1 or G4_AIR
  auto carinMaterial = G4Material::GetMaterial(fMuonTree->getParamS("materialCairn"));  // Rock2 or G4_AIR
  auto hillMaterial = G4Material::GetMaterial(fMuonTree->getParamS("materialHill"));   // Rock1 or G4_AIR
  auto chamberMaterial = G4Material::GetMaterial(fMuonTree->getParamS("materialChamber"));  // G4_AIR or Rock2
  auto passageMaterial = G4Material::GetMaterial(fMuonTree->getParamS("materialPassage"));  // G4_AIR or Rock2


  if ( ! defaultMaterial || ! sBarMaterial ) {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined."; 
    G4Exception("B4DetectorConstruction::DefineVolumes()",
      "MyCode0001", FatalException, msg);
  } 
   
  //     
  // World
  //

  worldSizeX = 1000.0*m ;  // half width
  worldSizeY = 1000.0*m ;  // half width
  worldSizeZ = 300.0*m ;  // half width

  auto worldS 
    = new G4Box("World",           // its name
                 worldSizeX, worldSizeY, worldSizeZ); // its size
                         
  auto worldLV
    = new G4LogicalVolume(
                 worldS,           // its solid
                 defaultMaterial,  // its material
                 "World");         // its name
                                   
  auto worldPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 worldLV,          // its logical volume                         
                 "World",          // its name
                 0,                // its mother  volume
                 false,            // no boolean operation
                 0,
                 fCheckOverlaps);		 // copy number
  
    //
    // HillTop
    //

    G4double HillToppRmin1 = 0.0;
    G4double HillToppRmin2 = 0.0;
    G4double HillToppDz = ((50.0-3.0)/2.0)*m;  //  10.0 m drop per 100 m in R, Z=+3.0 at R=0
    G4double HillToppSPhi = 0.0;
    G4double HillToppRmax1 = 500.0*m;
    G4double HillToppRamx2 = 30.0*m;
    G4double HillToppDPhi = 2.0*M_PI;
    
    auto HillTopS
        = new G4Cons("HillTop", //its name
                HillToppRmin1, HillToppRmax1, HillToppRmin2, HillToppRamx2, HillToppDz, HillToppSPhi, HillToppDPhi); // its size

    auto HillTopLV
        = new G4LogicalVolume(
                HillTopS,
                hillMaterial,
                "HillTop");

    new G4PVPlacement(
            0,
            G4ThreeVector(0.0,0.0,-HillToppDz),
            HillTopLV,
            "HillTop",
            worldLV,
            false,
            0,
            fCheckOverlaps);

    //
    // HillBottom
    //

    G4double HillBottompRmin1 = 0.0;
    G4double HillBottompRmin2 = 0.0;
    G4double HillBottompDz = 100.0*m;
    G4double HillBottompSPhi = 0.0;
    G4double HillBottompRmax1 = 700.0*m;
    G4double HillBottompRamx2 = 500.0*m;
    G4double HillBottompDPhi = 2.0*M_PI;
    
    auto HillBottomS
        = new G4Cons("HillBottom", //its name
                HillBottompRmin1, HillBottompRmax1, HillBottompRmin2, HillBottompRamx2, HillBottompDz, HillBottompSPhi, HillBottompDPhi); // its size

    auto HillBottomLV
        = new G4LogicalVolume(
                HillBottomS,
                hillMaterial,
                "HillBottom");

    new G4PVPlacement(
            0,
            G4ThreeVector(0.0,0.0,-HillBottompDz-HillToppDz*2),
            HillBottomLV,
            "HillBottom",
            worldLV,
            false,
            0,
            fCheckOverlaps);
   
  //                                 
  // camera
  //

  G4double cameraSizeX  = 1.0*m;
  // G4double cameraSizeY  = 5.0*m;
  G4double cameraSizeY  = fMuonTree->getParamF("cameraWidth")*m;
  G4double cameraSizeZ  = 0.1*m;

  G4double TraySizeX  = cameraSizeX;
  G4double TraySizeY  = cameraSizeY;
  G4double TraySizeZ  = 1.0*cm;;
  G4double TrayPosX   = 0.0;
  G4double TrayPosY   = 0.0;
  G4double ztray=(cameraSizeZ-TraySizeZ)/2.0;
  G4double TrayPosZ[] = {ztray,-ztray};

  G4RotationMatrix* cameraRot = new G4RotationMatrix;
  double  angle=90.0*M_PI/180.0;
  cameraRot -> rotateX(0.*rad);
  cameraRot -> rotateY(-angle*rad);
  cameraRot -> rotateZ(0.*rad);

  G4RotationMatrix* camera1Rot = new G4RotationMatrix;
  double  angleCam1=90.0*M_PI/180.0;
  camera1Rot -> rotateX(0.*rad);
  camera1Rot -> rotateY(-angleCam1*rad);
  camera1Rot -> rotateZ(0.*rad);

  auto CameraS
    = new G4Box("Camera",           // its name
                 cameraSizeX/2, cameraSizeY/2, cameraSizeZ/2); // its size
                         
  auto CameraLV
    = new G4LogicalVolume(
                 CameraS,           // its solid
                 defaultMaterial,  // its material
                 "Camera");         // its name
   /*
   new G4PVPlacement(
                 cameraRot,                // no rotation
                 G4ThreeVector(-31.0*m,0, 0.5*m),  // at (0,0,0)
                 CameraLV,          // its logical volume                         
                 "Camera",    // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps
   */
   double  c1x=fMuonTree->getParamF("camera1Xpos"); // - 50m, -70m etc.
   double  c1z=3.0+10.0*c1x/100.;             // slope 10m drop per 100m
   double  c1xshift=c1x+cameraSizeZ/m+0.5;    // note:  camera is on negative x side.
   double  xxxcam1=c1xshift*m;
   double  zzzcam1=(HillToppDz/m+c1z+fMuonTree->getParamF("camera1Zpos"))*m; // c1z and camera1Zpos are negative.

   std::cout<<"B4DetectorConstruction:  c1x="<<c1x<<"   c1z="<<c1z<<"  cameraSizeZ="<<cameraSizeZ<<std::endl;
   std::cout<<"B4DetectorConstruction:  xxxcam1="<<xxxcam1<<"   zzzcam1="<<zzzcam1<<std::endl;
   std::cout<<"B4DetectorConstruction:  cameraSize X "<<cameraSizeX<<"  y "<< cameraSizeY<<"  Z "<<cameraSizeZ<<std::endl;

   new G4PVPlacement(
                 camera1Rot,                // no rotation
                 G4ThreeVector(xxxcam1, 0, zzzcam1),  // 
                 CameraLV,          // its logical volume                         
                 "Camera",    // its name
                 HillTopLV,          // its mother  volume
                 false,            // no boolean operation
                 1,                // copy number
                 fCheckOverlaps);  // checking overlaps

//   Reference Plane:  a thin horizontal plane at the center of camera.

auto RefPlaneS
     = new G4Box("RefPlane",           // its name
                 cameraSizeX/2, cameraSizeY/2, 1.0); // 
auto RefPlaneLV
    = new G4LogicalVolume(
                 RefPlaneS,        // its solid
                 defaultMaterial, // its material
                "RefPlane");          // its name

   new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0.0, 0.0, 0.0),  // at (0,0,0)
                 RefPlaneLV,          // its logical volume                         
                 "RefPlane",    // its name
                 CameraLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps


   //    Two Trays

   auto TrayS
     = new G4Box("Tray1",           // its name
                  TraySizeX/2, TraySizeY/2, TraySizeZ/2); // its size  
   auto TrayLV
    = new G4LogicalVolume(
                 TrayS,        // its solid
                 sBarMaterial, // its material
                "Tray");          // its name

   new G4PVPlacement(              
                 0,                // no rotation
                 G4ThreeVector(TrayPosX,TrayPosY,TrayPosZ[0]),  // at (0,0,0)
                 TrayLV,          // its logical volume                         
                 "Tray",    // its name
                 CameraLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps

   new G4PVPlacement(
                 0,                 // no rotation
                 G4ThreeVector(TrayPosX,TrayPosY,TrayPosZ[1]),  // at (0,0,0)
                 TrayLV,          // its logical volume                         
                 "Tray",    // its name
                 CameraLV,          // its mother  volume
                 false,            // no boolean operation
                 1,                // copy number
                 fCheckOverlaps);  // checking overlaps


    //
    // Cairn
    //
    
    G4double CairnpRmin1 = 0.0;
    G4double CairnpRmin2 = 0.0;
    G4double CairnpDz = 5.0*m;
    G4double CairnpSPhi = 0.0;
    G4double CairnpRmax1 = 30.0*m;
    G4double CairnpRamx2 = 10.0*m;
    G4double CairnpDPhi = 2.0*M_PI;

    G4RotationMatrix* cairnRot = new G4RotationMatrix;
    double  angleCairn=fMuonTree->getParamF("cairnRotZ")*M_PI/180.0;
    cairnRot -> rotateX(0.);
    cairnRot -> rotateY(0.);
    cairnRot -> rotateZ(angleCairn);

    
    auto CairnS
        = new G4Cons("Cairn", //its name
                CairnpRmin1, CairnpRmax1, CairnpRmin2, CairnpRamx2, CairnpDz, CairnpSPhi, CairnpDPhi); // its size

    auto CairnLV
        = new G4LogicalVolume(
                CairnS,
                carinMaterial,
                "Cairn");

    new G4PVPlacement(
            cairnRot,
            G4ThreeVector(0.0,0.0,CairnpDz),
            CairnLV,
            "Cairn",
            worldLV,
            false,
            0,
            fCheckOverlaps);

    //
    // Chamber
    //

    // G4double ChamberSizeXYZ = 4.0*m;
    G4double ChamberSizeX = fMuonTree->getParamF("chamberSizeX")*m;
    G4double ChamberSizeY = fMuonTree->getParamF("chamberSizeY")*m;
    G4double ChamberSizeZ = fMuonTree->getParamF("chamberSizeZ")*m;
    G4double ChamberPosX = fMuonTree->getParamF("chamberPosX")*m;
    G4double ChamberPosY = fMuonTree->getParamF("chamberPosY")*m;
    G4double ChamberPosZ = fMuonTree->getParamF("chamberPosZ")*m;

    auto ChamberS
        = new G4Box("Chamber", //its name
                ChamberSizeX/2, ChamberSizeY/2, ChamberSizeZ/2); // its size

    auto ChamberLV
        = new G4LogicalVolume(
                ChamberS,
                chamberMaterial,
                "Chamber");

    new G4PVPlacement(
            0,
            G4ThreeVector(ChamberPosX,ChamberPosY,ChamberPosZ-CairnpDz),
            ChamberLV,
            "Chamber",
            CairnLV,
            false,
            0,
            fCheckOverlaps);

    //
    // Passage
    //

    // G4double PassageSizeXZ = 2.0*m;
    // G4double PassageSizeY = 25.0*m;
    // G4double PassageSizeY = 20.0*m;

    G4double PassageSizeX = fMuonTree->getParamF("passageSizeX")*m;
    G4double PassageSizeY = fMuonTree->getParamF("passageSizeY")*m;
    G4double PassageSizeZ = fMuonTree->getParamF("passageSizeZ")*m;
    G4double PassagePosX = fMuonTree->getParamF("passagePosX")*m;
    G4double PassagePosY = fMuonTree->getParamF("passagePosY")*m;
    G4double PassagePosZ = fMuonTree->getParamF("passagePosZ")*m;

    auto PassageS
        = new G4Box("Passage", //its name
                PassageSizeX/2.0, PassageSizeY/2.0, PassageSizeZ/2.0); // its size

    auto PassageLV
        = new G4LogicalVolume(
                PassageS,
                passageMaterial,
                "Passage");

    new G4PVPlacement(
            0,
            G4ThreeVector(PassagePosX, PassagePosY, PassagePosZ-CairnpDz),
            // G4ThreeVector(0.0,PassageSizeXZ/2+PassageSizeY/2,PassageSizeXZ/2-CairnpDz),
            PassageLV,
            "Passage",
            CairnLV,
            false,
            0,
            fCheckOverlaps);
  
  //                                       
  // Visualization attributes
  //

  worldLV->SetVisAttributes(new G4VisAttributes(TRUE,G4Colour(0.0,0.0,1.0)));
  CameraLV->SetVisAttributes(new G4VisAttributes(TRUE,G4Colour(0.0,1.0,0.0)));
  TrayLV->SetVisAttributes(new G4VisAttributes(TRUE,G4Colour(0.0,0.0,0.0)));
  //  sBARLV->SetVisAttributes(new G4VisAttributes(TRUE,G4Colour(1.0,0.0,0.0)));
  RefPlaneLV->SetVisAttributes(new G4VisAttributes(TRUE,G4Colour(1.0,0.0,0.0)));
  CairnLV->SetVisAttributes(new G4VisAttributes(TRUE,G4Colour(0.345098, 0.407843, 0.121569, 0.30)));
  HillTopLV->SetVisAttributes(new G4VisAttributes(TRUE,G4Colour(0.345098, 0.407843, 0.121569, 0.30)));
  HillBottomLV->SetVisAttributes(new G4VisAttributes(TRUE,G4Colour(0.345098, 0.407843, 0.121569, 0.30)));
  ChamberLV->SetVisAttributes(new G4VisAttributes(TRUE,G4Colour(0.45, 0.30, 0.10, 0.30)));
  PassageLV->SetVisAttributes(new G4VisAttributes(TRUE,G4Colour(0.45, 0.30, 0.10, 0.30)));


  //
  // Always return the physical World
  //
  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4DetectorConstruction::ConstructSDandField()
{ 
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  G4ThreeVector fieldValue;
  fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);
  
  // Register the field messenger for deleting
  G4AutoDelete::Register(fMagFieldMessenger);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
