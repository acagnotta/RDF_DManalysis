//#ifndef POST_H
//#define POST_H

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

const float TopRes_minpt=  0.;
const float TopRes_maxpt=  300.;
const float TopMix_minpt=  300.;
const float TopMix_maxpt=  500.;
const float TopMer_minpt=  500.;
const float TopMer_maxpt=  10000.;
const float TopRes_trs=  0.5411276;
const float TopMix_trs=  0.39578277;
const float TopMer_trs=  0.99;
const float dR=  0.8;
const float btag_mediumWP = 0.2783;

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

// -------------> 2018 data HEM
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
int w_nominalhemveto(float w_nominal, bool HEMVeto){
  int w_nominal_update = w_nominal;
  if (HEMVeto == false){
    w_nominal_update = w_nominal * 0.354;
  }
  return w_nominal_update;
}

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

// // ttbar overlap
// if ("TT" in sample.label): 
//     genpart = Collection(event,"GenPart")
//     top = list(filter(lambda x: x.pdgId==6 ,genpart))[0]
//     antitop = list(filter(lambda x: x.pdgId==-6 ,genpart))[0]
//     Mtt = (top.p4() + antitop.p4()).M()
//     SF_t = 0.973-0.000134*top.pt+0.103*math.exp(-0.0118*top.pt)
//     SF_antit = 0.973-0.000134*antitop.pt+0.103*math.exp(-0.0118*antitop.pt)
//     w_pt_nominal[0]=math.sqrt(SF_t*SF_antit)
//     if (Mtt>=700) and (not "Mtt" in sample.label):
//         #print(Mtt)
//         continue






// ########## ad hoc functions
bool LepVeto(rvec_f Electron_pt, rvec_f Electron_eta, rvec_f Electron_mvaFall17V1Iso_WPL, rvec_f Muon_pt, rvec_f Muon_eta, rvec_b Muon_looseId )
{
  int EleVetoPassed = 0;
  int MuVetoPassed = 0;
  bool IsLepVetoPassed = true;
  
  for (size_t i = 0; i < Muon_pt.size(); i++) 
    {
      if(Electron_mvaFall17V1Iso_WPL[i]==1 && Electron_pt[i] > 30.) EleVetoPassed+=1;
    }
  for (size_t i = 0; i< Muon_pt.size(); i++)
    {
      if(Muon_looseId[i]==1 && Muon_pt[i] > 30. && abs(Muon_eta[i])<2.4) MuVetoPassed+=1;
    }
  if(EleVetoPassed+MuVetoPassed >0) IsLepVetoPassed = false;
  
  return IsLepVetoPassed;
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


Float_t LeadingJetPt(rvec_i GoodJet_idx, rvec_f Jet_pt)
{
  int leadingjet_pt;
  RVec<float> GoodJet_pt;
  for(int i = 0; i < GoodJet_idx.size(); i++)
  {
    GoodJet_pt.emplace_back(Jet_pt[GoodJet_idx[i]]);
  }
  return Max(GoodJet_pt);
}

Int_t nForwardJet(rvec_i GoodJet_idx, rvec_f Jet_eta)
{
  int nfwdjet = 0;
  for(int i = 0; i < GoodJet_idx.size(); i++)
  {
    if (Jet_eta[GoodJet_idx[i]]>2.5)
    {
      nfwdjet += 1;
    }
  }
  return nfwdjet;
}

Int_t njetbtag(rvec_i GoodJet_idx, rvec_f Jet_btagDeepFlavB)
{
  int nbjet = 0;
  for(int i = 0; i < GoodJet_idx.size(); i++)
  {
    if (Jet_btagDeepFlavB[GoodJet_idx[i]] > btag_mediumWP)
    {
      nbjet += 1;
    }
  }
  return nbjet;
}

RVec<int> select_TopMer(rvec_f FatJet_deepTag_TvsQCD, rvec_f FatJet_pt, rvec_f FatJet_eta, rvec_f FatJet_phi)
{
  RVec<int> ids;
  for (int i = 0; i < FatJet_deepTag_TvsQCD.size(); i++)
  {
  	if(FatJet_deepTag_TvsQCD[i]>TopMer_trs && FatJet_pt[i]>TopMer_minpt && FatJet_pt[i]<TopMer_maxpt){
      ids.emplace_back(i);
	  }
  }
  return ids;
}

RVec<int> select_TopMix(rvec_f TopHighPt_score2, rvec_f TopHighPt_pt, rvec_f TopHighPt_eta, rvec_f TopHighPt_phi)
{
  RVec<int> ids;
  RVec<float> scores;
  for (int i = 0; i < TopHighPt_score2.size(); i++)
  {
  	if(TopHighPt_score2[i]>TopMix_trs && TopHighPt_pt[i]>TopMix_minpt && TopHighPt_pt[i]<TopMix_maxpt)
    {
      ids.emplace_back(i);
	    scores.emplace_back(TopHighPt_score2[i]);
	  }
  }
    
  RVec<int> ids_ = ids;
  RVec<int> ids_select;
  RVec<float> scores_ = scores;
  int n_notzero = 0;
    
  for(int j=0; j<scores_.size(); j++)
  { 
    if(scores_[j]!=0)
    {
	    n_notzero += 1;
    }
    else 
    {
	    n_notzero += 0;
    }
  }

  while(n_notzero!=0)
  {
    RVec<float> deltaRs;
    int bestTop_idx = ArgMax(scores_);
      
    for(int i = 0; i < ids_.size(); i++)
    {
	    if(i == bestTop_idx) continue;
	    if(scores_[i]!=0 && deltaR(TopHighPt_eta[bestTop_idx], TopHighPt_phi[bestTop_idx], TopHighPt_eta[i], TopHighPt_phi[i])<dR)  scores_[i]=0;
     
    }
    ids_select.emplace_back(bestTop_idx);
    scores_[bestTop_idx]=0;
    n_notzero =0;
    for(int j=0; j<scores_.size(); j++)
    { 
	    if(scores_[j]!=0)
      {
	      n_notzero += 1;
	    }
	    else 
      {
	      n_notzero += 0;
	    }
    }
  }
  return ids_select;
}

RVec<int> select_TopRes(rvec_f TopLowPt_scoreDNN, rvec_f TopLowPt_pt, rvec_f TopLowPt_eta, rvec_f TopLowPt_phi)
{
  RVec<int> ids;
  RVec<float> scores;
  for (int i = 0; i < TopLowPt_scoreDNN.size(); i++)
  {
	  if(TopLowPt_scoreDNN[i]>TopRes_trs && TopLowPt_pt[i]>TopRes_minpt && TopLowPt_pt[i]<TopRes_maxpt)
    {
	    ids.emplace_back(i);
	    scores.emplace_back(TopLowPt_scoreDNN[i]);
	  }
  }
    
  RVec<int> ids_ = ids;
  RVec<float> ids_select;
  RVec<float> scores_ = scores;
  int n_notzero = 0;
    
  for(int j=0; j<scores_.size(); j++)
  { 
    if(scores_[j]!=0)
    {
	    n_notzero += 1;
    }
    else 
    {
	    n_notzero += 0;
    }
  }

  while(n_notzero!=0)
  {
    RVec<float> deltaRs;
    int bestTop_idx = ArgMax(scores_);
      
    for(int i = 0; i < ids_.size(); i++)
    {
	    if(i == bestTop_idx) continue;
	    if(scores_[i]!=0 && deltaR(TopLowPt_eta[bestTop_idx], TopLowPt_phi[bestTop_idx], TopLowPt_eta[i], TopLowPt_phi[i])<dR)  scores_[i]=0;
    }
    ids_select.emplace_back(bestTop_idx);
    scores_[bestTop_idx]=0;
    n_notzero =0;
    for(int j=0; j<scores_.size(); j++)
    { 
      if(scores_[j]!=0)
      {
	      n_notzero += 1;
	    }
	    else 
      {
	      n_notzero += 0;
	    }
    }
  }
  return ids_select;
}

Int_t select_TopCategory(rvec_i GoodTopMer_idx, rvec_i GoodTopMix_idx, rvec_i GoodTopRes_idx){
  //return:  0- no top sel, 1- top merged, 2- top mix, 3- top resolved
  int nRes = GoodTopRes_idx.size();
  int nMix = GoodTopMix_idx.size();
  int nMer = GoodTopMer_idx.size();
  
  if (nRes>0 && nMix==0 && nMer==0){
    return 3;
  }
  else if (nRes<2 && nMix>0 && nMer==0){
    return 2;
  }
  else if (nRes==0 && nMix<2 && nMer>0){
    return 1;
  }
  else return 0;
}

Int_t select_bestTop(int EventTopCategory, rvec_i GoodTopMer_idx, rvec_i GoodTopMix_idx, rvec_i GoodTopRes_idx, rvec_f FatJet_deepTag_TvsQCD, rvec_f TopHighPt_score2, rvec_f TopLowPt_scoreDNN){
  //RVec<int> topselect ;
  //int bestTop_idx;
  RVec<float> scores;
  if (EventTopCategory==1){ 
    //topselect = GoodTopMer_idx;
    for(int i = 0; i < GoodTopMer_idx.size(); i++)
    {
      scores.emplace_back(FatJet_deepTag_TvsQCD[i]);
    }
  }
  else if (EventTopCategory==2){
    for(int i = 0; i < GoodTopMix_idx.size(); i++)
    {
      scores.emplace_back(TopHighPt_score2[i]);
    } 
  }
  else if (EventTopCategory==3){ 
    for(int i = 0; i < GoodTopRes_idx.size(); i++)
    {
      scores.emplace_back(TopLowPt_scoreDNN[i]);
    } 
  }
  else return -1;

  return ArgMax(scores);
}

Float_t select_TopVar(Int_t EventTopCategory, Int_t Top_idx, rvec_f FatJet_pt, rvec_f TopHighPt_pt, rvec_f TopLowPt_pt){
  if (EventTopCategory==1) return FatJet_pt[Top_idx];
  else if (EventTopCategory==2) return TopHighPt_pt[Top_idx];
  else if (EventTopCategory==3) return TopLowPt_pt[Top_idx];
  else return -1000;
}
