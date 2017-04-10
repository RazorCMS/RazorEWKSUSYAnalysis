#include <iostream>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TDirectory.h>
#include <TLegend.h>


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

void PlotSMS()
{
  gROOT->Reset();
  

  TFile* fout = new TFile("SMS_Plotting.root", "recreate");

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
  
  //200_1 MassPoint
  TFile* f1 = new TFile("/Users/cmorgoth/Work/data/HggRazor/EWKsignals/SMS-TChiWH_200_1_1pb_weighted.root", "read");
  TTree* t1 = (TTree*)f1->Get("HggRazor");
  t1->Draw("MR>>tmp1(80,0,2000)", "weight*btagCorrFactor*triggerEffSFWeight*photonEffSF*triggerEffWeight*(mGammaGamma >103. && mGammaGamma < 160. && pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && abs(pho1Eta) <1.48 && abs(pho2Eta)<1.48 && (pho1Pt>40||pho2Pt>40)  && pho1Pt> 25. && pho2Pt>25. && MR>0)", "goff");
  TH1F* h_200_1 = (TH1F*)gDirectory->Get("tmp1");
  h_200_1->Scale( 1.0/h_200_1->Integral() );
  h_200_1->SetLineColor(kBlue-3);
  h_200_1->SetFillColor(kBlue-3);
  h_200_1->SetFillStyle(3004);
  h_200_1->SetTitle("");
  h_200_1->SetStats(0);
  h_200_1->SetXTitle("M_{R} [GeV]");
  h_200_1->SetYTitle("a.u");
  h_200_1->Draw("hist");

  //450_1 MassPoint
  TFile* f2 = new TFile("/Users/cmorgoth/Work/data/HggRazor/EWKsignals/SMS-TChiWH_450_1_1pb_weighted.root", "read");
  TTree* t2 = (TTree*)f2->Get("HggRazor");
  t2->Draw("MR>>tmp2(80,0,2000)", "weight*btagCorrFactor*triggerEffSFWeight*photonEffSF*triggerEffWeight*(mGammaGamma >103. && mGammaGamma < 160. && pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && abs(pho1Eta) <1.48 && abs(pho2Eta)<1.48 && (pho1Pt>40||pho2Pt>40)  && pho1Pt> 25. && pho2Pt>25. && MR>0)", "goff");
  TH1F* h_450_1 = (TH1F*)gDirectory->Get("tmp2");
  h_450_1->Scale( 1.0/h_450_1->Integral() );
  h_450_1->SetLineColor(kRed);
  h_450_1->SetFillColor(kRed);
  h_450_1->SetFillStyle(3004);
  h_450_1->Draw("hist+same");

  //700_1 MassPoint
  TFile* f3 = new TFile("/Users/cmorgoth/Work/data/HggRazor/EWKsignals/SMS-TChiWH_700_1_1pb_weighted.root", "read");
  TTree* t3 = (TTree*)f3->Get("HggRazor");
  t3->Draw("MR>>tmp3(80,0,2000)", "weight*btagCorrFactor*triggerEffSFWeight*photonEffSF*triggerEffWeight*(mGammaGamma >103. && mGammaGamma < 160. && pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && abs(pho1Eta) <1.48 && abs(pho2Eta)<1.48 && (pho1Pt>40||pho2Pt>40)  && pho1Pt> 25. && pho2Pt>25. && MR>0)", "goff");
  TH1F* h_700_1 = (TH1F*)gDirectory->Get("tmp3");
  h_700_1->Scale( 1.0/h_700_1->Integral() );
  h_700_1->SetLineColor(kViolet-2);
  h_700_1->SetFillColor(kViolet-2);
  h_700_1->SetFillStyle(3004);
  h_700_1->Draw("hist+same");


  TLegend* leg = new TLegend( 0.4, 0.6, 0.89, 0.89, NULL, "brNDC" );
  leg->SetBorderSize(0);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  leg->SetTextSize(0.04);
  leg->AddEntry( h_200_1, " m_{#tilde{#chi}^{#pm}_{1}} = m_{#tilde{#chi}^{0}_{2}} = 200 GeV; m_{#tilde{#chi}^{0}_{1}} = 1 GeV", "f" );
  leg->AddEntry( h_450_1, " m_{#tilde{#chi}^{#pm}_{1}} = m_{#tilde{#chi}^{0}_{2}} = 450 GeV; m_{#tilde{#chi}^{0}_{1}} = 1 GeV", "f" );
  leg->AddEntry( h_700_1, " m_{#tilde{#chi}^{#pm}_{1}} = m_{#tilde{#chi}^{0}_{2}} = 700 GeV; m_{#tilde{#chi}^{0}_{1}} = 1 GeV", "f" );
  leg->Draw();
  
  return;
}
