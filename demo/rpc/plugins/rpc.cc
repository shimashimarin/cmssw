// -*- C++ -*-
//
// Package:    demo/rpc
// Class:      rpc
//
/**\class rpc rpc.cc demo/rpc/plugins/rpc.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shima Rin
//         Created:  Sat, 02 Mar 2024 22:58:01 GMT
//
//

// system include files
#include <memory>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "DataFormats/IRPCDigi/interface/IRPCDigi.h"
#include "DataFormats/MuonData/interface/MuonDigiCollection.h"
#include "DataFormats/IRPCDigi/interface/IRPCDigiCollection.h"

#include "TTree.h"

using namespace edm;
using namespace std;

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.

struct eventInfo
{
  int nRPCDetId;
  vector<int> RPCDetId_region;
  vector<int> RPCDetId_ring;
  vector<int> RPCDetId_station;
  vector<int> RPCDetId_sector;
  vector<int> RPCDetId_layer;
  vector<int> RPCDetId_subsector;
  vector<int> RPCDetId_roll;
  vector<int> RPCDetId_niRPCDigi;

  int niRPCDigi;
  vector<int> iRPCDigi_RPCDetId_idx;
  vector<int> iRPCDigi_strip;
  vector<int> iRPCDigi_bx;
  vector<int> iRPCDigi_sbx;
  vector<int> iRPCDigi_bxLR;
  vector<int> iRPCDigi_bxHR;
  vector<int> iRPCDigi_sbxLR;
  vector<int> iRPCDigi_sbxHR;
};

class rpc : public edm::one::EDAnalyzer<edm::one::SharedResources> {
public:
  explicit rpc(const edm::ParameterSet&);
  ~rpc() override;

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  void beginJob() override;
  void analyze(const edm::Event&, const edm::EventSetup&) override;
  void endJob() override;

  void initEventStructure();

  // ----------member data ---------------------------
  // edm::EDGetTokenT<MuonDigiCollection<RPCDetId,IRPCDigi>> srcIRPC_;  //used to select what tracks to read from configuration file
  edm::EDGetTokenT<IRPCDigiCollection> srcIRPC_;
  bool debugInfo_;

  //--- outputs
  Service<TFileService> fs_;
  TTree *eventTree;
  eventInfo evInfo;

  #ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
    edm::ESGetToken<SetupData, SetupRecord> setupToken_;
  #endif
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
rpc::rpc(const edm::ParameterSet& iConfig)
    : srcIRPC_(consumes<IRPCDigiCollection>(iConfig.getUntrackedParameter<edm::InputTag>("srcIRPC"))),
    debugInfo_(iConfig.getParameter<bool>("debugInfo")) {
      eventTree = fs_->make<TTree>( "event", "event" );

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  setupDataToken_ = esConsumes<SetupData, SetupRecord>();
#endif
  //now do what ever initialization is needed
}

rpc::~rpc() {
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  //
  // please remove this method altogether if it would be left empty
}

//
// member functions
//
// ------------ method called for each event  ------------
void rpc::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  Handle<IRPCDigiCollection> irpcDigis;
  iEvent.getByToken(srcIRPC_, irpcDigis);
  Handle<bool> debugInfo;

  // -- initialize output tree
  initEventStructure();

  // https://github.com/cms-sw/cmssw/blob/85c8117751a37223e789fa5849903e548e10b859/L1Trigger/Phase2L1GMT/src/L1TPhase2GMTEndcapStubProcessor.cc#L262
  auto rpcchamber = irpcDigis->begin();
  auto rpcchend = irpcDigis->end();
  int nrpc=0;
  int ndigi=0;
  for (; rpcchamber != rpcchend; ++rpcchamber) {
    const RPCDetId& detid = (*rpcchamber).first;

    if ((*rpcchamber).first.region() == 0)
      continue;

    if (debugInfo) {
      cout<<"---> Idx: "<<nrpc<<" - RPCDetId: "<<detid.region()<<"\t"<<detid.ring()<<"\t"<<detid.station()<<"\t"<<detid.sector()<<"\t"<<detid.layer()<<"\t"<<detid.subsector()<<"\t"<<detid.roll()<<endl;
    }
    evInfo.RPCDetId_region.push_back(detid.region());
    evInfo.RPCDetId_ring.push_back(detid.ring());
    evInfo.RPCDetId_station.push_back(detid.station());
    evInfo.RPCDetId_sector.push_back(detid.sector());
    evInfo.RPCDetId_layer.push_back(detid.layer());
    evInfo.RPCDetId_subsector.push_back(detid.subsector());
    evInfo.RPCDetId_roll.push_back(detid.roll());
    // ! FIXME:
    evInfo.RPCDetId_rollID.push_back(detid.rollId());

    auto digi = (*rpcchamber).second.first;
    auto dend = (*rpcchamber).second.second;

    int ndigi_for_detid = 0;
    for (; digi != dend; ++digi) {
      if (debugInfo) {
        cout<<"------> "<<ndigi<<" - IRPCDigi: "<<digi->strip()<<"\t"<<digi->bx()<<"\t"<<digi->sbx()<<"\t"<<digi->bxLR()<<"\t"<<digi->bxHR()<<"\t"<<digi->sbxLR()<<"\t"<<digi->sbxHR()<<endl;
      }

      evInfo.iRPCDigi_RPCDetId_idx.push_back(nrpc);
      evInfo.iRPCDigi_strip.push_back(digi->strip());
      evInfo.iRPCDigi_bx.push_back(digi->bx());
      evInfo.iRPCDigi_sbx.push_back(digi->sbx());
      evInfo.iRPCDigi_bxLR.push_back(digi->bxLR());
      evInfo.iRPCDigi_bxHR.push_back(digi->bxHR());
      evInfo.iRPCDigi_sbxLR.push_back(digi->sbxLR());
      evInfo.iRPCDigi_sbxHR.push_back(digi->sbxHR());

      ndigi++;
      ndigi_for_detid++;
    }
    evInfo.RPCDetId_niRPCDigi.push_back(ndigi_for_detid+1);
    nrpc++;
  }
  evInfo.nRPCDetId=nrpc+1;
  evInfo.niRPCDigi=ndigi+1;

  // --- fill the tree
  eventTree->Fill();

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  // if the SetupData is always needed
  auto setup = iSetup.getData(setupToken_);
  // if need the ESHandle to check if the SetupData was there or not
  auto pSetup = iSetup.getHandle(setupToken_);
#endif
}

// ------------ method called once each job just before starting event loop  ------------
void rpc::beginJob() {
  // please remove this method if not needed
  eventTree->Branch("nRPCDetId",             &evInfo.nRPCDetId);
  eventTree->Branch("RPCDetId_region",       &evInfo.RPCDetId_region);
  eventTree->Branch("RPCDetId_ring",         &evInfo.RPCDetId_ring);
  eventTree->Branch("RPCDetId_station",      &evInfo.RPCDetId_station);
  eventTree->Branch("RPCDetId_sector",       &evInfo.RPCDetId_sector);
  eventTree->Branch("RPCDetId_layer",        &evInfo.RPCDetId_layer);
  eventTree->Branch("RPCDetId_subsector",    &evInfo.RPCDetId_subsector);
  eventTree->Branch("RPCDetId_roll",         &evInfo.RPCDetId_roll);
  eventTree->Branch("RPCDetId_niRPCDigi",    &evInfo.RPCDetId_niRPCDigi);

  eventTree->Branch("niRPCDigi",             &evInfo.niRPCDigi);
  eventTree->Branch("iRPCDigi_RPCDetId_idx", &evInfo.iRPCDigi_RPCDetId_idx);
  eventTree->Branch("iRPCDigi_strip",        &evInfo.iRPCDigi_strip);
  eventTree->Branch("iRPCDigi_bx",           &evInfo.iRPCDigi_bx);
  eventTree->Branch("iRPCDigi_sbx",          &evInfo.iRPCDigi_sbx);
  eventTree->Branch("iRPCDigi_bxLR",         &evInfo.iRPCDigi_bxLR);
  eventTree->Branch("iRPCDigi_bxHR",         &evInfo.iRPCDigi_bxHR);
  eventTree->Branch("iRPCDigi_sbxLR",        &evInfo.iRPCDigi_sbxLR);
  eventTree->Branch("iRPCDigi_sbxHR",        &evInfo.iRPCDigi_sbxHR);
}

// ------------ method called once each job just after ending the event loop  ------------
void rpc::endJob() {
  // please remove this method if not needed
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void rpc::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

// ------------ method initialize tree structure ------------
void rpc::initEventStructure() {
  // per-event tree:
  evInfo.nRPCDetId = -9999;
  evInfo.RPCDetId_region.clear();
  evInfo.RPCDetId_ring.clear();
  evInfo.RPCDetId_station.clear();
  evInfo.RPCDetId_sector.clear();
  evInfo.RPCDetId_layer.clear();
  evInfo.RPCDetId_subsector.clear();
  evInfo.RPCDetId_roll.clear();
  evInfo.RPCDetId_niRPCDigi.clear();

  evInfo.niRPCDigi = -9999;
  evInfo.iRPCDigi_RPCDetId_idx.clear();
  evInfo.iRPCDigi_strip.clear();
  evInfo.iRPCDigi_bx.clear();
  evInfo.iRPCDigi_sbx.clear();
  evInfo.iRPCDigi_bxLR.clear();
  evInfo.iRPCDigi_bxHR.clear();
  evInfo.iRPCDigi_sbxLR.clear();
  evInfo.iRPCDigi_sbxHR.clear();
}

//define this as a plug-in
DEFINE_FWK_MODULE(rpc);