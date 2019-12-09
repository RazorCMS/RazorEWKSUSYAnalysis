#define OPTtree_cxx
#include <iostream>
#include "OPTtree.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void OPTtree::Loop()
{
//   In a ROOT session, you can do:
//      root> .L OPTtree.C
//      root> OPTtree t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;


   double ip_tagger   = 1.25;
   double ta_tagger   = -1.50;
   double amax_tagger = 0.60;
   double zpt_cut     = 100.0;
   
   TH1F* ntags_high = new TH1F("ntags_high", "ntags_high", 3, -0.5, 2.5);
   TH1F* ntags_low  = new TH1F("ntags_low", "ntags_low", 3, -0.5, 2.5);
   TH1F* tf         = new TH1F("tf", "tf", 3, -0.5, 2.5);
   
   TH1F* jet_pt_one_ntag = new TH1F("jet_pt_one_ntag","jet_pt_one_ntag", 100, 0.0, 200.0);
   TH1F* jet_pt_two_ntag_lead = new TH1F("jet_pt_one_ntag_lead","jet_pt_one_ntag_lead", 100, 0.0, 200.0);
   TH1F* jet_pt_two_ntag_sublead  = new TH1F("jet_pt_one_ntag_sublead","jet_pt_one_ntag_sublead", 100, 0.0, 200.0);
   
   Long64_t nentries = fChain->GetEntriesFast();
   
   std::cout << nentries << std::endl;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      int ntag = 0;
      double weight = OPT_base_weight->at(0)*OPT_ele_weight->at(0)*OPT_PU_weight->at(0);
      //std::cout << "OPT_ZPt: " << OPT_ZPt->size() << std::endl;
      for( int i = 0; i < OPT_AODCaloJetMedianLog10IPSig->size(); i++ )
	{
	  if( OPT_AODCaloJetMedianLog10IPSig->at(i) > ip_tagger && OPT_AODCaloJetMedianLog10TrackAngle->at(i) > ta_tagger && OPT_AODCaloJetAlphaMax->at(i) < amax_tagger) 
	    {
	      ntag++;
	      jet_pt_one_ntag->Fill(OPT_AODCaloJetPt->at(i), weight);
	    }
	}
      if(ntag > 2) ntag = 2;
      
      if( OPT_ZPt->at(0) >= zpt_cut ) ntags_high->Fill(ntag,weight);
      else ntags_low->Fill(ntag,weight);
      // if (Cut(ientry) < 0) continue;
   }
   
   tf = (TH1F*)ntags_high->Clone("tf");
   tf->Divide(ntags_low);
   
   TFile* fout = new TFile("file_out.root", "recreate");
   ntags_high->Write("ntags_high");
   ntags_low->Write("ntags_low");
   tf->Write("tf");
   jet_pt_one_ntag->Write("jet_pt_one_ntag");

   fout->Close();
}
