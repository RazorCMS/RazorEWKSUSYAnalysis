//C++
#include <iostream>
#include <fstream>
#include <map>
#include <stdlib.h>
//ROOT
#include <TFile.h>
#include <TTree.h>
#include <TGraph.h>
#include <TAxis.h>
//LOCAL INCLUDES
#include "CommandLineInput.hh"

struct Limit
{
  double obs;
  double exp0p025;
  double exp0p16;
  double exp0p5;
  double exp0p84;
  double exp0p975;
};

int main( int argc, char** argv )
{

  //-----------------
  //Input File List
  //-----------------
  std::string inputList = ParseCommandLine( argc, argv, "-inputList=" );
  if (  inputList == "" )
    {
      std::cerr << "[ERROR]: please provide an inputList. Use --inputList=" << std::endl;
      return -1;
    }

  std::ifstream ifs ( inputList.c_str(), std::ifstream::in );


  std::map<float, Limit> mymap;
  
  std::string fname;
  if( ifs.is_open() )
    {
      while( ifs.good() )
	{
	  ifs >> fname;
	  if ( ifs.eof() ) break;
	  //std::cout << "fname: " << fname << std::endl;
	  TFile* fin = new TFile( fname.c_str(), "READ" );
	  int low  = fname.find(".mH")+3;
	  int high = fname.find(".root") - low;
	  std::string mass = fname.substr( low, high );
	  float _mass = atof( mass.c_str() );
	  TTree* tree = (TTree*)fin->Get("limit");
	  double limit;
	  Limit tmpLimit;
	  tree->SetBranchAddress( "limit", &limit );
	  tree->GetEntry(0);
	  tmpLimit.exp0p025 = limit*10.;
	  tree->GetEntry(1);
	  tmpLimit.exp0p16 = limit*10.;
	  tree->GetEntry(2);
	  tmpLimit.exp0p5 = limit*10.;
	  tree->GetEntry(3);
	  tmpLimit.exp0p84 = limit*10.;
	  tree->GetEntry(4);
	  tmpLimit.exp0p975 = limit*10.;
	  tree->GetEntry(5);
	  tmpLimit.obs = limit*10.;
	  //std::cout << "mass: " << mass << "-> " << exp0p025 << " " << exp0p16 << " " << exp0p5 << " " << exp0p84
	  //<< " " << exp0p975 << " " << obs << std::endl;
	  if ( mymap.find( _mass ) == mymap.end() )
	    {
	      mymap[_mass] = tmpLimit;
	    }
	  delete fin;
	}
    }
  else
    {
      std::cerr << "[ERROR] can't open file " << inputList << std::endl;
    }

  int npoints = mymap.size();
  float x[npoints];
  float expL[npoints];
   

  int ctr = 0;
  for ( auto tmp : mymap )
    {
      //std::cout << "mass: " << tmp.first << " expL: " << tmp.second.exp0p5 << std::endl;
      x[ctr]    = tmp.first;
      expL[ctr] = tmp.second.exp0p5;
      ctr++;
    }

  TFile* out = new TFile("out_test.root", "recreate");
  TGraph* g1 = new TGraph(npoints, x, expL);

  g1->Write("g1");
  g1->GetXaxis()->SetRangeUser(0, 30);
  out->Close();
  return 0;
}
