#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <assert.h>
//ROOT INCLUDES
#include <TFile.h>
#include <TROOT.h>
//#include <RooArgSet.h>
//LOCAL INCLUDES
#include "HggAux.hh"
#include "HggRazorSystematics.hh"
#include "CommandLineInput.hh"

const bool _debug = true;



//----------------------------------------------
//Load Binning
//----------------------------------------------
std::vector<float*> SetBinning(std::vector<Bin> bins, std::string category)
{

  std::vector<float*> myVec;
  for(int i=0; i<bins.size(); ++i) {
    float *tmpbin = new float[5];
    if (bins[i].box == category) {
      tmpbin[0] = bins[i].x1;
      tmpbin[1] = bins[i].y1;
      tmpbin[2] = bins[i].x2;
      tmpbin[3] = bins[i].y2;
      tmpbin[4] = bins[i].bin;
      myVec.push_back(tmpbin);
    }
  }

  return myVec;
};

//----------------
//Static Variables
//----------------
float HggRazorSystematics::NR_kf = 1.0;
int   HggRazorSystematics::n_PdfSys = 60;


int main( int argc, char* argv[] )
{

  //RooFit::PrintLevel(5);
  //RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
  gROOT->Reset();
  std::string inputList = ParseCommandLine( argc, argv, "-inputList=" );
  if (  inputList == "" )
    {
      std::cerr << "[ERROR]: please provide an input list file using --inputList=<path_to_list_file>" << std::endl;
      return -1;
    }
  //-----------------
  //Selection TString
  //-----------------
  std::string categoryMode = ParseCommandLine( argc, argv, "-category=" );
  if (  categoryMode == "" )
    {
      std::cerr << "[ERROR]: please provide the category. Use --category=<highpt,hzbb,highres,lowres>" << std::endl;
      return -1;
    }

  //-----------------
  //Output file TString
  //-----------------
  std::string outputFile = ParseCommandLine( argc, argv, "-outputFile=" );
  if (  outputFile == "" )
    {
      std::cerr << "[ERROR]: please provide an output file using --outputFile=<outputfile>" << std::endl;
      return -1;
    }
 
  //-----------------
  //Lumi Normalization
  //-----------------
  double lumi = 0;
  std::string lumiString = ParseCommandLine( argc, argv, "-lumi=" );
  if (  lumiString == "" )
    {
      std::cerr << "[ERROR]: please provide the luminosity. For example, use --lumi=2000" << std::endl;
      return -1;
    }
  lumi = float(atoi(lumiString.c_str()));
  std::cerr << "[INFO] : Using Luminosity = " << lumi << "\n";

  //-----------------
  //Analysis Tag
  //-----------------
  std::string analysisTag = ParseCommandLine( argc, argv, "-analysisTag=" );
  if ( analysisTag == "" )
    {
      std::cerr << "[ERROR]: please provide the analysisTag. Use --analysisTag=<Razor2015_76X,Razor2016_80X>" << std::endl;
      return -1;
    } 
  
  //-----------------
  //pTGammaGamma cut
  //-----------------
  std::string usePtGammaGamma = ParseCommandLine( argc, argv, "-usePtGammaGamma=" );
  if ( usePtGammaGamma == "yes" )
    {
      std::cerr << "[INFO]: enabling pTGammaGamma cut for all boxes" << std::endl;
    } 
  
  //-----------------
  //Binning File 
  //-----------------
  std::string binDefinitionFilename = ParseCommandLine( argc, argv, "-binningFile=" );
  if ( binDefinitionFilename == "" )
    {
      std::cerr << "[ERROR]: please provide the bin definition file. Use --binningFile=<binningFile>" << std::endl;
      return -1;
    } 
  
  //-----------------
  //Load Binning
  //-----------------
  std::vector<Bin> binVector;
  std::ifstream binDefFile( binDefinitionFilename.c_str(), std::fstream::in );
  if ( binDefFile.is_open() ) {
    float x1, x2, y1, y2;
    int binN;
    std::string box, f1;
    while ( binDefFile.good() ) {
      binDefFile >> binN >> x1 >> x2 >> y1 >> y2 >> box >> f1;
      if ( binDefFile.eof() ) break;
      Bin mybin;
      mybin.bin = binN;
      mybin.f1 = f1;
      mybin.box = box;
      mybin.x1 = x1;
      mybin.x2 = x2;
      mybin.y1 = y1;
      mybin.y2 = y2;
      binVector.push_back(mybin);
    }
  } else {
    std::cout << "Unable to open binning lookup table" << std::endl;
  }


  TString cut = "mGammaGamma > 103. && mGammaGamma < 160. && pho1passIso == 1 && pho2passIso == 1 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && abs(pho1Eta) <1.48 && abs(pho2Eta)<1.48 && (pho1Pt>40||pho2Pt>40)  && pho1Pt> 25. && pho2Pt>25.";
  if (usePtGammaGamma == "yes") {
    cut = cut + " && pTGammaGamma > 20 ";
  }

  TString categoryCutString;
  if (categoryMode == "highpt") categoryCutString = " && pTGammaGamma >= 110 ";
  else if (categoryMode == "hzbb") categoryCutString = " && pTGammaGamma < 110 && ( abs(mbbH_L-125.) < 15. || ( abs(mbbH_L-125.) >= 15. && abs(mbbZ_L-91.) < 15 ) )";
  else if (categoryMode == "highres") categoryCutString = " && pTGammaGamma < 110 && abs(mbbH_L-125.) >= 15 && abs(mbbZ_L-91.) >= 15 && sigmaMoverM < 0.0085";
  else if (categoryMode == "lowres") categoryCutString  = " && pTGammaGamma < 110 && abs(mbbH_L-125.) >= 15 && abs(mbbZ_L-91.) >= 15 && sigmaMoverM >= 0.0085 ";
  else if (categoryMode == "inclusive") categoryCutString = "";
  // combined highres / lowres box
  else if (categoryMode == "highreslowres") categoryCutString = " && pTGammaGamma < 110 && abs(mbbH_L-125.) >= 15 && abs(mbbZ_L-91.) >= 15";
  else if (categoryMode == "highpthighres") categoryCutString = " && pTGammaGamma >= 110 && sigmaMoverM < 0.0085";
  else if (categoryMode == "highptlowres") categoryCutString = " && pTGammaGamma >= 110 && sigmaMoverM >= 0.0085";

  //TString triggerCut = " && ( HLTDecision[82] || HLTDecision[83] || HLTDecision[93] ) ";
  TString metFilterCut = " && (Flag_HBHENoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1 && Flag_HBHEIsoNoiseFilter == 1)";
  TString triggerCut = "";
  //TString metFilterCut = "";


  if ( analysisTag == "Razor2015_76X" ) {
    cut = cut + categoryCutString + triggerCut+ metFilterCut;  
  } else if ( analysisTag == "Razor2016_80X" ) {
    //for 80X MC, trigger table doesn't exist. so don't apply triggers.
    cut = cut + categoryCutString + metFilterCut;
  } else {
    std::cerr << "Analysis Tag " << analysisTag << " not recognized. Error!\n";
    return -1;
  }
  std::cerr << "[INFO] : Using Analysis Tag: " << analysisTag  << "\n";

  std::cerr << "===========================================================================" << std::endl;
  std::cerr << "[INFO]: cut--> " << cut << std::endl;
  std::cerr << "===========================================================================" << std::endl;
  
  std::ifstream ifs( inputList, std::ifstream::in );
  assert(ifs);

  std::vector<std::pair<float,float>> facScaleSys;
  std::vector<std::pair<float,float>> renScaleSys;
  std::vector<std::pair<float,float>> facRenScaleSys;

  std::vector<float*> myVectBinning;
  myVectBinning = SetBinning(binVector, categoryMode);

  if (!(categoryMode == "highpt" || categoryMode == "hzbb" 
	|| categoryMode == "highres"|| categoryMode == "lowres"))
     {
       std::cerr << "[ERROR]: category is not <highpt/hzbb/highres/lowres>; quitting" << std::endl;
       return -1;
     } 

  TH2Poly* nominal  = new TH2Poly("nominal_SMH", "", 150, 10000, 0, 1 );
  std::map< std::pair<float,float>, float > sysMap;
  for ( auto tmp : myVectBinning ) nominal->AddBin( tmp[0], tmp[1], tmp[2], tmp[3] );
  
  std::string process, rootFileName;
  while ( ifs.good() )
    {
      ifs >> process >> rootFileName;
      if ( ifs.eof() ) break;
      if ( process.find("#") != std::string::npos ) continue;
      if ( _debug ) std::cout << process << " " << rootFileName << std::endl;
      TFile* fin = new TFile( rootFileName.c_str(), "READ");
      std::cout << "[INFO]: checking file: " << rootFileName << std::endl;
      assert( fin );
      if ( _debug ) std::cout << "[INFO]: file: " << rootFileName << " passed check\n\n"<< std::endl;
      
      //------------------------
      //Getting TTree and Histos
      //------------------------
      TTree* tree = (TTree*)fin->Get("HggRazor");
      assert( tree );
      TH1F* NEvents = (TH1F*)fin->Get("NEvents");
      if ( process != "signal" ) assert( NEvents );
      TH1F* SumScaleWeights   = (TH1F*)fin->Get("SumScaleWeights");
      if ( process != "signal" ) assert( SumScaleWeights );
      TH1F* SumPdfWeights   = (TH1F*)fin->Get("SumPdfWeights");
      if ( process != "signal" ) assert( SumPdfWeights );
      
      TFile* tmp = new TFile("tmp.root", "RECREATE");
      TTree* cutTree = tree->CopyTree( cut );
      TString currentProcess = process.c_str();

      //---------------------------
      //Create HggSystematic object
      //---------------------------
      HggRazorSystematics* hggSys = new HggRazorSystematics( cutTree, currentProcess, categoryMode, analysisTag, _debug, _debug );
      hggSys->SetLumi(lumi);
      hggSys->SetBinningVector( myVectBinning );
      hggSys->InitMrRsqTH2Poly( 1 );
      hggSys->SetNeventsHisto( NEvents );
      hggSys->SetFacScaleWeightsHisto( SumScaleWeights );
      hggSys->SetPdfWeightsHisto( SumPdfWeights );
      hggSys->Loop();
      for ( auto tmp: myVectBinning )
	{
	  int bin = nominal->FindBin( tmp[0]+10, tmp[1]+0.0001 );
	  nominal->SetBinContent( bin, nominal->GetBinContent(bin) + hggSys->GetNominalYield( tmp[0], tmp[1] ) );
	}
      
      hggSys->WriteOutput( "histoMR_Rsq" );
      delete hggSys;
      if ( _debug ) std::cout << "deleted hggSys" << std::endl;
      //delete tmp;
      if ( _debug ) std::cout << "deleted tmp File" << std::endl;
    }

  
  //********************************************************
  //Print output
  //********************************************************
  std::ofstream outf;
  outf.open(outputFile.c_str());  

  /*
  std::cout << "#category\t\tmr_l\tmr_h\trsq_l\trsq_h\tSMHY\t\tFSU\t\tFSD";
  for( int ipdf = 0; ipdf < 60; ipdf++ ) std::cout << "\t\tPDF" << ipdf;
  std::cout << "\t\tJESU\t\tJESD"<< std::endl;
  */
   for ( auto tmp: myVectBinning )
     {
       int bin   = nominal->FindBin( tmp[0]+10, tmp[1]+0.0001 );
       float nom = nominal->GetBinContent( bin );
     }

   outf.close();
   
   
   TFile* sF = new TFile( "fullSys.root", "recreate" );
   nominal->Write("SMH_nominal");
   sF->Close();
   
   return 0;
};

