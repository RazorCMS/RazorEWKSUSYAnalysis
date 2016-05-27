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
#include <TCanvas.h>
#include <TStyle.h>
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


const float lumi = 5;
//Axis
const float axisTitleSize = 0.06;
const float axisTitleOffset = .8;

const float axisTitleSizeRatioX   = 0.18;
const float axisLabelSizeRatioX   = 0.12;
const float axisTitleOffsetRatioX = 0.94;

const float axisTitleSizeRatioY   = 0.15;
const float axisLabelSizeRatioY   = 0.108;
const float axisTitleOffsetRatioY = 0.32;

//Margins
const float leftMargin   = 0.12;
const float rightMargin  = 0.05;
const float topMargin    = 0.07;
const float bottomMargin = 0.12;

//CMS STANDARD
TString CMSText = "CMS";
TString extraText   = "Preliminary";
//TString lumiText = "2.32 fb^{-1} (13 TeV)";
TString lumiText = "27 pb^{-1} (13 TeV)";

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
  float obsL[npoints];
  
  float xp[2*npoints];
  float OneS[2*npoints];
  float TwoS[2*npoints];
   

  int ctr = 0;
  for ( auto tmp : mymap )
    {
      //std::cout << "mass: " << tmp.first << " expL: " << tmp.second.exp0p5 << std::endl;
      x[ctr]    = tmp.first;
      obsL[ctr] = tmp.second.obs;
      expL[ctr] = tmp.second.exp0p5;
      
      xp[ctr] = tmp.first;
      xp[2*npoints-(ctr+1)] = tmp.first;     

      OneS[ctr] = tmp.second.exp0p16;
      OneS[2*npoints-(ctr+1)] = tmp.second.exp0p84;

      TwoS[ctr] = tmp.second.exp0p025;
      TwoS[2*npoints-(ctr+1)] = tmp.second.exp0p975;
       
      ctr++;
    }

  TFile* out = new TFile("out_test.root", "recreate");
  TGraph* gObs = new TGraph(npoints, x, obsL);
  TGraph* gExp = new TGraph(npoints, x, expL);
  TGraph* gOneS = new TGraph(2*npoints, xp, OneS);
  TGraph* gTwoS = new TGraph(2*npoints, xp, TwoS);

  TCanvas* c = new TCanvas( "c", "c", 2119, 33, 800, 700 );
  c->SetHighLightColor(2);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetLeftMargin( leftMargin );
  c->SetRightMargin( rightMargin );
  c->SetTopMargin( topMargin );
  c->SetBottomMargin( bottomMargin );
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);

  gStyle->SetPaintTextFormat("4.3f");
  
  gTwoS->SetFillColor(kSpring-3);
  gOneS->SetFillColor(kSpring+10);
  gExp->SetLineWidth(3);
  gExp->SetLineStyle(2);
  gObs->SetLineWidth(3);

  gTwoS->SetTitle("");
  gTwoS->GetXaxis()->SetTitle("M_{G} (GeV)");
  gTwoS->GetYaxis()->CenterTitle(kTRUE);
  gTwoS->GetYaxis()->SetTitle("95% C.L. limit #sigma(pp#rightarrowG#rightarrow#gamma#gamma) (fb)");
  gTwoS->Draw("AFC");
  gOneS->Draw("FC");
  gExp->Draw("C");
  gObs->Draw("C");

  c->SaveAs("NarrowResLimit.pdf");
  c->SaveAs("NarrowResLimit.C");
  
  gObs->GetXaxis()->SetRangeUser(0, 30);
  gObs->Write("gObs");
  gExp->Write("gExp");
  gOneS->Write("gOneS");
  gTwoS->Write("gTwoS");
  
  out->Close();
  return 0;
}
