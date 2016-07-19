#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <assert.h>
//ROOT
#include <TFile.h>
#include <TH2F.h>
#include <TGraph.h>
//LOCAL INCLUDES
#include "CommandLineInput.hh"
#include "HggAux.hh"
#include "AssortedFunctions.hh"

std::map<float, float> maxLimit;
std::map<float, float, std::greater<float> > minLimit;

int main( int argc, char* argv[] )
{
  
  // primary list -- file with path to combine output root file
  std::string inputList = ParseCommandLine( argc, argv, "-inputList=" );
  if (  inputList == "" )
    {
      std::cerr << "[ERROR]: please provide an input file using --inputList=<path_to_file>" << std::endl;
      return -1;
    }
  
  // file containing nominal cross sections for models
  std::string xsecFile = ParseCommandLine( argc, argv, "-xsecFile=" );
  if ( xsecFile == "" ) {
    std::cerr << "[ERROR]: please provide an xsec file using --xsecFile=<path_to_file>" << std::endl;
    return -1;
  }

  FillCrossSectionMap( xsecFile );

  TFile* fout = new TFile("test_limit.root", "recreate");
  TH2F* h2_limit = new TH2F("h2_limit", "", 50, 0, 750, 50, 0, 750);
    
  std::ifstream ifs( inputList.c_str(), std::fstream::in );
  if ( ifs.is_open() )
    {
      std::string fname;
      while ( ifs.good() )
	{
	  ifs >> fname;
	  if ( ifs.eof() ) break;
	  std::cout << "[INFO]: fname-> " << fname << std::endl;
	  Limit myLimit;
	  GetLimit( myLimit, fname, 5.0 );
	  h2_limit->Fill(myLimit.msb, myLimit.mlsp, myLimit.xsecL );

	  //Find Max msb for an excluded point
	  if ( maxLimit.find(myLimit.mlsp) == maxLimit.end() && myLimit.obs < 1.0 )
	    {
	      maxLimit[myLimit.mlsp] = myLimit.msb;
	    }
	  else if ( myLimit.obs < 1.0 && myLimit.msb > maxLimit[myLimit.mlsp])
	    {
	      maxLimit[myLimit.mlsp] = myLimit.msb; 
	    }

	  //Find min smb for an excluded point
	  if ( minLimit.find(myLimit.mlsp) == minLimit.end() && myLimit.obs < 1.0 )
	    {
	      minLimit[myLimit.mlsp] = myLimit.msb;
	    }
	  else if ( myLimit.obs < 1.0 && myLimit.msb < maxLimit[myLimit.mlsp])
	    {
	      minLimit[myLimit.mlsp] = myLimit.msb; 
	    }
	  //std::cout << "[INFO]: fname-> " << fname << std::endl;
	}
    }
  else
    {
      std::cout << "Unable to open binning lookup table" << std::endl;
    }

  //  auto sortMapUp = [] (std::map<float,float> a, std::map<float,float> b){ } 
  for ( auto tmp : maxLimit ) std::cout << tmp.first << " " << tmp.second << std::endl;
  for ( auto tmp : minLimit ) std::cout << tmp.first << " " << tmp.second << std::endl;

  const int npoints = maxLimit.size() + minLimit.size();
  float _msb[npoints];
  float _mlsp[npoints];
  int ctr = 0;
  for ( auto tmp : maxLimit )
    {
      _msb[ctr]  = tmp.second;
      _mlsp[ctr] = tmp.first;
      ctr++;
    }
  for ( auto tmp : minLimit )
    {
      _msb[ctr]  = tmp.second;
      _mlsp[ctr] = tmp.first;
      ctr++;
    }

  TGraph* contour = new TGraph( npoints, _msb, _mlsp );
  
  fout->cd();
  h2_limit->Write("limit");
  contour->Write("contour");
  fout->Close();
  
  return 0;
}
