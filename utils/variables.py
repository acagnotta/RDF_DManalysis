import math
import numpy as np
class variable(object):
    def __init__(self, name, title, taglio=None, nbins=None, xmin=None, xmax=None, xarray=None, MConly = False, noUnOvFlowbin = False):
        self._name = name
        self._title = title
        self._taglio = taglio
        self._nbins = nbins
        self._xmin = xmin
        self._xmax = xmax
        self._xarray = xarray
        self._MConly = MConly
        self._noUnOvFlowbin = noUnOvFlowbin
    def __str__(self):
        return  '\"'+str(self._name)+'\",\"'+str(self._title)+'\",\"'+str(self._taglio)+'\",'+str(self._nbins)+','+str(self._xmin)+','+str(self._xmax)
#variable("Top_pt", "Top p_T [GeV]", nbins = 50, xmin = 0 , xmax = 1000)
class variable2D(object):
    def __init__(self, name, xname, yname, xtitle, ytitle, taglio=None, nxbins=None, xmin=None, xmax=None, xarray=None, 
                    nybins=None, ymin=None, ymax=None, yarray=None):
        self._name = name
        self._xname = xname
        self._yname = yname
        self._xtitle = xtitle
        self._ytitle = ytitle
        self._taglio = taglio
        self._nxbins = nxbins
        self._xmin = xmin
        self._xmax = xmax
        self._xarray = xarray
        self._nybins = nybins
        self._ymin = ymin
        self._ymax = ymax
        self._yarray = yarray
    def __str__(self):
        return  '\"'+str(self._name)+'\",\"'+str(self._xtitle)+'\",\"'+str(self._ytitle)+'\",\"'+str(self._taglio)+'\",'+str(self._nxbins)+','+str(self._xmin)+','+str(self._xmax)+','+str(self._nybins)+','+str(self._ymin)+','+str(self._ymax)


### Definition of requeriments for plots (cut), variables and regions

requirements = ""#"leptonveto" #"leptonveto && MET_pt>150 && MinDelta_phi>0.6"

######## 1D variables for histos

vars = []

vars.append(variable(name = "SFbtag_nominal", title= "#omega_{b-tag SF}", nbins = 100, xmin = 0, xmax=2, MConly = True))

# vars.append(variable(name = "MET_pt", title= "p_{T}^{miss} [GeV]", nbins = 6, xmin = 200, xmax=800))
# vars.append(variable(name = "MET_phi", title= "MET #phi", nbins = 6, xmin = -math.pi, xmax=math.pi))
vars.append(variable(name = "PuppiMET_pt", title= "p_{T}^{miss}(Puppi) [GeV]", nbins = 6, xmin = 200, xmax=800))
vars.append(variable(name = "PuppiMET_phi", title= "MET #phi (Puppi) [GeV]", nbins = 6, xmin = -math.pi, xmax=math.pi))
vars.append(variable(name = "PuppiMET_T1_pt_nominal", title= "p_{T}^{miss}(Puppi) nominal [GeV]", nbins = 12, xmin = 250, xmax=850))
vars.append(variable(name = "PuppiMET_T1_phi_nominal", title= "Puppi MET #phi nominal", nbins = 6, xmin = -math.pi, xmax=math.pi))

vars.append(variable(name = "LeadingJetPt_pt", title= "Leading Jet p_{T} [GeV]", nbins = 8, xmin = 50, xmax=850))
# vars.append(variable(name = "LeadingJetPt_eta", title= "Leading Jet #eta", nbins = 8, xmin = -4, xmax=4))
# vars.append(variable(name = "LeadingJetPt_phi", title= "Leading Jet #phi", nbins = 6, xmin = -math.pi, xmax=math.pi))
# vars.append(variable(name = "LeadingJetPt_mass", title= "Leading Jet mass [GeV]", nbins = 10, xmin = 50, xmax=550))

vars.append(variable(name = "LeadingFatJetPt_pt", title= "Leading FatJet p_{T} [GeV]", nbins = 8, xmin = 50, xmax=850))
# vars.append(variable(name = "LeadingFatJetPt_eta", title= "Leading FatJet #eta", nbins = 8, xmin = -4, xmax=4))
# vars.append(variable(name = "LeadingFatJetPt_phi", title= "Leading FatJet #phi", nbins = 6, xmin = -math.pi, xmax=math.pi))
# vars.append(variable(name = "LeadingFatJetPt_mass", title= "Leading FatJet mass [GeV]", nbins = 10, xmin = 50, xmax=550))
# vars.append(variable(name = "LeadingMuonPt_pt", title= "Leading Muon p_{T} [GeV]", nbins = 30, xmin = 0, xmax=300))
# vars.append(variable(name = "LeadingMuonPt_eta", title= "Leading Muon #eta", nbins = 8, xmin = -4, xmax=4))
# vars.append(variable(name = "LeadingMuonPt_phi", title= "Leading Muon #phi", nbins = 6, xmin = -math.pi, xmax=math.pi))
# vars.append(variable(name = "LeadingElectronPt_pt", title= "Leading Electron p_{T} [GeV]", nbins = 30, xmin = 0, xmax=300))
# vars.append(variable(name = "LeadingElectronPt_eta", title= "Leading Electron #eta", nbins = 8, xmin = -4, xmax=4))
# vars.append(variable(name = "LeadingElectronPt_phi", title= "Leading Electron #phi", nbins = 6, xmin = -math.pi, xmax=math.pi))

vars.append(variable(name = "nTopMixed", title= "# Top Candidate Mix", nbins = 40, xmin = -0.5, xmax=80.5))
vars.append(variable(name = "nTopResolved", title= "# Top Candidate Resolved", nbins = 25, xmin = -0.5, xmax=49.5))
vars.append(variable(name = "nJet", title= "# Jet", nbins = 10, xmin = -0.5, xmax=9.5))
vars.append(variable(name = "nJetBtag", title= "# b-Jet ", nbins = 5, xmin = -0.5, xmax=4.5))
vars.append(variable(name = "nFatJet", title= "# FatJet", nbins = 5, xmin = -0.5, xmax=4.5))
vars.append(variable(name = "MinDelta_phi", title= "min #Delta #phi", nbins = 18, xmin = 0, xmax = math.pi))
vars.append(variable(name = "MaxEta_jet", title= "max #eta jet", nbins = 5, xmin = 0, xmax = 5))
vars.append(variable(name = "HT_eventHT", title= "event HT", nbins = 20, xmin = 0, xmax = 2000))
# vars.append(variable(name = "run", title= "Run Number", nbins = 5142, xmin = 315251.5, xmax = 320393.5))
vars.append(variable(name = "PV_npvsGood", title= "Number of PV", nbins = 25, xmin = -0.5, xmax = 49.5))

vars.append(variable(name = "TopMixed_TopScore", title= "Top Mixed Score", nbins = 20, xmin = 0, xmax=1, noUnOvFlowbin = True))
vars.append(variable(name = "TopResolved_TopScore", title= "Top Resolved Score", nbins = 20, xmin = 0, xmax=1, noUnOvFlowbin = True))


# ######### Da aggiungere per girare la nuova versione Framework (Jan2024)
vars.append(variable(name = "EventTopCategory", title= "Top Category", nbins = 4, xmin = 0.5, xmax = 4.5))
# vars.append(variable(name = "Top_truth", title= "Top Truth", nbins = 4, xmin = -0.5, xmax = 3.5, MConly = True))
# vars.append(variable(name = "EventTopCategoryWithTruth", title= "Top Category (only true)", nbins = 4, xmin = 0.5, xmax = 4.5, MConly = True))
vars.append(variable(name = "Top_mass", title= "Top mass [GeV]", nbins = 30, xmin = 100, xmax=250, noUnOvFlowbin = True))
vars.append(variable(name = "Top_pt", title= "Top p_{T} [GeV]", nbins = 30, xmin = 100, xmax=1000, noUnOvFlowbin = True))
vars.append(variable(name = "Top_score", title= "Top Score", nbins = 20, xmin = 0, xmax=1, noUnOvFlowbin = True))

# vars.append(variable(name = "Top_isolationPtJetsdR04", title= "Top Iso p_{T} (#Delta R=0.4)", nbins = 20, xmin = 0, xmax=2, noUnOvFlowbin = True))
# vars.append(variable(name = "Top_isolationPtJetsdR06", title= "Top Iso p_{T} (#Delta R=0.6)", nbins = 20, xmin = 0, xmax=2, noUnOvFlowbin = True))
# vars.append(variable(name = "Top_isolationPtJetsdR08", title= "Top Iso p_{T} (#Delta R=0.8)", nbins = 20, xmin = 0, xmax=2, noUnOvFlowbin = True))
# vars.append(variable(name = "Top_isolationPtJetsdR12", title= "Top Iso p_{T} (#Delta R=1.2)", nbins = 20, xmin = 0, xmax=2, noUnOvFlowbin = True))
# vars.append(variable(name = "Top_isolationNJetsdR04", title= "Top Iso n_{jet}  (#Delta R=0.4)", nbins = 11, xmin = -0.5, xmax=10.5, noUnOvFlowbin = True))
# vars.append(variable(name = "Top_isolationNJetsdR06", title= "Top Iso n_{jet}  (#Delta R=0.6)", nbins = 11, xmin = -0.5, xmax=10.5, noUnOvFlowbin = True))
# vars.append(variable(name = "Top_isolationNJetsdR08", title= "Top Iso n_{jet}  (#Delta R=0.8)", nbins = 11, xmin = -0.5, xmax=10.5, noUnOvFlowbin = True))
# vars.append(variable(name = "Top_isolationNJetsdR12", title= "Top Iso n_{jet}  (#Delta R=1.2)", nbins = 11, xmin = -0.5, xmax=10.5, noUnOvFlowbin = True))


#  aggiungere plot per controllare la preselection dei fatjet
#  a bassa ed alto eta



######## 1D variables for histos
vars2D = []

# vars2D.append(variable2D(name = "MinDelta_phiVsHT_eventHT", xname = "MinDelta_phi", yname = "HT_eventHT", xtitle = " min #Delta #phi", ytitle = "event HT", nxbins = 18, xmin = 0, xmax = math.pi,
#                             nybins = 20, ymin = 0, ymax = 2000))

################## December 2023    
nocut = ""
hemveto = "(isMC || (year != 2018) || (HEMVeto || run<319077.))" 
met_filters = "(Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter && Flag_ecalBadCalibFilter && Flag_eeBadScFilter)"
hlt_filters = "(HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60 || HLT_PFMETNoMu120_PFMHTNoMu120_IDTight || HLT_Ele32_WPTight_Gsf || HLT_Ele115_CaloIdVT_GsfTrkIdT || HLT_Photon200 || HLT_IsoMu24)"
hlt2_filters = "(HLT_PFMET120_PFMHT120_IDTight || HLT_PFMETNoMu120_PFMHTNoMu120_IDTight)"
hlt3_filters = "(HLT_PFMET140_PFMHT140_IDTight || HLT_PFMETNoMu140_PFMHTNoMu140_IDTight)"
metcut = "(MET_pt>250)"
hltmet_filters = "(HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60 || HLT_PFMETNoMu120_PFMHTNoMu120_IDTight)"
hltmu_filters = "(HLT_IsoMu24)"
################## January 2024
singleLep   = "((nTightElectron == 1 && nVetoElectron == 1 && nTightMuon == 0 && nVetoMuon == 0)||(nTightElectron == 0 && nVetoElectron == 0 && nTightMuon == 1 && nVetoMuon == 1))"
singleMu    = "(nTightElectron == 0 && nVetoElectron == 0 && nTightMuon == 1 && nVetoMuon == 1)"
singleE     = "(nTightElectron == 1 && nVetoElectron == 1 && nTightMuon == 0 && nVetoMuon == 0)"


regions = {
    
    ################### May2024


    "AllSRs"               : "PuppiMET_T1_pt_nominal>250 && MinDelta_phi>0.6 && (nVetoElectron==0 && nVetoMuon ==0)",
    "ResSR"                : "PuppiMET_T1_pt_nominal>250 && MinDelta_phi>0.6 && (nVetoElectron==0 && nVetoMuon ==0) && EventTopCategory==1",
    "MixSR"                : "PuppiMET_T1_pt_nominal>250 && MinDelta_phi>0.6 && (nVetoElectron==0 && nVetoMuon ==0) && EventTopCategory==2",
    "MerSR"                : "PuppiMET_T1_pt_nominal>250 && MinDelta_phi>0.6 && (nVetoElectron==0 && nVetoMuon ==0) && EventTopCategory==3",
    "NoTop"                : "PuppiMET_T1_pt_nominal>250 && MinDelta_phi>0.6 && (nVetoElectron==0 && nVetoMuon ==0) && EventTopCategory==4",

    # "All"                            : "",   
    "Presel"               : "PuppiMET_T1_pt_nominal>250",
    "AH"                   : "PuppiMET_T1_pt_nominal>250 && (nVetoMuon+nVetoElectron) == 0 && nJetBtag > 0",


    # "orthogonalPreselR"    : "PuppiMET_T1_pt_nominal>100 && MinDelta_phi>0.6 && nVetoElectron+nVetoMuon > 0",

    "SL"                   : singleLep + " && nJetBtag > 0",
    "SEl"                  : singleE   + " && nJetBtag > 0",
    "SMu"                  : singleMu  + " && nJetBtag > 0",

    "AH1lWR"               : singleLep + " && nGoodJet>=3 && MT<=140 && nJetBtag == 0",
    "AH1lWREl"             : singleE   + " && nGoodJet>=3 && MT<=140 && nJetBtag == 0",
    "AH1lWRMu"             : singleMu  + " && nGoodJet>=3 && MT<=140 && nJetBtag == 0",

    "AH0lZR"               : "PuppiMET_T1_pt_nominal>250 && MinDelta_phi>2.5 && (nVetoMuon+nVetoElectron) == 0 && nJetBtag == 0", 
    "AH0lQCDR"             : "PuppiMET_T1_pt_nominal<250 && MinDelta_phi<0.6 && (nVetoMuon+nVetoElectron) == 0 && nJetBtag == 0", 

    "PreselResolved"       : "PuppiMET_T1_pt_nominal>250 && EventTopCategory==1",
    "PreselMixed"          : "PuppiMET_T1_pt_nominal>250 && EventTopCategory==2",
    "PreselMerged"         : "PuppiMET_T1_pt_nominal>250 && EventTopCategory==3",
    "PreselNoTop"          : "PuppiMET_T1_pt_nominal>250 && EventTopCategory==4",
    
    ################### December 2023
    
    # "NoCut"                             : nocut,
    # # "HEMVeto"                         : hemveto,
    # # "HEMVeto_MET_filters"             : hemveto +" && " + met_filters,
    # "HEMVeto_HLTmet"                 : hemveto +" && " + hltmet_filters,
    # "HEMVeto_HLTmu"                  : hemveto +" && " + hltmu_filters,
    # "HEMVeto_HLT"                    : hemveto +" && (" + hltmet_filters +" && " + hltmu_filters + ")",
    # "HEMVeto_HLTmet_METfilt"         : hemveto +" && " + met_filters +" && "+ hltmet_filters,
    # "HEMVeto_HLTmu_METfilt"          : hemveto +" && " + met_filters +" && "+ hltmu_filters,
    # "HEMVeto_HLT_METfilt"            : hemveto +" && " + met_filters +" && (" + hltmet_filters +" && " + hltmu_filters + ")",
    # "HEMVeto_HLTmet_METcut"          : hemveto +" && " + hltmet_filters +" && "+ metcut,
    # "HEMVeto_HLTmu_METcut"           : hemveto +" && " + hltmu_filters +" && "+ metcut,
    # "HEMVeto_HLT_METcut"             : hemveto +" && (" + hltmet_filters +" && " + hltmu_filters + ") && "+ metcut,
    # "AH_HLT"                         : hemveto +" && (" + hltmet_filters +" && " + hltmu_filters + ") && "+ metcut+" && "+"(nVetoMuon+nVetoElectron) == 0 && nJetBtag > 0 && nGoodJet>3",
    # "AH1lWRmu_HLT"                   : hemveto +" && (" + hltmet_filters +" && " + hltmu_filters + ") && "+ metcut + " && " + "(nTightElectron == 0 && nVetoElectron == 0 && nTightMuon == 1 && nVetoMuon == 1) && nGoodJet>=3 && MT<=140 && nJetBtag == 0",
    # "SL_HLT"                         : hemveto +" && (" + hltmet_filters +" && " + hltmu_filters + ") && "+ metcut + " && " + "((nTightElectron == 1 && nVetoElectron == 1 && nTightMuon == 0 && nVetoMuon == 0)||(nTightElectron == 0 && nVetoElectron == 0 && nTightMuon == 1 && nVetoMuon == 1)) && nJetBtag > 0",
    # "AH_HLTmet"                      : hemveto +" && " + hltmet_filters +" && "+ metcut+" && "+"(nVetoMuon+nVetoElectron) == 0 && nJetBtag > 0 && nGoodJet>3",
    # "AH1lWRmu_HLTmet"                : hemveto +" && " + hltmet_filters +" && "+ metcut + " && " + "(nTightElectron == 0 && nVetoElectron == 0 && nTightMuon == 1 && nVetoMuon == 1) && nGoodJet>=3 && MT<=140 && nJetBtag == 0",
    # "SL_HLTmet"                      : hemveto +" && " + hltmet_filters +" && "+ metcut + " && " + "((nTightElectron == 1 && nVetoElectron == 1 && nTightMuon == 0 && nVetoMuon == 0)||(nTightElectron == 0 && nVetoElectron == 0 && nTightMuon == 1 && nVetoMuon == 1)) && nJetBtag > 0",
    # "AH_HLTmu"                       : hemveto +" && " + hltmu_filters +" && "+ metcut+" && "+"(nVetoMuon+nVetoElectron) == 0 && nJetBtag > 0 && nGoodJet>3",
    # "AH1lWRmu_HLTmu"                 : hemveto +" && " + hltmu_filters +" && "+ metcut + " && " + "(nTightElectron == 0 && nVetoElectron == 0 && nTightMuon == 1 && nVetoMuon == 1) && nGoodJet>=3 && MT<=140 && nJetBtag == 0",
    # "SL_HLTmu"                       : hemveto +" && " + hltmu_filters +" && "+ metcut + " && " + "((nTightElectron == 1 && nVetoElectron == 1 && nTightMuon == 0 && nVetoMuon == 0)||(nTightElectron == 0 && nVetoElectron == 0 && nTightMuon == 1 && nVetoMuon == 1)) && nJetBtag > 0",

    # "resolved_1fwjet": "EventTopCategory==3 && nForwardJet>0", 
    # "mixed_1fwjet": "EventTopCategory==2 && nForwardJet>0", 
    # "merged_1fwjet": "EventTopCategory==1 && nForwardJet>0",
    # "resolved_0fwjet": "EventTopCategory==3 && nForwardJet==0", 
    # "mixed_0fwjet": "EventTopCategory==2 && nForwardJet==0", 
    # "merged_0fwjet" : "EventTopCategory==1 && nForwardJet==0",
    # "noTopRegion" : "EventTopCategory==0"
}