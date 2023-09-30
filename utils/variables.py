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

### Definition of requeriments for plots (cut), variables and regions

requirements = "" #"leptonveto && MET_pt>150 && MinDelta_phi>0.6"

vars = []

vars.append(variable(name = "MET_pt", title= "MET p_{T} [GeV]", nbins = 20, xmin = 25, xmax=1025))
#vars.append(variable(name = "PuppiMET_pt", title= "Puppi MET p_{T} [GeV]", nbins = 20, xmin = 25, xmax=1025))
vars.append(variable(name = "PuppiMET_pt", title= "p_{T}^{miss} [GeV]", nbins = 20, xmin = 25, xmax=1025))
vars.append(variable(name = "MET_phi", title= "MET #phi", nbins = 6, xmin = -math.pi, xmax=math.pi))
vars.append(variable(name = "LeadingJet_pt", title= "Leading Jet p_{T} [GeV]", nbins = 30, xmin = 50, xmax=950))
vars.append(variable(name = "nTopHighPt", title= "# Top Candidate Mix", nbins = 80, xmin = -0.5, xmax=80.5))
vars.append(variable(name = "nTopLowPt", title= "# Top Candidate Resolved", nbins = 50, xmin = -0.5, xmax=50.5))
vars.append(variable(name = "nJet", title= "# Jet", nbins = 25, xmin = -0.5, xmax=25.5))
vars.append(variable(name = "nJetBtag", title= "# b-Jet ", nbins = 20, xmin = -0.5, xmax=20.5))
vars.append(variable(name = "nFatJet", title= "# FatJet", nbins = 10, xmin = -0.5, xmax=10.5))
vars.append(variable(name = "MinDelta_phi", title= "min #Delta #phi", nbins = 20, xmin = 0, xmax = math.pi))
vars.append(variable(name = "MaxEta_jet", title= "max #eta jet", nbins = 24, xmin = 0, xmax = 6))
vars.append(variable(name = "HT_eventHT", title= "event HT", nbins = 70, xmin = 0, xmax = 7000))

# vars.append(variable(name = "Top_mass", title= "Top mass [GeV]", nbins = 30, xmin = 100, xmax=250))
# vars.append(variable(name = "Top_pt", title= "Top p_{T} [GeV]", nbins = 30, xmin = 100, xmax=1000))

regions = {
    "all_regions" : "",  #### EventTopCategory!=0 fatto per fare selezione sui dati e comparare con MC18, da rimuovere il taglio qui
    "rA": "MET_pt>200 && MinDelta_phi>0.6 && MinDelta_phi<2.5",
    "rB": "MET_pt>200 && MinDelta_phi>2.5",
    "rC": "MET_pt>200 && MinDelta_phi>0.6 && MinDelta_phi<2.5 && nJetBtag > 0 ",
    "rD": "MET_pt>200 && MinDelta_phi>2.5 && nJetBtag > 0",
    "rE": "MET_pt>200 && MinDelta_phi>0.6 && MinDelta_phi<2.5 && nJetBtag == 0 ",
    "rF": "MET_pt>200 && MinDelta_phi>2.5 && nJetBtag == 0",
    # "rA": "MET_pt>200 && MinDelta_phi>0.6 && MinDelta_phi<2.5 && nJet>3",
    # "rB": "MET_pt>200 && MinDelta_phi>2.5 && nJet>3",
    # "rC": "MET_pt>200 && MinDelta_phi>0.6 && MinDelta_phi<2.5 && nJet<4",
    # "rD": "MET_pt>200 && MinDelta_phi>2.5 && nJet<4",
    
    # "resolved_1fwjet": "EventTopCategory==3 && nForwardJet>0", 
    # "mixed_1fwjet": "EventTopCategory==2 && nForwardJet>0", 
    # "merged_1fwjet": "EventTopCategory==1 && nForwardJet>0",
    # "resolved_0fwjet": "EventTopCategory==3 && nForwardJet==0", 
    # "mixed_0fwjet": "EventTopCategory==2 && nForwardJet==0", 
    # "merged_0fwjet" : "EventTopCategory==1 && nForwardJet==0",
    # "noTopRegion" : "EventTopCategory==0"
}