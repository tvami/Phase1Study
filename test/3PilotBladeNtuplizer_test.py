# Source: PilotBladeStudy copied and modified
# Author: Tamas Almos Vami
# Year: 2015
# Description: Phase1 MC Simulation NTuplizer

import FWCore.ParameterSet.Config as cms

process = cms.Process('Analysis')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi') 
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
#process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.Geometry.GeometrySimDB_cff')
process.load('Configuration.Geometry.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')



# ------------------- Input ----------------------------
nEvents = 'test'
process.maxEvents = cms.untracked.PSet(
  input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring('file:/data/vami/projects/pilotBlade/ppProcessing/PilotBlade_HIFlowCorr_RAWtoRECO_test.root'), #15 event input
  #fileNames = cms.untracked.vstring('file:/data/vami/projects/pilotBlade/ppProcessing/PilotBlade_HIFlowCorr_RAWtoRECO_Run263742_1k.root'), #1k input
  secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(
)
#-------------------------------------------------------

#----------------Production Info------------------------
process.configurationMetadata = cms.untracked.PSet(
  annotation = cms.untracked.string('Phase1Ntuplizer.py nevts:10'),
  name = cms.untracked.string('Applications'),
  version = cms.untracked.string('$Revision: 1.19 $')
)
#-------------------------------------------------------

## ------------------- Output ---------------------------
# we do not save the output from the standard sequance 
# only the output of the NTuplizer (Phase1Study)
#-------------------------------------------------------

# --------------------- GlobalTag ----------------------
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')
#process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_Prompt_v2', '')
#-------------------------------------------------------

#---------------------- Refitter -----------------------
process.load("RecoTracker.TrackProducer.TrackRefitters_cff")
process.Refitter = process.TrackRefitterP5.clone()
process.Refitter.src = 'generalTracks'
process.Refitter.TrajectoryInEvent = True
#-------------------------------------------------------

#------------------- Phase1Study -------------------
process.Phase1Study = cms.EDAnalyzer("Phase1Study",
  trajectoryInput = cms.string('Refitter'),
  fileName = cms.string('nTuplePhase1_'+nEvents+'.root'),
  usePixelCPE= cms.bool(True),
)
#-------------------------------------------------------

#--------------------- EndPath -------------------------
process.Refitter_step = cms.Path(
  process.MeasurementTrackerEvent*
  process.Refitter
)

process.Phase1Study_step = cms.Path(process.Phase1Study)
#-------------------------------------------------------

#--------------------- Schedule ------------------------
process.schedule = cms.Schedule(
  process.Refitter_step,
  process.Phase1Study_step,	
)

# customisation of the process
from SLHCUpgradeSimulations.Configuration.postLS1Customs import customisePostLS1 
process = customisePostLS1(process)
#-------------------------------------------------------
