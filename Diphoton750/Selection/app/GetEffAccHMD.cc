//C++
#include <iostream>
#include <fstream>
#include <map>
#include <stdlib.h>
//ROOT
#include <TDirectory.h>
#include <TFile.h>
#include <TH1F.h>
#include <TF1.h>
#include <TTree.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TEfficiency.h>
#include <TGraphAsymmErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLatex.h>
#include <TLegend.h>
//LOCAL INCLUDES
#include "CommandLineInput.hh"

struct Eff
{
  double eff;
  double errUp;
  double errDown;
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
TString lumiText = "2.69 fb^{-1} (13 TeV)";

bool AddCMS( TCanvas* C );

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

  //-----------------
  //Selection TString
  //-----------------
  std::string categoryMode = ParseCommandLine( argc, argv, "-category=" );
  if (  categoryMode == "" )
    {
      std::cerr << "[ERROR]: please provide the category. Use --category=<ebeb,ebee>" << std::endl;
      return -1;
    }
  
  TString cut = "pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1Pt> 75. && pho2Pt>75. && HLTDecision[93] == 1";
  TString categoryCutString;

  if (categoryMode == "ebeb") categoryCutString = " && mGammaGamma >= 230 && abs(pho1DefaultSC_Eta) <1.4442 && abs(pho2DefaultSC_Eta) < 1.4442";
  else if (categoryMode == "ebee") categoryCutString = " && mGammaGamma >= 330 && ( (abs(pho1DefaultSC_Eta) < 1.4442 && abs(pho2DefaultSC_Eta) > 1.566) || (abs(pho1DefaultSC_Eta) > 1.566 && abs(pho2DefaultSC_Eta) < 1.4442) )";
  
  cut = cut + categoryCutString;

  std::ifstream ifs ( inputList.c_str(), std::ifstream::in );


  std::map<float, Eff> mymap;
  
  std::string fname;
  if( ifs.is_open() )
    {
      while( ifs.good() )
	{
	  ifs >> fname;
	  if ( ifs.eof() ) break;
	  //std::cout << "fname: " << fname << std::endl;
	  TFile* fin = new TFile( fname.c_str(), "READ" );
	  int low  = fname.find("_M-")+3;
	  int high = fname.find("_TuneCUEP8M1_13TeV-pythia8") - low;
	  std::string mass = fname.substr( low, high );
	  float _mass = atof( mass.c_str() );
	  TTree* tree = (TTree*)fin->Get("HggRazor");
	  TH1F* nevents = (TH1F*)fin->Get("NEvents");
	  tree->Draw("mGammaGamma>>tmp1(10000,0,10000)", cut, "goff");
	  TH1F* selected = (TH1F*)gDirectory->Get("tmp1");
	  float accEff = selected->Integral()/nevents->Integral();
	  //float err = sqrt( accEff*(1-accEff)/nevents->Integral());
	  float errUp   = fabs( accEff-TEfficiency::ClopperPearson( nevents->Integral(), selected->Integral(), 0.68, 1 ) );
	  float errDown = fabs( accEff-TEfficiency::ClopperPearson( nevents->Integral(), selected->Integral(), 0.68, 0 ) );
	  Eff tmp;
	  tmp.eff     = accEff;
	  tmp.errUp   = errUp;
	  tmp.errDown = errDown;
	  std::cout << "mass: " << mass << " " << selected->Integral() << " " << nevents->Integral()
		    << "-> " << accEff << " +/-" << errUp << " " << errDown << std::endl;
	  
	  //<< " " << exp0p975 << " " << obs << std::endl;
	  if ( mymap.find( _mass ) == mymap.end() )
	    {
	      mymap[_mass] = tmp;
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
  float AccEff[npoints];
  float xerrU[npoints];
  float xerrD[npoints];
  float yerrU[npoints];
  float yerrD[npoints];
  
  int ctr = 0;
  for ( auto tmp : mymap )
    {
      //if ( tmp.first > 1000 && tmp.first < 1300 ) std::cout << "mass: " << tmp.first << " expL: " << tmp.second.exp0p5 << std::endl;
      x[ctr]    = tmp.first;
      AccEff[ctr] = tmp.second.eff;
      xerrU[ctr] = 0;
      xerrD[ctr] = 0;
      yerrU[ctr] = tmp.second.errUp;
      yerrD[ctr] = tmp.second.errDown;
      ctr++;
    }

  TString mFname = "AccEff_GluGlu_0p014_EBEE_FINAL";
  TFile* out = new TFile(mFname+".root", "recreate");
  TGraph* gAccEff = new TGraph(npoints, x, AccEff);

  TF1 *fpol = new TF1 ("fpol", "pol4", 490., 4010.);
  TGraphAsymmErrors* gr = new TGraphAsymmErrors(npoints,x,AccEff,xerrU,xerrD,yerrU,yerrD);
  gr->Fit( fpol, "RF+EX0" );
  gr->SetMarkerStyle(20);
  gr->SetMarkerColor(kBlue-3);
  gr->SetMarkerSize(0.7);
  gr->SetLineColor(kBlue-3);
  gr->SetLineWidth(1);

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

 

  gr->SetTitle("");
  gr->GetXaxis()->SetTitleSize(0.05);
  gr->GetXaxis()->SetTitle("M_{G} (GeV)");
  gr->GetYaxis()->SetTitleSize(0.05);
  //gAccEff->GetYaxis()->CenterTitle(kTRUE);
  gr->GetYaxis()->SetTitle("#epsilon #times A");

  gr->GetYaxis()->SetRangeUser(0,1);
  gr->GetXaxis()->SetRangeUser(500,4300);
  gr->Draw("AP");

  TLegend* leg = new TLegend( 0.6, 0.78, 0.89, 0.89, NULL, "brNDC" );
  leg->SetBorderSize(0);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->SetTextSize(0.04);
  leg->AddEntry( gr, " EBEE J=0", "ep" );
  leg->Draw();

  AddCMS(c);

  
  c->SaveAs(mFname+".pdf");
  c->SaveAs(mFname+".C");
  
  gAccEff->Write("gAccEff");
  fpol->Write("pol3Fit");
  gr->Write("gr");
 
  
  out->Close();
  return 0;
}


bool AddCMS( TCanvas* C )
{
  C->cd();
  float lumix = 0.955;
  float lumiy = 0.945;
  float lumifont = 42;
  
  float cmsx = 0.28;
  float cmsy = 0.875;
  float cmsTextFont   = 61;  // default is helvetic-bold
  float extrax = cmsx + 0.078;
  float extray = cmsy - 0.04;
  float extraTextFont = 52;  // default is helvetica-italics
  // ratio of "CMS" and extra text size
  float extraOverCmsTextSize  = 0.76;
  float cmsSize = 0.06;
  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  float extraTextSize = extraOverCmsTextSize*cmsSize;
  latex.SetTextFont(lumifont);
  latex.SetTextAlign(31); 
  latex.SetTextSize(cmsSize);    
  latex.DrawLatex(lumix, lumiy,lumiText);

  latex.SetTextFont(cmsTextFont);
  latex.SetTextAlign(31); 
  latex.SetTextSize(cmsSize);
  latex.DrawLatex(cmsx, cmsy, CMSText);
   
  latex.SetTextFont(extraTextFont);
  latex.SetTextAlign(31); 
  latex.SetTextSize(extraTextSize);
  latex.DrawLatex(extrax, extray, extraText);
  return true;
};
