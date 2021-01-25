// -*- C++ -*-
//
// Package:     PhysicsTools/NanoAODOutput
// Class  :     NanoAODRNTupleOutputModule
//
// Implementation:
//     [Notes on implementation]
//
// Original Author:  Max Orok
//         Created:  Wed, 13 Jan 2021 14:21:41 GMT
//

#include <string>

#include <ROOT/RNTuple.hxx>
#include <ROOT/RNTupleModel.hxx>

#include "FWCore/Framework/interface/one/OutputModule.h"
#include "FWCore/Framework/interface/RunForOutput.h"
#include "FWCore/Framework/interface/LuminosityBlockForOutput.h"
#include "FWCore/Framework/interface/EventForOutput.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/JobReport.h"
#include "FWCore/Utilities/interface/Digest.h"
#include "FWCore/Utilities/interface/GlobalIdentifier.h"

class NanoAODRNTupleOutputModule : public edm::one::OutputModule<> {
public:
  NanoAODRNTupleOutputModule(edm::ParameterSet const& pset);
  ~NanoAODRNTupleOutputModule() override;

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  void openFile(edm::FileBlock const&) override;
  bool isFileOpen() const override;
  void write(edm::EventForOutput const& e) override;
  void writeLuminosityBlock(edm::LuminosityBlockForOutput const&) override;
  void writeRun(edm::RunForOutput const&) override;
  void reallyCloseFile() override;

  std::string m_fileName;
  std::string m_logicalFileName;
  edm::JobReport::Token m_jrToken;

  std::unique_ptr<ROOT::Experimental::RNTupleModel> m_model;
};

NanoAODRNTupleOutputModule::NanoAODRNTupleOutputModule(edm::ParameterSet const& pset)
    : edm::one::OutputModuleBase::OutputModuleBase(pset),
      edm::one::OutputModule<>(pset),
      m_fileName(pset.getUntrackedParameter<std::string>("fileName")),
      m_logicalFileName(pset.getUntrackedParameter<std::string>("logicalFileName")),
      m_model(ROOT::Experimental::RNTupleModel::Create()) {}

NanoAODRNTupleOutputModule::~NanoAODRNTupleOutputModule() {}

void NanoAODRNTupleOutputModule::writeLuminosityBlock(edm::LuminosityBlockForOutput const& iLumi) {}
void NanoAODRNTupleOutputModule::writeRun(edm::RunForOutput const& iRun) {}

bool NanoAODRNTupleOutputModule::isFileOpen() const {
  return nullptr != m_model.get();
}

void NanoAODRNTupleOutputModule::openFile(edm::FileBlock const&) {
  // m_model->MakeField<std::vector<float>>("floats");

  edm::Service<edm::JobReport> jr;
  cms::Digest branchHash;
  m_jrToken = jr->outputFileOpened(m_fileName,
                                   m_logicalFileName,
                                   std::string(),
                                   // TODO check if needed
                                   //m_fakeName ? "PoolOutputModule" : "NanoAODOutputModule",
                                   "NanoAODRNTupleOutputModule",
                                   description().moduleLabel(),
                                   edm::createGlobalIdentifier(),
                                   std::string(),
                                   branchHash.digest().toString(),
                                   std::vector<std::string>());
}

void NanoAODRNTupleOutputModule::write(edm::EventForOutput const& iEvent) {

}

void NanoAODRNTupleOutputModule::reallyCloseFile() {
  {
    auto ntuple = ROOT::Experimental::RNTupleWriter::Recreate(std::move(m_model), "ntuple", m_fileName);
    ntuple->Fill();
  }

  edm::Service<edm::JobReport> jr;
  jr->outputFileClosed(m_jrToken);
}

void NanoAODRNTupleOutputModule::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription desc;

  desc.addUntracked<std::string>("fileName");
  desc.addUntracked<std::string>("logicalFileName", "");

  const std::vector<std::string> keep = {"drop *",
                                         "keep nanoaodFlatTable_*Table_*_*",
                                         "keep edmTriggerResults_*_*_*",
                                         "keep String_*_genModel_*",
                                         "keep nanoaodMergeableCounterTable_*Table_*_*",
                                         "keep nanoaodUniqueString_nanoMetadata_*_*"};
  edm::one::OutputModule<>::fillDescription(desc, keep);

  descriptions.addDefault(desc);
}

DEFINE_FWK_MODULE(NanoAODRNTupleOutputModule);
