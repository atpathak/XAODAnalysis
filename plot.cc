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
using namespace std;

int main(int argc, char *argv[]){

  int decay = argc>1 ? atoi(argv[1]) : 1; // 0 : lepton, 1 : 1 prong, 2 : 3 prong

  TString Prong[4] = {"numCharged1","numChargedPion1","numCharged3","numChargedPion3"};

  TFile *f = TFile::Open("submitDir/hist-mc15_13TeV.344084.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_ggH125_taumu.merge.DAOD_HIGG4D2.e5003_s2726_r7772_r7676_p2949.root");

  int pmin[14] = {20, 40, 50, 55, 59, 64, 70, 80, 90,  100,  200, 400, 800,  1200 };
  int pmax[14] = {40, 50, 55, 59, 64, 70, 80, 90, 100, 200,  400, 800, 1200, 2000 };

  
  
    for ( int i = 0; i < 14; ++i){
      
      TH1F *Angle_Vis_neutrino = (TH1F*)f->Get(Form("h_Angle_Vis_neutrino_%s_%d",Prong[decay].Data(),i))->Clone();
      Angle_Vis_neutrino->SetTitle(Form("%s: %d < P (GeV) < %d",Prong[decay].Data(),pmin[i],pmax[i]));
      TCanvas* c1=new TCanvas("c1","c1",400,400);
      Angle_Vis_neutrino->Draw();
      c1->Update();
      c1->SaveAs(Form("Plots/Angle_Vis_neutrino_%s_%d.pdf",Prong[decay].Data(),i+1));
      delete c1;
      c1=0;
      
      delete Angle_Vis_neutrino;
      Angle_Vis_neutrino=0;


   }

    TH1F *numCharged = (TH1F*)f->Get("h_numCharged");
    TH1F *numChargedPion = (TH1F*)f->Get("h_numChargedPion");
    TCanvas* c2=new TCanvas("c2","c2",400,400);
    numCharged->Draw();
    c2->Update();
    c2->SaveAs("Plots/numCharged.pdf");
    delete c2;
    c2=0;
    delete numCharged;
    numCharged=0;

    TCanvas* c3=new TCanvas("c3","c3",400,400);
    numChargedPion->Draw();
    c3->Update();
    c3->SaveAs("Plots/numChargedPion.pdf");
    delete c3;
    c3=0;
    delete numChargedPion;
    numChargedPion=0;

    TH2F *numCharged_vs_numChargedPion = (TH2F*)f->Get("h_numCharged_vs_numChargedPion");
    TH2F *taup_vs_numCharged = (TH2F*)f->Get("h_taup_vs_numCharged");
    TH2F *taup_vs_numChargedPion = (TH2F*)f->Get("h_taup_vs_numChargedPion");
    TH2F *mvis_vs_numCharged = (TH2F*)f->Get("h_mvis_vs_numCharged");
    TH2F *mvis_vs_numChargedPion = (TH2F*)f->Get("h_mvis_vs_numChargedPion");

    TCanvas* c4=new TCanvas("c2","c2",400,400);
    numCharged_vs_numChargedPion->Draw();
    c4->SaveAs("Plots/numCharged_vs_numChargedPion.pdf");
    delete c4;
    c4=0;
    delete numCharged_vs_numChargedPion;
    numCharged_vs_numChargedPion=0;

    TCanvas* c5=new TCanvas("c2","c2",400,400);
    taup_vs_numCharged->Draw();
    c5->SaveAs("Plots/taup_vs_numCharged.pdf");
    delete c5;
    c5=0;
    delete taup_vs_numCharged;
    taup_vs_numCharged=0;
    
    TCanvas* c6=new TCanvas("c2","c2",400,400);
    taup_vs_numChargedPion->Draw();
    c6->SaveAs("Plots/taup_vs_numChargedPion.pdf");
    delete c6;
    c6=0;
    delete taup_vs_numChargedPion;
    taup_vs_numChargedPion=0;
    
    TCanvas* c7=new TCanvas("c2","c2",400,400);
    mvis_vs_numCharged->Draw();
    c7->SaveAs("Plots/mvis_vs_numCharged.pdf");
    delete c7;
    c7=0;
    delete mvis_vs_numCharged;
    mvis_vs_numCharged=0;

    TCanvas* c8=new TCanvas("c2","c2",400,400);
    mvis_vs_numChargedPion->Draw();
    c8->SaveAs("Plots/mvis_vs_numChargedPion.pdf");
    delete c8;
    c8=0;
    delete mvis_vs_numChargedPion;
    mvis_vs_numChargedPion=0;


    
   
   f->Close();
  
}
