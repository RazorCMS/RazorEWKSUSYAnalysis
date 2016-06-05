

void MakeMassResidual() {

  

  ifstream myfile;
  ifstream exofile;
  myfile.open ("massList.EBEB.caltech.2016.txt");
  exofile.open ("EXOEventList/2016/full_event_list/massList.EBEB.exo.txt");

  assert(myfile.is_open());  
  assert(exofile.is_open());

  std::map<string,double> myMap;
  std::map<string,double> exoMap;

  while(!myfile.eof()) {
    string runLumiEvent;
    double mass; 
    myfile >> runLumiEvent >> mass;
    //cout << runLumiEvent << " " << mass << "\n";
    myMap[runLumiEvent] = mass;
  }
  
  while(!exofile.eof()) {
    string runLumiEvent;
    double mass; 
    exofile >> runLumiEvent >> mass;
    //cout << runLumiEvent << " " << mass << "\n";
    exoMap[runLumiEvent] = mass;
  }


  TH1F *histMassResiduals = new TH1F("histMassResiduals","; (m_{#gamma#gamma}^{Caltech} - m_{#gamma#gamma}^{flashgg}) / m_{#gamma#gamma}^{flashgg}; Number of Events", 100, -0.000025, 0.000025);
  
  std::map<string,double>::iterator itExo;
  std::map <string, double>::iterator it = myMap.begin();
  for(it = myMap.begin(); it != myMap.end(); it++) {

    if (it->first == "") continue;
    cout<< it->first << " " << it->second << " ";
    
    itExo = exoMap.find(it->first);
    if (itExo != exoMap.end()) {
      cout << itExo->second;
      histMassResiduals->Fill(  (it->second - itExo->second) / itExo->second);

      if ((it->second - itExo->second) / itExo->second > 0.01) {
    	cout << it->first << " " << it->second << " " << itExo->second << "\n";
      }

    } else {
      cout << "not found";
    }
    cout << "\n";
 
  }


  TCanvas *cv;
  cv = new TCanvas("cv","cv", 800,600);
  cv->SetBottomMargin(0.15);
  histMassResiduals->SetStats(true);
  histMassResiduals->Draw("hist");
  histMassResiduals->GetXaxis()->SetTitleOffset(1.4);
  histMassResiduals->GetXaxis()->SetTitleSize(0.045);
  histMassResiduals->GetXaxis()->SetLabelSize(0.04);
  histMassResiduals->GetYaxis()->SetTitleOffset(1.0);
  histMassResiduals->GetYaxis()->SetTitleSize(0.045);
  histMassResiduals->GetYaxis()->SetLabelSize(0.04);
  cv->SaveAs("MassComparison_2016.gif");

}
