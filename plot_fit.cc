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

double myDelThetaHadFunc(double *x, double *par)
{
  double fitval=1.0E-10;
  if(x[0]>TMath::Pi() || x[0]<0.0) return fitval;
  const double arg=x[0];
  const double arg_L=arg;
  const double mean=par[1];
  const double sigmaG=par[2];
  const double mpv=par[3];
  const double sigmaL=par[4];
  const double norm=sqrt(2.0*TMath::Pi());
  const double g1=TMath::Gaus(arg,mean,sigmaG)/norm;
  const double g2=TMath::Landau(arg_L,mpv,sigmaL)/norm;
  fitval=par[0]*g1/sigmaG+par[5]*g2/sigmaL;//+par[6];

  if(fitval<0.0) return 0.0;
  return fitval;
}

//double dTheta3Dparam(const int & parInd, const int & tau_type, const double & P_tau, const double *par) {
double dTheta3Dparam(double *p, double *par) {
 //tau_type 0: l, 1:1-prong, 3:3-prong
  const double P_tau=p[0];
  if(P_tau<0.0) return 0.0;
  /*
  if(parInd==0) {
    if (m_MMCCalibrationSet==MMCCalibrationSet::MMC2011){
      return (par[0]+par[1]*P_tau)*0.00125;
    }
    else if (m_MMCCalibrationSet==MMCCalibrationSet::MMC2012
             || m_MMCCalibrationSet==MMCCalibrationSet::MMC2015
             || m_MMCCalibrationSet==MMCCalibrationSet::MMC2015HIGHMASS
             || m_MMCCalibrationSet==MMCCalibrationSet::MMC2016MC15C
             || m_MMCCalibrationSet==MMCCalibrationSet::UPGRADE
             || m_MMCCalibrationSet==MMCCalibrationSet::LFVMMC2012){
      return (par[0]+par[1]*P_tau+par[2]*pow(P_tau,2)+par[3]*pow(P_tau,3)+par[4]*pow(P_tau,4))*0.00125;
    }
  }
  else { // parInd==0
    if (m_MMCCalibrationSet==MMCCalibrationSet::MMC2011){
      return par[0]*(exp(-par[1]*P_tau)+par[2]/P_tau)+par[3];
    }
    else if (m_MMCCalibrationSet==MMCCalibrationSet::MMC2012
             || m_MMCCalibrationSet==MMCCalibrationSet::MMC2015
             || m_MMCCalibrationSet==MMCCalibrationSet::MMC2015HIGHMASS
             || m_MMCCalibrationSet==MMCCalibrationSet::MMC2016MC15C
             || m_MMCCalibrationSet==MMCCalibrationSet::UPGRADE
             || m_MMCCalibrationSet==MMCCalibrationSet::LFVMMC2012){
	     // if(tau_type==0) return par[0]*(exp(-par[1]*P_tau)+par[2]/P_tau)+par[3]+par[4]*P_tau;
	     */
  else return par[0]*(exp(-par[1]*sqrt(P_tau))+par[2]/P_tau)+par[3]+par[4]*P_tau;
  
  // }
  //return 0.;
}

double dTheta3Dparam0(double *p, double *par) {
 //tau_type 0: l, 1:1-prong, 3:3-prong
  const double P_tau=p[0];
  if(P_tau<0.0) return 0.0;
  else return (par[0]+par[1]*P_tau+par[2]*pow(P_tau,2)+par[3]*pow(P_tau,3)+par[4]*pow(P_tau,4))*0.00125;
  }

int main(){


  TFile *f1 = TFile::Open("AllRoot/all.root");
  TTree *mytree1 = (TTree*)f1->Get("tree");

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
     "tau_Momentum/1000  > 800. &&  tau_Momentum/1000   < 2000."
    };
  TString cut1 = "IsHadronicTau == 1";
  TString cut2 = "Angle_Vis_neutrino < .25";
  TString cut3 = "numCharged == 1";
  TString cut4 = "numNeutral == 0";
  TString cut5 = "numNeutral > 0";
  TString cut6 = "numCharged == 3";

  TH1F *h_1 = new TH1F("h_1", "h_1" ,100, 0., 0.25);
  TH1F *h_2 = new TH1F("h_2", "h_2" ,100, 0., 0.25);
  TH1F *h_3 = new TH1F("h_3", "h_3" ,100, 0., 0.25);

  int fit_status[3][10];
  double fit_param[3][6][10];
  double fit_error[3][6][10];
  
  for (int icut = 0; icut < 3 ; ++icut) {
    for (int ipbin = 0; ipbin < 10; ++ipbin) {
      fit_status[icut][ipbin] = -1;
      //
      for (int i3 = 0; i3 < 6; ++i3) {
	fit_param[icut][i3][ipbin] = 0;
	fit_error[icut][i3][ipbin] = 0;
      }
      //
      if(icut == 0){
	if(ipbin == 2){
	  fit_param[icut][0][ipbin] = 2 ;
	  fit_param[icut][1][ipbin] = 0.1;
	  fit_param[icut][2][ipbin] = 0.1;
	  fit_param[icut][3][ipbin] = 0.01;
	  fit_param[icut][4][ipbin] = 0.01;
	  fit_param[icut][5][ipbin] = 10;
	}else if(ipbin == 8){
	  fit_param[icut][0][ipbin] = 1 ;
	  fit_param[icut][1][ipbin] = 0.1;
	  fit_param[icut][2][ipbin] = 0.1;
	  fit_param[icut][3][ipbin] = 0.01;
	  fit_param[icut][4][ipbin] = 0.01;
	  fit_param[icut][5][ipbin] = 10;
	}else{
	  fit_param[icut][0][ipbin] = 1 ;
	  fit_param[icut][1][ipbin] = 0.2;
	  fit_param[icut][2][ipbin] = 0.2;
	  fit_param[icut][3][ipbin] = 0.02;
	  fit_param[icut][4][ipbin] = 0.02;
	  fit_param[icut][5][ipbin] = 10;
	}
      }
      if(icut == 1){
      fit_param[icut][0][ipbin] = 3 ;
      fit_param[icut][1][ipbin] = 0.2;
      fit_param[icut][2][ipbin] = 0.2;
      fit_param[icut][3][ipbin] = 0.02;
      fit_param[icut][4][ipbin] = 0.02;
      fit_param[icut][5][ipbin] = 15;
      }
      if(icut == 2){
      fit_param[icut][0][ipbin] = 3 ;
      fit_param[icut][1][ipbin] = 0.2;
      fit_param[icut][2][ipbin] = 0.2;
      fit_param[icut][3][ipbin] = 0.02;
      fit_param[icut][4][ipbin] = 0.02;
      fit_param[icut][5][ipbin] = 15;
      }
    }
  }
  for (int icut = 0 ; icut < 3 ; ++icut) {
    for ( int ipbin = 0 ; ipbin < 10 ; ++ipbin){
      
      if(icut == 0) mytree1->Project("h_1","Angle_Vis_neutrino", Form( "%s && %s && %s && %s && %s",cut1.Data(), cut2.Data(), cut3.Data(), cut4.Data(), cuts[ipbin].Data()));
      if(icut == 1) mytree1->Project("h_2","Angle_Vis_neutrino", Form( "%s && %s && %s && %s && %s",cut1.Data(), cut2.Data(), cut3.Data(), cut5.Data(), cuts[ipbin].Data()));
      if(icut == 2) mytree1->Project("h_3","Angle_Vis_neutrino", Form( "%s && %s && %s && %s"      ,cut1.Data(), cut2.Data(), cut6.Data(),              cuts[ipbin].Data()));
      /*
	h_1->Scale(1/h_1->Integral());
	h_2->Scale(1/h_2->Integral());
	h_3->Scale(1/h_3->Integral());
	
	h_1->SetLineColor(kMagenta);
	h_2->SetLineColor(kBlue);
	h_3->SetLineColor(kGreen);
    */
      gStyle->SetOptStat("e");
      gStyle->SetOptFit(01);
      
      TF1 *func = new TF1("fit",myDelThetaHadFunc,0,0.2,6);
      
    // for (int icut = 0 ; icut < 3 ; ++icut) {
      func->SetParameters(  fit_param[icut][0][ipbin],
			    fit_param[icut][1][ipbin],
			    fit_param[icut][2][ipbin],
			    fit_param[icut][3][ipbin],
			    fit_param[icut][4][ipbin],
			    fit_param[icut][5][ipbin]);
      func->SetParLimits(0,0,10000); // norm > 0
      func->SetParLimits(5,0,10000); // norm > 0
      
      func->SetParLimits(1,0,0.25);    // gaussian mean
      func->SetParLimits(2,0,0.25);    // gaussian width
      func->SetParLimits(3,0,0.25);    // 1andau mean
      func->SetParLimits(4,0,0.25);    // landau mean
      
      if(icut == 0){
	fit_status[icut][ipbin] = h_1->Fit("fit","LLMR","",0.0,0.25);
	//func->SetLineColor(kCyan);
      }
      if(icut == 1){
	fit_status[icut][ipbin] = h_2->Fit("fit","LLMR","",0.0,0.25);
	//	func->SetLineColor(kBlack);
      }
      if(icut == 2){
	//cout << "icut :" << icut << endl; 
	fit_status[icut][ipbin] = h_3->Fit("fit","LLMR","",0.0,0.25);
	//	func->SetLineColor(kPink);
	

	//cout << "fun->GetLinecolor : " << func->GetLineColor() << endl;
      }
      //}
 
    
      for (int i=0;i<6; ++i ) {
      fit_param[icut][i][ipbin] = func->GetParameter(i);
      fit_error[icut][i][ipbin] = func->GetParError(i);
      }
    
      if(icut == 0){
	TCanvas* c1=new TCanvas("c1","c1",400,400);
	h_1->SetTitle(Form("Angle(n_cha = 1 & n_neu = 0): %d < P(Gev) < %d", pmin[ipbin] , pmax[ipbin]));
	h_1->Draw();
	c1->Modified();
	c1->Update();
	c1->SaveAs(Form("/afs/cern.ch/user/a/atpathak/afswork/public/Pixel/LFV_Plots/Plots_NewFit/Angle_Vis_neutrino_decay1_Fit_%d.pdf",ipbin+1));
	delete c1;
	c1=0;
      }
      if(icut == 1){
	TCanvas* c2=new TCanvas("c2","c2",400,400);
	h_2->SetTitle(Form("Angle(n_cha = 1 & n_neu > 0): %d < P(Gev) < %d", pmin[ipbin] , pmax[ipbin]));
	h_2->Draw();
	c2->Modified();
	c2->Update();
	c2->SaveAs(Form("/afs/cern.ch/user/a/atpathak/afswork/public/Pixel/LFV_Plots/Plots_NewFit/Angle_Vis_neutrino_decay2_Fit_%d.pdf",ipbin+1));
	delete c2;
	c2=0;
      }
      if(icut == 2){
	TCanvas* c3=new TCanvas("c3","c3",400,400);
	h_3->SetTitle(Form("Angle(n_cha = 3): %d < P(Gev) < %d", pmin[ipbin] , pmax[ipbin]));
	h_3->Draw();
	c3->Modified();
	c3->Update();
	c3->SaveAs(Form("/afs/cern.ch/user/a/atpathak/afswork/public/Pixel/LFV_Plots/Plots_NewFit/Angle_Vis_neutrino_decay3_Fit_%d.pdf",ipbin+1));
	delete c3;
	c3=0;
      }
      /*
	h_1->Draw();
	h_2->Draw("same");
	h_3->Draw("same");
      */
      /*
	TLegend* leg_hist = new TLegend(0.69,0.3,.99,0.5);
	leg_hist->AddEntry(h_1,"(n_cha = 1 & n_neu = 0)","l");
	leg_hist->AddEntry(h_2,"(n_cha = 1 & n_neu > 0)","l");
	leg_hist->AddEntry(h_3,"(n_cha = 3)","l");
	leg_hist->Draw();
      */
      /*
	gPad->Modified();
	c1->Modified();
	c1->Update();
	c1->SaveAs(Form("Plots_Fit/Angle_Vis_neutrino_Fit_%d.pdf",ipbin+1));
      */
      /*
      if(icut == 0){
	delete c1;
	c1=0;
      }
      if(icut == 1){
	delete c2;
	c2=0;
      }
      if(icut == 2){
	delete c3;
	c3=0;
      }
      */
    }
  }
  for (int icut = 0 ; icut < 3 ; ++icut) {
    for (int ipbin = 0; ipbin < 10; ++ipbin) {
      cout << "icut = " << icut << "ipbin = " << ipbin << " " << pmin[ipbin] << " < p < " << pmax[ipbin]  << " fit_status = " << fit_status[icut][ipbin] << " fit_param = " ;
      for (int i = 0; i < 6; ++i) {
	cout << fit_param[icut][i][ipbin] << " " ;
      }
      cout << endl;
    }
  }

  int fitp_status[3][10];
  double fitp_param[3][6][10];
  double fitp_error[3][6][10];

  for (int icut = 0 ; icut < 3 ; ++icut) {
    for (int i = 0; i<6; ++i) {
      fitp_status[icut][i] = -1;

      for (int ip = 0; ip < 5; ++ip) {
	fitp_param[icut][ip][i] = 0;
	fitp_error[icut][ip][i] = 0;
      }
      if(icut == 0){
	fitp_param[icut][0][i] = 1;    //50. ;
	fitp_param[icut][1][i] = 1;    //10;
	fitp_param[icut][2][i] = 1;    //0.04;
	fitp_param[icut][3][i] = 1;    //0.001;
	fitp_param[icut][4][i] = 1;    //0.0001;
      }
      if(icut == 1){
	fitp_param[icut][0][i] = 1 ;
	fitp_param[icut][1][i] = 1;
	fitp_param[icut][2][i] = 1;
	fitp_param[icut][3][i] = 0;
	fitp_param[icut][4][i] = 0;
      }
      if(icut == 2){
	fitp_param[icut][0][i] = 1 ;
	fitp_param[icut][1][i] = 1;
	fitp_param[icut][2][i] = 1;
	fitp_param[icut][3][i] = 1;
	fitp_param[icut][4][i] = 1;
      }
    }
  }
      
  
  for (int i = 0; i<6; ++i) {
    for (int icut = 0 ; icut < 3 ; ++icut) {

      double plotmax = 10.;
      if (i==0) plotmax = 50.;
      if (i==1) plotmax = 0.05;
      if (i==2) plotmax = 0.06;
      if (i==3) plotmax = 0.03;
      if (i==4) plotmax = 0.008;
      if (i==5) plotmax = 35;
      
      TH1D* hpfit = new TH1D(Form("Fit_p%d",i),Form("Fit_p%d",icut,i),2110,25.,2135.);
      for (int ipbin = 0; ipbin < 10; ++ipbin) {
	Double_t p = pmin[ipbin] + (pmax[ipbin]-pmin[ipbin])/2;
	int ibin = hpfit->FindBin(p);
	hpfit->SetBinContent(ibin,fit_param[icut][i][ipbin]);
	hpfit->SetBinError  (ibin,fit_error[icut][i][ipbin]);
	cout << hpfit->GetName() << " ipbin = " << ipbin << " p = " << p << " ibin = " << ibin << " cont = " <<  fit_param[icut][i][ipbin] << " err = " << fit_error[icut][i][ipbin] << endl;
      }
      TF1 *func_1 ;
      if(i==0) func_1 = new TF1("fit_1",dTheta3Dparam0,0,600,5);
      else TF1 *func_1 = new TF1("fit_1",dTheta3Dparam,0,1500,5);
       
      func_1->SetParameters(fitp_param[icut][0][i],
			     fitp_param[icut][1][i],
			     fitp_param[icut][2][i],
			     fitp_param[icut][3][i],
			     fitp_param[icut][4][i]);
      
      if(icut == 0){
	TCanvas* c4=new TCanvas("c4","c4",400,400);
	hpfit->SetTitle(Form("Angle(n_cha = 1 & n_neu = 0): Fit_p%d",i));
	hpfit->SetMaximum(plotmax);
	fitp_status[icut][i] = hpfit->Fit("fit_1","","",0.0,1500.0);
	//hpfit->Fit("expo");
	hpfit->Draw();
	gPad->Update(); 
	c4->Update();
	c4->SaveAs(Form("/afs/cern.ch/user/a/atpathak/afswork/public/Pixel/LFV_Plots/Plots_NewFit/decay%d_FitP%d.pdf",icut,i));
	delete c4;
	c4=0;
	delete hpfit;
	hpfit=0;
      }
      if(icut == 1){
	TCanvas* c5=new TCanvas("c5","c5",400,400);
	hpfit->SetTitle(Form("Angle(n_cha = 1 & n_neu > 0): Fit_p%d",i));
	hpfit->SetMaximum(plotmax);
	fitp_status[icut][i] = hpfit->Fit("fit_1","","",0.0,1500.0);
	//hpfit->Fit("expo");
	hpfit->Draw();
	gPad->Update(); 
	c5->Update();
	c5->SaveAs(Form("/afs/cern.ch/user/a/atpathak/afswork/public/Pixel/LFV_Plots/Plots_NewFit/decay%d_FitP%d.pdf",icut,i));
	delete c5;
	c5=0;
	delete hpfit;
	hpfit=0;
      }
      if(icut == 2){
	TCanvas* c6=new TCanvas("c6","c6",400,400);
	hpfit->SetTitle(Form("Angle(n_cha = 3): Fit_p%d",i));
	hpfit->SetMaximum(plotmax);
	fitp_status[icut][i] = hpfit->Fit("fit_1","","",0.0,1500.0);
	//hpfit->Fit("expo");
	hpfit->Draw();
	gPad->Update(); 
	c6->Update();
	c6->SaveAs(Form("/afs/cern.ch/user/a/atpathak/afswork/public/Pixel/LFV_Plots/Plots_NewFit/decay%d_FitP%d.pdf",icut,i));
	delete c6;
	c6=0;
	delete hpfit;
	hpfit=0;
      }
    }
  }
   return 0;
}
      
