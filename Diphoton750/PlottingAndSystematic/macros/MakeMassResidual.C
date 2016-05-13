

void MakeMassResidual() {

  

  ifstream myfile;
  ifstream exofile;
  myfile.open ("massList.EBEE.caltech.txt");
  exofile.open ("EXOEventList/full_event_list_vertex0/massList.EBEE.exo.txt");

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


  TH1F *histMassResiduals = new TH1F("histMassResiduals","; (m_{#gamma#gamma}^{Caltech} - m_{#gamma#gamma}^{Ref}) / m_{#gamma#gamma}^{Ref}; Number of Events", 100, -0.01, 0.01);
  
  std::map<string,double>::iterator itExo;
  std::map <string, double>::iterator it = myMap.begin();
  for(; it != myMap.end(); it++) {
    cout<< it->first << " " << it->second << " ";
    
    itExo = exoMap.find(it->first);
    if (itExo != exoMap.end()) {
      cout << itExo->second;
      histMassResiduals->Fill(  (it->second - itExo->second) / itExo->second);
    } else {
      cout << "not found";
    }
    cout << "\n";
 
  }


  TCanvas *cv;
  cv = new TCanvas("cv","cv", 800,600);
  histMassResiduals->Draw("hist");
  histMassResiduals->GetXaxis()->SetTitleOffset(1.2);
  histMassResiduals->GetYaxis()->SetTitleOffset(1.2);
  cv->SaveAs("MassResiduals.gif");

}
