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
using namespace std;

int main(){

  //TFile *f = TFile::Open("RootDir_tautau/data-myOutput/mc15_13TeV.341123.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_ggH125_tautaulh.merge.DAOD_HIGG4D2.e3935_s2608_s2183_r7772_r7676_p2949.root");
  //TFile *f = TFile::Open("RootDir_taumu/data-myOutput/mc15_13TeV.344084.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_ggH125_taumu.merge.DAOD_HIGG4D2.e5003_s2726_r7772_r7676_p2949.root");
  TFile *f = TFile::Open("RootDir_Ztautau/data-myOutput/mc15_13TeV.361108.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Ztautau.merge.DAOD_HIGG4D2.e3601_s2726_r7725_r7676_p2949.root");

  TTree *mytree = (TTree*)f->Get("tree");
  
  TCut cut1 = "Angle_Vis_neutrino < .25";
  TCut cut0 = "Angle_tau_truevis < .25";
  TCut cut2 = " Momentum/1000 > 40" ;
  TCut cut3 = " Momentum/1000 < 80" ;
  //TCut cut3 = "Pt_tau/1000 > 40";
  //TCut cuts = cut1 && cut2;
  //*/
  TH2F *h_AngleMom = new TH2F("h_AngleMom", "Angle_vs_Momentum_Ztautau",100, 0., 100., 100, 0., 0.25);
  TH2F *h_AngleMomtau = new TH2F("h_AngleMomtau", "Angle_vs_Momentum_Ztautau",100, 0., 100., 100, 0., 0.25);
  TH2F *h_Anglemvis = new TH2F("h_Anglemvis", "Angle_vs_mvis_Ztautau: 40 < P < 80",100, 0., 2., 100, 0., 0.25);
  TH2F *h_AnglenumNeutral = new TH2F("h_AnglenumNeutral", "Angle_vs_numNeutral_Ztautau: 40 < P < 80",4, -0.5, 3.5, 100, 0., 0.25);
  TH2F *h_AnglenumNeutralPion = new TH2F("h_AnglenumNeutralPion", "Angle_vs_numNeutralPion_Ztautau: 40 < P < 80",4, -0.5, 3.5, 100, 0., 0.25);
  //mytree->Draw("Angle_Vis_neutrino:Momentum/1000 >> h_AngleMom","cuts","colz");
  TCanvas* c1=new TCanvas("c1","c1",400,400);
  mytree->Draw("Angle_Vis_neutrino: Momentum/1000 >> h_AngleMom", cut1 && cut2 && cut3);
  mytree->Draw("Angle_tau_truevis: Momentum/1000 >> h_AngleMomtau", cut0 && cut2 && cut3);
  mytree->Draw("Angle_Vis_neutrino: m_vis/1000 >> h_Anglemvis", cut1 && cut2 && cut3);
  mytree->Draw("Angle_Vis_neutrino: numNeutral >> h_AnglenumNeutral", cut1 && cut2 && cut3);
  mytree->Draw("Angle_Vis_neutrino: numNeutralPion >> h_AnglenumNeutralPion", cut1 && cut2 && cut3);
  TH2F *AngleMom = (TH2F*)gDirectory->Get("h_AngleMom");
  TH2F *AngleMomtau = (TH2F*)gDirectory->Get("h_AngleMomtau");
  TH2F *Anglemvis = (TH2F*)gDirectory->Get("h_Anglemvis");
  TH2F *AnglenumNeutral = (TH2F*)gDirectory->Get("h_AnglenumNeutral");
  TH2F *AnglenumNeutralPion = (TH2F*)gDirectory->Get("h_AnglenumNeutralPion");
  // AngleMom->Draw("colz");
  // AngleMomtau->Draw("colz");
  // Anglemvis->Draw("colz");
  //AnglenumNeutral->Draw("colz");
  AnglenumNeutralPion->Draw("colz");
  TH1D *AngprojY = AngleMom->ProjectionY();
  TH1D *AngtauprojY = AngleMomtau->ProjectionY();
  AngprojY->SetTitle("Angle_Ztautau: 60 < P < 80 ");
  AngtauprojY->SetTitle("Angle_Ztautau: 60 < P < 80 ");
  //AngprojY->Draw();
  //AngtauprojY->Draw();
  c1->Update();
  //c1->SaveAs("Plots_ntruple/Angle_Vis_neutrino_vs_Momentum_Ztautau.pdf");
  //c1->SaveAs("Plots_ntruple/Angle_tau_truevis_vs_Momentum_Ztautau.pdf");
  //c1->SaveAs("Plots_ntruple/Angle_Vis_neutrino_vs_mvis_Ztautau.pdf");
  //c1->SaveAs("Plots_ntruple/Angle_Vis_neutrino_vs_numNeutral_Ztautau.pdf");
  c1->SaveAs("Plots_ntruple/Angle_Vis_neutrino_vs_numNeutralPion_Ztautau.pdf");
  delete c1;
  c1=0;

   delete AngleMom;
   AngleMom=0;

   // delete AngprojY;
   //AngprojY=0;

   f->Close();


}
  
  
