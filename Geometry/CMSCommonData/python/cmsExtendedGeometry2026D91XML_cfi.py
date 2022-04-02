import FWCore.ParameterSet.Config as cms

# This config was generated automatically using generate2026Geometry.py
# If you notice a mistake, please update the generating script, not just this config

XMLIdealGeometryESSource = cms.ESSource("XMLIdealGeometryESSource",
    geomXMLFiles = cms.vstring(
        'Geometry/CMSCommonData/data/materials/2021/v1/materials.xml',
        'Geometry/CMSCommonData/data/rotations.xml',
        'Geometry/CMSCommonData/data/extend/v2/cmsextent.xml',
        'Geometry/CMSCommonData/data/cavernData/2021/v1/cavernData.xml',
        'Geometry/CMSCommonData/data/cms/2026/v5/cms.xml',
        'Geometry/CMSCommonData/data/cmsMother.xml',
        'Geometry/CMSCommonData/data/eta3/etaMax.xml',
        'Geometry/CMSCommonData/data/cmsTracker.xml',
        'Geometry/CMSCommonData/data/caloBase/2026/v7/caloBase.xml',
        'Geometry/CMSCommonData/data/cmsCalo.xml',
        'Geometry/CMSCommonData/data/muonBase/2026/v5/muonBase.xml',
        'Geometry/CMSCommonData/data/cmsMuon.xml',
        'Geometry/CMSCommonData/data/mgnt.xml',
        'Geometry/CMSCommonData/data/beampipe/2026/v3/beampipe.xml',
        'Geometry/CMSCommonData/data/cmsBeam/2026/v1/cmsBeam.xml',
        'Geometry/CMSCommonData/data/muonMB.xml',
        'Geometry/CMSCommonData/data/muonMagnet.xml',
        'Geometry/CMSCommonData/data/cavern/2021/v1/cavern.xml',
        'Geometry/CMSCommonData/data/cavernFloor/2017/v1/cavernFloor.xml',
        'Geometry/TrackerCommonData/data/PhaseII/TFPXTEPXReordered/trackerParameters.xml',
        'Geometry/TrackerCommonData/data/pixfwdCommon.xml',
        'Geometry/TrackerCommonData/data/PhaseII/Tracker_DD4hep_compatible_2021_02/pixfwd.xml',
        'Geometry/TrackerCommonData/data/PhaseII/OuterTracker616_2020_04/pixbar.xml',
        'Geometry/TrackerCommonData/data/trackermaterial.xml',
        'Geometry/TrackerCommonData/data/PhaseII/OuterTracker616_2020_04/otst.xml',
        'Geometry/TrackerCommonData/data/PhaseII/Tracker_DD4hep_compatible_OT801_IT640/tracker.xml',
        'Geometry/TrackerCommonData/data/PhaseII/Tracker_DD4hep_compatible_OT801_IT640/pixel.xml',
        'Geometry/TrackerCommonData/data/PhaseII/TiltedTracker404/trackerbar.xml',
        'Geometry/TrackerCommonData/data/PhaseII/TiltedTracker404/trackerfwd.xml',
        'Geometry/TrackerCommonData/data/PhaseII/Tracker_DD4hep_compatible_2021_02/trackerStructureTopology.xml',
        'Geometry/TrackerCommonData/data/PhaseII/Tracker_DD4hep_compatible_OT801_IT640/pixelStructureTopology.xml',
        'Geometry/TrackerSimData/data/PhaseII/Tracker_DD4hep_compatible_2021_02/trackersens.xml',
        'Geometry/TrackerSimData/data/PhaseII/Tracker_DD4hep_compatible_OT801_IT640/pixelsens.xml',
        'Geometry/TrackerRecoData/data/PhaseII/Tracker_DD4hep_compatible_OT801_IT640/trackerRecoMaterial.xml',
        'Geometry/TrackerSimData/data/PhaseII/Tracker_DD4hep_compatible_2021_02/trackerProdCuts.xml',
        'Geometry/TrackerSimData/data/PhaseII/Tracker_DD4hep_compatible_OT801_IT640/pixelProdCuts.xml',
        'Geometry/TrackerSimData/data/trackerProdCutsBEAM.xml',
        'Geometry/EcalCommonData/data/eregalgo/2026/v2/eregalgo.xml',
        'Geometry/EcalCommonData/data/ectkcable/2026/v1/ectkcable.xml',
        'Geometry/EcalCommonData/data/ectkcablemat/2026/v2/ectkcablemat.xml',
        'Geometry/EcalCommonData/data/ebalgo.xml',
        'Geometry/EcalCommonData/data/ebcon/2021/v1/ebcon.xml',
        'Geometry/EcalCommonData/data/ebrot.xml',
        'Geometry/HcalCommonData/data/hcalrotations.xml',
        'Geometry/HcalCommonData/data/hcal/v2/hcalalgo.xml',
        'Geometry/HcalCommonData/data/hcalbarrelalgo.xml',
        'Geometry/HcalCommonData/data/hcalcablealgo/v2/hcalcablealgo.xml',
        'Geometry/HcalCommonData/data/hcalouteralgo.xml',
        'Geometry/HcalCommonData/data/hcalforwardalgo.xml',
        'Geometry/HcalCommonData/data/hcalSimNumbering/NoHE/hcalSimNumbering.xml',
        'Geometry/HcalCommonData/data/hcalRecNumbering/NoHE/hcalRecNumbering.xml',
        'Geometry/HcalCommonData/data/average/hcalforwardmaterial.xml',
        'Geometry/HGCalCommonData/data/hgcalMaterial/v2/hgcalMaterial.xml',
        'Geometry/HGCalCommonData/data/hgcal/v16/hgcal.xml',
        'Geometry/HGCalCommonData/data/hgcalcell/v16/hgcalcell.xml',
        'Geometry/HGCalCommonData/data/hgcalwafer/v16/hgcalwafer.xml',
        'Geometry/HGCalCommonData/data/hgcalEE/v16/hgcalEE.xml',
        'Geometry/HGCalCommonData/data/hgcalHEsil/v16/hgcalHEsil.xml',
        'Geometry/HGCalCommonData/data/hgcalHEmix/v16/hgcalHEmix.xml',
        'Geometry/HGCalCommonData/data/hgcalCons/v16/hgcalCons.xml',
        'Geometry/HGCalCommonData/data/hgcalConsData/v16/hgcalConsData.xml',
        'Geometry/MuonCommonData/data/mbCommon/2021/v1/mbCommon.xml',
        'Geometry/MuonCommonData/data/mb1/2015/v2/mb1.xml',
        'Geometry/MuonCommonData/data/mb2/2015/v2/mb2.xml',
        'Geometry/MuonCommonData/data/mb3/2015/v2/mb3.xml',
        'Geometry/MuonCommonData/data/mb4/2015/v2/mb4.xml',
        'Geometry/MuonCommonData/data/mb4Shield/2021/v1/mb4Shield.xml',
        'Geometry/MuonCommonData/data/muonYoke/2026/v3/muonYoke.xml',
        'Geometry/MuonCommonData/data/mf/2026/v8/mf.xml',
        'Geometry/MuonCommonData/data/csc/2021/v2/csc.xml',
        'Geometry/MuonCommonData/data/rpcf/2026/v3/rpcf.xml',
        'Geometry/MuonCommonData/data/gemf/TDR_BaseLine/gemf.xml',
        'Geometry/MuonCommonData/data/gem11/TDR_BaseLine/gem11.xml',
        'Geometry/MuonCommonData/data/gem21/TDR_Eta16/gem21.xml',
        'Geometry/MuonCommonData/data/mfshield/2026/v6/mfshield.xml',
        'Geometry/MuonCommonData/data/ge0/TDR_Dev/v4/ge0.xml',
        'Geometry/MuonCommonData/data/ge0shield/2026/v1/ge0shield.xml',
        'Geometry/ForwardCommonData/data/forwardshield/2026/v4/forwardshield.xml',
        'Geometry/ForwardCommonData/data/brmrotations.xml',
        'Geometry/ForwardCommonData/data/brm/2026/v1/brm.xml',
        'Geometry/ForwardCommonData/data/zdcmaterials.xml',
        'Geometry/ForwardCommonData/data/lumimaterials.xml',
        'Geometry/ForwardCommonData/data/zdcrotations.xml',
        'Geometry/ForwardCommonData/data/lumirotations.xml',
        'Geometry/ForwardCommonData/data/zdc.xml',
        'Geometry/ForwardCommonData/data/zdclumi.xml',
        'Geometry/ForwardCommonData/data/cmszdc.xml',
        'Geometry/MTDCommonData/data/mtdMaterial/v3/mtdMaterial.xml',
        'Geometry/MTDCommonData/data/btl/v1/btl.xml',
        'Geometry/MTDCommonData/data/etl/v7/etl.xml',
        'Geometry/MTDCommonData/data/mtdParameters/v3/mtdStructureTopology.xml',
        'Geometry/MTDCommonData/data/mtdParameters/v2/mtdParameters.xml',
    )+
    cms.vstring(
        'Geometry/MuonCommonData/data/muonNumbering/TDR_DeV/v5/muonNumbering.xml',
        'Geometry/EcalSimData/data/PhaseII/ecalsens.xml',
        'Geometry/HcalCommonData/data/hcalsens/NoHE/hcalsenspmf.xml',
        'Geometry/HcalSimData/data/hf.xml',
        'Geometry/HcalSimData/data/hfpmt.xml',
        'Geometry/HcalSimData/data/hffibrebundle.xml',
        'Geometry/HcalSimData/data/CaloUtil/2026/v2c/CaloUtil.xml',
        'Geometry/HGCalSimData/data/hgcsensv15.xml',
        'Geometry/MuonSimData/data/PhaseII/v2/muonSens.xml',
        'Geometry/DTGeometryBuilder/data/dtSpecsFilter/2021/v1/dtSpecsFilter.xml',
        'Geometry/CSCGeometryBuilder/data/cscSpecsFilter.xml',
        'Geometry/CSCGeometryBuilder/data/cscSpecs.xml',
        'Geometry/RPCGeometryBuilder/data/2026/v1/RPCSpecs.xml',
        'Geometry/GEMGeometryBuilder/data/v12/GEMSpecsFilter.xml',
        'Geometry/GEMGeometryBuilder/data/v12/GEMSpecs.xml',
        'Geometry/ForwardCommonData/data/brmsens.xml',
        'Geometry/ForwardSimData/data/zdcsens.xml',
        'Geometry/MTDSimData/data/v2/mtdsens.xml',
        'Geometry/HcalSimData/data/HcalProdCuts/2021/v1/HcalProdCuts.xml',
        'Geometry/EcalSimData/data/EcalProdCuts.xml',
        'Geometry/HGCalSimData/data/hgcProdCutsv15.xml',
        'Geometry/MuonSimData/data/muonProdCuts/2026/v2/muonProdCuts.xml',
        'Geometry/ForwardSimData/data/zdcProdCuts.xml',
        'Geometry/ForwardSimData/data/ForwardShieldProdCuts.xml',
        'Geometry/MTDSimData/data/v2/mtdProdCuts.xml',
        'Geometry/CMSCommonData/data/FieldParameters.xml',
    ),
    rootNodeName = cms.string('cms:OCMS')
)
