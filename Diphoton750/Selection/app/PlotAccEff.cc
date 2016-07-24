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
//TString extraText   = "Preliminary";
TString extraText   = "Simulation";
//TString lumiText = "2.32 fb^{-1} (13 TeV)";
//TString lumiText = "2.69 fb^{-1} (13 TeV)";
TString lumiText = "13 TeV";

bool AddCMS( TCanvas* C );

int main( int argc, char** argv )
{

  TFile* f = new TFile("AccEff_GluGlu_5p6_EBEB.root","read");
  TGraphAsymmErrors* g1 = (TGraphAsymmErrors*)f->Get("gr");
  f = new TFile("AccEff_GluGlu_5p6_EBEE.root","read");
  TGraphAsymmErrors* g2 = (TGraphAsymmErrors*)f->Get("gr");
  f = new TFile("AccEff_RSGrav_k02_EBEB.root","read");
  TGraphAsymmErrors* g3 = (TGraphAsymmErrors*)f->Get("gr");
  f = new TFile("AccEff_RSGrav_k02_EBEE.root","read");
  TGraphAsymmErrors* g4 = (TGraphAsymmErrors*)f->Get("gr");
  
  TString mFname = "AccEff_LargestWidth";
  TFile* out = new TFile(mFname+".root", "recreate");
  g1->SetMarkerStyle(20);
  g1->SetMarkerColor(kBlue-3);
  g1->SetMarkerSize(0.7);
  g1->SetLineColor(kBlue-3);
  g1->SetLineWidth(1);

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

 

  g1->SetTitle("");
  g1->GetXaxis()->SetTitleSize(0.05);
  g1->GetXaxis()->SetTitle("M_{G} (GeV)");
  g1->GetYaxis()->SetTitleSize(0.05);
  //gAccEff->GetYaxis()->CenterTitle(kTRUE);
  g1->GetYaxis()->SetTitle("#epsilon #times A");

  g1->GetYaxis()->SetRangeUser(0,1);
  g1->GetXaxis()->SetRangeUser(500,4300);
  
 
  TF1* f1 = g1->GetFunction("fpol");
  f1->SetLineColor(kRed-4);
  g1->SetMarkerColor(kRed-4);
  g1->Draw("AP");

  
  TF1* f2 = g2->GetFunction("fpol");
  f2->SetLineStyle(2);
  f2->SetLineColor(kRed-4);
  g1->SetMarkerColor(kRed-4);
  g2->Draw("P");

  TF1* f3 = g3->GetFunction("fpol");
  f3->SetLineColor(kBlue-4);
  g3->SetMarkerColor(kBlue-4);
  g3->Draw("P");

  TF1* f4 = g4->GetFunction("fpol");
  f4->SetLineColor(kBlue-4);
  f4->SetLineStyle(2);
  g4->SetMarkerColor(kBlue-4);
  g4->Draw("P");

  TLegend* leg = new TLegend( 0.66, 0.68, 0.94, 0.89, NULL, "brNDC" );
  leg->SetBorderSize(0);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->SetTextSize(0.04);
  leg->AddEntry( f1, " EBEB J=0", "l" );
  leg->AddEntry( f2, " EBEE J=0", "l" );
  leg->AddEntry( f3, " EBEB J=2", "l" );
  leg->AddEntry( f4, " EBEE J=2", "l" );

  leg->Draw();

  AddCMS(c);

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    
  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.04);    
  latex.DrawLatex( 0.32, 0.7, "#frac{#Gamma}{M} = 5.6%" );
  
  
  c->SaveAs(mFname+".pdf");
  c->SaveAs(mFname+".C");
  
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
  float extrax = cmsx + 0.069;
  float extray = cmsy - 0.05;
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
