import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing('analysis')
options.parseArguments()

process = cms.Process("NTUPLE")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

# Input source
# process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1000))
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(options.inputFiles)
)


# import FWCore.PythonUtilities.LumiList as LumiList
# import FWCore.ParameterSet.Types as CfgTypes
# process.source.lumisToProcess = CfgTypes.untracked(CfgTypes.VLuminosityBlockRange())
# myLumis = LumiList.LumiList(filename = "JSON_dataNtuples.txt").getCMSSWString().split(',')
# process.source.lumisToProcess.extend(myLumis) 

# producer under test
process.PFTree = cms.EDAnalyzer("MiniAODPFeleTuplizer",
    electrons = cms.InputTag("slimmedElectrons"),
)

process.LPTree = cms.EDAnalyzer("MiniAODLPeleTuplizer",
    electrons = cms.InputTag("slimmedLowPtElectrons"),
)

# output file
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('SimpleNtuple.root')
)

process.p = cms.Path(process.PFTree*process.LPTree)