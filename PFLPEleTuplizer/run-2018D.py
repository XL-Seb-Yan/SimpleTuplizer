import FWCore.ParameterSet.Config as cms

process = cms.Process("L1NTUPLE")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

# Input source
# process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1000))
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring("file:/eos/home-x/xuyan/RKProj/lowpt/2022_data.root")
)


# import FWCore.PythonUtilities.LumiList as LumiList
# import FWCore.ParameterSet.Types as CfgTypes
# process.source.lumisToProcess = CfgTypes.untracked(CfgTypes.VLuminosityBlockRange())
# myLumis = LumiList.LumiList(filename = "JSON_dataNtuples.txt").getCMSSWString().split(',')
# process.source.lumisToProcess.extend(myLumis) 

# producer under test
process.Tree = cms.EDAnalyzer("MiniAODPFeleTuplizer",
    electrons = cms.InputTag("slimmedElectrons"),
)

# output file
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('SimpleNtuple.root')
)

process.p = cms.Path(process.Tree)