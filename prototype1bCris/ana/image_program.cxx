#include <fstream>
#include <iostream>
{
   std::map<std::string, TH1D*> histo1D;
   std::map<std::string, TH1D*>::iterator histo1Diter;

   std::map<std::string, TH2D*> histo2D;
   std::map<std::string, TH2D*>::iterator histo2Diter;

   TFile *f1 = new TFile("away.root","READ"); //away
   TFile *f2 = new TFile("towards.root","READ"); //towards

   //TCanvas *c1 = new TCanvas("c1","c1",600,400);
   //TCanvas *c2 = new TCanvas("c2","c2",600,400);

   TH1D* GenPaway=(TH1D*)f1->Get("GenP");
   TH1D* GenPtank=(TH1D*)f2->Get("GenP");
   
   TH2D* XYaway=(TH2D*)f1->Get("XYview");
   TH2D* XYtank=(TH2D*)f2->Get("XYview");

   TH1D* Tray1Xaway=(TH1D*)f1->Get("Tray1Xview");
   TH1D* Tray1Xtank=(TH1D*)f2->Get("Tray1Xview");

   TH2D* Tray1XYaway=(TH2D*)f1->Get("Tray1XYview");
   TH2D* Tray1XYtank=(TH2D*)f2->Get("Tray1XYview");
   
   TH1D* XTt=(TH1D*)Tray1Xtank->Clone();
   TH1D* GPt=(TH1D*)GenPtank->Clone();   
 
   TCanvas *c6 = new TCanvas("c6","c6",600,400);
   GenPtank->SetLineColorAlpha(4, 0.35);
   GenPaway->SetLineColorAlpha(3, 0.35);
   GenPaway->Draw();
   GPt->Draw("same hist");
   c6->SaveAs("GenPcompare.png");

   TCanvas *c1 = new TCanvas("c1","c1",600,400);
   GenPtank->SetLineColorAlpha(4, 0.35);
   GenPtank->Draw();
   GenPaway->Draw("same hist");
   GenPtank->Divide(GenPaway);
   GenPtank->Draw();
   c1->SaveAs("GenPratio.png");
   
   TCanvas *c2 = new TCanvas("c2","c2",600,400);
   Tray1Xtank->SetLineColorAlpha(4, 0.35);
   Tray1Xaway->SetLineColorAlpha(3, 0.35);
   Tray1Xaway->Draw();
   XTt->Draw("same hist");  
   c2->SaveAs("Xviewcompare.png");

   TCanvas *c3 = new TCanvas("c3","c3",600,400);
   Tray1Xtank->SetLineColorAlpha(4, 0.35);
   Tray1Xtank->Draw();
   Tray1Xaway->Draw("same hist");
   Tray1Xtank->Divide(Tray1Xaway);
   Tray1Xtank->Draw();
   c3->SaveAs("Xviewratio.png");

   int nx=XYaway->GetNbinsY();
   int ny=XYaway->GetNbinsX();
   cout<<"nx="<<nx<<"   ny="<<ny<<endl;

   TH2D* plotA=new TH2D("plotA","MC",10,0.0,50.0,10,0.0,50.0);

   for (int ix=1; ix<nx; ix++) {
      for(int iy=1; iy<ny; iy++) {
         double wtA=XYaway->GetBinContent(ix,iy);//collecting bin contents for everybin in 2D projection plot of away
         double wtT=XYtank->GetBinContent(ix,iy);//collection bin contents for everybin in 2D projection plot of watertank
         double wt=wtT/wtA;//taking ratio
         //cout<<"wt = "<<wtT<<endl;
         if(wt>2.5) wt=2.5;
          //cout<<"wt "<<wt<<"\n";
          double y=5*iy;
	  double x=5*ix;
	  //double y=20.0-2.0*ix+2.0/2.0;
          //double x=20.0-2.0*iy+2.0/2.0;
          //double x=1500-150*ix+150;
          //double y=1500-150*iy+150;
          //double x=2.5*(ix-26)-2.5/2.0;
          //double y=2.5*(iy-15)-2.5/2.0;
         plotA->Fill(x,y,wt);
         //out<<x<<" "<<y<<" "<<wt<<endl;
        }
   }
  //out.close();
  plotA->GetXaxis()->SetTitle("X (cm)");
  plotA->GetYaxis()->SetTitle("Y (cm)");
  
  int nxi=Tray1XYaway->GetNbinsY();
  int nyi=Tray1XYaway->GetNbinsX();
  
  TH2D* plotB=new TH2D("plotB","MC",50,-25.0,25.0,50,-25.0,25.0);
     for (int ix=1; ix<nxi; ix++) {
      for(int iy=1; iy<nyi; iy++) {
         double wtA=Tray1XYaway->GetBinContent(ix,iy);//collecting bin contents for everybin in 2D projection plot of away
         double wtT=Tray1XYtank->GetBinContent(ix,iy);//collection bin contents for everybin in 2D projection plot of watertank
         double wt=wtT/wtA;//taking ratio
         //cout<<"wt = "<<wtT<<endl;
         if(wt>2.5) wt=2.5;
          //cout<<"wt "<<wt<<"\n";
          double y=-30+iy;
          double x=-30+ix;
          //double y=20.0-2.0*ix+2.0/2.0;
          //double x=20.0-2.0*iy+2.0/2.0;
          //double x=1500-150*ix+150;
          //double y=1500-150*iy+150;
          //double x=2.5*(ix-26)-2.5/2.0;
          //double y=2.5*(iy-15)-2.5/2.0;
         plotB->Fill(x,y,wt);
         //out<<x<<" "<<y<<" "<<wt<<endl;
        }
   }
  
  plotB->GetXaxis()->SetTitle("X (cm)");
  plotB->GetYaxis()->SetTitle("Y (cm)");
  
  TCanvas *c4 = new TCanvas("c4","c4",600,400);
  plotA->Draw("colz hist");
  c4->SaveAs("plotA.png");

  TCanvas *c5 = new TCanvas("c5","c5",600,400);
  plotB->Draw("colz hist");
  c5->SaveAs("plotB.png");
}

