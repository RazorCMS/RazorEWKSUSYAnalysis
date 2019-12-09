#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <assert.h>
//ROOT INCLUDES
#include <TFile.h>
#include <TROOT.h>
//LOCAL INCLUDES
#include "OPTtree.hh"
#include "HggRazorSystematics.hh"
#include "CommandLineInput.hh"

const bool _debug = true;

int main( int argc, char* argv[] )
{
  gROOT->Reset();
  std::string inputFile = ParseCommandLine( argc, argv, "-inputFile=" );
  if (  inputFile == "" )
    {
      std::cerr << "[ERROR]: please provide an input list file using --inputFile=<path_to_list_file>" << std::endl;
      return -1;
    }
  
  std::cerr << "===========================================================================" << std::endl;
  std::cerr << "[INFO]: INPUT ROOT FILE--> " << inputFile << std::endl;
  std::cerr << "===========================================================================" << std::endl;
  TFile* fin = new TFile(inputFile.c_str(), "READ");
  TTree* tree = (TTree*)fin->Get("OPTtree");

  OPTtree* opt = new OPTtree(tree);
  opt->Loop();
  
  return 0;
};

