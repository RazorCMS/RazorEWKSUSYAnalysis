#include <iostream>
#include <vector>
#include <fstream>
#include <assert.h>
//ROOT INCLUDES
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TROOT.h>
//LOCAL INCLUDES
#include "AssortedFunctions.hh"
#include "CommandLineInput.hh"

int main( int argc, char* argv[] )
{

  gROOT->Reset();
  std::string inputFile = ParseCommandLine( argc, argv, "-inputFile=" );
  if (  inputFile == "" )
    {
      std::cerr << "[ERROR]: please provide an input list file using --inputFile=<path_to_list_file>" << std::endl;
      return -1;
    }
  //-----------------
  //Selection TString
  //-----------------
  std::string categoryMode = ParseCommandLine( argc, argv, "-category=" );
  if (  categoryMode == "" )
    {
      std::cerr << "[ERROR]: please provide the category. Use --category=<ebeb,ebee>" << std::endl;
      return -1;
    }
  
  TString cut = "pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1Pt> 75. && pho2Pt>75.";
  TString categoryCutString;

  if (categoryMode == "ebeb") categoryCutString = " && mGammaGamma >= 230 && abs(pho1DefaultSC_Eta) <1.4442 && abs(pho2DefaultSC_Eta) < 1.4442";
  else if (categoryMode == "ebee") categoryCutString = " && mGammaGamma >= 340 && ( (abs(pho1DefaultSC_Eta) < 1.4442 && abs(pho2DefaultSC_Eta) > 1.566) || (abs(pho1DefaultSC_Eta) > 1.566 && abs(pho2DefaultSC_Eta) < 1.4442) )";
  
  cut = cut + categoryCutString;

  TFile* fin = new TFile( inputFile.c_str(), "READ");
  std::cout << "[INFO]: checking file: " << inputFile << std::endl;
  assert( fin );
  std::cout << "[INFO]: file: " << inputFile << " passed check\n\n"<< std::endl;
      
  //------------------------
  //Getting TTree and Histos
  //------------------------
  TTree* tree = (TTree*)fin->Get("HggRazor");
  assert( tree );
  
  TFile* tmp = new TFile("tmp.root", "RECREATE");
  TTree* cutTree = tree->CopyTree( cut );
  
  cutTree->Draw("mGammaGamma>>h_mgg(720,230,2030)", "weight*pileupWeight*(1)", "goff");
    
  TH1F* h_mgg = (TH1F*)tmp->Get("h_mgg");
  double effSigma = GetEffSigma( h_mgg );
  std::cout << "[RESULT]: category: " << categoryMode << "; Effective Sigma = " << effSigma << std::endl;
  h_mgg->Write("mgg");
  tmp->Close();
  
  return 0;
}
