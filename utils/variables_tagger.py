import math
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

#### Alternative Truth
topTypes = ["Resolved", "Mixed"]
TruthType = { "Top"+t: {"standard" : "Top"+t+"_truth", "truth1"   : "Top"+t+"_truth1", "truth2"   : "Top"+t+"_truth2"}  for t in topTypes}

######## 1D variables for histos

vars = []

vars.append(variable(name = "MET_pt", title= "MET p_{T} [GeV]", nbins = 8, xmin = 25, xmax=825))
vars.append(variable(name = "MET_phi", title= "MET #phi", nbins = 6, xmin = -math.pi, xmax=math.pi))
vars.append(variable(name = "PuppiMET_pt", title= "p_{T}^{miss} [GeV]", nbins = 8, xmin = 25, xmax=825))

# vars.append(variable(name = "LeadingJetPt_pt", title= "Leading Jet p_{T} [GeV]", nbins = 8, xmin = 50, xmax=850))
# vars.append(variable(name = "LeadingJetPt_eta", title= "Leading Jet #eta", nbins = 8, xmin = -4, xmax=4))
# vars.append(variable(name = "LeadingJetPt_phi", title= "Leading Jet #phi", nbins = 6, xmin = -math.pi, xmax=math.pi))
# vars.append(variable(name = "LeadingJetPt_mass", title= "Leading Jet mass [GeV]", nbins = 10, xmin = 50, xmax=550))

# vars.append(variable(name = "LeadingFatJetPt_pt", title= "Leading FatJet p_{T} [GeV]", nbins = 8, xmin = 50, xmax=850))
# vars.append(variable(name = "LeadingFatJetPt_eta", title= "Leading FatJet #eta", nbins = 8, xmin = -4, xmax=4))
# vars.append(variable(name = "LeadingFatJetPt_phi", title= "Leading FatJet #phi", nbins = 6, xmin = -math.pi, xmax=math.pi))
# vars.append(variable(name = "LeadingFatJetPt_mass", title= "Leading FatJet mass [GeV]", nbins = 10, xmin = 50, xmax=550))
# vars.append(variable(name = "LeadingMuonPt_pt", title= "Leading Muon p_{T} [GeV]", nbins = 30, xmin = 0, xmax=300))
# vars.append(variable(name = "LeadingMuonPt_eta", title= "Leading Muon #eta", nbins = 8, xmin = -4, xmax=4))
# vars.append(variable(name = "LeadingMuonPt_phi", title= "Leading Muon #phi", nbins = 6, xmin = -math.pi, xmax=math.pi))
# vars.append(variable(name = "LeadingElectronPt_pt", title= "Leading Electron p_{T} [GeV]", nbins = 30, xmin = 0, xmax=300))
# vars.append(variable(name = "LeadingElectronPt_eta", title= "Leading Electron #eta", nbins = 8, xmin = -4, xmax=4))
# vars.append(variable(name = "LeadingElectronPt_phi", title= "Leading Electron #phi", nbins = 6, xmin = -math.pi, xmax=math.pi))
# vars.append(variable(name = "nTopHighPt", title= "# Top Candidate Mix", nbins = 80, xmin = -0.5, xmax=80.5))
# vars.append(variable(name = "nTopLowPt", title= "# Top Candidate Resolved", nbins = 50, xmin = -0.5, xmax=50.5))
vars.append(variable(name = "nGoodJet", title= "# Jet", nbins = 10, xmin = -0.5, xmax=9.5))
vars.append(variable(name = "nJetBtag", title= "# b-Jet ", nbins = 5, xmin = -0.5, xmax=4.5))
# vars.append(variable(name = "nFatJet", title= "# FatJet", nbins = 5, xmin = -0.5, xmax=4.5))
# vars.append(variable(name = "MinDelta_phi", title= "min #Delta #phi", nbins = 18, xmin = 0, xmax = math.pi))
# vars.append(variable(name = "MaxEta_jet", title= "max #eta jet", nbins = 5, xmin = 0, xmax = 5))
# vars.append(variable(name = "HT_eventHT", title= "event HT", nbins = 20, xmin = 0, xmax = 2000))
# vars.append(variable(name = "run", title= "Run Number", nbins = 5142, xmin = 315251.5, xmax = 320393.5))
# vars.append(variable(name = "PV_npvsGood", title= "Number of PV", nbins = 51, xmin = -0.5, xmax = 50.5))

# vars.append(variable(name = "EventTopCategory", title= "Top Category", nbins = 4, xmin = 0.5, xmax = 4.5))
# vars.append(variable(name = "Top_truth", title= "Top Truth", nbins = 4, xmin = -0.5, xmax = 3.5, MConly = True))
# vars.append(variable(name = "EventTopCategoryWithTruth", title= "Top Category (only true)", nbins = 4, xmin = 0.5, xmax = 4.5, MConly = True))



vars.append(variable(name = "Top_mass_Resolved", title= "best Top Resolved mass [GeV]", nbins = 30, xmin = 100, xmax=250, noUnOvFlowbin = True))
vars.append(variable(name = "Top_pt_Resolved", title= "best Top Resolved p_{T} [GeV]", nbins = 30, xmin = 100, xmax=1000, noUnOvFlowbin = True))
vars.append(variable(name = "Top_score_Resolved", title= "best Top Resolved Score", nbins = 20, xmin = 0, xmax=1, noUnOvFlowbin = True))
vars.append(variable(name = "Top_mass_Mixed", title= "best Top Mixed mass [GeV]", nbins = 30, xmin = 100, xmax=250, noUnOvFlowbin = True))
vars.append(variable(name = "Top_pt_Mixed", title= "best Top Mixed p_{T} [GeV]", nbins = 30, xmin = 100, xmax=1000, noUnOvFlowbin = True))
vars.append(variable(name = "Top_score_Mixed", title= "best Top Mixed Score", nbins = 20, xmin = 0, xmax=1, noUnOvFlowbin = True))
vars.append(variable(name = "nClusterT1TopMixed", title = "# Top Clusters T1 Mixed ", nbins = 16, xmin = -0.5, xmax = 15.5, noUnOvFlowbin = False))
vars.append(variable(name = "nClusterT2TopMixed", title = "# Top Clusters T2 Mixed", nbins = 16, xmin = -0.5, xmax = 15.5, noUnOvFlowbin = False))
vars.append(variable(name = "nClusterT1TopResolved", title = "# Top Clusters T1 Resolved", nbins = 16, xmin = -0.5, xmax = 15.5, noUnOvFlowbin = False))
vars.append(variable(name = "nClusterT2TopResolved", title = "# Top Clusters T2 Resolved", nbins = 16, xmin = -0.5, xmax = 15.5, noUnOvFlowbin = False))
vars.append(variable(name = "nTopClusterT1MixedReco", title = "# Top Clusters T1 Reco Mixed" , nbins = 16, xmin = -0.5, xmax = 15.5, noUnOvFlowbin = False)) 
vars.append(variable(name = "nTopClusterT2MixedReco", title = "# Top Clusters T2 Reco Mixed" , nbins = 16, xmin = -0.5, xmax = 15.5, noUnOvFlowbin = False)) 
vars.append(variable(name = "nTopClusterT1ResolvedReco", title = "# Top Clusters T1 Reco Resolved" , nbins = 16, xmin = -0.5, xmax = 15.5, noUnOvFlowbin = False)) 
vars.append(variable(name = "nTopClusterT2ResolvedReco", title = "# Top Clusters T2 Reco Resolved" , nbins = 16, xmin = -0.5, xmax = 15.5, noUnOvFlowbin = False)) 
vars.append(variable(name = "TopMixed_TopScore", title = "Top Mixed Score", nbins = 20, xmin = 0, xmax = 1, noUnOvFlowbin = True, MConly = False))
vars.append(variable(name = "TopMixed_Score_truthstandard", title = "Top Mixed Score (True Standard Top)", nbins = 20, xmin = 0, xmax = 1, noUnOvFlowbin = True, MConly = True))
vars.append(variable(name = "TopMixed_Score_truth1_incl", title = "Top Mixed Score (True t1 Top)", nbins = 20, xmin = 0, xmax = 1, noUnOvFlowbin = True, MConly = True))
vars.append(variable(name = "TopMixed_Score_truth2_incl", title = "Top Mixed Score (True t2 Top)", nbins = 20, xmin = 0, xmax = 1, noUnOvFlowbin = True, MConly = True))
vars.append(variable(name = "TopMixed_Score_truth1", title = "Top Mixed Score (only True t1 Top)", nbins = 20, xmin = 0, xmax = 1, noUnOvFlowbin = True, MConly = True))
vars.append(variable(name = "TopMixed_Score_truth2", title = "Top Mixed Score (only True t2 Top)", nbins = 20, xmin = 0, xmax = 1, noUnOvFlowbin = True, MConly = True))
vars.append(variable(name = "TopResolved_TopScore", title = "Top Resolved Score", nbins = 20, xmin = 0, xmax = 1, noUnOvFlowbin = True, MConly = False))
vars.append(variable(name = "TopResolved_Score_truthstandard", title = "Top Resolved Score (True Standard Top)", nbins = 20, xmin = 0, xmax = 1, noUnOvFlowbin = True, MConly = True))
vars.append(variable(name = "TopResolved_Score_truth1", title = "Top Resolved Score (only True t1 Top)", nbins = 20, xmin = 0, xmax = 1, noUnOvFlowbin = True, MConly = True))
vars.append(variable(name = "TopResolved_Score_truth2", title = "Top Resolved Score (only True t2 Top)", nbins = 20, xmin = 0, xmax = 1, noUnOvFlowbin = True, MConly = True))
vars.append(variable(name = "TopResolved_Score_truth1_incl", title = "Top Resolved Score (True t1 Top)", nbins = 20, xmin = 0, xmax = 1, noUnOvFlowbin = True, MConly = True))
vars.append(variable(name = "TopResolved_Score_truth2_incl", title = "Top Resolved Score (True t2 Top)", nbins = 20, xmin = 0, xmax = 1, noUnOvFlowbin = True, MConly = True))

for top in TruthType.keys():
    t = top.replace("Top","")
    for tr in TruthType[top].keys():
        vars.append(variable(name = "nTopClusterT1"+t+"MCTag"+tr, title = "# Top Clusters T1 MC tagged ("+tr+") "+t+"" , nbins = 16, xmin = -0.5, xmax = 15.5, noUnOvFlowbin = False, MConly = True)) 
        vars.append(variable(name = "nTopClusterT2"+t+"MCTag"+tr, title = "# Top Clusters T2 MC tagged ("+tr+") "+t+"" , nbins = 16, xmin = -0.5, xmax = 15.5, noUnOvFlowbin = False, MConly = True)) 
        vars.append(variable(name = "nTopClusterT2"+t+"TrueReco"+tr, title = "# Top Clusters T2 true reco ("+tr+") "+t+"" , nbins = 16, xmin = -0.5, xmax = 15.5, noUnOvFlowbin = False, MConly = True)) 
        vars.append(variable(name = "nTopClusterT1"+t+"TrueReco"+tr, title = "# Top Clusters T1 true reco ("+tr+") "+t+"" , nbins = 16, xmin = -0.5, xmax = 15.5, noUnOvFlowbin = False, MConly = True)) 
        vars.append(variable(name = "TopClusterT1"+t+"TrueRecoFirstCluster"+tr, title = "Top "+t+" Cluster T1 True Reco ("+tr+")", nbins = 3, xmin = -0.5, xmax = 2.5, noUnOvFlowbin = True, MConly = True)) 
        vars.append(variable(name = "TopClusterT2"+t+"TrueRecoFirstCluster"+tr, title = "Top "+t+" Cluster T2 True Reco ("+tr+")", nbins = 3, xmin = -0.5, xmax = 2.5, noUnOvFlowbin = True, MConly = True)) 
        vars.append(variable(name = "TopClusterT1"+t+"FalseRecoFirstCluster"+tr, title = "Top "+t+" Cluster T1 False Reco ("+tr+")", nbins = 3, xmin = -0.5, xmax = 2.5, noUnOvFlowbin = True, MConly = True)) 
        vars.append(variable(name = "TopClusterT2"+t+"FalseRecoFirstCluster"+tr, title = "Top "+t+" Cluster T2 False Reco ("+tr+")", nbins = 3, xmin = -0.5, xmax = 2.5, noUnOvFlowbin = True, MConly = True)) 
        vars.append(variable(name = "TopClusterT1"+t+"MCTagTrueFirstCluster"+tr, title = "Top "+t+" Cluster T1 True ("+tr+")", nbins = 3, xmin = -0.5, xmax = 2.5, noUnOvFlowbin = True, MConly = True)) 
        vars.append(variable(name = "TopClusterT2"+t+"MCTagTrueFirstCluster"+tr, title = "Top "+t+" Cluster T2 True ("+tr+")", nbins = 3, xmin = -0.5, xmax = 2.5, noUnOvFlowbin = True, MConly = True)) 
        vars.append(variable(name = "TopClusterT1"+t+"MCTagFalseFirstCluster"+tr, title = "Top "+t+" Cluster T1 False ("+tr+")", nbins = 3, xmin = -0.5, xmax = 2.5, noUnOvFlowbin = True, MConly = True)) 
        vars.append(variable(name = "TopClusterT2"+t+"MCTagFalseFirstCluster"+tr, title = "Top "+t+" Cluster T2 False ("+tr+")", nbins = 3, xmin = -0.5, xmax = 2.5, noUnOvFlowbin = True, MConly = True))




# vars.append(variable(name = "Top_isolationPtJetsdR04", title= "Top Iso p_{T} (#Delta R=0.4)", nbins = 20, xmin = 0, xmax=2, noUnOvFlowbin = True))
# vars.append(variable(name = "Top_isolationPtJetsdR06", title= "Top Iso p_{T} (#Delta R=0.6)", nbins = 20, xmin = 0, xmax=2, noUnOvFlowbin = True))
# vars.append(variable(name = "Top_isolationPtJetsdR08", title= "Top Iso p_{T} (#Delta R=0.8)", nbins = 20, xmin = 0, xmax=2, noUnOvFlowbin = True))
# vars.append(variable(name = "Top_isolationPtJetsdR12", title= "Top Iso p_{T} (#Delta R=1.2)", nbins = 20, xmin = 0, xmax=2, noUnOvFlowbin = True))
# vars.append(variable(name = "Top_isolationNJetsdR04", title= "Top Iso n_{jet}  (#Delta R=0.4)", nbins = 11, xmin = -0.5, xmax=10.5, noUnOvFlowbin = True))
# vars.append(variable(name = "Top_isolationNJetsdR06", title= "Top Iso n_{jet}  (#Delta R=0.6)", nbins = 11, xmin = -0.5, xmax=10.5, noUnOvFlowbin = True))
# vars.append(variable(name = "Top_isolationNJetsdR08", title= "Top Iso n_{jet}  (#Delta R=0.8)", nbins = 11, xmin = -0.5, xmax=10.5, noUnOvFlowbin = True))
# vars.append(variable(name = "Top_isolationNJetsdR12", title= "Top Iso n_{jet}  (#Delta R=1.2)", nbins = 11, xmin = -0.5, xmax=10.5, noUnOvFlowbin = True))

######## 1D variables for histos
vars2D = []

# vars2D.append(variable2D(name = "nGoodTopResolvedVsnGoodTopMixed", xname = "nGoodTopResolved", yname = "nGoodTopMixed", xtitle = "# Top Resolved", ytitle = "# Top Mixed", nxbins = 6, xmin = -0.5, xmax = 5.5,
#                             nybins = 6, ymin = -0.5, ymax = 5.5))

regions = {
    # "NoCut"                             : nocut,
    # "HEMVeto"                         : hemveto,
    # "HEMVeto_MET_filters"             : hemveto +" && " + met_filters,
    "All"                            : "",
    "Presel"                         : "MET_pt>25",
    "1TopLep"                        : "MET_pt>25 && NGoodTopLep==1",
    "0TopLep"                        : "MET_pt>25 && NGoodTopLep==0",
    "atLeast2TopLep"                 : "MET_pt>25 && NGoodTopLep>1",
    "1TopLepMCtag"                   : "MET_pt>25 && NGoodTopLep==1 && BJetTopLep_MCtag",
    
#     "PreselResolved"                 : "MET_pt>25 && EventTopCategory==1",
#     "PreselMixed"                    : "MET_pt>25 && EventTopCategory==2",
#     "PreselMerged"                   : "MET_pt>25 && EventTopCategory==3",
#     "PreselNoTop"                    : "MET_pt>25 && EventTopCategory==4",
    
    # "AH"                             : "MET_pt>25 && nJetBtag > 1 && nGoodJet>3",
    # "TopMixReg"                      : "MET_pt>25 && Top_score > 0.7584613561630249"
    
    # "AHResolved"                     : "MET_pt>25 && nJetBtag > 1 && nGoodJet>3 && EventTopCategory==1",
    # "AHMixed"                        : "MET_pt>25 && nJetBtag > 1 && nGoodJet>3 && EventTopCategory==2",
    # "AHMerged"                       : "MET_pt>25 && nJetBtag > 1 && nGoodJet>3 && EventTopCategory==3",
    # "AHNoTop"                        : "MET_pt>25 && nJetBtag > 1 && nGoodJet>3 && EventTopCategory==4",
}