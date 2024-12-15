// c++  `root-config --cflags` -o muonAnalysis3 sc8muontree.cc muonAnalysis3_newsh.cc `root-config --glibs`
//
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <cassert>
#include <vector>
#include <time.h>

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TProfile.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TStyle.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TRatioPlot.h"

#include "sc8muontree.h"

using namespace std;

//   define a struct globally.
struct TrackPoint{
   TVector3 x3;
   TVector3 p3;
};

// ==========================================================================
class AnaMuon {
   public:
      AnaMuon(TFile * fout); 
      ~AnaMuon();
      void analyze(sc8muontree ev);
      void endjob();

   private:

      vector<TrackPoint>  reconstructTracks(sc8muontree ev);
      vector<TrackPoint>  estimateXYatZ(vector<double> zPlane,TrackPoint tk );

      std::map<std::string, TH1D*> histo1D;
      std::map<std::string, TH1D*>::iterator histo1Diter;

      std::map<std::string, TH2D*> histo2D;
      std::map<std::string, TH2D*>::iterator histo2Diter;
      ofstream myfile[2];
      double xme;
      double angle;
      //int printHitFlag;
      int event;
      vector<double> xe;
      vector<double> ang;
      vector<double> xe2;
      vector<double> ang2;
};
class Track {
   public:
      Track(double _x, double _y, double _xs, double _ys) {
        x=_x; y=_y; xs=_xs; ys=_ys;
      };
      double x;    // at z=0
      double y;    // at z=0
      double xs;   // xslope = (x0-x2)/(z0-z2)
      double ys;   // yslope = (y1-y3)/(z1-z3)
     // vector<Hit> hits;
};

// =========================================  zzanaMuon

AnaMuon::AnaMuon(TFile * fout) {
  std::string filename[2]= {"example.txt","example1.txt",/*"example2.txt"*/};

   for (int i = 0; i < 2; i++)
	{
		myfile[i].open(filename[i].c_str());
	} 
   //printHitFlag=0;
   event=1;
   xme=0;
   angle=0.0;
   xe.clear();
   ang.clear();
   fout->cd();
   //new code: start
   histo1D["L0Ch"]=new TH1D("L0Ch","L0 Channel Numbers",15,0.,15.);
   histo1D["L0Ch"]->GetXaxis()->SetTitle("Ch number 0 to 10");
   histo1D["L0Ch"]->GetYaxis()->SetTitle("Number of hits");
   histo1D["L1Ch"]=new TH1D("L1Ch","L1 Channel Numbers",15,0.,15.);
   histo1D["L1Ch"]->GetXaxis()->SetTitle("Ch number 0 to 10");
   histo1D["L1Ch"]->GetYaxis()->SetTitle("Number of hits");
   histo1D["L2Ch"]=new TH1D("L2Ch","L2 Channel Numbers",15,0.,15.);
   histo1D["L2Ch"]->GetXaxis()->SetTitle("Ch number 0 to 10");
   histo1D["L2Ch"]->GetYaxis()->SetTitle("Number of hits");
   histo1D["L3Ch"]=new TH1D("L3Ch","L3 Channel Numbers",15,0.,15.);
   histo1D["L3Ch"]->GetXaxis()->SetTitle("Ch number 0 to 10");
   histo1D["L3Ch"]->GetYaxis()->SetTitle("Number of hits");
   
  //new code: end
  //muX,Yproj
   int nbins = 200;   
   histo1D["GenP"]=new TH1D("GenP","Gen P (GeV)",100,0.,100.);
   histo1D["GenId"]=new TH1D("GenId","Gen Id",100,0.,20.);
   histo2D["GenXY"]=new TH2D("GenXY","Gen X vs Y (cm)",100,-100.0,100.0,100,-100.0,100.0);

   histo1D["HitP"]=new TH1D("HitP","Hit P (GeV)",100,0.,100.);
   histo2D["HitXY"]=new TH2D("HitXY","Hit X vs Y (cm)",100,-100.0,100.0,100,-100.0,100.0);

   histo1D["Layer1Edep"]=new TH1D("Layer1Edep","Layer1 Edep (MeV)",100,0.0,30.0);
   histo1D["Layer1ChId"]=new TH1D("Layer1ChId","Layer1 Channel ID (Edep weighted)",10,0.0,10.0);
   histo1D["Layer2Edep1"]=new TH1D("Layer2Edep1","Layer2 Edep 1(MeV)",100,0.0,30.0);
   histo1D["Layer2Edep"]=new TH1D("Layer2Edep","Layer2 Edep (MeV)",100,0.0,30.0);
   histo1D["Layer2ChId"]=new TH1D("Layer2ChId","Layer2 Channel ID (Edep weighted)",10,0.0,10.0);
   histo1D["Layer3Edep"]=new TH1D("Layer3Edep","Layer1 Edep (MeV)",100,0.0,30.0);
   histo1D["Layer3ChId"]=new TH1D("Layer3ChId","Layer3 Channel ID (Edep weighted)",10,0.0,10.0);
   histo1D["Layer4Edep"]=new TH1D("Layer4Edep","Layer4 Edep (MeV)",100,0.0,30.0);
   histo1D["Layer4ChId"]=new TH1D("Layer4ChId","Layer4 Channel ID (Edep weighted)",10,0.0,10.0);
   
   histo1D["Yview"]=new TH1D("Yview","Y View",12,0,60);
   histo1D["Yview1"]=new TH1D("Yview1","Y View",12,0,60);
   histo1D["Xview"]=new TH1D("Xview","X View",12,0,60);
   histo1D["Xview1"]=new TH1D("Xview1","X View",12,0,60);
   histo2D["XYview"]=new TH2D("XYview","XY View",10,0,50,10,0,50);
   
   histo1D["Tray1Yview"]=new TH1D("Tray1Yview","Y View L1",50,-25,25);
   histo1D["Tray1Xview"]=new TH1D("Tray1Xview","X View L1",50,-25,25);
   histo2D["Tray1XYview"]=new TH2D("Tray1XYview","XY View L1",50,-25,25,50,-25,25);

   histo1D["Tray2Yview"]=new TH1D("Tray2Yview","Y View L2",50,-25,25);
   histo1D["Tray2Xview"]=new TH1D("Tray2Xview","X View L2",50,-25,25);
   histo2D["Tray2XYview"]=new TH2D("Tray2XYview","XY View L2",50,-25,25,50,-25,25);

   histo1D["Theta45"]= new TH1D("Theta45","Angle from Zenith",70,0,35);
   
   int nz=20;
   double xylim=500.0;
   for (int i=0; i<nz; i++) {
     string hname="xZ"+to_string(i);
     string htitle="(reco) x at Z"+to_string(i);
     histo1D[hname]=new TH1D(hname.c_str(),htitle.c_str(),100,-xylim,xylim);
     histo1D[hname]->GetXaxis()->SetTitle("X distance [cm]");
     histo1D[hname]->GetYaxis()->SetTitle("Number of Events");
     string hname3="yZ"+to_string(i);
     string htitle3="(reco) y at Z"+to_string(i);
     histo1D[hname3]=new TH1D(hname3.c_str(),htitle3.c_str(),100,-xylim,xylim);
     histo1D[hname3]->GetXaxis()->SetTitle("Y distance [cm]");
     histo1D[hname3]->GetYaxis()->SetTitle("Number of Events");
     string hname2="xyZ"+to_string(i);
     string htitle2="(reco) x-y at Z"+to_string(i);
     histo2D[hname2]=new TH2D(hname2.c_str(),htitle2.c_str(),20,-xylim/2.0,xylim/2.0,20,-xylim/2.0,xylim/2.0);
     histo2D[hname2]->GetXaxis()->SetTitle("X projection");
     histo2D[hname2]->GetYaxis()->SetTitle("Y projection");
   } 
}
//---------------------------------------------------------------------
AnaMuon::~AnaMuon() {} ;

//---------------------------------------------------------------------
void AnaMuon::analyze(sc8muontree ev) {
   double zCry;
   double xmax,xmin,ymax,ymin;

   // reconstruct tracks...
   vector<TrackPoint> recoedTracks=reconstructTracks(ev);
   xe.clear();
   ang.clear();
   xe2.clear();
   ang2.clear();
   for(int i=0; i<ev.nGenPar; i++) {
     histo1D["GenP"]->Fill(ev.GenParP[i]);
     histo1D["GenId"]->Fill(ev.GenParId[i]);    
    
      double Pmev=ev.GenParP[i]*1000.0;
     histo2D["GenXY"]->Fill(ev.GenParVx[i],ev.GenParVy[i]);
     zCry=ev.GenParVz[i];   // z coordinate of muon source (CRY)...
   }  // end of loop over Gen Par.


  TrackPoint tkRef;
  
  for(int i=0; i<ev.nHitsT1; i++) {
     histo1D["Tray1Yview"]->Fill(ev.HitsT1Vy[i]);
     histo1D["Tray1Xview"]->Fill(ev.HitsT1Vx[i]);
     histo2D["Tray1XYview"]->Fill(ev.HitsT1Vx[i],ev.HitsT1Vy[i]);
  }

  for(int i=0; i<ev.nHitsT2; i++) {
     histo1D["Tray2Yview"]->Fill(ev.HitsT2Vy[i]);
     histo1D["Tray2Xview"]->Fill(ev.HitsT2Vx[i]);
     histo2D["Tray2XYview"]->Fill(ev.HitsT2Vx[i],ev.HitsT2Vy[i]);
  }

   for(int i=0; i<ev.nHitsT1; i++) {
     histo1D["Theta45"]->Fill(atan(sqrt(pow(ev.GenParPx[i],2)+pow(ev.GenParPy[i],2))/abs(ev.GenParPz[i]))/(4*atan(1))*180.); //acos(2*ev.HitsT1Vz[i])/sqrt(pow(ev.HitsT1Vx[i]-ev.HitsT2Vx[i],2)+pow(ev.HitsT1Vy[i]-ev.HitsT2Vy[i],2)+pow(2*ev.HitsT1Vz[i],2)));
  }

  for(int i=0; i<ev.nHitsR1; i++) {
      double Pmev2=ev.HitsR1P[i]*1000.0;
     histo1D["HitP"]->Fill(ev.HitsR1P[i]);
     histo2D["HitXY"]->Fill(ev.HitsR1Vx[i],ev.HitsR1Vy[i]);
     // save the first hit in the refence plane...
     if(i==0) {
       if(abs(ev.HitsR1Vx[i])<25.0 && abs(ev.HitsR1Vz[i])<25.0) {
         TVector3 xx(ev.HitsR1Vx[i],ev.HitsR1Vy[i],ev.HitsR1Vz[i]);
         TVector3 pp(ev.HitsR1Px[i],ev.HitsR1Py[i],ev.HitsR1Pz[i]);
         tkRef.x3=xx;
         tkRef.p3=pp;
       }
     }
   }

//   RPs code...
   for(int i=0; i<10; i++) {
     double edep1=ev.EdepS1[i];
     double edep2=ev.EdepS2[i];
     double edep3=ev.EdepS3[i];
     double edep4=ev.EdepS4[i];
     double e_cut=0.0; //threshold energy

     if(edep1>e_cut) {
         histo1D["L0Ch"]->Fill(i);
	 histo1D["Yview"]->Fill(i*5);
     }
     if(edep2>e_cut) {
         histo1D["L1Ch"]->Fill(i);
	 histo1D["Xview"]->Fill(i*5);
     }
     if(edep3>e_cut) {
         histo1D["L2Ch"]->Fill(i);
     }
     if(edep4>e_cut) {
         histo1D["L3Ch"]->Fill(i);
     }
     
   }   // end of for-loop over scint bars...

// muon tracks ... rp

   int nhits=0;
   double xx=0;
   for(int i=0; i<10; i++) {
     double edep=ev.EdepS1[i];
     double edep2=ev.EdepS2[i];
     double edep3=ev.EdepS3[i];
     double edep4=ev.EdepS4[i];
     if(edep>0.0) {
       histo1D["Layer1Edep"]->Fill(edep);
       histo1D["Layer1ChId"]->Fill(double(i),edep);
       nhits=nhits+1;
     }
     if(edep2>0.0) {
       histo1D["Layer2Edep"]->Fill(edep2);
       histo1D["Layer2ChId"]->Fill(double(i),edep2);
     }
     if(edep3>0.0) {
       histo1D["Layer3Edep"]->Fill(edep3);
       histo1D["Layer3ChId"]->Fill(double(i),edep3);
     }
     if(edep4>0.0) {
       histo1D["Layer4Edep"]->Fill(edep4);
       histo1D["Layer4ChId"]->Fill(double(i),edep4);
     }
   }
     // end of loop over scinti bars..   
  
   for(int i=0; i<10; i++){
   for(int j=0; j<10; j++){
       if(ev.EdepS1[i]>0.0 && ev.EdepS2[j]>0.0) {
	  histo1D["Yview1"]->Fill(5*i);
	  histo1D["Xview1"]->Fill(5*j);
          histo2D["XYview"]->Fill(5*i,5*j);
       }
   }}


//   createzplane where we check the position of tracks.
     double zRef=0.0;
     double nz=20.0;
     double dz=(1000.0-zRef)/nz;
     vector<double> zPlane;
     for (int i=0; i<nz; i++) { 
        double z=dz*i;
        zPlane.push_back(z); 
     }

//   hits in planes at different elevation (z)...
 /*  if(ev.nHitsR1>0) {
     //  get hits in planes at different elevation (z)...  
     vector<TrackPoint>  tkZs=estimateXYatZ(zPlane,tkRef );
     for (int i=0; i<tkZs.size(); i++) {
        double x=tkZs[i].x3.x();
        double y=tkZs[i].x3.y();
        string hname="xAtZ"+to_string(i);
        if(y>-5000.0 && y<5000.0) {
           histo1D[hname]->Fill(x);
        }
	  	string hname4="yAtZ"+to_string(i);
        if(x>-5000.0 && x<5000.0) {
           histo1D[hname4]->Fill(y);
        }
        string hname2="xyAtZ"+to_string(i);
        histo2D[hname2]->Fill(x,y);

     }   // end of loop over trueTracks in RefPlane.
  }
*/



//  use recoedTracks...
   if(recoedTracks.size()>0) {
     //  get hits in planes at different elevation (z)...  
     //  just use the first track for nwow.
    vector<TrackPoint>  tkZs=estimateXYatZ(zPlane,recoedTracks[0]);
     for (int i=0; i<tkZs.size(); i++) {
        double x=tkZs[i].x3.x();
        double y=tkZs[i].x3.y();
        if(i==5){
           xme=tkZs[i].x3.x();
           angle=atan(tkZs[i].p3.x()/tkZs[i].p3.z());
            
        }
        
        
        string hname="xZ"+to_string(i);
        if(y>-5000.0 && y<5000.0) {
           histo1D[hname]->Fill(x);
	  
        
        }
        string hname3="yZ"+to_string(i);
        if(x>-5000.0 && x<5000.0) {
           histo1D[hname3]->Fill(y);
        }
        string hname2="xyZ"+to_string(i);
        histo2D[hname2]->Fill(x,y);
    }  // end of if(recoedTracks.size()>0)
    event=event+1; 
   }
}  // end of AnaMuon::analyze

//=============================================================================
void AnaMuon::endjob() {
myfile[0].close();
myfile[1].close();
}
//=============================================================================
vector<TrackPoint>  AnaMuon::estimateXYatZ(vector<double> zPlane,TrackPoint tk ) {
   vector<TrackPoint> tkout;
     int nZplanes=zPlane.size();
     if(nZplanes>0) {
        for (int i=0; i<nZplanes; i++) {
          double dz=zPlane[i]-tk.x3.z();
          double x=dz*(tk.p3.x()/tk.p3.z())+tk.x3.x();
          double y=dz*(tk.p3.y()/tk.p3.z())+tk.x3.y();
          double z=zPlane[i];
          // cout<<"   in estimate   x"<<x<<"  y "<<y<<"  z "<<z<<endl;
          // cout<<"      zPlane[i] "<<zPlane[i]<<"  tk.x3.z() "<<tk.x3.z()<<endl; 
          TVector3 xx(x,y,z);
          
          TrackPoint tkTmp;
          tkTmp.x3=xx;
          tkTmp.p3=tk.p3;  // track vector does not change.
          tkout.push_back(tkTmp);
       // }
     }
   }  // end of if if(abs(tk.x3.x())<25.0 && abs(tk.x3.y()) <25.0) {
   return tkout;;
}

//=============================================================================
vector<TrackPoint>  AnaMuon::reconstructTracks(sc8muontree ev ) {
   vector<TrackPoint> recoedTracks;
   // layer 1 and 3 measure the y-corrdinate 
   // layer 2 and 4 measure the z-coordinate
   double zpos[]={0.0, 59.373, 51.88, -51.88, -59.373};  // index 0 is dummy
   vector<double> y1,y3;
   vector<double> x2,x4;

   //  store x and y coordinates...
   double xesum[]={0.0, 0.0, 0.0, 0.0, 0.0};
   double esum[]= {0.0, 0.0, 0.0, 0.0, 0.0};
   
   for(int i=0; i<10; i++) {
     double edep1=ev.EdepS1[i];   // y1
     double edep2=ev.EdepS2[i];   // x2
     double edep3=ev.EdepS3[i];   // y3
     double edep4=ev.EdepS4[i];   // x4
     
     double xyval=5.0*i+2.5;

     if(edep1>0.0) {xesum[1]=xesum[1]+edep1*xyval; esum[1]=esum[1]+edep1;}
     if(edep2>0.0) {xesum[2]=xesum[2]+edep2*xyval; esum[2]=esum[2]+edep2;}
     if(edep3>0.0) {xesum[3]=xesum[3]+edep3*xyval; esum[3]=esum[3]+edep3;}
     if(edep4>0.0) {xesum[4]=xesum[4]+edep4*xyval; esum[4]=esum[4]+edep4;}
   } // end of for loop

   double a;
   if(esum[1]>0.0) {a=xesum[1]/esum[1]; y1.push_back(a);}
   if(esum[2]>0.0) {a=xesum[2]/esum[2]; x2.push_back(a);}
   if(esum[3]>0.0) {a=xesum[3]/esum[3]; y3.push_back(a);}
   if(esum[4]>0.0) {a=xesum[4]/esum[4]; x4.push_back(a);}
   // reconstruct tracks...
   if(y1.size()==1 && y3.size()==1 && x2.size()==1 && x4.size()==1) {
      for(int iy1=0; iy1<y1.size(); iy1++) {
      for(int iy3=0; iy3<y3.size(); iy3++) {
        double yslope=(y3[iy3]-y1[iy1])/(zpos[3]-zpos[1]);
        double ypos=y1[iy1]+yslope*(0.0-zpos[1]);
        // calculate x slopes
        for(int ix2=0; ix2<x2.size(); ix2++) {
        for(int ix4=0; ix4<x4.size(); ix4++) {
          double xslope=(x4[ix4]-x2[ix2])/(zpos[4]-zpos[2]);
          double xpos=x2[ix2]+xslope*(0.0-zpos[2]);
         TrackPoint tkTemp;
         TVector3 xx(xpos,ypos,0.0); 
         TVector3 pp(xslope,yslope,1.0); 
         tkTemp.x3=xx;
         tkTemp.p3=pp;         
         recoedTracks.push_back(tkTemp);
        }  // end of loop over x4
        }  // end of loop over x2.
      }  // end of loop over y3.
      }  // end of loop over y1.
   }
   return recoedTracks;
}  // end of AnaMuon::reconstructTracks

// ==========================================================================
int main(int argc, char **argv) {

   string inputFileName=argv[1];
   string outputFileName=argv[2];
   cout<<"Input file name="<<inputFileName<<endl;
   cout<<"Output file name="<<outputFileName<<endl;
   TFile *fout = new TFile(outputFileName.c_str(),"recreate");

   AnaMuon ana(fout);

   TFile fin(inputFileName.c_str());

   TTree * tree;
   fin.GetObject("tree",tree);

   //   print out ntuple data structure...
   // tree->Print();

   sc8muontree ev;
   ev.Init(tree);

   int nentries = tree->GetEntriesFast();
  
   cout<<"nentries  "<<nentries<<endl;

   int nMax=1000000000;
   int nn=0;
   while ( ev.GetEntry(nn)){
       nn++;
       if(nn>nMax) break;
       ana.analyze(ev);
   } // end of event loop.

   ana.endjob();

   fout->Write();
   fout->Close();

}

