#include "TH1.h"
#include "TFile.h"
#include "TString.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>     /* atof */
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"
#include "TF1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TGraphErrors.h"
#include "TFrame.h"
#include <TPaveStats.h>
#include "TAttText.h"
#include "TMultiGraph.h"
#include "TTree.h"
#include <TCut.h>
#include <TLegend.h>
using namespace std;

int main(){

   TFile *f1 = TFile::Open("AllRoot/ggH125_taumu_new.root");
   TTree *mytree1 = (TTree*)f1->Get("tree");
   //TFile *f2 = TFile::Open("AllRoot/VBFH125_taumu.root");
   //TTree *mytree2 = (TTree*)f2->Get("tree");
   TFile *f3 = TFile::Open("AllRoot/ggH125_taue_new.root");
   TTree *mytree3 = (TTree*)f3->Get("tree");
   //TFile *f4 = TFile::Open("AllRoot/VBFH125_taue.root");
   //TTree *mytree4 = (TTree*)f4->Get("tree");
   TFile *f5 = TFile::Open("AllRoot/ggH125_tautau_new.root");
   TTree *mytree5 = (TTree*)f5->Get("tree");
   //TFile *f6 = TFile::Open("AllRoot/Ztautau.root");
   //TTree *mytree6 = (TTree*)f6->Get("tree");
   
   
   int pmin[10] = {20, 40, 50, 60, 75, 90,  150, 250, 400, 800};    //  200., 400., 800.,  1200. };
   int pmax[10] = {40, 50, 60, 75, 90, 150, 250, 400, 800, 2000};  //400., 800., 1200., 2000. };
   
    
   std::vector<TString> cuts = {
     "tau_Momentum/1000  > 20.   &&  tau_Momentum/1000  < 40.",
     "tau_Momentum/1000  > 40.   &&  tau_Momentum/1000  < 50.",
     "tau_Momentum/1000  > 50.  &&  tau_Momentum/1000   < 60.",
     "tau_Momentum/1000  > 60.  &&  tau_Momentum/1000   < 75.",
     "tau_Momentum/1000  > 75.  &&  tau_Momentum/1000   < 90.",
     "tau_Momentum/1000  > 90.  &&  tau_Momentum/1000   < 150.",
     "tau_Momentum/1000  > 150.  &&  tau_Momentum/1000  < 250.",
     "tau_Momentum/1000  > 250.  &&  tau_Momentum/1000  < 400.",
     "tau_Momentum/1000  > 400.  &&  tau_Momentum/1000  < 800.",
     "tau_Momentum/1000  > 800. &&  tau_Momentum/1000   < 2000."};
   /*,
     "tau_Momentum/1000  > 200. &&  tau_Momentum/1000   < 400.",
     "tau_Momentum/1000  > 400. &&  tau_Momentum/1000   < 800.",
     "tau_Momentum/1000  > 800. &&  tau_Momentum/1000   < 1200.",
     "tau_Momentum/1000  > 1200.&&  tau_Momentum/1000   < 2000."
     };*/
   

   TString cut1 = "IsHadronicTau == 1";
   TString cut2 = "Angle_Vis_neutrino < .25";
   TString cut3 = "numCharged == 1";
   TString cut4 = "numNeutral == 0";
   TString cut5 = "numNeutral > 0";
   TString cut6 = "numCharged == 3";
   //   TString cut7 = " tau_Momentum/1000 > 400" ;
   //   TString cut8 = " tau_Momentum/1000 < 800" ;
   // TCut cut10 = "cuts.at(ipbin)";
   TH1F *h_1 = new TH1F("h_1","h_1",100, 0., 0.25);
   //TH1F *h_2 = new TH1F("h_2", "h_2",100, 0., 0.25);
   TH1F *h_3 = new TH1F("h_3", "h_3",100, 0., 0.25);
   //TH1F *h_4 = new TH1F("h_4", "h_4",100, 0., 0.25);
   TH1F *h_5 = new TH1F("h_5", "h_5",100, 0., 0.25);
   //TH1F *h_6 = new TH1F("h_6", "h_6",100, 0., 0.25);
   for ( int i = 0; i < 3 ; ++i){
     for ( int ipbin = 0; ipbin < 10 ; ++ipbin){
     
       if (i == 0){
	 mytree1->Project("h_1","Angle_Vis_neutrino", Form( "%s && %s && %s && %s && %s",cut1.Data(), cut2.Data(), cut3.Data(), cut4.Data(), cuts[ipbin].Data()));
	 //mytree2->Project("h_2","Angle_Vis_neutrino", Form( "%s && %s && %s && %s && %s",cut1.Data(), cut2.Data(), cut3.Data(), cut4.Data(), cuts[ipbin].Data()));
	 mytree3->Project("h_3","Angle_Vis_neutrino", Form( "%s && %s && %s && %s && %s",cut1.Data(), cut2.Data(), cut3.Data(), cut4.Data(), cuts[ipbin].Data()));
	 //mytree4->Project("h_4","Angle_Vis_neutrino", Form( "%s && %s && %s && %s && %s",cut1.Data(), cut2.Data(), cut3.Data(), cut4.Data(), cuts[ipbin].Data()));
	 mytree5->Project("h_5","Angle_Vis_neutrino", Form( "%s && %s && %s && %s && %s",cut1.Data(), cut2.Data(), cut3.Data(), cut4.Data(), cuts[ipbin].Data()));
	 //mytree6->Project("h_6","Angle_Vis_neutrino", Form( "%s && %s && %s && %s && %s",cut1.Data(), cut2.Data(), cut3.Data(), cut4.Data(), cuts[ipbin].Data()));
       }
       if (i == 1){
	 mytree1->Project("h_1","Angle_Vis_neutrino", Form( "%s && %s && %s && %s && %s",cut1.Data(), cut2.Data(), cut3.Data(), cut5.Data(), cuts[ipbin].Data()));
	 //mytree2->Project("h_2","Angle_Vis_neutrino", Form( "%s && %s && %s && %s && %s",cut1.Data(), cut2.Data(), cut3.Data(), cut5.Data(), cuts[ipbin].Data()));
	 mytree3->Project("h_3","Angle_Vis_neutrino", Form( "%s && %s && %s && %s && %s",cut1.Data(), cut2.Data(), cut3.Data(), cut5.Data(), cuts[ipbin].Data()));
	 //mytree4->Project("h_4","Angle_Vis_neutrino", Form( "%s && %s && %s && %s && %s",cut1.Data(), cut2.Data(), cut3.Data(), cut5.Data(), cuts[ipbin].Data()));
	 mytree5->Project("h_5","Angle_Vis_neutrino", Form( "%s && %s && %s && %s && %s",cut1.Data(), cut2.Data(), cut3.Data(), cut5.Data(), cuts[ipbin].Data()));
	 //mytree6->Project("h_6","Angle_Vis_neutrino", Form( "%s && %s && %s && %s && %s",cut1.Data(), cut2.Data(), cut3.Data(), cut5.Data(), cuts[ipbin].Data()));
       }
     if (i == 2){
     mytree1->Project("h_1","Angle_Vis_neutrino", Form( "%s && %s && %s && %s",cut1.Data(), cut2.Data(), cut6.Data(), cuts[ipbin].Data()));
     //mytree2->Project("h_2","Angle_Vis_neutrino", Form( "%s && %s && %s && %s",cut1.Data(), cut2.Data(), cut6.Data(), cuts[ipbin].Data()));
     mytree3->Project("h_3","Angle_Vis_neutrino", Form( "%s && %s && %s && %s",cut1.Data(), cut2.Data(), cut6.Data(), cuts[ipbin].Data()));
     //mytree4->Project("h_4","Angle_Vis_neutrino", Form( "%s && %s && %s && %s",cut1.Data(), cut2.Data(), cut6.Data(), cuts[ipbin].Data()));
     mytree5->Project("h_5","Angle_Vis_neutrino", Form( "%s && %s && %s && %s",cut1.Data(), cut2.Data(), cut6.Data(), cuts[ipbin].Data()));
     //mytree6->Project("h_6","Angle_Vis_neutrino", Form( "%s && %s && %s && %s",cut1.Data(), cut2.Data(), cut6.Data(), cuts[ipbin].Data()));
     }
     
     //     mytree2->Draw("Angle_Vis_neutrino >> h_2", cut1 && cut2 && cut3 &&  cut10);
     //     mytree3->Draw("Angle_Vis_neutrino >> h_3", cut1 && cut2 && cut3 &&  cut10);
     //     mytree4->Draw("Angle_Vis_neutrino >> h_4", cut1 && cut2 && cut3 &&  cut10);
       /*
       mytree1->Draw("Angle_Vis_neutrino >> h_1", "tau_Momentum/1000 >  i && tau_Momentum/1000 < j");
       mytree2->Draw("Angle_Vis_neutrino  >> h_2","tau_Momentum/1000 >  i && tau_Momentum/1000 < j");
       mytree3->Draw("Angle_Vis_neutrino >> h_3", "tau_Momentum/1000 >  i && tau_Momentum/1000 < j");
       mytree4->Draw("Angle_Vis_neutrino >> h_4", "tau_Momentum/1000 >  i && tau_Momentum/1000 < j");
       mytree1->Draw("Angle_Vis_neutrino >> h_1", Form("tau_Momentum/1000 >%d && tau_Momentum/1000 < %d",i,j));
       mytree2->Draw("Angle_Vis_neutrino  >> h_2",Form("tau_Momentum/1000 >%d && tau_Momentum/1000 < %d",i,j));
       mytree3->Draw("Angle_Vis_neutrino >> h_3", Form("tau_Momentum/1000 >%d && tau_Momentum/1000 < %d",i,j));
       mytree4->Draw("Angle_Vis_neutrino >> h_4", Form("tau_Momentum/1000 >%d && tau_Momentum/1000 < %d",i,j));
       */
     // std::cout << "cuts: " << cuts.at(ipbin) << " ipbin:" << ipbin << std::endl;

     /*
     TH1F *gghtaumu  = (TH1F*)gDirectory->Get("h_1");
     TH1F *vbfhtaumu = (TH1F*)gDirectory->Get("h_2");
     TH1F *gghtaue   = (TH1F*)gDirectory->Get("h_3");
     TH1F *vbfhtaue  = (TH1F*)gDirectory->Get("h_4");
     */
     
      TCanvas* c1=new TCanvas("c1","c1",400,400);
      h_1->SetLineColor(kRed);
      //h_2->SetLineColor(kBlue);
      h_3->SetLineColor(kGreen);
      //h_4->SetLineColor(kMagenta);
      h_5->SetLineColor(kBlack);
      //h_6->SetLineColor(kCyan);
      gStyle->SetOptStat(0);
      h_1->Scale(1/h_1->Integral());
      //h_2->Scale(1/h_2->Integral());
      h_3->Scale(1/h_3->Integral());
      //h_4->Scale(1/h_4->Integral());
      h_5->Scale(1/h_5->Integral());
      //h_6->Scale(1/h_6->Integral());
      //     gghtaue->SetLineColor(kGreen);
      //     vbfhtaue->SetLineColor(kMagenta);
      if(i==0) {
	h_1->SetTitle(Form("Angle(n_cha = 1 & n_neu = 0) : %d < P(Gev) < %d", pmin[ipbin] , pmax[ipbin]));
	//h_2->SetTitle(Form("Angle(n_cha = 1 & n_neu = 0) : %d < P(Gev) < %d", pmin[ipbin] , pmax[ipbin]));
	h_3->SetTitle(Form("Angle(n_cha = 1 & n_neu = 0) : %d < P(Gev) < %d", pmin[ipbin] , pmax[ipbin]));
	//h_4->SetTitle(Form("Angle(n_cha = 1 & n_neu = 0) : %d < P(Gev) < %d", pmin[ipbin] , pmax[ipbin]));
	h_5->SetTitle(Form("Angle(n_cha = 1 & n_neu = 0) : %d < P(Gev) < %d", pmin[ipbin] , pmax[ipbin]));
	//h_6->SetTitle(Form("Angle(n_cha = 1 & n_neu = 0) : %d < P(Gev) < %d", pmin[ipbin] , pmax[ipbin]));
      }
      if(i==1) {
	h_1->SetTitle(Form("Angle(n_cha = 1 & n_neu > 0) : %d < P(Gev) < %d", pmin[ipbin] , pmax[ipbin]));
	//h_2->SetTitle(Form("Angle(n_cha = 1 & n_neu > 0) : %d < P(Gev) < %d", pmin[ipbin] , pmax[ipbin]));
	h_3->SetTitle(Form("Angle(n_cha = 1 & n_neu > 0) : %d < P(Gev) < %d", pmin[ipbin] , pmax[ipbin]));
	//h_4->SetTitle(Form("Angle(n_cha = 1 & n_neu > 0) : %d < P(Gev) < %d", pmin[ipbin] , pmax[ipbin]));
	h_5->SetTitle(Form("Angle(n_cha = 1 & n_neu > 0) : %d < P(Gev) < %d", pmin[ipbin] , pmax[ipbin]));
	//h_6->SetTitle(Form("Angle(n_cha = 1 & n_neu > 0) : %d < P(Gev) < %d", pmin[ipbin] , pmax[ipbin]));
      }
      if(i==2) {
	h_1->SetTitle(Form("Angle(n_cha = 3) : %d < P(Gev) < %d", pmin[ipbin] , pmax[ipbin]));
	//h_2->SetTitle(Form("Angle(n_cha = 3) : %d < P(Gev) < %d", pmin[ipbin] , pmax[ipbin]));
	h_3->SetTitle(Form("Angle(n_cha = 3) : %d < P(Gev) < %d", pmin[ipbin] , pmax[ipbin]));
	//h_4->SetTitle(Form("Angle(n_cha = 3) : %d < P(Gev) < %d", pmin[ipbin] , pmax[ipbin]));
	h_5->SetTitle(Form("Angle(n_cha = 3) : %d < P(Gev) < %d", pmin[ipbin] , pmax[ipbin]));
	//h_6->SetTitle(Form("Angle(n_cha = 3) : %d < P(Gev) < %d", pmin[ipbin] , pmax[ipbin]));
      }
      h_1->Draw();
      //h_2->Draw("same");
      h_3->Draw("same");
      //h_4->Draw("same");
      h_5->Draw("same");
      //h_6->Draw("same");
     //     vbfhtaumu->Draw("same");
     //     vbfhtaue->Draw("same");
     TLegend* leg_hist = new TLegend(0.7,0.7,0.9,0.9);
     leg_hist->AddEntry(h_1,"gghtaumu","l");
     //leg_hist->AddEntry(h_2,"vbfhtaumu","l");
     leg_hist->AddEntry(h_3,"gghtaue","l");
     //leg_hist->AddEntry(h_4,"vbfhtaue","l");
     leg_hist->AddEntry(h_5,"gghtautau","l");
     //leg_hist->AddEntry(h_6,"Ztautau","l");
     //     leg_hist->AddEntry(vbfhtaumu,"vbfhtaumu","l");
     //     leg_hist->AddEntry(vbfhtaue,"vbfhtaue","l");
     leg_hist->Draw();
     c1->Update();
     //c1->SaveAs("Plots_New/Angle_Vis_neutrino_1.pdf");
     c1->SaveAs(Form("/afs/cern.ch/user/a/atpathak/afswork/public/Pixel/LFV_Plots/Plots_project_New/Angle_Vis_neutrino_cut%d_%d.pdf",i+1,ipbin+1));
     delete c1;
     c1=0;
     /* 
     delete h_1;
     h_1=0;
     delete h_2;
     h_2=0;*/
     //     delete gghtaue;
     //     gghtaue=0;
     //     delete vbfhtaue;
     //     vbfhtaue=0;
   }
  }
   
}
   
