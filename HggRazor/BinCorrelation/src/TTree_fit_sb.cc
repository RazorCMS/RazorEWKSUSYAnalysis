#define tree_fit_sb_cxx
#include <iostream>

#include "TTree_fit_sb.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void tree_fit_sb::Loop()
{
//   In a ROOT session, you can do:
//      root> .L tree_fit_sb.C
//      root> tree_fit_sb t
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

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      std::cout << "Photon_Trigger: " << Photon_Trigger << std::endl;
      // if (Cut(ientry) < 0) continue;
   }
}

void tree_fit_sb::void SetSystematics()
{
  systematics[0] = CMS_Lumi;
  systematics[1] = Photon_Trigger;
  systematics[2] = SMH_JES;
  systematics[3] = SMH_btag;
  systematics[4] = SMH_facRenScale_bin0;
  systematics[5] = SMH_facRenScale_bin1;
  systematics[6] = SMH_facRenScale_bin2;
  systematics[7] = SMH_facRenScale_bin3;
  systematics[8] = SMH_facRenScale_bin4;
  systematics[9] = SMH_facRenScale_bin5;
  systematics[10] = SMH_facRenScale_bin6;
  systematics[11] = SMH_facRenScale_bin7;
  systematics[12] = SMH_facRenScale_bin8;
  systematics[13] = SMH_facRenScale_bin9;
  systematics[14] = SMH_facRenScale_bin10;
  systematics[15] = SMH_facRenScale_bin11;
  systematics[16] = SMH_facRenScale_bin12;
  systematics[17] = SMH_facRenScale_bin13;
  systematics[18] = SMH_facScale_bin0;
  systematics[19] = SMH_facScale_bin1;
  systematics[20] = SMH_facScale_bin2;
  systematics[21] = SMH_facScale_bin3;
  systematics[22] = SMH_facScale_bin4;
  systematics[23] = SMH_facScale_bin5;
  systematics[24] = SMH_facScale_bin6;
  systematics[25] = SMH_facScale_bin7;
  systematics[26] = SMH_facScale_bin8;
  systematics[27] = SMH_facScale_bin9;
  systematics[28] = SMH_facScale_bin10;
  systematics[29] = SMH_facScale_bin11;
  systematics[30] = SMH_facScale_bin12;
  systematics[31] = SMH_facScale_bin13;
  systematics[32] = SMH_renScale_bin0;
  systematics[33] = SMH_renScale_bin1;
  systematics[34] = SMH_renScale_bin2;
  systematics[35] = SMH_renScale_bin3;
  systematics[36] = SMH_renScale_bin4;
  systematics[37] = SMH_renScale_bin5;
  systematics[38] = SMH_renScale_bin6;
  systematics[39] = SMH_renScale_bin7;
  systematics[40] = SMH_renScale_bin8;
  systematics[41] = SMH_renScale_bin9;
  systematics[42] = SMH_renScale_bin10;
  systematics[43] = SMH_renScale_bin11;
  systematics[44] = SMH_renScale_bin12;
  systematics[45] = SMH_renScale_bin13;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf1;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf1;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf1;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf1;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf1;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf1;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_pdf0;
  systematics[46] = SMH_misstag;
  systematics[47] = 
  
  
};
