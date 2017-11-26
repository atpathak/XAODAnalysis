// Infrastructure include(s):
#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"
// ASG status code check
#include <AsgTools/MessageCheck.h>
#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <MyAnalysis/MyxAODAnalysis.h>
// EDM includes:
#include "xAODEventInfo/EventInfo.h"
#include "xAODJet/JetContainer.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODTau/TauJetContainer.h"
#include "xAODTau/TauDefs.h" 
#include "xAODTau/TauJet.h"
#include "xAODTruth/TruthEventContainer.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include <string>
#include <TFile.h>

//#include "xAODTruth/TruthTaus.h"

// this is needed to distribute the algorithm to the workers
ClassImp(MyxAODAnalysis)



MyxAODAnalysis :: MyxAODAnalysis ()
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().
}



EL::StatusCode MyxAODAnalysis :: setupJob (EL::Job& job)
{
  // Here you put code that sets up the job on the submission object
  // so that it is ready to work with your algorithm, e.g. you can
  // request the D3PDReader service or add output files.  Any code you
  // put here could instead also go into the submission script.  The
  // sole advantage of putting it here is that it gets automatically
  // activated/deactivated when you add/remove the algorithm from your
  // job, which may or may not be of value to you.

 // let's initialize the algorithm to use the xAODRootAccess package
  job.useXAOD ();
  ANA_CHECK_SET_TYPE (EL::StatusCode); // set type of return code you are expecting (add to top of each function once)
  ANA_CHECK(xAOD::Init());


  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: histInitialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.

  h_jetPt = new TH1F("h_jetPt", "h_jetPt", 100, 0, 500); // jet pt [GeV]
  wk()->addOutput (h_jetPt);

  h_tauPt = new TH1F("h_tauPt", "h_tauPt", 100, 0, 500); // tau pt [GeV]
  wk()->addOutput (h_tauPt);
  
  h_tauEta = new TH1F("h_tauEta", "h_tauEta", 100, -2.5, 2.5); // tau Eta 
  wk()->addOutput (h_tauEta);

  h_numCharged = new TH1F("h_numCharged", "h_numCharged", 4, -0.5, 3.5); // No of prong 
  wk()->addOutput (h_numCharged);
  
  h_numChargedPion = new TH1F("h_numChargedPion", "h_numChargedPion", 4, -0.5, 3.5); // No of prong 
  wk()->addOutput (h_numChargedPion);

  h_numCharged_vs_numChargedPion = new TH2F("h_numCharged_vs_numChargedPion", "h_numCharged_vs_numChargedPion", 4, -0.5, 3.5, 4, -0.5, 3.5); // No of prong 
  wk()->addOutput (h_numCharged_vs_numChargedPion);

  
  h_taup_vs_numCharged     = new TH2F("h_taup_vs_numCharged",     "h_taup_vs_numCharged",     100, 0, 1000, 4, -0.5, 3.5); // No of prong 
  wk()->addOutput (h_taup_vs_numCharged);
  
  h_taup_vs_numChargedPion = new TH2F("h_taup_vs_numChargedPion", "h_mvis_vs_numChargedPion", 100, 0, 1000, 4, -0.5, 3.5); // No of prong 
  wk()->addOutput (h_taup_vs_numChargedPion);
  
  h_mvis_vs_numCharged     = new TH2F("h_mvis_vs_numCharged",     "h_mvis_vs_numCharged",     100, 0, 2, 4, -0.5, 3.5); // No of prong 
  wk()->addOutput (h_mvis_vs_numCharged);
  
  h_mvis_vs_numChargedPion = new TH2F("h_mvis_vs_numChargedPion", "h_mvis_vs_numChargedPion", 100, 0, 2, 4, -0.5, 3.5); // No of prong 
  wk()->addOutput (h_mvis_vs_numChargedPion);
  
  //  h_Ang_vs_Momen_n1Charged = new TH2F("h_Ang_vs_Momen_n1Charged", "h_Ang_vs_Momen_n1Charged", 250, 0., 0.25, 100, 0., 500.);
  //  wk()->addOutput (h_Ang_vs_Momen_n1Charged);
  
  /*
  h_Angle_Vis_neutrino_vs_Momentum_numCharged3 = new TH2F ("h_Angle_Vis_neutrino_vs_Momentum_numCharged3", "h_Angle_Vis_neutrino_vs_Momentum_numCharged3", 250, 0., 0.25, 250, 0., 500.); 
  wk()->addOutput (h_Angle_Vis_neutrino_vs_Momentum_numCharged3);

  h_Angle_Vis_neutrino_vs_Momentum_numChargedPion1 = new TH2F ("h_Angle_Vis_neutrino_vs_Momentum_numChargedPion1", "h_Angle_Vis_neutrino_vs_Momentum_numChargedPion1", 250, 0., 0.25, 250, 0., 500.); 
  wk()->addOutput (h_Angle_Vis_neutrino_vs_Momentum_numChargedPion1);

  h_Angle_Vis_neutrino_vs_Momentum_numChargedPion3 = new TH2F ("h_Angle_Vis_neutrino_vs_Momentum_numChargedPion3", "h_Angle_Vis_neutrino_vs_Momentum_numChargedPion3", 250, 0., 0.25, 250, 0., 500.); 
  wk()->addOutput (h_Angle_Vis_neutrino_vs_Momentum_numChargedPion3);
  */
  
  h_Angle_Vis_neutrino_numCharged1.reserve(14);
  for (int ipbin = 0 ; ipbin < 14 ; ++ipbin){
    //
    h_Angle_Vis_neutrino_numCharged1[ipbin] = new TH1F(Form("h_Angle_Vis_neutrino_numCharged1_%d",ipbin),
						       Form("h_Angle_Vis_neutrino_numCharged1_%d",ipbin),  500, 0, 0.25); // Angle between Visible with InVisible 
    wk()->addOutput (h_Angle_Vis_neutrino_numCharged1[ipbin]);
  }
  //
  h_Angle_Vis_neutrino_numChargedPion1.reserve(14);
  for (int ipbin = 0 ; ipbin < 14 ; ++ipbin){
    h_Angle_Vis_neutrino_numChargedPion1[ipbin] = new TH1F(Form("h_Angle_Vis_neutrino_numChargedPion1_%d",ipbin),
							   Form("h_Angle_Vis_neutrino_numChargedPion1_%d",ipbin),  500, 0, 0.25); // Angle between Visible with InVisible 
    wk()->addOutput (h_Angle_Vis_neutrino_numChargedPion1[ipbin]);
  }

  h_Angle_Vis_neutrino_numCharged3.reserve(14);
  for (int ipbin = 0 ; ipbin < 14 ; ++ipbin){
    //
    h_Angle_Vis_neutrino_numCharged3[ipbin] = new TH1F(Form("h_Angle_Vis_neutrino_numCharged3_%d",ipbin),
						       Form("h_Angle_Vis_neutrino_numCharged3_%d",ipbin),  500, 0, 0.25); // Angle between Visible with InVisible 
    wk()->addOutput (h_Angle_Vis_neutrino_numCharged3[ipbin]);
  }
  //
  h_Angle_Vis_neutrino_numChargedPion3.reserve(14);
  for (int ipbin = 0 ; ipbin < 14 ; ++ipbin){
    h_Angle_Vis_neutrino_numChargedPion3[ipbin] = new TH1F(Form("h_Angle_Vis_neutrino_numChargedPion3_%d",ipbin),
							   Form("h_Angle_Vis_neutrino_numChargedPion3_%d",ipbin),  500, 0, 0.25); // Angle between Visible with InVisible 
    wk()->addOutput (h_Angle_Vis_neutrino_numChargedPion3[ipbin]);
  }
  
  // get the output file, create a new TTree and connect it to that output
  // define what braches will go in that tree
  TFile *outputFile = wk()->getOutputFile (outputName);
  tree = new TTree ("tree", "tree");
  tree->SetDirectory (outputFile);
  tree->Branch("Angle_Vis_neutrino", &Angle_Vis_neutrino);
  tree->Branch("Angle_tau_truevis", &Angle_tau_truevis);
  tree->Branch("Angle_tau_neu", &Angle_tau_neu);
  tree->Branch("tau_Momentum", &tau_Momentum);
  tree->Branch("tau_pt", &tau_pt);
  tree->Branch("tau_m", &tau_m);
  tree->Branch("tau_eta", &tau_eta);
  tree->Branch("tau_phi", &tau_phi);
  tree->Branch("vis_pt", &vis_pt);
  tree->Branch("vis_m", &vis_m);
  tree->Branch("vis_eta", &vis_eta);
  tree->Branch("vis_phi", &vis_phi);
  tree->Branch("vis_Momentum", &vis_Momentum);
  tree->Branch("neu_pt", &neu_pt);
  tree->Branch("neu_m", &neu_m);
  tree->Branch("neu_eta", &neu_eta);
  tree->Branch("neu_phi", &neu_phi);
  tree->Branch("neu_Momentum", &neu_Momentum);
  tree->Branch("IsHadronicTau", &IsHadronicTau);
  tree->Branch("numCharged", &numCharged);
  tree->Branch("numChargedPion", &numChargedPion);
  tree->Branch("numNeutral", &numNeutral);
  tree->Branch("numNeutralPion", &numNeutralPion);
  tree->Branch("DecayModeVector_0", &DecayModeVector_0);
  tree->Branch("taujet_m", &taujet_m);
  
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: fileExecute ()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: changeInput (bool firstFile)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: initialize ()
{
  ANA_CHECK_SET_TYPE (EL::StatusCode); // set type of return code you are expecting (add to top of each function once)
  // Here you do everything that you need to do after the first input
  // file has been connected and before the first event is processed,
  // e.g. create additional histograms based on which variables are
  // available in the input files.  You can also create all of your
  // histograms and trees in here, but be aware that this method
  // doesn't get called if no events are processed.  So any objects
  // you create here won't be available in the output if you have no
  // input events.

  xAOD::TEvent* m_event = wk()->xaodEvent(); // you should have already added this as described before

  // as a check, let's see the number of events in our xAOD
  Info("initialize()", "Number of events = %lli", m_event->getEntries() ); // print long long int
  // count number of events
  m_eventCounter = 0;
  m_numCleanEvents = 0;

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: execute ()
{
  ANA_CHECK_SET_TYPE (EL::StatusCode); // set type of return code you are expecting (add to top of each function once)
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.
  
  // print every 100 events, so we know where we are:
  xAOD::TEvent* m_event = wk()->xaodEvent();
  if( (m_eventCounter % 100) ==0 ) Info("execute()", "Event number = %i", m_eventCounter );
  m_eventCounter++;
  
  //----------------------------
  // Event information
  //--------------------------- 
  const xAOD::EventInfo* eventInfo = 0;
  ANA_CHECK(m_event->retrieve( eventInfo, "EventInfo"));  
  
  // check if the event is data or MC
  // (many tools are applied either to data or MC)
  bool isMC = false;
  // check if the event is MC
  if(eventInfo->eventType( xAOD::EventInfo::IS_SIMULATION ) ){
    isMC = true; // can do something with this later
  } 
  //--------------------------------------------------------------------------------------------------
  //  //------------------------------------------------------------
  //  // Apply event cleaning to remove events due to 
  //  // problematic regions of the detector 
  //  // or incomplete events.
  //  // Apply to data.
  //  //------------------------------------------------------------
  //  
  //  // reject event if:
  //  if(!isMC){
  //    if(   (eventInfo->errorState(xAOD::EventInfo::LAr)==xAOD::EventInfo::Error ) || (eventInfo->errorState(xAOD::EventInfo::Tile)==xAOD::EventInfo::Error ) || (eventInfo->errorState(xAOD::EventInfo::SCT)==xAOD::EventInfo::Error ) || (eventInfo->isEventFlagBitSet(xAOD::EventInfo::Core, 18) ) ) {
  //      return EL::StatusCode::SUCCESS; // go to the next event
  //    } // end if event flags check
  //  } // end if the event is data
  //  m_numCleanEvents++;
  //
  //  // get jet container of interest
  //  const xAOD::JetContainer* jets = 0;
  //  ANA_CHECK(m_event->retrieve( jets, "AntiKt4EMTopoJets" ));
  //  //Info("execute()", "  number of jets = %lu", jets->size());
  //
  //  // loop over the jets in the container
  //  xAOD::JetContainer::const_iterator jet_itr = jets->begin();
  //  xAOD::JetContainer::const_iterator jet_end = jets->end();
  //  for( ; jet_itr != jet_end; ++jet_itr ) {
  //    //Info("execute()", "  jet pt = %.2f GeV", ((*jet_itr)->pt() * 0.001)); // just to print out something
  //       h_jetPt->Fill( ( (*jet_itr)->pt()) * 0.001); // GeV
  //  } // end for loop over jets
  //  //------------
  //// MUONS
  ////------------
  //  // get muon container of interest
  //  const xAOD::MuonContainer* muons = 0;
  //  ANA_CHECK(m_event->retrieve( muons, "Muons" ));
  //
  //
  //  // loop over the muons in the container
  //  xAOD::MuonContainer::const_iterator muon_itr = muons->begin();
  //  xAOD::MuonContainer::const_iterator muon_end = muons->end();
  //  for( ; muon_itr != muon_end; ++muon_itr ) {
  //    //Info("execute()", "  original muon pt = %.2f GeV", ((*muon_itr)->pt() * 0.001)); // just to print out something
  //  } // end for loop over muons
  // ----------------------------------------------------------------------------------------------------------------------


    //----------------------------------------------
    /*
    const xAOD::TauJet* tau_max = 0;
    for( const xAOD::TauJet *tau : *taus) {
      n_reco_tau++;
	const xAOD::TauJet* this_reco_tau = tau;
	if (this_reco_tau->pt() > reco_pt_max) {
	  reco_pt_max = this_reco_tau->pt();
	  tau_max = this_reco_tau;
	}
      }
    */
    //} 
  //  ANA_CHECK(m_event->retrieve( taus, "TauJets" ));
  //
  //  // loop by iterators over tau container 
  //  xAOD::TauJetContainer::const_iterator itS = taus->begin();
  //  xAOD::TauJetContainer::const_iterator itSE = taus->end();
  //  for (; itS != itSE; ++itS) {
  //    //xAOD::TauJet_v2 *pTau = *itS;
  //    //Info("execute()", "  original tau pt = %.2f GeV", ((*itS)->pt() * 0.001)); // just to print out something
  //    //Info("execute()", "  original tau eta = ", ((*itS)->eta())); // just to print out something
  //     h_tauPt->Fill( ( (*itS)->pt()) * 0.001); // GeV
  //     h_tauEta->Fill( ( (*itS)->eta()) ); // 
  //  } //// end for loop over taus

  /*
*Br    4 :TauJetsAuxDyn.pt : vector<float>                                   *
*Br    6 :TauJetsAuxDyn.eta : vector<float>                                  *
*Br    8 :TauJetsAuxDyn.phi : vector<float>                                  *
*Br   10 :TauJetsAuxDyn.m : vector<float>                                    *
*Br   11 :TauJetsAuxDyn.IsTruthMatched : vector<char>                        *
*Br   24 :TauJetsAuxDyn.isTauFlags : vector<unsigned int>                    *
*Br   27 :TauJetsAuxDyn.mPanTauCellBased : vector<float>                     *
*Br   28 :TauJetsAuxDyn.pantau_CellBasedInput_BDTValue_1p0n_vs_1p1n :        *
*Br   29 :TauJetsAuxDyn.pantau_CellBasedInput_BDTValue_1p1n_vs_1pXn :        *
*Br   30 :TauJetsAuxDyn.pantau_CellBasedInput_BDTValue_3p0n_vs_3pXn :        *
*Br   31 :TauJetsAuxDyn.pantau_CellBasedInput_DecayMode : vector<int>        *
*Br   32 :TauJetsAuxDyn.pantau_CellBasedInput_DecayModeProto : vector<int>   *
*Br   36 :TauJetsAuxDyn.pantau_CellBasedInput_isPanTauCandidate : vector<int>*
  *Br   55 :TauJetsAuxDyn.hadronicPFOLinks.size() :                                   *
  *Br   56 :TauJetsAuxDyn.shotPFOLinks.size() :                                       *
  *Br   57 :TauJetsAuxDyn.chargedPFOLinks.size() :                                    *
  *Br   58 :TauJetsAuxDyn.neutralPFOLinks.size() :                                    *
  *Br   59 :TauJetsAuxDyn.pi0PFOLinks.size() :                                        *
  *Br   60 :TauJetsAuxDyn.protoChargedPFOLinks.size() :                               *
  *Br   61 :TauJetsAuxDyn.protoNeutralPFOLinks.size() :                               *
  *Br   62 :TauJetsAuxDyn.protoPi0PFOLinks.size() :                                   *
  *Br   63 :TauJetsAuxDyn.charge
  *    
  */
  //----------------
  // TruthParticle
  //----------------
  
  /*get TruthParticle of interest
    const xAOD::TruthEventContainer* truthevents = 0;
    ANA_CHECK(m_event->retrieve( truthevents, "TruthEvents" ));
    
    // loop by iterators over truth container
    xAOD::TruthEventContainer::const_iterator truth_itS = truthevents->begin();
    xAOD::TruthEventContainer::const_iterator truth_itSE = truthevents->end();
    for (; truth_itS != truth_itSE; ++truth_itS) {
    const std::vector<float> weights = (*truth_itS)->weights();
    //int nVert = (*truth_itS)->nTruthVertices();
    //int nPart = (*truth_itS)->nTruthParticles();
    //Info("excute()", " nPart = ", (*truth_itS)->nTruthParticles());
    //Info("excute()", " nVert = ", nVert);
    //Info("excute()", " weights = ", weights);
    
    //const xAOD::TruthVertex* vertex = (*truth_itS)->truthVertex(iVtx);
    //const xAOD::TruthParticle* particle = (*truth_itS)->truthParticle(iPart);
    } //// end for loop over truth particle  
  */
  /*get TruthTau of interest
    const xAOD::TruthTaus* truthtaus = 0;
    ANA_CHECK(m_event->retrieve( truthtaus, "TruthTaus" ));
    
    // loop by iterators over truth container
    xAOD::TruthEventContainer::const_iterator truthtau_itS = truthtaus->begin();
    xAOD::TruthEventContainer::const_iterator truthtau_itSE = truthtaus->end();
    for (; truthtau_itS != truthtau_itSE; ++truthtau_itS) {
    
    Info("execute()", "  truth tau pt = %.2f GeV", ((*truthtau_itS)->pt_vis() * 0.001)); // just to print out something    
    
    } //// end for loop over truth taus 
  */
  
  /*
    const xAOD::TruthParticleContainer* truthtaus = 0;
    ANA_CHECK(m_event->retrieve( truthtaus, "TruthTaus" ));
    
    // loop by iterators over truth container
    xAOD::TruthParticleContainer::const_iterator truthtau_itS = truthtaus->begin();
    xAOD::TruthParticleContainer::const_iterator truthtau_itSE = truthtaus->end();
    for (; truthtau_itS != truthtau_itSE; ++truthtau_itS) {
    xAOD::TruthParticle *truthtau = *truthtau_itS;
    //    truthtau->Print();
    //double eta_vis = truthtaus->auxdata<double>("eta_vis");
    // Info("execute()", "  truth tau pt_vis = %.2f GeV", eta_vis);
    Info("execute()", "  truth tau px = %.2f GeV", ((*truthtau_itS)->m())); // just to print out something    
    
    } //// end for loop over truth taus
  */ 
  //-----------------------------------------------------------
  //----------------
  // TruthTaus
  //----------------

  int pmin[14] = {20, 40, 50, 55, 59, 64, 70, 80,  90, 100,  200, 400,  800,  1200 };
  int pmax[14] = {40, 50, 55, 59, 64, 70, 80, 90, 100, 200,  400, 800, 1200,  2000 };
  
  const xAOD::TruthParticleContainer* truths = 0;

  
  if (isMC){
    if( !m_event->retrieve( truths, "TruthTaus" ).isSuccess() ){
      Error("execute()", "Failed to retrieve TruthParticle. Exiting." );
      return EL::StatusCode::FAILURE;
    }
    
    int n_truth_tau = 0;
    const xAOD::TruthParticle* truth_tau_0 = 0;
    const xAOD::TruthParticle* truth_tau_1 = 0;
    double pt_max_0 = 0;
    double pt_max_1 = 0;

    for (auto  xTruthParticle=truths->begin(); xTruthParticle !=truths->end()  ; ++xTruthParticle) {
      int iAbsPdgId = (*xTruthParticle)->absPdgId();
      if ( iAbsPdgId == 15 ){
	n_truth_tau++;
	const xAOD::TruthParticle* this_truth_tau = *xTruthParticle;
	if (this_truth_tau->p4().Pt() > pt_max_0) {
	  pt_max_1 = pt_max_0;
	  truth_tau_1 = truth_tau_0;
	  pt_max_0 = this_truth_tau->p4().Pt();
	  truth_tau_0 = this_truth_tau;
	} else if (this_truth_tau->p4().Pt() > pt_max_1 && this_truth_tau->p4().Pt() <= pt_max_0) {
	  pt_max_1 = this_truth_tau->p4().Pt();
	  truth_tau_1 = this_truth_tau;
	}
      }
    }
    
    std::cout << "n_truth_tau: " << n_truth_tau << " pt_max_0 = " << pt_max_0/1000 << " pt_max_1 = " << pt_max_1/1000 << std::endl;

     //----------------
    // TAUS
    //----------------
    // get Taus container of interest
    
    int n_reco_tau = 0;
    
    double min_delta_r_0 = 1e9;
    double min_delta_r_1 = 1e9;
    const xAOD::TauJet* reco_tau_0 = 0;
    const xAOD::TauJet* reco_tau_1 = 0;
    
    const xAOD::TauJetContainer* taus = 0;
    ANA_CHECK(m_event->retrieve( taus, "TauJets" ));
    double reco_pt_max = 0;
    const xAOD::TauJet* reco_tau = 0;
    xAOD::TauJetContainer::const_iterator itS = taus->begin();
    xAOD::TauJetContainer::const_iterator itSE = taus->end();
    std::cout << "taus->size(): " << taus->size() << std::endl;
    
    for (; itS != itSE; ++itS) {
      n_reco_tau++;
      const xAOD::TauJet* this_reco_tau = (*itS);
      std::cout << "reco_pt: " << this_reco_tau->pt()/1000 << " reco_eta = " << this_reco_tau->eta() << " reco_phi = " << this_reco_tau->phi() << std::endl;
      
      if (truth_tau_0) {
	Double_t deta_0 = this_reco_tau->eta()-truth_tau_0->p4().Eta();
	Double_t dphi_0 = TVector2::Phi_mpi_pi(this_reco_tau->phi()-truth_tau_0->p4().Phi());
	double delta_r_0 = TMath::Sqrt( deta_0*deta_0+dphi_0*dphi_0 );
	if (delta_r_0 < min_delta_r_0) {
	  min_delta_r_0 = delta_r_0;
	  reco_tau_0 = this_reco_tau;
	}
      }

      if (truth_tau_1) {
	Double_t deta_1 = this_reco_tau->eta()-truth_tau_1->p4().Eta();
	Double_t dphi_1 = TVector2::Phi_mpi_pi(this_reco_tau->phi()-truth_tau_1->p4().Phi());
	double delta_r_1 = TMath::Sqrt( deta_1*deta_1+dphi_1*dphi_1 );
	if (delta_r_1 < min_delta_r_1) {
	  min_delta_r_1 = delta_r_1;
	  reco_tau_1 = this_reco_tau;
	}
      }

    }

    if (min_delta_r_0 > 0.4) {
      reco_tau_0 = 0;
    } else {
      std::cout << "reco_tau_0 matched with truth_tau_0 " << std::endl;
    }

    if (min_delta_r_1 > 0.4) {
      reco_tau_1 = 0;
    } else {
      std::cout << "reco_tau_1 matched with truth_tau_1 " << std::endl;
    }

    std::cout << "n_reco_tau: " << n_reco_tau << std::endl;



    //    if (n_reco_tau >= 2 && reco_pt_max/1000 > 10 && reco_tau) {
    //      std::cout << "isTau: " << reco_tau->isTau( xAOD::TauJetParameters::IsTauFlag(xAOD::TauJetParameters::JetBDTSigMedium)) << std::endl;
    //    }



    for (int i = 0 ; i < 2; ++i ) {
      
      if (
	  (i == 0 && n_truth_tau > 0 && pt_max_0/1000 > 0 && truth_tau_0) ||
	  (i == 1 && n_truth_tau > 1 && pt_max_1/1000 > 0 && truth_tau_1)
	  ) {
	
	const xAOD::TruthParticle* truth_tau = (i==0) ? truth_tau_0 : truth_tau_1;

	const xAOD::TauJet* reco_tau = (i==0) ? reco_tau_0 : reco_tau_1;
	
	//      std::cout << "isTau: " << truth_tau->isTau() << std::endl;
	
	if (truth_tau->isTau() && reco_tau) {
	  IsHadronicTau = truth_tau->auxdata<char>("IsHadronicTau");
	  //std::cout << "IsHadronicTau: " << IsHadronicTau << std::endl;
	  
	  //if (IsHadronicTau == 1 ) {
	  TLorentzVector p4 = truth_tau->p4();
	  //	    std::cout << "p4 : "; p4.Print();
	  //	    std::cout << "p4.pt : " << p4.Pt() << std::endl;
	  //std::cout << "p4.Mass : " << p4.M() << std::endl;
	  //std::cout << "p4.Momentum : " << p4.P() << std::endl;
	  
	  vis_pt             =  truth_tau->auxdata<double>("pt_vis");
	  vis_m              =  truth_tau->auxdata<double>("m_vis");
	  vis_eta            =  truth_tau->auxdata<double>("eta_vis");
	  vis_phi            =  truth_tau->auxdata<double>("phi_vis");
	  DecayModeVector    =  truth_tau->auxdata<std::vector<int>>("DecayModeVector");
	  DecayModeVector_0  =  DecayModeVector[0] ;
	  //std::cout << "DecayModeVector_0 : " << DecayModeVector_0 << std::endl;
	  
	  /*
	    std::cout << "pt_vis : " << pt_vis << std::endl;
	    std::cout << "Eta_vis : " << Eta_vis << std::endl;
	    std::cout << "phi_vis : " << phi_vis << std::endl;
	    std::cout << "m_vis : " << m_vis << std::endl;
	  */
	  
	  TLorentzVector truevis_p4;
	  truevis_p4.SetPtEtaPhiM(vis_pt,vis_eta,vis_phi,vis_m);
	  //std::cout << "truevis_p4.Mass : " << truevis_p4.M() << std::endl;
	  //std::cout << "truevis_p4.Momentum : " << truevis_p4.P() << std::endl;
	  
	  TLorentzVector neutrino_p4 = p4 - truevis_p4 ;
	  /*
	    std::cout << "p4.P : " << p4.P() << std::endl;
	    std::cout << "neutrino_p4.Mass : " << neutrino_p4.M() << std::endl;
	    std::cout << "neutrino_p4.Momentum : " << neutrino_p4.P() << std::endl;
	    
	    std::cout << "truevis_p4 : "; truevis_p4.Print();
	    std::cout << " neutrino_p4 : "; neutrino_p4.Print();
	    std::cout << "truevis_p4.pt : " << truevis_p4.Pt() << std::endl;
	    std::cout << "neutrino_p4.pt : " << neutrino_p4.Pt() << std::endl;
	  */
	  
	  //Double_t Angle_Vis_neutrino_1Prong = truevis_p4.Angle(neutrino_p4.Vect());
	  //h_Angle_Vis_neutrino_1Prong->Fill(Angle_Vis_neutrino_1Prong);
	  //std::cout << "Angle_Vis_neutrino_1Prong =  " << Angle_Vis_neutrino_1Prong  << std::endl;
	  
	  
	  Angle_Vis_neutrino =   truevis_p4.Angle(neutrino_p4.Vect());
	  Angle_tau_truevis  =   p4.Angle(truevis_p4.Vect());
	  Angle_tau_neu      =   p4.Angle(neutrino_p4.Vect());
	  tau_Momentum       =   p4.P();
	  tau_pt             =   p4.Pt();
	  tau_m              =   p4.M();
	  tau_eta            =   p4.Eta();
	  tau_phi            =   p4.Phi();
	  vis_Momentum       =   truevis_p4.P();
	  neu_pt             =   neutrino_p4.Pt();
	  neu_m              =   neutrino_p4.M();
	  neu_eta            =   neutrino_p4.Eta();
	  neu_phi            =   neutrino_p4.Phi();
	  neu_Momentum       =   neutrino_p4.P();
	  /*
	    std::cout << "Angle_Vis_neutrino: " << Angle_Vis_neutrino << std::endl;
	    std::cout << " Momentum : " <<  Momentum << std::endl;
	    std::cout << " Angle_tau_truevis : " <<  Angle_tau_truevis << std::endl;
	    std::cout << "Pt_tau : " << Pt_tau << std::endl;
	  */
	  
	  //std::cout << "Angle_Vis_neutrino_1Prong_ipbin =  " << Angle_Vis_neutrino_1Prong_ipbin  << std::endl;
	  
	  numCharged = truth_tau->auxdata<size_t>("numCharged");
	  h_numCharged->Fill(numCharged);
	  
	  numChargedPion = truth_tau->auxdata<size_t>("numChargedPion");
	  h_numChargedPion->Fill(numChargedPion);
	  
	  numNeutral = truth_tau->auxdata<size_t>("numNeutral");
	  numNeutralPion = truth_tau->auxdata<size_t>("numNeutralPion");
	  /*
	    std::cout << "numCharged: " << numCharged << std::endl;
	    std::cout << "numChargedPion: " << numChargedPion << std::endl;
	    std::cout << "numNeutral: " << numNeutral << std::endl;
	    std::cout << "numNeutralPion: " << numNeutralPion << std::endl;
	  */
	  
	  
	  h_numCharged_vs_numChargedPion->Fill(numCharged, numChargedPion);
	  
	  h_taup_vs_numCharged->Fill(p4.P()/1000, numCharged);
	  h_taup_vs_numChargedPion->Fill(p4.P()/1000, numChargedPion);
	  
	  h_mvis_vs_numCharged->Fill(vis_m/1000, numCharged);
	  h_mvis_vs_numChargedPion->Fill(vis_m/1000, numChargedPion);
	  
	  if (numCharged == 1) {
	    //	     h_Ang_vs_Momen_n1Charged->Fill(Angle_Vis_neutrino, p4.P()/1000);
	  }
	  
	  /*
	    if (numCharged == 3) h_Angle_Vis_neutrino_vs_Momentum_numCharged3->Fill(Angle_Vis_neutrino, p4.P()/1000);
	    
	    if (numChargedPion == 1) h_Angle_Vis_neutrino_vs_Momentum_numChargedPion1->Fill(Angle_Vis_neutrino, p4.P()/1000);
	    if (numChargedPion == 3) h_Angle_Vis_neutrino_vs_Momentum_numChargedPion3->Fill(Angle_Vis_neutrino, p4.P()/1000);*/
	  
	  int this_ipbin = -1;
	  for (int ipbin = 0 ; ipbin < 14 ; ++ipbin) {
	    if ( p4.P()/1000 > pmin[ipbin] && p4.P()/1000 < pmax[ipbin]) {
	      this_ipbin = ipbin ;
	      break;
	    }
	  }
	  
	  if (this_ipbin > -1) {
	    
	    if (numCharged == 1) h_Angle_Vis_neutrino_numCharged1[this_ipbin]->Fill(Angle_Vis_neutrino);
	    if (numCharged == 3) h_Angle_Vis_neutrino_numCharged3[this_ipbin]->Fill(Angle_Vis_neutrino);
	    
	    if (numChargedPion == 1) h_Angle_Vis_neutrino_numChargedPion1[this_ipbin]->Fill(Angle_Vis_neutrino);
	    if (numChargedPion == 3) h_Angle_Vis_neutrino_numChargedPion3[this_ipbin]->Fill(Angle_Vis_neutrino);
	    
	  }
	  
	  tree->Fill();
	  
	}
	
      }
      
    }
    
    
    
   
  } // end of isMC 
    
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: postExecute ()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: finalize ()
{
  ANA_CHECK_SET_TYPE (EL::StatusCode); // set type of return code you are expecting (add to top of each function once)
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.  This is different from histFinalize() in that it only
  // gets called on worker nodes that processed input events.
  Info("finalize()", "Number of clean events = %i", m_numCleanEvents);
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: histFinalize ()
{
  // This method is the mirror image of histInitialize(), meaning it
  // gets called after the last event has been processed on the worker
  // node and allows you to finish up any objects you created in
  // histInitialize() before they are written to disk.  This is
  // actually fairly rare, since this happens separately for each
  // worker node.  Most of the time you want to do your
  // post-processing on the submission node after all your histogram
  // outputs have been merged.  This is different from finalize() in
  // that it gets called on all worker nodes regardless of whether
  // they processed input events.

  /* delete h_jetPt; h_jetPt = 0;
  delete h_tauPt; h_tauPt = 0;
  delete h_tauEta; h_tauEta = 0;
  delete h_numCharged; h_numCharged = 0;*/
  /*
  for (int ipbin = 0 ; ipbin < 14 ; ++ipbin){
    delete h_Angle_Vis_neutrino_1Prong[ipbin] ; h_Angle_Vis_neutrino_1Prong[ipbin] = 0; 
  }
  */


  return EL::StatusCode::SUCCESS;
}
