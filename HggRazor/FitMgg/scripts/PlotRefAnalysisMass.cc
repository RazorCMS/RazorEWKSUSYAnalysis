#include <iostream>
#include <fstream>

#include <TSystem.h>
#include <TDirectory.h>
#include <TTree.h>
#include <TLegend.h>
#include "TString.h"
#include <TROOT.h>
#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TObject.h"
#include "TNamed.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TMath.h"

#include "TBox.h"

#include "RooWorkspace.h"
#include "RooPlot.h"
#include "RooFitResult.h"
#include "RooRealVar.h"
#include "RooAbsPdf.h"
#include "RooAbsData.h"
#include "RooCurve.h"


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

  gROOT->Reset();
  
  std::ifstream ifs ( "/Users/cmorgoth/Work/HighMassDiphoton/ReferenceFiles/massList.EBEB.exo.txt", std::ifstream::in );
  assert( ifs );

  TFile* fin = new TFile("/Users/cmorgoth/Work/HighMassDiphoton/SignalSamples/smearSamples/HggRazorExo_DoubleEG_2015D_GoodLumiSilver.root", "READ");
  TTree* tree = (TTree*)fin->Get("HggRazor");
  //EBEB
  TString cut = "mGammaGamma > 230. && pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && abs(pho1DefaultSC_Eta) <1.4442 && abs(pho2DefaultSC_Eta) < 1.4442 && pho1Pt> 75. && pho2Pt>75. && HLTDecision[93] == 1 && (Flag_HBHENoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1)";
  //EBEE
  //TString cut = "mGammaGamma > 320. && pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1Pt> 75. && pho2Pt>75. && ( (abs(pho1DefaultSC_Eta) > 1.566 && abs(pho2DefaultSC_Eta) < 1.4442) || (abs(pho1DefaultSC_Eta) < 1.4442 && abs(pho2DefaultSC_Eta) > 1.566) ) && HLTDecision[93] == 1 && (Flag_HBHENoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1)";

  tree->Draw("mGammaGamma>>tmp1(70,230,1630)", cut);//EBEB
  //tree->Draw("mGammaGamma>>tmp1(70,230,1630)", cut);//EBEE
  TH1F* hc = (TH1F*)gDirectory->Get("tmp1");
  
  TFile* fout = new TFile("HistoMassEBEB.root", "RECREATE");
  TH1F* h = new TH1F("h", "mass", 70, 230, 1630);
  
  if ( ifs.is_open() )
    {
      std::string dummy;
      float mass;
      while ( ifs.good() )
	{
	  if ( ifs.eof() ) break;
	  ifs >> dummy >> mass;
	  //std::cout << dummy << " " << mass << std::endl;
	  h->Fill(mass);
	}
    }
  else
    {
      std::cout << "unable to open file!!!" << std::endl;
    }
  
  
  TCanvas* cv = new TCanvas( "cv", "cv", 2119, 33, 800, 700 );
  cv->SetHighLightColor(2);
  cv->SetFillColor(0);
  cv->SetBorderMode(0);
  cv->SetBorderSize(2);
  cv->SetLeftMargin( leftMargin );
  cv->SetRightMargin( rightMargin );
  cv->SetTopMargin( topMargin );
  cv->SetBottomMargin( bottomMargin );
  cv->SetFrameBorderMode(0);
  cv->SetFrameBorderMode(0);

  /*
  TLegend* leg = new TLegend( 0.7, 0.6, 0.93, 0.89, NULL, "brNDC" );
  leg->SetBorderSize(0);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->SetTextSize(0.04);
  leg->AddEntry( h_tmp2, " Data", "lep" );
  leg->AddEntry( dummy, " Fit model", "l" );
  leg->AddEntry( gsigma, " #pm 1 #sigma", "f" );
  leg->AddEntry( gsigma2, " #pm 2 #sigma", "f" );
  leg->Draw();
  */
  h->SetMarkerStyle(20);
  h->SetMarkerColor(kBlack);
  h->SetLineColor(kBlack);
  h->SetLineWidth(2);
  h->SetMarkerSize(2);

  hc->SetMarkerStyle(20);
  hc->SetMarkerColor(kRed);
  hc->SetLineColor(kRed);
  hc->SetLineWidth(1);
  hc->SetMarkerSize(1);
  
  h->SetStats(0);
  h->SetTitle("");
  h->SetYTitle("events / ( 20 GeV )");
  h->GetYaxis()->SetTitleSize(0.06);
  h->GetYaxis()->SetTitleOffset(0.85);
  h->SetXTitle("m_{#gamma#gamma} GeV");
  h->GetXaxis()->SetTitleSize(0.06);
  h->GetXaxis()->SetTitleOffset(0.85);
  h->Draw("E1");
  hc->Draw("same+E1");

  TH1F* ratio = new TH1F( *h );
  ratio->Divide( hc );

  cv->SetLogy();
  cv->SaveAs("dataReferenceEBEB.pdf");
  cv->SaveAs("dataReferenceEBEB.png");
  cv->SaveAs("dataReferenceEBEB.C");
  
  h->Write("mass");
  hc->Write("mass_caltech");
  fout->Close();
  
  return 0;
};

bool AddCMS( TCanvas* C )
{
  C->cd();
  float lumix = 0.955;
  float lumiy = 0.945;
  float lumifont = 42;
  
  float cmsx = 0.32;
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

