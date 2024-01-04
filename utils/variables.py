import math
class variable(object):
    def __init__(self, name, title, taglio=None, nbins=None, xmin=None, xmax=None, xarray=None):
        self._name = name
        self._title = title
        self._taglio = taglio
        self._nbins = nbins
        self._xmin = xmin
        self._xmax = xmax
        self._xarray = xarray
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

vars.append(variable(name = "MET_pt", title= "MET p_{T} [GeV]", nbins = 6, xmin = 200, xmax=800))
vars.append(variable(name = "MET_phi", title= "MET #phi", nbins = 6, xmin = -math.pi, xmax=math.pi))
vars.append(variable(name = "PuppiMET_pt", title= "p_{T}^{miss} [GeV]", nbins = 6, xmin = 200, xmax=800))

vars.append(variable(name = "LeadingJetPt_pt", title= "Leading Jet p_{T} [GeV]", nbins = 8, xmin = 50, xmax=850))
# vars.append(variable(name = "LeadingJetPt_eta", title= "Leading Jet #eta", nbins = 8, xmin = -4, xmax=4))
# vars.append(variable(name = "LeadingJetPt_phi", title= "Leading Jet #phi", nbins = 6, xmin = -math.pi, xmax=math.pi))
# vars.append(variable(name = "LeadingJetPt_mass", title= "Leading Jet mass [GeV]", nbins = 10, xmin = 50, xmax=550))

vars.append(variable(name = "LeadingFatJetPt_pt", title= "Leading FatJet p_{T} [GeV]", nbins = 8, xmin = 50, xmax=850))
# vars.append(variable(name = "LeadingFatJetPt_eta", title= "Leading FatJet #eta", nbins = 8, xmin = -4, xmax=4))
# vars.append(variable(name = "LeadingFatJetPt_phi", title= "Leading FatJet #phi", nbins = 6, xmin = -math.pi, xmax=math.pi))
# vars.append(variable(name = "LeadingFatJetPt_mass", title= "Leading FatJet mass [GeV]", nbins = 10, xmin = 50, xmax=550))
vars.append(variable(name = "LeadingMuonPt_pt", title= "Leading Muon p_{T} [GeV]", nbins = 30, xmin = 0, xmax=300))
# vars.append(variable(name = "LeadingMuonPt_eta", title= "Leading Muon #eta", nbins = 8, xmin = -4, xmax=4))
# vars.append(variable(name = "LeadingMuonPt_phi", title= "Leading Muon #phi", nbins = 6, xmin = -math.pi, xmax=math.pi))
vars.append(variable(name = "LeadingElectronPt_pt", title= "Leading Electron p_{T} [GeV]", nbins = 30, xmin = 0, xmax=300))
# vars.append(variable(name = "LeadingElectronPt_eta", title= "Leading Electron #eta", nbins = 8, xmin = -4, xmax=4))
# vars.append(variable(name = "LeadingElectronPt_phi", title= "Leading Electron #phi", nbins = 6, xmin = -math.pi, xmax=math.pi))
# vars.append(variable(name = "nTopHighPt", title= "# Top Candidate Mix", nbins = 80, xmin = -0.5, xmax=80.5))
# vars.append(variable(name = "nTopLowPt", title= "# Top Candidate Resolved", nbins = 50, xmin = -0.5, xmax=50.5))
vars.append(variable(name = "nJet", title= "# Jet", nbins = 10, xmin = -0.5, xmax=9.5))
vars.append(variable(name = "nJetBtag", title= "# b-Jet ", nbins = 5, xmin = -0.5, xmax=4.5))
vars.append(variable(name = "nFatJet", title= "# FatJet", nbins = 5, xmin = -0.5, xmax=4.5))
vars.append(variable(name = "MinDelta_phi", title= "min #Delta #phi", nbins = 18, xmin = 0, xmax = math.pi))
vars.append(variable(name = "MaxEta_jet", title= "max #eta jet", nbins = 5, xmin = 0, xmax = 5))
vars.append(variable(name = "HT_eventHT", title= "event HT", nbins = 20, xmin = 0, xmax = 2000))
# vars.append(variable(name = "run", title= "Run Number", nbins = 5142, xmin = 315251.5, xmax = 320393.5))
vars.append(variable(name = "PV_npvsGood", title= "Number of PV", nbins = 51, xmin = -0.5, xmax = 50.5))

# vars.append(variable(name = "Top_mass", title= "Top mass [GeV]", nbins = 30, xmin = 100, xmax=250))
# vars.append(variable(name = "Top_pt", title= "Top p_{T} [GeV]", nbins = 30, xmin = 100, xmax=1000))

######## 1D variables for histos
vars2D = []

# vars2D.append(variable2D(name = "MinDelta_phiVsHT_eventHT", xname = "MinDelta_phi", yname = "HT_eventHT", xtitle = " min #Delta #phi", ytitle = "event HT", nxbins = 18, xmin = 0, xmax = math.pi,
#                             nybins = 20, ymin = 0, ymax = 2000))


singleLep   = "((nTightElectron == 1 && nVetoElectron == 1 && nTightMuon == 0 && nVetoMuon == 0)||(nTightElectron == 0 && nVetoElectron == 0 && nTightMuon == 1 && nVetoMuon == 1))"
singleMu    = "(nTightElectron == 0 && nVetoElectron == 0 && nTightMuon == 1 && nVetoMuon == 1)"
singleE     = "(nTightElectron == 1 && nVetoElectron == 1 && nTightMuon == 0 && nVetoMuon == 0)"

regions = {
    # "NoCut"                             : nocut,
    # "HEMVeto"                         : hemveto,
    # "HEMVeto_MET_filters"             : hemveto +" && " + met_filters,
    "Presel"                         : "MET_pt>250",
    "AH"                             : "MET_pt>250  && (nVetoMuon+nVetoElectron) == 0 && nJetBtag > 0 && nGoodJet>3",

    "SL"                             : "MET_pt>250  && " + singleLep + " && nJetBtag > 0",
    "SEl"                            : "MET_pt>250  && " + singleE   + " && nJetBtag > 0",
    "SMu"                            : "MET_pt>250  && " + singleMu  + " && nJetBtag > 0",

    "AH1lWR"                         : "MET_pt>250  && " + singleLep + " && nGoodJet>=3 && MT<=140 && nJetBtag == 0",
    "AH1lWREl"                       : "MET_pt>250  && " + singleE   +" && nGoodJet>=3 && MT<=140 && nJetBtag == 0",
    "AH1lWRMu"                       : "MET_pt>250  && " + singleMu  +" && nGoodJet>=3 && MT<=140 && nJetBtag == 0",

    
    # "resolved_1fwjet": "EventTopCategory==3 && nForwardJet>0", 
    # "mixed_1fwjet": "EventTopCategory==2 && nForwardJet>0", 
    # "merged_1fwjet": "EventTopCategory==1 && nForwardJet>0",
    # "resolved_0fwjet": "EventTopCategory==3 && nForwardJet==0", 
    # "mixed_0fwjet": "EventTopCategory==2 && nForwardJet==0", 
    # "merged_0fwjet" : "EventTopCategory==1 && nForwardJet==0",
    # "noTopRegion" : "EventTopCategory==0"
}