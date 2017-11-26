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
void SetUp(){
  cout << "SetUp Plain " << endl;
  gROOT->SetStyle("Plain");
  //  gROOT->SetBatch(kTRUE);
  gROOT->ForceStyle();
  gStyle->SetStatW(0.2);
  gStyle->SetStatH(0.2);
  gStyle->SetStatX(0.95);
  gStyle->SetStatY(0.95);
  gStyle->SetStatStyle(0);
  gStyle->SetStatFontSize(0.1);
  gStyle->SetStatTextColor(4);
  gStyle->SetOptTitle(0);
  //  gStyle->SetStatFontSize(0.08);
  //  gStyle->SetTitleH(0.1);
  //  gStyle->SetTitleW(0.60);
  //  gStyle->SetTitleX(0.25);
  //  gStyle->SetTitleY(0.90);
  //  gStyle->SetTitleStyle(1);
  //  gStyle->SetTitleFontSize(0.1);
  //  gStyle->SetLabelFont(64,"X");
  //  gStyle->SetLabelSize(20,"X");
  //  gStyle->SetTitleOffset(1,"X");
  //  gStyle->SetTitleFont(64,"X");
  //  gStyle->SetTitleSize(30,"X");
  //  gStyle->SetLabelFont(64,"Y");
  //  gStyle->SetLabelSize(20,"Y");
  gStyle->SetTitleOffset(1,"Y");
  //  gStyle->SetTitleFont(64,"Y");
  //  gStyle->SetTitleSize(30,"Y");
  //  gStyle->SetLabelFont(64,"Z");
  //  gStyle->SetLabelSize(20,"Z");
  gStyle->SetNdivisions(504,"X");
  gStyle->SetNdivisions(505,"Y");
  gStyle->SetOptFit();
  gStyle->SetOptStat(1110);
  gStyle->SetPadTopMargin(0.05);
  //  gStyle->SetPadBottomMargin(0.1);
  gStyle->SetPadLeftMargin(0.2);
  gStyle->SetPadRightMargin(0.05);
  //
  if (!gROOT->GetClass("TMultiLayerPerceptron")) {
    gSystem->Load("libMLP");
    gSystem->Load("libTreePlayer");
  }
  return;
}

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

/* returns parameters for dTheta3D pdf
double dTheta3Dparam(const int & parInd, const int & tau_type, const double & P_tau, const double *par) {
  //tau_type 0: l, 1:1-prong, 3:3-prong
  if(P_tau<0.0) return 0.0;


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
      if(tau_type==0) return par[0]*(exp(-par[1]*P_tau)+par[2]/P_tau)+par[3]+par[4]*P_tau;
      else return par[0]*(exp(-par[1]*sqrt(P_tau))+par[2]/P_tau)+par[3]+par[4]*P_tau;
    }
  }
  return 0.;
  }*/

int main(int argc, char *argv[]) {
  
  //SetUp();

  int pbin = argc>1 ? atoi(argv[1]) : -1; // pbin : 0 to 8

  int decay = argc>2 ? atoi(argv[2]) : 1; // 0 : lepton, 1 : 1 prong, 2 : 3 prong

  int calib = argc>3 ? atoi(argv[3]) : 1; //  0: MMC2011, 1:MMC2012
  

  TString Prong[3] = {"","1Prong","3Prong"};
  
  int pmin[14] = {20, 40, 50, 55, 59, 64, 70, 80, 90,  100,  200, 400, 800,  1200 };
  int pmax[14] = {40, 50, 55, 59, 64, 70, 80, 90, 100, 200,  400, 800, 1200, 2000 };


  int fit_status[2][3][14];
  double fit_param[2][3][6][14];
  double fit_error[2][3][6][14];
  
  for (int i1 = 0 ; i1 <2; ++i1) {
    for (int i2 = 0; i2 < 3 ; ++i2) {
      for (int i4 = 0; i4 < 14; ++i4) {
	fit_status[i1][i2][i4] = -1;
	//
	for (int i3 = 0; i3 < 6; ++i3) {
	  fit_param[i1][i2][i3][i4] = 0;
	  fit_error[i1][i2][i3][i4] = 0;
	}
	//
	fit_param[calib][decay][0][i4] = 1 ;
	fit_param[calib][decay][1][i4] = 0.1;
	fit_param[calib][decay][2][i4] = 0.1;
	fit_param[calib][decay][3][i4] = 0.01;
	fit_param[calib][decay][4][i4] = 0.01;
	fit_param[calib][decay][5][i4] = 10;
      }
    }
  }
  for (int ipbin = 0 ; ipbin < 14; ++ipbin) {

    if ( (pbin > -1 && ipbin == pbin)  || (pbin == -1) ) {
      
      TFile *f = TFile::Open("submitDir/hist-mc15_13TeV.344084.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_ggH125_taumu.merge.DAOD_HIGG4D2.e5003_s2726_r7772_r7676_p2949.root");
      
      TH1D *h3d = (TH1D*)f->Get(Form("h_Angle_Vis_neutrino_%s_%d",Prong[decay].Data(),i))->Clone();
      
      h3d->SetTitle(Form("%sP%d: %d < P (GeV) < %d",Prong[decay].Data(),ipbin+1, pmin[ipbin],pmax[ipbin]));
      
      gStyle->SetOptStat("e");
      gStyle->SetOptFit(01);
      
      TF1 *func = new TF1("fit",myDelThetaHadFunc,0,0.2,6);
      
      func->SetParameters(fit_param[calib][decay][0][ipbin],
			  fit_param[calib][decay][1][ipbin],
			  fit_param[calib][decay][2][ipbin],
			  fit_param[calib][decay][3][ipbin],
			  fit_param[calib][decay][4][ipbin],
			  fit_param[calib][decay][5][ipbin]);
      func->SetParLimits(0,0,10000); // norm > 0
      func->SetParLimits(5,0,10000); // norm > 0
      
      func->SetParLimits(1,0,0.25); // gaussian mean
      func->SetParLimits(2,0,0.25); // gaussian width
      func->SetParLimits(3,0,0.25);   // 1andau mean
      func->SetParLimits(4,0,0.25);   // landau mean
      
      if (decay == 1 && ipbin==0) { // One Prong , 20 < P < 35
	//	fuct
      }
      
      fit_status[calib][decay][ipbin] = h3d->Fit("fit","LLMR","",0.0,0.2);
      
      for (int i=0;i<6; ++i ) {
	fit_param[calib][decay][i][ipbin] = func->GetParameter(i);
	fit_error[calib][decay][i][ipbin] = func->GetParError(i);
      }
      
      TCanvas* c1=new TCanvas("c1","c1",400,400);
      //c1->SetLogx();
      //c1->SetLogy();
      h3d->Draw();
      gPad->Update();
      
      TPaveStats *sb2 = (TPaveStats*)h3d->FindObject("stats");
      sb2->SetX1NDC(0.5);
      sb2->SetX2NDC(0.9);
      sb2->SetY1NDC(0.3);
      sb2->SetY2NDC(0.9);
      sb2->SetTextColor(2);
      gPad->Modified();
      c1->Modified();
      
      c1->Update();
      c1->SaveAs(Form("Plots_Fit/New_range/Cut%sP%d_Angle_Vis_InVis_New.pdf",Prong[decay].Data(),ipbin+1));
      
      delete c1;
      c1=0;

      delete func;
      func = 0;
      
      delete h3d;
      h3d=0;
      
      f->Close();
    }
  }

  for (int ipbin = 0; ipbin < 14; ++ipbin) {
    if ( (pbin > -1 && ipbin == pbin)  || (pbin == -1) ) {
      
      cout << "ipbin = " << ipbin << " " << pmin[ipbin] << " < p < " << pmax[ipbin]  << " fit_status = " << fit_status[calib][decay][ipbin] << " fit_param = " ;
      for (int i = 0; i < 6; ++i) {
	cout << fit_param[calib][decay][i][ipbin] << " " ;
      }
      cout << endl;
    }
  }

  if (pbin == -1) {
    for (int i = 0; i<6; ++i) {
      double plotmax = 10.;
      if (i==0) plotmax = 5.;
      if (i==1) plotmax = 0.05;
      if (i==2) plotmax = 0.06;
      if (i==3) plotmax = 0.03;
      if (i==4) plotmax = 0.008;
      if (i==5) plotmax = 35;
      
      TH1D* hpfit = new TH1D(Form("Fit_p%d",i),Form("Fit_p%d",i),2110,25.,2135);
      for (int ipbin = 0; ipbin < 14; ++ipbin) {
	double p = pmin[ipbin] + (pmax[ipbin]-pmin[ipbin])/2;
	int ibin = hpfit->FindBin(p);
	hpfit->SetBinContent(ibin,fit_param[calib][decay][i][ipbin]);
	hpfit->SetBinError  (ibin,fit_error[calib][decay][i][ipbin]);
	cout << hpfit->GetName() << " ipbin = " << ipbin << " p = " << p << " ibin = " << ibin << " cont = " <<  fit_param[calib][decay][i][ipbin] << " err = " << fit_error[calib][decay][i][ipbin] << endl;
      }
      
      
      TCanvas* c2=new TCanvas("c2","c2",400,400);
      hpfit->Draw("L");
      gPad->Update(); 
      c2->Update();
      c2->SaveAs(Form("Plots_Fit/New_range/Cut%s_FitP%d.pdf",Prong[decay].Data(),i));
      
      delete c2;
      c2=0;
      
      delete hpfit;
      hpfit=0;
    }
    
  }

  return 0;
}
