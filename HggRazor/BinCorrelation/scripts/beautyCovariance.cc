{
  gROOT->Reset();
  gStyle->SetPaintTextFormat(".1f");
  TFile* fin = new TFile("histos_correlation.root");
  TH1F* h = (TH1F*)fin->Get("corr");
  h->SetStats(0);
  //h->SetTitle("Background Covariance Matrix");
  h->SetTitle("Background Correlation Matrix");
  corr->SetMinimum(-1);
  corr->SetMaximum(1);
  //corr->SetMinimum(-4000);
  //corr->SetMaximum(4000);
  gStyle->SetPaintTextFormat(".2f");
  //x-axis labels
  h->GetXaxis()->SetBinLabel( 1 , "Bin 0");
  h->GetXaxis()->SetBinLabel( 2 , "Bin 1");
  h->GetXaxis()->SetBinLabel( 3 , "Bin 2");
  h->GetXaxis()->SetBinLabel( 4 , "Bin 3");
  h->GetXaxis()->SetBinLabel( 5 , "Bin 4");
  h->GetXaxis()->SetBinLabel( 6 , "Bin 5");
  h->GetXaxis()->SetBinLabel( 7 , "Bin 6");
  h->GetXaxis()->SetBinLabel( 8 , "Bin 7");
  h->GetXaxis()->SetBinLabel( 9 , "Bin 8");
  h->GetXaxis()->SetBinLabel( 10 , "Bin 9 HighRes");
  h->GetXaxis()->SetBinLabel( 11 , "Bin 10 HighRes");
  h->GetXaxis()->SetBinLabel( 12 , "Bin 11 HighRes");
  h->GetXaxis()->SetBinLabel( 13 , "Bin 12 HighRes");
  h->GetXaxis()->SetBinLabel( 14 , "Bin 13 HighRes");
  h->GetXaxis()->SetBinLabel( 15 , "Bin 9 LowRes");
  h->GetXaxis()->SetBinLabel( 16 , "Bin 10 LowRes");
  h->GetXaxis()->SetBinLabel( 17 , "Bin 11 LowRes");
  h->GetXaxis()->SetBinLabel( 18 , "Bin 12 LowRes");
  h->GetXaxis()->SetBinLabel( 19 , "Bin 13 LowRes");
  h->GetXaxis()->LabelsOption("v");
  //y-axis labels
  h->GetYaxis()->SetBinLabel( 1 , "Bin 0");
  h->GetYaxis()->SetBinLabel( 2 , "Bin 1");
  h->GetYaxis()->SetBinLabel( 3 , "Bin 2");
  h->GetYaxis()->SetBinLabel( 4 , "Bin 3");
  h->GetYaxis()->SetBinLabel( 5 , "Bin 4");
  h->GetYaxis()->SetBinLabel( 6 , "Bin 5");
  h->GetYaxis()->SetBinLabel( 7 , "Bin 6");
  h->GetYaxis()->SetBinLabel( 8 , "Bin 7");
  h->GetYaxis()->SetBinLabel( 9 , "Bin 8");
  h->GetYaxis()->SetBinLabel( 10 , "Bin 9 HighRes");
  h->GetYaxis()->SetBinLabel( 11 , "Bin 10 HighRes");
  h->GetYaxis()->SetBinLabel( 12 , "Bin 11 HighRes");
  h->GetYaxis()->SetBinLabel( 13 , "Bin 12 HighRes");
  h->GetYaxis()->SetBinLabel( 14 , "Bin 13 HighRes");
  h->GetYaxis()->SetBinLabel( 15 , "Bin 9 LowRes");
  h->GetYaxis()->SetBinLabel( 16 , "Bin 10 LowRes");
  h->GetYaxis()->SetBinLabel( 17 , "Bin 11 LowRes");
  h->GetYaxis()->SetBinLabel( 18 , "Bin 12 LowRes");
  h->GetYaxis()->SetBinLabel( 19 , "Bin 13 LowRes");
  
  h->Draw("colz+text");

  TFile* fout = new TFile("CorrelationMatrixHggRazor.root", "Recreate");
  h->Write("covariance");
  fout->Close();
  
}
