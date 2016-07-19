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

//Expected
std::map<float, float> maxExp;
std::map<float, float, std::greater<float> > minExp;
//-1sigma
std::map<float, float> maxMsigma;
std::map<float, float, std::greater<float> > minMsigma;
//+1sigma
std::map<float, float> maxPsigma;
std::map<float, float, std::greater<float> > minPsigma;



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
  TH2F* h2_limit = new TH2F("h2_limit", "", 15, 0, 750, 15, 0, 750);
    
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
	  else if ( myLimit.obs < 1.0 && myLimit.msb < minLimit[myLimit.mlsp])
	    {
	      minLimit[myLimit.mlsp] = myLimit.msb; 
	    }

	  //---------------------------------------------------
	  //Find Max msb for an excluded point (Expected Limit)
	  //---------------------------------------------------
	  if ( maxExp.find(myLimit.mlsp) == maxExp.end() && myLimit.exp < 1.0 )
	    {
	      maxExp[myLimit.mlsp] = myLimit.msb;
	    }
	  else if ( myLimit.exp < 1.0 && myLimit.msb > maxExp[myLimit.mlsp])
	    {
	      maxExp[myLimit.mlsp] = myLimit.msb; 
	    }

	  //Find min smb for an excluded point
	  if ( minExp.find(myLimit.mlsp) == minExp.end() && myLimit.exp < 1.0 )
	    {
	      minExp[myLimit.mlsp] = myLimit.msb;
	    }
	  else if ( myLimit.exp < 1.0 && myLimit.msb < minExp[myLimit.mlsp])
	    {
	      minExp[myLimit.mlsp] = myLimit.msb; 
	    }

	  //---------------------------------------------------
	  //Find Max msb for an excluded point (Expected Limit +1sigma)
	  //---------------------------------------------------
	  if ( maxPsigma.find(myLimit.mlsp) == maxPsigma.end() && myLimit.q84 < 1.0 )
	    {
	      maxPsigma[myLimit.mlsp] = myLimit.msb;
	    }
	  else if ( myLimit.q84 < 1.0 && myLimit.msb > maxPsigma[myLimit.mlsp])
	    {
	      maxPsigma[myLimit.mlsp] = myLimit.msb; 
	    }

	  //Find min smb for an excluded point
	  if ( minPsigma.find(myLimit.mlsp) == minPsigma.end() && myLimit.q84 < 1.0 )
	    {
	      minPsigma[myLimit.mlsp] = myLimit.msb;
	    }
	  else if ( myLimit.q84 < 1.0 && myLimit.msb < minPsigma[myLimit.mlsp])
	    {
	      minPsigma[myLimit.mlsp] = myLimit.msb; 
	    }

	  //---------------------------------------------------
	  //Find Max msb for an excluded point (Expected Limit -1sigma)
	  //---------------------------------------------------
	  if ( maxMsigma.find(myLimit.mlsp) == maxMsigma.end() && myLimit.q16 < 1.0 )
	    {
	      maxMsigma[myLimit.mlsp] = myLimit.msb;
	    }
	  else if ( myLimit.q16 < 1.0 && myLimit.msb > maxMsigma[myLimit.mlsp])
	    {
	      maxMsigma[myLimit.mlsp] = myLimit.msb; 
	    }

	  //Find min smb for an excluded point
	  if ( minMsigma.find(myLimit.mlsp) == minMsigma.end() && myLimit.q16 < 1.0 )
	    {
	      minMsigma[myLimit.mlsp] = myLimit.msb;
	    }
	  else if ( myLimit.q16 < 1.0 && myLimit.msb < minMsigma[myLimit.mlsp])
	    {
	      minMsigma[myLimit.mlsp] = myLimit.msb; 
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
  std::cout << "---------------------" << std::endl;
  for ( auto tmp : maxExp ) std::cout << tmp.first << " " << tmp.second << std::endl;
  for ( auto tmp : minExp ) std::cout << tmp.first << " " << tmp.second << std::endl;
  std::cout << "---------------------" << std::endl;
  for ( auto tmp : maxPsigma ) std::cout << tmp.first << " " << tmp.second << std::endl;
  for ( auto tmp : minPsigma ) std::cout << tmp.first << " " << tmp.second << std::endl;
  std::cout << "---------------------" << std::endl;
  for ( auto tmp : maxMsigma ) std::cout << tmp.first << " " << tmp.second << std::endl;
  for ( auto tmp : minMsigma ) std::cout << tmp.first << " " << tmp.second << std::endl;

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
  
  const int nExp = maxExp.size() + minExp.size();
  float _msbExp[nExp];
  float _mlspExp[nExp];
  ctr = 0;
  for ( auto tmp : maxExp )
    {
      _msbExp[ctr]  = tmp.second;
      _mlspExp[ctr] = tmp.first;
      ctr++;
    }
  for ( auto tmp : minExp )
    {
      _msbExp[ctr]  = tmp.second;
      _mlspExp[ctr] = tmp.first;
      ctr++;
    }
  TGraph* expL = new TGraph( nExp, _msbExp, _mlspExp );
  //-------------
  //+1Sigma
  //------------
  const int nPsigma = maxPsigma.size() + minPsigma.size();
  float _msbPsigma[nPsigma];
  float _mlspPsigma[nPsigma];
  ctr = 0;
  for ( auto tmp : maxPsigma )
    {
      _msbPsigma[ctr]  = tmp.second;
      _mlspPsigma[ctr] = tmp.first;
      ctr++;
    }
  for ( auto tmp : minPsigma )
    {
      _msbPsigma[ctr]  = tmp.second;
      _mlspPsigma[ctr] = tmp.first;
      ctr++;
    }
  TGraph* psigma = new TGraph( nPsigma, _msbPsigma, _mlspPsigma );
  //-------------
  //-1Sigma
  //------------
  const int nMsigma = maxMsigma.size() + minMsigma.size();
  float _msbMsigma[nMsigma];
  float _mlspMsigma[nMsigma];
  ctr = 0;
  for ( auto tmp : maxMsigma )
    {
      _msbMsigma[ctr]  = tmp.second;
      _mlspMsigma[ctr] = tmp.first;
      ctr++;
    }
  for ( auto tmp : minMsigma )
    {
      _msbMsigma[ctr]  = tmp.second;
      _mlspMsigma[ctr] = tmp.first;
      ctr++;
    }
  TGraph* msigma = new TGraph( nMsigma, _msbMsigma, _mlspMsigma );
  
  fout->cd();
  h2_limit->Write("limit");
  contour->Write("contour");
  expL->Write("expL");
  psigma->Write("psigma");
  msigma->Write("msigma");
  fout->Close();
  
  return 0;
}
