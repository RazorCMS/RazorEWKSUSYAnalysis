//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Dec  7 17:15:49 2019 by ROOT version 6.13/02
// from TTree OPTtree/Optimization Variables
// found on file: AllYears_DYJetsToLL_M-50_OPTtree.root
//////////////////////////////////////////////////////////

#ifndef OPTtree_h
#define OPTtree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class OPTtree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   std::vector<int>     *OPT_Event;
   std::vector<float>   *OPT_EventWeight;
   std::vector<int>     *OPT_nJets;
   std::vector<float>   *OPT_ZPt;
   std::vector<float>   *OPT_ZSf;
   std::vector<float>   *OPT_base_weight;
   std::vector<float>   *OPT_ele_weight;
   std::vector<float>   *OPT_mu_weight;
   std::vector<float>   *OPT_PU_weight;
   std::vector<float>   *OPT_AODCaloJetMedianLog10IPSig;
   std::vector<float>   *OPT_AODCaloJetMedianLog10TrackAngle;
   std::vector<float>   *OPT_AODCaloJetAlphaMax;
   std::vector<float>   *OPT_AODCaloJetEta;
   std::vector<float>   *OPT_AODCaloJetPt;

   // List of branches
   TBranch        *b_OPT_Event;   //!
   TBranch        *b_OPT_EventWeight;   //!
   TBranch        *b_OPT_nJets;   //!
   TBranch        *b_OPT_ZPt;   //!
   TBranch        *b_OPT_ZSf;   //!
   TBranch        *b_OPT_base_weight;   //!
   TBranch        *b_OPT_ele_weight;   //!
   TBranch        *b_OPT_mu_weight;   //!
   TBranch        *b_OPT_PU_weight;   //!
   TBranch        *b_OPT_AODCaloJetMedianLog10IPSig;   //!
   TBranch        *b_OPT_AODCaloJetMedianLog10TrackAngle;   //!
   TBranch        *b_OPT_AODCaloJetAlphaMax;   //!
   TBranch        *b_OPT_AODCaloJetEta;   //!
   TBranch        *b_OPT_AODCaloJetPt;   //!

   OPTtree(TTree *tree=0);
   virtual ~OPTtree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef OPTtree_cxx
OPTtree::OPTtree(TTree *tree) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("AllYears_DYJetsToLL_M-50_OPTtree.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("AllYears_DYJetsToLL_M-50_OPTtree.root");
      }
      f->GetObject("OPTtree",tree);

   }
   Init(tree);
}

OPTtree::~OPTtree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t OPTtree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t OPTtree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void OPTtree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   OPT_Event = 0;
   OPT_EventWeight = 0;
   OPT_nJets = 0;
   OPT_ZPt = 0;
   OPT_ZSf = 0;
   OPT_base_weight = 0;
   OPT_ele_weight = 0;
   OPT_mu_weight = 0;
   OPT_PU_weight = 0;
   OPT_AODCaloJetMedianLog10IPSig = 0;
   OPT_AODCaloJetMedianLog10TrackAngle = 0;
   OPT_AODCaloJetAlphaMax = 0;
   OPT_AODCaloJetEta = 0;
   OPT_AODCaloJetPt = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("OPT_Event", &OPT_Event, &b_OPT_Event);
   fChain->SetBranchAddress("OPT_EventWeight", &OPT_EventWeight, &b_OPT_EventWeight);
   fChain->SetBranchAddress("OPT_nJets", &OPT_nJets, &b_OPT_nJets);
   fChain->SetBranchAddress("OPT_ZPt", &OPT_ZPt, &b_OPT_ZPt);
   fChain->SetBranchAddress("OPT_ZSf", &OPT_ZSf, &b_OPT_ZSf);
   fChain->SetBranchAddress("OPT_base_weight", &OPT_base_weight, &b_OPT_base_weight);
   fChain->SetBranchAddress("OPT_ele_weight", &OPT_ele_weight, &b_OPT_ele_weight);
   fChain->SetBranchAddress("OPT_mu_weight", &OPT_mu_weight, &b_OPT_mu_weight);
   fChain->SetBranchAddress("OPT_PU_weight", &OPT_PU_weight, &b_OPT_PU_weight);
   fChain->SetBranchAddress("OPT_AODCaloJetMedianLog10IPSig", &OPT_AODCaloJetMedianLog10IPSig, &b_OPT_AODCaloJetMedianLog10IPSig);
   fChain->SetBranchAddress("OPT_AODCaloJetMedianLog10TrackAngle", &OPT_AODCaloJetMedianLog10TrackAngle, &b_OPT_AODCaloJetMedianLog10TrackAngle);
   fChain->SetBranchAddress("OPT_AODCaloJetAlphaMax", &OPT_AODCaloJetAlphaMax, &b_OPT_AODCaloJetAlphaMax);
   fChain->SetBranchAddress("OPT_AODCaloJetEta", &OPT_AODCaloJetEta, &b_OPT_AODCaloJetEta);
   fChain->SetBranchAddress("OPT_AODCaloJetPt", &OPT_AODCaloJetPt, &b_OPT_AODCaloJetPt);
   Notify();
}

Bool_t OPTtree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void OPTtree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t OPTtree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef OPTtree_cxx
