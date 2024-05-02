#include "ROOT/RDataFrame.hxx"
#include "ROOT/RVec.hxx"
#include "TCanvas.h"
#include "TH1D.h"
#include "TFile.h"
#include "TH2D.h"
#include "TLatex.h"
#include "Math/Vector4D.h"
#include "TStyle.h"
#include <map>

#include "TDavixFile.h"

using namespace ROOT::VecOps;
using RNode = ROOT::RDF::RNode;
using rvec_f = const RVec<float> &;
using rvec_i = const RVec<int> &;
using rvec_b = const RVec<bool> &;
using rvec_rvec_i = const RVec<RVec<int>> &;

const float TopRes_trs=  0.5411276;
const float TopMix_trs=  0.7584613561630249;
const float TopMer_trs=  0.94;
const float dR=  0.8;

const float btagDeepB_mediumWP_2018   = 0.2783;
const float btagPNet_mediumWP_2022    = 0.245 ;
const float btagPNet_mediumWP_2022EE  = 0.2605;


//  Top Resolved threshold {'fpr 10': 0.1334565, 'fpr 5': 0.24193972, 'fpr 1': 0.5411276, 'fpr 01': 0.77197933}
//  Top Mixed threshold {'fpr 10': 0.13067308068275452, 'fpr 5': 0.2957885265350342, 'fpr 1': 0.7584613561630249, 'fpr 01': 0.9129540324211121}

// ########################################################
bool isMC(int SampleFlag){
  if (SampleFlag == 0) return false;
  else return true;
}

// ############### from skimtree_utils

float deltaPhi (float phi1, float phi2){
  float dphi = (phi1-phi2);
  while(dphi >  M_PI) dphi -= 2*M_PI;
  while(dphi < -M_PI) dphi += 2*M_PI;
  return dphi;
}

float deltaR(float eta1, float phi1, float eta2, float phi2){
  return hypot(eta1 - eta2, deltaPhi(phi1, phi2)); 
}

// ########################################################
// ############## Un/Ov flow bin ##########################
// ########################################################

float UnOvBin(float var, int bins, float xmin, float xmax){ 
  float fvar;
  float half_step = ((xmax-xmin)/float(bins))/2.; 

  if(var>=xmax) fvar = xmax-half_step;
  else if(var<=xmin) fvar = xmin+half_step;
  else fvar = var; 

  return fvar;
}

// ########################################################
// ############## TT doublecount ##########################
// ########################################################

bool tt_mtt_doublecounting(rvec_f GenPart_pdgId, rvec_f GenPart_pt, rvec_f GenPart_eta, rvec_f GenPart_phi, rvec_f GenPart_mass){ 
  TLorentzVector top;
  TLorentzVector antitop;
  bool pass = true;
  for(size_t i = 0; i<GenPart_pdgId.size(); i++){
    if(GenPart_pdgId[i]==6){
      top.SetPtEtaPhiM(GenPart_pt[i], GenPart_eta[i], GenPart_phi[i], GenPart_mass[i]);
      
    } else if(GenPart_pdgId[i]==-6){
      antitop.SetPtEtaPhiM(GenPart_pt[i], GenPart_eta[i], GenPart_phi[i], GenPart_mass[i]);
      
    }
  }
  float Mtt = (top+antitop).M();
  if(Mtt>=700){
    pass = false;
  }
  return pass;
}

// ########################################################
// ############## HEMVeto 2018 ############################
// ########################################################

bool hemveto(rvec_f Jet_eta, rvec_f Jet_phi, rvec_f Electron_eta, rvec_f Electron_phi){
  float hemvetoetaup = -3.05;
  float hemvetoetadown = -1.35;
  float hemvetophiup = -1.62;
  float hemvetophidown = -0.82;
  bool passesMETHEMVeto = true;

  for(size_t i = 0; i < Jet_eta.size(); i++){
    if(Jet_eta[i]>hemvetoetaup && Jet_eta[i]<hemvetoetadown && Jet_phi[i]>hemvetophiup && Jet_phi[i]<hemvetophidown){
      passesMETHEMVeto = false;
    }
  }
  for(size_t i = 0; i < Electron_eta.size(); i++){
    if(Electron_eta[i]>hemvetoetaup && Electron_eta[i]<hemvetoetadown && Electron_phi[i]>hemvetophiup && Electron_phi[i]<hemvetophidown){
      passesMETHEMVeto = false;
    }
  }
  return passesMETHEMVeto; 
}

int w_nominalhemveto(float w_nominal, bool HEMVeto, int year){
  int w_nominal_update = w_nominal;
  if (HEMVeto == false and year == 2018){
    // w_nominal_update = w_nominal * 0.354; //da controllare questo parametro che dipende da quanti dati giriamo
    // w_nominal_update = w_nominal * 0.932;
    w_nominal_update = w_nominal * 0; // se giro solo eraD
  }
  return w_nominal_update;
}

// ########################################################
// ############## Filter and Define #######################
// ########################################################

RVec<int> GetGoodElectron(rvec_f Electron_pt, rvec_f Electron_eta, rvec_i Electron_mvaFall17V2Iso_WPL, rvec_f Electron_miniPFRelIso_all)
{
  RVec<int> ids;
  for(int i = 0; i<Electron_pt.size(); i++)
  {
      if (Electron_pt[i]>35 && abs(Electron_eta[i]) < 2.5 && Electron_mvaFall17V2Iso_WPL[i] == 1 && abs(Electron_miniPFRelIso_all[i]) < 0.1)
      {
        ids.emplace_back(i);
      }
  }
  return ids;
}

RVec<int> GetGoodMuon(rvec_f Muon_pt, rvec_f Muon_eta, rvec_i Muon_tightId, rvec_f Muon_miniPFRelIso_all)
{
  RVec<int> ids;
  for(int i = 0; i<Muon_pt.size(); i++)
  {
      if (Muon_pt[i] > 30 && abs(Muon_eta[i]) < 2.4 && Muon_tightId[i] == 1 && abs(Muon_miniPFRelIso_all[i]) < 0.1)
      {
        ids.emplace_back(i);
      }
  }
  return ids;
}

RVec<int> GetGoodJet(rvec_f Jet_pt, rvec_i Jet_jetId)
{
  RVec<int> ids;
  for(int i = 0; i<Jet_pt.size(); i++)
  {
      if (Jet_pt[i]>25 && Jet_jetId[i]>0)
      {
        ids.emplace_back(i);
      }
  }
  return ids;
}

RVec<int> GetJetBTag(rvec_i GoodJet, rvec_f Jet_btagDeepB, int year, bool EE){
    RVec<int> ids;
    float bthres;
    if(year == 2018){
        bthres = btagDeepB_mediumWP_2018;
    }else if(year == 2022){
        if(EE){
            bthres = btagPNet_mediumWP_2022EE;
        }
        else{
            bthres = btagPNet_mediumWP_2022;
        }
    }
    
    for(int i = 0; i<GoodJet.size(); i++)
    {
        if (Jet_btagDeepB[GoodJet[i]]>bthres)
        {
            ids.emplace_back(i);
        }
    }
    return ids;
}

bool atLeast1GoodLep(rvec_i GoodMu_idx, rvec_i GoodEl_idx){
    if ((GoodMu_idx.size() + GoodEl_idx.size())>=1) return true;
    else return false;
}

// ########################################################
// ###########Alternative Truth definition ################
// ########################################################

//  Alternative truth definition
RVec<int> get_pos_nums(int num) 
{
    RVec<int> pos_nums;
    while (num != 0) {
        if (num % 10 != 0) pos_nums.emplace_back(num % 10);
        num = num / 10;
    }
    return pos_nums;
}

RVec<int> SetDifference(rvec_i v2, rvec_i v1) 
{
  RVec<int> diff;
  for (int i = 0; i < v2.size(); i++) {
    if (std::find(v1.begin(), v1.end(), v2[i]) == v1.end()) {
      diff.emplace_back(v2[i]);
    }
  }
  return diff;
}

RVec<int> UniqueFlavList(int idxJet0, int idxJet1, int idxJet2) 
{
  RVec<int> common_element = Intersect(get_pos_nums(idxJet0), get_pos_nums(idxJet1));
  RVec<int> tmp_ = SetDifference(get_pos_nums(idxJet1), common_element);
  RVec<int> jetflavs_list_ = Concatenate(get_pos_nums(idxJet0), tmp_);
  RVec<int> common_element_ = Intersect(jetflavs_list_, get_pos_nums(idxJet2));
  RVec<int> tmp__ = SetDifference(get_pos_nums(idxJet2), common_element_);
  RVec<int> jetflavs_list = Concatenate(jetflavs_list_, tmp__); 
    
  return jetflavs_list;
}

int truth_2(int idxJet0, int idxJet1, int idxJet2, int idxFatJet, rvec_i Jet_matched, rvec_i Jet_topMother, rvec_i Jet_pdgId, rvec_i FatJet_matched, rvec_i FatJet_topMother, rvec_i FatJet_pdgId) 
{
    int top_truth = 0;
    RVec<int> jetflavs_list;
    RVec<int> fatjetflavs_list;

    if (idxJet2==-1) 
    {
        int matchedJets = 0;
        if (Jet_matched[idxJet0] > 0) matchedJets++;
        if (Jet_matched[idxJet1] > 0) matchedJets++;

        if ( matchedJets >=2 && FatJet_matched[idxFatJet] > 0 && (FatJet_topMother[idxFatJet] == Jet_topMother[idxJet1] && FatJet_topMother[idxFatJet] == Jet_topMother[idxJet0])) 
        {
          RVec<int> common_element = Intersect(get_pos_nums(Jet_pdgId[idxJet0]), get_pos_nums(Jet_pdgId[idxJet1]));
          RVec<int> tmp_ = SetDifference(get_pos_nums(Jet_pdgId[idxJet1]), common_element);
          jetflavs_list = Concatenate(get_pos_nums(Jet_pdgId[idxJet0]), tmp_);
          fatjetflavs_list = get_pos_nums(FatJet_pdgId[idxFatJet]);
        }
    } else {
      if (idxFatJet != -1) {
        int matchedJets = 0;
        if (Jet_matched[idxJet0] > 0) matchedJets++;
        if (Jet_matched[idxJet1] > 0) matchedJets++;
        if (Jet_matched[idxJet2] > 0) matchedJets++;

        if (matchedJets >= 2 && FatJet_matched[idxFatJet] > 0 && (Jet_topMother[idxJet0] == Jet_topMother[idxJet1] || Jet_topMother[idxJet0] == Jet_topMother[idxJet2] || Jet_topMother[idxJet1] == Jet_topMother[idxJet2]) && (Jet_topMother[idxJet0] == FatJet_topMother[idxFatJet] || Jet_topMother[idxJet1] == FatJet_topMother[idxFatJet] || Jet_topMother[idxJet2] == FatJet_topMother[idxFatJet])) 
        {
          jetflavs_list = UniqueFlavList(Jet_pdgId[idxJet0], Jet_pdgId[idxJet1], Jet_pdgId[idxJet2]);
          fatjetflavs_list = get_pos_nums(FatJet_pdgId[idxFatJet]);
        }
        }else 
        {
          // cout<<"3j0fj"<<endl;
          int matchedJets = 0;
          if (Jet_matched[idxJet0] > 0) matchedJets++;
          if (Jet_matched[idxJet1] > 0) matchedJets++;
          if (Jet_matched[idxJet2] > 0) matchedJets++;
          if (matchedJets>=2 && (Jet_topMother[idxJet0] == Jet_topMother[idxJet1] || Jet_topMother[idxJet1] == Jet_topMother[idxJet2] || Jet_topMother[idxJet0] == Jet_topMother[idxJet2])) 
          {
            jetflavs_list = UniqueFlavList(Jet_pdgId[idxJet0], Jet_pdgId[idxJet1], Jet_pdgId[idxJet2]);
            RVec<int> fatjetflavs_list {};
          }          
        }
    }

    if (jetflavs_list.size() >= 2 || fatjetflavs_list.size() >= 2) 
    {
      top_truth = 1;
    } else 
    {
      RVec<int> flavs_list = Intersect(jetflavs_list, fatjetflavs_list);
      if (flavs_list.size() >= 2) {
          top_truth = 1;
      } else {
          top_truth = 0;
      }
    }

    return top_truth;
}

int truth_1(int idxJet0, int idxJet1, int idxJet2, int idxFatJet, rvec_i Jet_matched, rvec_i Jet_topMother, rvec_i Jet_pdgId, rvec_i FatJet_matched, rvec_i FatJet_topMother, rvec_i FatJet_pdgId) 
{
    int top_truth = 0;
    RVec<int> jetflavs_list;
    RVec<int> fatjetflavs_list;

    if (idxJet2==-1) 
    {
        int matchedJets = 0;
        if (Jet_matched[idxJet0] > 0) matchedJets++;
        if (Jet_matched[idxJet1] > 0) matchedJets++;

        if ( matchedJets >=1 && FatJet_matched[idxFatJet] > 0 && (FatJet_topMother[idxFatJet] == Jet_topMother[idxJet1] || FatJet_topMother[idxFatJet] == Jet_topMother[idxJet0])) 
        {
          RVec<int> common_element = Intersect(get_pos_nums(Jet_pdgId[idxJet0]), get_pos_nums(Jet_pdgId[idxJet1]));
          RVec<int> tmp_ = SetDifference(get_pos_nums(Jet_pdgId[idxJet1]), common_element);
          jetflavs_list = Concatenate(get_pos_nums(Jet_pdgId[idxJet0]), tmp_);
          fatjetflavs_list = get_pos_nums(FatJet_pdgId[idxFatJet]);
        }
    } else {
      if (idxFatJet != -1) {
        int matchedJets = 0;
        if (Jet_matched[idxJet0] > 0) matchedJets++;
        if (Jet_matched[idxJet1] > 0) matchedJets++;
        if (Jet_matched[idxJet2] > 0) matchedJets++;

        if (matchedJets >= 1 && FatJet_matched[idxFatJet] > 0 && (Jet_topMother[idxJet0] == FatJet_topMother[idxFatJet] || Jet_topMother[idxJet1] == FatJet_topMother[idxFatJet] || Jet_topMother[idxJet2] == FatJet_topMother[idxFatJet])) 
        {
          jetflavs_list = UniqueFlavList(Jet_pdgId[idxJet0], Jet_pdgId[idxJet1], Jet_pdgId[idxJet2]);
          fatjetflavs_list = get_pos_nums(FatJet_pdgId[idxFatJet]);
        }
        }else 
        {
          int matchedJets = 0;
          if (Jet_matched[idxJet0] > 0) matchedJets++;
          if (Jet_matched[idxJet1] > 0) matchedJets++;
          if (Jet_matched[idxJet2] > 0) matchedJets++;
          if (matchedJets>=1) 
          {
            jetflavs_list = UniqueFlavList(Jet_pdgId[idxJet0], Jet_pdgId[idxJet1], Jet_pdgId[idxJet2]);  
            RVec<int> fatjetflavs_list {};
          }          
        }
    }

    if (jetflavs_list.size() >= 1 || fatjetflavs_list.size() >= 1) 
    {
      top_truth = 1;
    } else 
    {
      RVec<int> flavs_list = Intersect(jetflavs_list, fatjetflavs_list);
      if (flavs_list.size() >= 1) {
          top_truth = 1;
      } else {
          top_truth = 0;
      }
    }

    return top_truth;
}

RVec<int> CalculateToptruth2(rvec_i TopMixed_idxJet0, rvec_i TopMixed_idxJet1, rvec_i TopMixed_idxJet2, rvec_i TopMixed_idxFatJet, rvec_i Jet_matched, rvec_i Jet_topMother, rvec_i Jet_pdgId, rvec_i FatJet_matched, rvec_i FatJet_topMother, rvec_i FatJet_pdgId)
{
  RVec<int> TopMixed_truth;
  RVec<int> idxFatJet;
  if(TopMixed_idxFatJet.size()==0) 
  {
    RVec<int> tmp;
    for(int i = 0; i < TopMixed_idxJet0.size(); i++)
    {
      tmp.emplace_back(-1);
    }
    idxFatJet = tmp;
  }else
  {
    idxFatJet = TopMixed_idxFatJet;
  }
  for (int i = 0; i < TopMixed_idxJet0.size(); i++)
  {
    TopMixed_truth.emplace_back(truth_2(TopMixed_idxJet0[i], TopMixed_idxJet1[i], TopMixed_idxJet2[i], idxFatJet[i], Jet_matched, Jet_topMother, Jet_pdgId, FatJet_matched, FatJet_topMother, FatJet_pdgId));
  }
  return TopMixed_truth;
}

RVec<int> CalculateToptruth1(rvec_i TopMixed_idxJet0, rvec_i TopMixed_idxJet1, rvec_i TopMixed_idxJet2, rvec_i TopMixed_idxFatJet, rvec_i Jet_matched, rvec_i Jet_topMother, rvec_i Jet_pdgId, rvec_i FatJet_matched, rvec_i FatJet_topMother, rvec_i FatJet_pdgId)
{
  RVec<int> TopMixed_truth;
  RVec<int> idxFatJet;
  if(TopMixed_idxFatJet.size()==0) 
  {
    RVec<int> tmp;
    for(int i = 0; i < TopMixed_idxJet0.size(); i++)
    {
      tmp.emplace_back(-1);
    }
    idxFatJet = tmp;
  }else
  {
    idxFatJet = TopMixed_idxFatJet;
  }
  for (int i = 0; i < TopMixed_idxJet0.size(); i++)
  {
    TopMixed_truth.emplace_back(truth_1(TopMixed_idxJet0[i], TopMixed_idxJet1[i], TopMixed_idxJet2[i], idxFatJet[i], Jet_matched, Jet_topMother, Jet_pdgId, FatJet_matched, FatJet_topMother, FatJet_pdgId));
  }
  return TopMixed_truth;
}

// ############## TopSelection ############################

// Leptonic
RVec<int> countTopLep(rvec_i GoodMu_idx, rvec_f Muon_eta, rvec_f Muon_phi, rvec_i GoodEl_idx, rvec_f Electron_eta, rvec_f Electron_phi, rvec_i JetBTag_idx, rvec_f Jet_eta, rvec_f Jet_phi)
{
  // return deltaR(Jet_eta[JetBTag_idx[0]], Jet_phi[JetBTag_idx[0]], Electron_eta[GoodEl_idx[0]], Electron_phi[GoodEl_idx[0]]);
  RVec<int> b;
  for(int i=0; i < JetBTag_idx.size(); i++)
  {
    bool alreadycounted = false;
    for(int e=0; e < GoodEl_idx.size(); e++)
    {
      if(deltaR(Jet_eta[JetBTag_idx[i]], Jet_phi[JetBTag_idx[i]], Electron_eta[GoodEl_idx[e]], Electron_phi[GoodEl_idx[e]]) < 2.) 
      {
        b.emplace_back(JetBTag_idx[i]);
        alreadycounted = true;
      }
      if(alreadycounted) 
      {
          break;
      }
    }
    if(!alreadycounted)
    {
        for(int m=0; m < GoodMu_idx.size(); m++)
        {
          if(deltaR(Jet_eta[JetBTag_idx[i]], Jet_phi[JetBTag_idx[i]], Muon_eta[GoodMu_idx[m]], Muon_phi[GoodMu_idx[m]]) < 2.) 
          {
            b.emplace_back(JetBTag_idx[i]);
            alreadycounted = true;
          }
          if(alreadycounted) 
          {
              break;
          }
        }
    }
  }
  return b;
}

RVec<float> drBLep(rvec_i GoodMu_idx, rvec_f Muon_eta, rvec_f Muon_phi, rvec_i GoodEl_idx, rvec_f Electron_eta, rvec_f Electron_phi, rvec_i JetBTag_idx, rvec_f Jet_eta, rvec_f Jet_phi)
{
  // return deltaR(Jet_eta[JetBTag_idx[0]], Jet_phi[JetBTag_idx[0]], Electron_eta[GoodEl_idx[0]], Electron_phi[GoodEl_idx[0]]);
  RVec<float> b;
  for(int i=0; i < JetBTag_idx.size(); i++)
  {
    bool alreadycounted = false;
    for(int e=0; e < GoodEl_idx.size(); e++)
    {
      if(deltaR(Jet_eta[JetBTag_idx[i]], Jet_phi[JetBTag_idx[i]], Electron_eta[GoodEl_idx[e]], Electron_phi[GoodEl_idx[e]]) < 2.) 
      {
        b.emplace_back(deltaR(Jet_eta[JetBTag_idx[i]], Jet_phi[JetBTag_idx[i]], Electron_eta[GoodEl_idx[e]], Electron_phi[GoodEl_idx[e]]));
        alreadycounted = true;
      }
      if(alreadycounted) 
      {
          break;
      }
    }
    if(!alreadycounted)
    {
        for(int m=0; m < GoodMu_idx.size(); m++)
        {
          if(deltaR(Jet_eta[JetBTag_idx[i]], Jet_phi[JetBTag_idx[i]], Muon_eta[GoodMu_idx[m]], Muon_phi[GoodMu_idx[m]]) < 2.) 
          {
            b.emplace_back(deltaR(Jet_eta[JetBTag_idx[i]], Jet_phi[JetBTag_idx[i]], Muon_eta[GoodMu_idx[m]], Muon_phi[GoodMu_idx[m]]));
            alreadycounted = true;
          }
          if(alreadycounted) 
          {
              break;
          }
        }
    }
  }
  return b;
}

int nearest(rvec_i GoodTopLepBJet_idx, rvec_f GoodTopLepBJet_dr)
{
    int idx = -1000;
    if(GoodTopLepBJet_dr.size()>0)
    {
        int i = ArgMin(GoodTopLepBJet_dr);
        idx = GoodTopLepBJet_idx[i];
    }        
    return idx;
}

int BJetTopLep_MCtag(rvec_i Jet_matched, rvec_i Jet_pdgId, rvec_i Jet_topMother, int BJetTopLep)
{
    int t = 0, tbar = 0;
    int tagged = 0;
    for(int i = 0; i< Jet_topMother.size(); i++)
    {
      if(Jet_topMother[i] == 6)  t +=1;
      if(Jet_topMother[i] == -6) tbar +=1;
    }
    if(Jet_matched[BJetTopLep] == 1 && Jet_pdgId[BJetTopLep] == 5 && ((t==1 && Jet_topMother[BJetTopLep]==6)||(tbar==1 && Jet_topMother[BJetTopLep]==-6)))
    {
      tagged = 1;
    }
    return tagged;
}

//Hadronic

// Top Merged, FatJet over threshold of particleNet_TvsQCD
RVec<int> select_TopMer(rvec_f FatJet_particleNet_TvsQCD)
{
  RVec<int> ids;
  for (int i = 0; i < FatJet_particleNet_TvsQCD.size(); i++)
  {
  	if(FatJet_particleNet_TvsQCD[i]>TopMer_trs){
      ids.emplace_back(i);
	  }
  }
  return ids;
}

bool check_same_top(int idx_fj_1, int idx_j0_1, int idx_j1_1, int idx_j2_1, int idx_fj_2, int idx_j0_2, int idx_j1_2, int idx_j2_2)
{
  std::vector<int> list_1 = {idx_j0_1, idx_j1_1, idx_j2_1};
  std::vector<int> list_2 = {idx_j0_2, idx_j1_2, idx_j2_2};
  
  // Remove elements equal to -1
  list_1.erase(std::remove(list_1.begin(), list_1.end(), -1), list_1.end());
  list_2.erase(std::remove(list_2.begin(), list_2.end(), -1), list_2.end());
  
  std::set<int> set_1(list_1.begin(), list_1.end());
  std::set<int> set_2(list_2.begin(), list_2.end());
  
  std::set<int> intersection;
  std::set_intersection(set_1.begin(), set_1.end(), set_2.begin(), set_2.end(), std::inserter(intersection, intersection.begin()));
  
  bool check_jets = !intersection.empty();

  bool check_fj = (idx_fj_1 == idx_fj_2)||(idx_fj_1 == -1 || idx_fj_2 == -1);
  
  return check_jets || check_fj;
}

bool check_same_top_type2(int idx_fj_1, int idx_j0_1, int idx_j1_1, int idx_j2_1, int idx_fj_2, int idx_j0_2, int idx_j1_2, int idx_j2_2)
{
  std::vector<int> list_1 = {idx_j0_1, idx_j1_1, idx_j2_1};
  std::vector<int> list_2 = {idx_j0_2, idx_j1_2, idx_j2_2};
  
  // Remove elements equal to -1
  list_1.erase(std::remove(list_1.begin(), list_1.end(), -1), list_1.end());
  list_2.erase(std::remove(list_2.begin(), list_2.end(), -1), list_2.end());
  
  std::set<int> set_1(list_1.begin(), list_1.end());
  std::set<int> set_2(list_2.begin(), list_2.end());
  
  std::set<int> intersection;
  std::set_intersection(set_1.begin(), set_1.end(), set_2.begin(), set_2.end(), std::inserter(intersection, intersection.begin()));
  
  int check_common_elements = intersection.size();
  // bool check_fj_p1 = (idx_fj_1 == -1 && idx_fj_2 != -1) || (idx_fj_1 != -1 && idx_fj_2 == -1);
  bool common_fatjet = (idx_fj_1 == idx_fj_2) && (idx_fj_1 != -1 && idx_fj_2 != -1);
  // se hanno il fatjet in comune ma che non sia per entrambi -1 
  bool sametop = true;
  if (check_common_elements==0 || (check_common_elements==1 && !common_fatjet)) sametop = false;
  return sametop;   
}

// Top Mixed, candidates over threshold of TopScore and candidates not overlapping (do not share any abject)
RVec<int> select_TopMix(rvec_f TopMixed_TopScore, rvec_f TopMixed_idxFatJet, rvec_f TopMixed_idxJet0, rvec_f TopMixed_idxJet1, rvec_f TopMixed_idxJet2)
{
  RVec<int> ids;
  RVec<float> scores;
  RVec<float> ids_selected;

  for (int i = 0; i < TopMixed_TopScore.size(); i++)
  {
  	if(TopMixed_TopScore[i]>TopMix_trs)
    {
      ids.emplace_back(i);
	    scores.emplace_back(TopMixed_TopScore[i]);
	  }
  }
  const RVec<int> scores_indices_ = Argsort(scores);
  RVec<int> scores_indices = Reverse(scores_indices_);
  RVec<int> ids_sorted = Take(ids, scores_indices);
  RVec<float> scores_sorted = Take(scores, scores_indices);
  
  for(int i = 0; i < ids_sorted.size(); i++)
  {
    if(i==0)
    {
      ids_selected.emplace_back(ids_sorted[i]);
    }
    else 
    {
      bool same_top = false;
      int bestTop_idx = 0;
      while(!same_top and bestTop_idx < ids_selected.size())
      {
        same_top = check_same_top(TopMixed_idxFatJet[ids_sorted[i]], TopMixed_idxJet0[ids_sorted[i]], TopMixed_idxJet1[ids_sorted[i]], TopMixed_idxJet2[ids_sorted[i]], TopMixed_idxFatJet[ids_sorted[bestTop_idx]], TopMixed_idxJet0[ids_sorted[bestTop_idx]], TopMixed_idxJet1[ids_sorted[bestTop_idx]], TopMixed_idxJet2[ids_sorted[bestTop_idx]]);
        bestTop_idx += 1;
      }
      if(!same_top)
      {
        ids_selected.emplace_back(ids_sorted[i]);
      }
    }

  }
  return ids_selected;
}

RVec<int> select_TopRes(rvec_f TopResolved_TopScore, rvec_f TopResolved_idxJet0, rvec_f TopResolved_idxJet1, rvec_f TopResolved_idxJet2)
{
  RVec<int> ids;
  RVec<float> scores;
  RVec<int> ids_selected;
  for (int i = 0; i < TopResolved_TopScore.size(); i++)
  {
	  if(TopResolved_TopScore[i]>TopRes_trs)
    {
	    ids.emplace_back(i);
	    scores.emplace_back(TopResolved_TopScore[i]);
	  }
  }
  const RVec<int> scores_indices_ = Argsort(scores);
  RVec<int> scores_indices = Reverse(scores_indices_);
  RVec<int> ids_sorted = Take(ids, scores_indices);
  RVec<float> scores_sorted = Take(scores, scores_indices);

  for(int i = 0; i < ids_sorted.size(); i++)
  {
    if(i==0)
    {
      ids_selected.emplace_back(ids_sorted[i]);
    }
    else 
    {
      bool same_top = false;
      int bestTop_idx = 0;
      while(!same_top and bestTop_idx < ids_selected.size())
      {
        same_top = check_same_top(-1, TopResolved_idxJet0[ids_sorted[i]], TopResolved_idxJet1[ids_sorted[i]], TopResolved_idxJet2[ids_sorted[i]], -1, TopResolved_idxJet0[ids_sorted[bestTop_idx]], TopResolved_idxJet1[ids_sorted[bestTop_idx]], TopResolved_idxJet2[ids_sorted[bestTop_idx]]);
        bestTop_idx += 1;
      }
      if(!same_top)
      {
        ids_selected.emplace_back(ids_sorted[i]);
      }
    }

  }
  return ids_selected;
}

Int_t nTop(rvec_i ids)
{
  return ids.size();
}

Int_t select_TopCategory(rvec_i GoodTopMer_idx, rvec_i GoodTopMix_idx, rvec_i GoodTopRes_idx)
{
  //return:  1- Event Resolved, 2- Event Mixed, 3- Event Merged, 4- Event Nothing, ...

  int nRes = GoodTopRes_idx.size();
  int nMix = GoodTopMix_idx.size();
  int nMer = GoodTopMer_idx.size();
  
  if (nRes==1 && nMix==0 && nMer==0){
    return 1;
  }
  else if (nRes<=1 && nMix==1 && nMer==0){
    return 2;
  }
  else if (nRes==0 && nMix<=1 && nMer==1){
    return 3;
  }
  else return 4;
}

Int_t select_bestTop(int EventTopCategory, rvec_f FatJet_particleNet_TvsQCD, rvec_f TopMixed_TopScore, rvec_f TopResolved_TopScore){
  //RVec<int> topselect ;
  //int bestTop_idx;
  RVec<float> scores;
  int idx;
  if (EventTopCategory==3){ 
    //topselect = GoodTopMer_idx;
    for(int i = 0; i < FatJet_particleNet_TvsQCD.size(); i++)
    {
      scores.emplace_back(FatJet_particleNet_TvsQCD[i]);
    }
    idx = ArgMax(scores);
  }
  else if (EventTopCategory==2){
    for(int i = 0; i < TopMixed_TopScore.size(); i++)
    {
      scores.emplace_back(TopMixed_TopScore[i]);
    }
    idx = ArgMax(scores); 
  }
  else if (EventTopCategory==1){ 
    for(int i = 0; i < TopResolved_TopScore.size(); i++)
    {
      scores.emplace_back(TopResolved_TopScore[i]);
    } 
    idx = ArgMax(scores);
  }
  else idx = -1;

  return idx;
}

Float_t select_TopVar(Int_t EventTopCategory, Int_t Top_idx, rvec_f FatJet_pt, rvec_f TopMixed_pt, rvec_f TopResolved_pt)
{
  if (EventTopCategory==1) return TopResolved_pt[Top_idx];
  else if (EventTopCategory==2) return TopMixed_pt[Top_idx];
  else if (EventTopCategory==3) return FatJet_pt[Top_idx];
  else return -1000;
}

// ########################################################
// ############## TopClusters  ############################
// ########################################################
// NB: queste funzioni vanno debuggate

// return the list of indices of tops that share the same objects, at least 1 (fatjet and/or jets)
// this is our definition of top cluster
// To be clear, we define clusters starting from the best Top (best Top = Top with highest score),
// then we collect all the tops that share object with the fist one, and so on

// utiliziamo il fatto che posso storare una lista di liste in RDataFrame e poi raggiungere tutti gli elementi

RVec<RVec<int>> findTopClustersType1(rvec_f TopMixed_TopScore, rvec_f TopMixed_idxFatJet, rvec_f TopMixed_idxJet0, rvec_f TopMixed_idxJet1, rvec_f TopMixed_idxJet2, int bjetTopLep)
{
  RVec<int> idxFatJet;
  if (TopMixed_idxFatJet.size() != TopMixed_TopScore.size())
  {
    RVec<int> tmp_idx;
    for(int i = 0; i < TopMixed_TopScore.size(); i++)
    {
      tmp_idx.emplace_back(-1);
    }
    idxFatJet = tmp_idx;
  }
  else{idxFatJet = idxFatJet;}

  RVec<RVec<int>> clusters;
  RVec<int> tmp;
  RVec<float> scores;
  for(int i = 0; i < TopMixed_TopScore.size(); i++)
    {
      if(TopMixed_idxJet0[i] != bjetTopLep && TopMixed_idxJet1[i] != bjetTopLep && TopMixed_idxJet2[i] != bjetTopLep)
      {
          tmp.emplace_back(i);
          scores.emplace_back(TopMixed_TopScore[i]);
      }
    }
  const RVec<int> scores_indices_ = Argsort(scores);
  RVec<int> scores_indices = Reverse(scores_indices_);
    
  RVec<int> ids_sorted = Take(tmp, scores_indices);

  // ids_sorted is the list of indices of tops sorted by score we need to loop
  RVec<int> survived_top = ids_sorted;
  while(survived_top.size()!=0)
    {
      int fixedtop = survived_top[0];
      RVec<int> cluster;
      cluster.emplace_back(fixedtop);
      RVec<int> tokeep;
      for(int i = 1; i < survived_top.size(); i++)
      {
        if(check_same_top(idxFatJet[fixedtop], TopMixed_idxJet0[fixedtop], TopMixed_idxJet1[fixedtop], TopMixed_idxJet2[fixedtop], idxFatJet[survived_top[i]], TopMixed_idxJet0[survived_top[i]], TopMixed_idxJet1[survived_top[i]], TopMixed_idxJet2[survived_top[i]]))
        {
          cluster.emplace_back(survived_top[i]);
        }
        else
        {
          tokeep.emplace_back(i);
        }
      }
      survived_top = Take(survived_top, tokeep);
      clusters.emplace_back(cluster);
    }
  return clusters;
}

// return the list of indices of tops that share the same objects, at least 2 (fatjet and/or jets)
// this is our definition of top cluster
// To be clear, we define clusters starting from the best Top (best Top = Top with highest score),
// then we collect all the tops that share object with the fist one, and so on

// utiliziamo il fatto che posso storare una lista di liste in RDataFrame e poi raggiungere tutti gli elementi

RVec<RVec<int>> findTopClustersType2(rvec_f TopMixed_TopScore, rvec_f TopMixed_idxFatJet, rvec_f TopMixed_idxJet0, rvec_f TopMixed_idxJet1, rvec_f TopMixed_idxJet2, int bjetTopLep)
{
  RVec<int> idxFatJet;
  if (TopMixed_idxFatJet.size() != TopMixed_TopScore.size())
  {
    RVec<int> tmp_idx;
    for(int i = 0; i < TopMixed_TopScore.size(); i++)
    {
      tmp_idx.emplace_back(-1);
    }
    idxFatJet = tmp_idx;
  }
  else{idxFatJet = idxFatJet;}
  
    RVec<RVec<int>> clusters;
  RVec<int> tmp;
  RVec<float> scores;
  for(int i = 0; i < TopMixed_TopScore.size(); i++)
    {
      if(TopMixed_idxJet0[i] != bjetTopLep && TopMixed_idxJet1[i] != bjetTopLep && TopMixed_idxJet2[i] != bjetTopLep)
      {
          tmp.emplace_back(i);
          scores.emplace_back(TopMixed_TopScore[i]);
      }
    }
  const RVec<int> scores_indices_ = Argsort(scores);
  RVec<int> scores_indices = Reverse(scores_indices_);
    
  RVec<int> ids_sorted = Take(tmp, scores_indices);
    
  // ids_sorted is the list of indices of tops sorted by score we need to loop
  RVec<int> survived_top = ids_sorted;
  while(survived_top.size()!=0)
    {
      int fixedtop = survived_top[0];
      RVec<int> cluster;
      cluster.emplace_back(fixedtop);
      RVec<int> tokeep;
      for(int i = 1; i < survived_top.size(); i++)
      {
        if(check_same_top_type2(idxFatJet[fixedtop], TopMixed_idxJet0[fixedtop], TopMixed_idxJet1[fixedtop], TopMixed_idxJet2[fixedtop], idxFatJet[survived_top[i]], TopMixed_idxJet0[survived_top[i]], TopMixed_idxJet1[survived_top[i]], TopMixed_idxJet2[survived_top[i]]))
        {
          cluster.emplace_back(survived_top[i]);
        }
        else
        {
          tokeep.emplace_back(i);
        }
      }
      survived_top = Take(survived_top, tokeep);
      clusters.emplace_back(cluster);
    }
  return clusters;
}

// return a bool that is true if one of the tops in the cluster is tagged as real top
RVec<int> MCTaggedTopCluster(rvec_rvec_i topcluster, rvec_i TopMixed_truth)
{
  RVec<int> tagged;
  for (int i = 0; i < topcluster.size(); i++)
  {
    int flag = 0;
    for(int j = 0; j < topcluster[i].size(); j++)
    {
      if (TopMixed_truth[topcluster[i][j]]){ flag =1; }
    }
    if (flag){tagged.emplace_back(1);}
    else{tagged.emplace_back(0);}
  }
  if(topcluster.size()==0){tagged.emplace_back(-1);}
  return tagged;
}

// return a bool that is true if one of the tops in the cluster is selected as top
RVec<int> RecoTaggedTopClusterMixed(rvec_rvec_i topcluster, rvec_f TopMixed_TopScore)
{
  RVec<int> tagged;

  for (int i = 0; i < topcluster.size(); i++)
  {
    int flag = 0;
    for(int j = 0; j < topcluster[i].size(); j++)
    {
      if (TopMixed_TopScore[topcluster[i][j]] >= TopMix_trs){flag +=1;}
    }
    tagged.emplace_back(flag);
  }
  if(topcluster.size()==0){tagged.emplace_back(-1);}
  return tagged;
}
RVec<int> RecoTaggedTopClusterResolved(rvec_rvec_i topcluster, rvec_f TopResolved_TopScore)
{
  RVec<int> tagged;

  for (int i = 0; i < topcluster.size(); i++)
  {
    int flag = 0;
    for(int j = 0; j < topcluster[i].size(); j++)
    {
      if (TopResolved_TopScore[topcluster[i][j]] >= TopRes_trs)
      {
        flag =1;
      }
    }
    if (flag){tagged.emplace_back(1);}
    else{tagged.emplace_back(0);}
  }
  if(topcluster.size()==0){tagged.emplace_back(-1);}
  return tagged;
}

// ########################################################
// ##############   TopUtils   ############################
// ########################################################
Int_t select_TopCategoryWithTruth(int EventTopCategory, rvec_i FatJet_matched, rvec_i GoodTopMer_idx, rvec_i TopMixed_truth, rvec_i GoodTopMix_idx, rvec_i TopResolved_truth, rvec_i GoodTopRes_idx)
{
  int category;
  if(EventTopCategory==1)
  {
    for(int i = 0; i < GoodTopRes_idx.size(); i++)
    {
      if (TopResolved_truth[GoodTopRes_idx[i]]==1) 
      {
        category = 1;
      }
    }
  }
  else if(EventTopCategory==2)
  {
    for(int i = 0; i < GoodTopMix_idx.size(); i++)
    {
      if (TopMixed_truth[GoodTopMix_idx[i]]==1)
      {
        category = 2;
      } 
    }
  }
  else if(EventTopCategory==3)
  {
    for(int i = 0; i < GoodTopMer_idx.size(); i++)
    {
      if (FatJet_matched[GoodTopMer_idx[i]]==3)
      {
        category = 3;
      } 
    }
  }
  else if (EventTopCategory==4) 
  {
    for(int i = 0; i < GoodTopRes_idx.size(); i++)
    {
      if (TopResolved_truth[GoodTopRes_idx[i]]==1)
      {
        category = 4;
      } 
    }
    for(int i = 0; i < GoodTopMix_idx.size(); i++)
    {
      if (TopMixed_truth[GoodTopMix_idx[i]]==1)
      {
        category = 4;
      } 
    }
    for(int i = 0; i < GoodTopMer_idx.size(); i++)
    {
      if (FatJet_matched[GoodTopMer_idx[i]]==3)
      {
        category = 4;
      } 
    }
  }
  else
  {
    category = -1;
  }
  return category;
}