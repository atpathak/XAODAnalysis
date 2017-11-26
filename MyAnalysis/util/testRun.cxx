#include "xAODRootAccess/Init.h"
#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/ScanDir.h"
#include "SampleHandler/ToolsDiscovery.h"
#include "EventLoop/Job.h"
#include "EventLoop/DirectDriver.h"
#include "SampleHandler/DiskListLocal.h"
#include <TSystem.h>
#include "PathResolver/PathResolver.h"
#include "xAODJet/JetContainer.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODTau/TauJetContainer.h"
#include "xAODTau/TauDefs.h" 
#include "xAODTau/TauJet.h"
#include "TString.h"
#include <string>
#include <EventLoopAlgs/NTupleSvc.h>
#include <EventLoop/OutputStream.h>

#include "MyAnalysis/MyxAODAnalysis.h"

int main( int argc, char* argv[] ) {

  // Take the submit directory from the input if provided:
  std::string submitDir = "submitDir";
  if( argc > 1 ) submitDir = argv[ 1 ];

  // Set up the job for xAOD access:
  xAOD::Init().ignore();

  // Construct the samples to run on:
  SH::SampleHandler sh;

  // use SampleHandler to scan all of the subdirectories of a directory for particular MC single file:
  //std::string inputFilePath = PathResolverFindCalibDirectory("/eos/user/n/ndang/xTau/DAOD/mc15_13TeV.344084.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_ggH125_taumu.merge.DAOD_HIGG4D2.e5003_s2726_r7772_r7676_p2949/");
  //SH::ScanDir().filePattern("DAOD_HIGG4D2.10353992._000001.pool.root.1").scan(sh,inputFilePath);
  //SH::ScanDir().filePattern("DAOD_HIGG4D2.10353992*").scan(sh,inputFilePath);
  //std::string inputFilePath = PathResolverFindCalibDirectory("/eos/user/n/ndang/xTau/DAOD/mc15_13TeV.344085.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_VBFH125_taumu.merge.DAOD_HIGG4D2.e5003_s2726_r7772_r7676_p2949/");
  //SH::ScanDir().filePattern("DAOD_HIGG4D2.10356895*").scan(sh,inputFilePath);
  //std::string inputFilePath = PathResolverFindCalibDirectory("/eos/user/n/ndang/xTau/DAOD/mc15_13TeV.344088.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_ggH125_taue.merge.DAOD_HIGG4D2.e5003_s2726_r7772_r7676_p2949/");
  //SH::ScanDir().filePattern("DAOD_HIGG4D2.10356698*").scan(sh,inputFilePath);
  //std::string inputFilePath = PathResolverFindCalibDirectory("/eos/user/n/ndang/xTau/DAOD/mc15_13TeV.344089.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_VBFH125_taue.merge.DAOD_HIGG4D2.e5003_s2726_r7772_r7676_p2949/");
  //SH::ScanDir().filePattern("DAOD_HIGG4D2.10356712*").scan(sh,inputFilePath);
  std::string inputFilePath = PathResolverFindCalibDirectory("/eos/user/a/atpathak/LFV_Input/mc15_13TeV.341123.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_ggH125_tautaulh.merge.DAOD_HIGG4D2.e3935_s2608_s2183_r7772_r7676_p2949/");
  SH::ScanDir().filePattern("DAOD_HIGG4D2.10353371*").scan(sh,inputFilePath);
  // SH::ScanDir().filePattern("DAOD_HIGG4D2.10353371._000001.pool.root.1").scan(sh,inputFilePath);
  //std::string inputFilePath = PathResolverFindCalibDirectory("/eos/user/a/atpathak/LFV_Input/mc15_13TeV.361108.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Ztautau.merge.DAOD_HIGG4D2.e3601_s2726_r7725_r7676_p2949/");
  //SH::ScanDir().filePattern("DAOD_HIGG4D2*").scan(sh,inputFilePath);
  //std::string inputFilePath = PathResolverFindCalibDirectory("/eos/user/a/atpathak/LFV_Input/mc15_13TeV.361108.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Ztautau.merge.DAOD_TAUP3.e3601_a766_a818_r7676_p2949/");
  //SH::ScanDir().filePattern("DAOD_TAUP3.12362264._000068.pool.root.1").scan(sh,inputFilePath);
  //SH::ScanDir().filePattern("DAOD_TAUP3*").scan(sh,inputFilePath);


  // Set the name of the input TTree. It's always "CollectionTree"
  // for xAOD files.
   sh.setMetaString( "nc_tree", "CollectionTree" );

  // Print what we found:
  sh.print();

  
  
  // Create an EventLoop job:
  EL::Job job;
  job.sampleHandler( sh );
  // job.options()->setDouble (EL::Job::optMaxEvents, 2000);

  
  
  // Add our analysis to the job:
  MyxAODAnalysis* alg = new MyxAODAnalysis();
  // define an output and an ntuple associated to that output
  EL::OutputStream output  ("myOutput");
  job.outputAdd (output);
  EL::NTupleSvc *ntuple = new EL::NTupleSvc ("myOutput");
  job.algsAdd (ntuple);
  job.algsAdd( alg );
  alg->outputName = "myOutput"; // give the name of the output to our algorithm
  
  // Run the job using the local/direct driver:
  EL::DirectDriver driver;
  driver.submit( job, submitDir );

  return 0;
}
