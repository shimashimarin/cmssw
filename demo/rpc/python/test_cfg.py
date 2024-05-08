import FWCore.ParameterSet.Config as cms

process = cms.Process("demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
# replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/gridgroup/cms/jxiao/rpc/run/out/step2_780005_0.root'
    )
)

process.TFileService = cms.Service("TFileService",
        fileName = cms.string('rpcdemo.root')
)

process.demo = cms.EDAnalyzer('rpc',
   srcIRPC = cms.untracked.InputTag('simMuonIRPCDigis'),
   debugInfo = cms.bool(True),
)

process.p = cms.Path(process.demo)
