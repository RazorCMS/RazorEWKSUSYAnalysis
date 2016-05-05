//C++ INCLUDES
#include <iostream>
#include <map>
#include <stdlib.h>
//ROOT INCLUDES
#include <TString.h>
#include <THStack.h>
//LOCAL INCLUDES
#include "HggTree.hh"
#include "HggRazorClass.hh"
#include "HggAux.hh"
#include "CommandLineInput.hh"
#include "TChainTools.hh"
#include "PlotCosmetics.hh"

// D e f i n e  B i n n i n g
//---------------------------
//H
//int HggRazorClass::n_mgg   = 38;
//float HggRazorClass::mgg_l = 103.;
//float HggRazorClass::mgg_h = 160.;

//HighMass Diphotons
int HggRazorClass::n_mgg   = 50;
float HggRazorClass::mgg_l = 230.;
float HggRazorClass::mgg_h = 1230.;

//Z
//int HggRazorClass::n_mgg = 28;
//float HggRazorClass::mgg_l = 70.;
//float HggRazorClass::mgg_h = 112.;

int HggRazorClass::n_ptgg   = 52;
float HggRazorClass::ptgg_l = 0.;
float HggRazorClass::ptgg_h = 520.;

int HggRazorClass::n_sigmaMoverM   = 80;
float HggRazorClass::sigmaMoverM_l = .0;
float HggRazorClass::sigmaMoverM_h = .04;

int HggRazorClass::n_mr   = 50;
float HggRazorClass::mr_l = 130.;
float HggRazorClass::mr_h = 2630.;

int HggRazorClass::n_rsq   = 60;
float HggRazorClass::rsq_l = .0;
float HggRazorClass::rsq_h = 3.0;

int HggRazorClass::n_unroll_highPt  = 15;
int HggRazorClass::n_unroll_highRes = 10;

float HggRazorClass::highPt_MR[6] = {150., 200., 300., 500., 1600., 10000.};
float HggRazorClass::highPt_R0[6] = {0.0, 0.05, 0.1, 0.15, 0.2, 2.0};
float HggRazorClass::highPt_R1[5] = {0.0, 0.05, 0.1, 0.15, 2.0};
float HggRazorClass::highPt_R2[4] = {0.0, 0.05, 0.1, 2.0};
float HggRazorClass::highPt_R3[3] = {0.0, 0.05, 2.0};
float HggRazorClass::highPt_R4[2] = {0.0, 2.0};

float HggRazorClass::highRes_MR[5] = {150., 250., 400., 1400., 10000.};
float HggRazorClass::highRes_R0[5] = {0.0, 0.05, 0.1, 0.15, 2.0};
float HggRazorClass::highRes_R1[4] = {0.0, 0.05, 0.1, 2.0};
float HggRazorClass::highRes_R2[3] = {0.0, 0.05, 1.0};
float HggRazorClass::highRes_R3[2] = {0.0, 2.0};


//photon1
int HggRazorClass::n_pho1pt   = 70;
float HggRazorClass::pho1pt_l = .0;
float HggRazorClass::pho1pt_h = 700.0;

int HggRazorClass::n_pho1eta   = 30;
float HggRazorClass::pho1eta_l = -3.0;
float HggRazorClass::pho1eta_h = 3.0;

int HggRazorClass::n_pho1phi   = 40;
float HggRazorClass::pho1phi_l = -4.0;
float HggRazorClass::pho1phi_h = 4.0;

int HggRazorClass::n_pho1sigmaIetaIeta   = 50;
float HggRazorClass::pho1sigmaIetaIeta_l = .0;
float HggRazorClass::pho1sigmaIetaIeta_h = .02;

int HggRazorClass::n_pho1r9   = 50;
float HggRazorClass::pho1r9_l = 0.0;
float HggRazorClass::pho1r9_h = 1.5;

int HggRazorClass::n_pho1HoverE   = 30;
float HggRazorClass::pho1HoverE_l = 0.0;
float HggRazorClass::pho1HoverE_h = .06;

int HggRazorClass::n_pho1sumChargedHadronPt   = 50;
float HggRazorClass::pho1sumChargedHadronPt_l = 0.0;
float HggRazorClass::pho1sumChargedHadronPt_h = 5.0;

int HggRazorClass::n_pho1sumNeutralHadronEt   = 50;
float HggRazorClass::pho1sumNeutralHadronEt_l = 0.0;
float HggRazorClass::pho1sumNeutralHadronEt_h = 5.0;

int HggRazorClass::n_pho1sumPhotonEt   = 50;
float HggRazorClass::pho1sumPhotonEt_l = 0.0;
float HggRazorClass::pho1sumPhotonEt_h = 5.0;

int HggRazorClass::n_pho1sigmaEoverE   = 80;
float HggRazorClass::pho1sigmaEoverE_l = .00;
float HggRazorClass::pho1sigmaEoverE_h = .04;

//photon2
int HggRazorClass::n_pho2pt   = 70;
float HggRazorClass::pho2pt_l = .0;
float HggRazorClass::pho2pt_h = 700.0;

int HggRazorClass::n_pho2eta   = 30;
float HggRazorClass::pho2eta_l = -3.0;
float HggRazorClass::pho2eta_h = 3.0;

int HggRazorClass::n_pho2phi   = 40;
float HggRazorClass::pho2phi_l = -4.0;
float HggRazorClass::pho2phi_h = 4.0;

int HggRazorClass::n_pho2sigmaIetaIeta   = 50;
float HggRazorClass::pho2sigmaIetaIeta_l = .0;
float HggRazorClass::pho2sigmaIetaIeta_h = .02;

int HggRazorClass::n_pho2r9   = 50;
float HggRazorClass::pho2r9_l = 0.0;
float HggRazorClass::pho2r9_h = 1.5;

int HggRazorClass::n_pho2HoverE   = 30;
float HggRazorClass::pho2HoverE_l = 0.0;
float HggRazorClass::pho2HoverE_h = .06;

int HggRazorClass::n_pho2sumChargedHadronPt   = 50;
float HggRazorClass::pho2sumChargedHadronPt_l = 0.0;
float HggRazorClass::pho2sumChargedHadronPt_h = 5.0;

int HggRazorClass::n_pho2sumNeutralHadronEt   = 50;
float HggRazorClass::pho2sumNeutralHadronEt_l = 0.0;
float HggRazorClass::pho2sumNeutralHadronEt_h = 5.0;

int HggRazorClass::n_pho2sumPhotonEt   = 50;
float HggRazorClass::pho2sumPhotonEt_l = 0.0;
float HggRazorClass::pho2sumPhotonEt_h = 5.0;

int HggRazorClass::n_pho2sigmaEoverE = 80;
float HggRazorClass::pho2sigmaEoverE_l = .0;
float HggRazorClass::pho2sigmaEoverE_h = .04;

int HggRazorClass::n_njets = 11;
float HggRazorClass::njets_l = .0;
float HggRazorClass::njets_h = 10;

//C u s t o m MR_RSQ_BINNING
//--------------------------
//HighPt
const int N_HighPt = 5;
float MR_HighPt[N_HighPt+1] = {150,200,300,500,1600,3000};
float Rsq_HighPt[N_HighPt+1] = {0.01,0.05,0.10,0.15,0.20,1.00};

//HighRes
const int N_HighRes = 4;
float MR_HighRes[N_HighRes+1] = {150,250,400,1400,3000};
float Rsq_HighRes[N_HighRes+1] = {0.01,0.05,0.10,0.15,1.00};

//Hbb
const int N_Hbb = 2;
float MR_Hbb[N_Hbb+1] = {150,300,3000};
float Rsq_Hbb[N_Hbb+1] = {0.01,0.05,1.00};

float hpt_k[2]  = { 1.0, 1.0};
float hres_k[2] = { 1.0, 1.0};
float lres_k[2] = { 1.0, 1.0};

//-----------------------------------
//A p p l y   B a s e l i n e   C u t
//-----------------------------------

//DATA
//GammaGamma
//TString cut = "MR > 0.0 && t1Rsq > 0.0 && abs( pho1Eta ) < 1.48 && abs( pho2Eta ) < 1.48 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && pTGammaGamma>20 && mGammaGamma>103 && mGammaGamma<160 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1passIso == 1 && pho2passIso == 1";
//MGammaGamma HighMass
TString cut = "abs( pho1Eta ) < 1.48 && abs( pho2Eta ) < 1.48 && pho1Pt > 25. && pho2Pt> 25. && pTGammaGamma>0 && mGammaGamma>230 && mGammaGamma<1230 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1passIso == 1 && pho2passIso == 1";

//EBEB
//TString cut = "pho1passEleVeto == 0 && pho2passEleVeto == 0 && pho1passIso == 1 && pho2passIso == 1 && abs( pho1Eta ) < 1.479 && abs( pho2Eta ) < 1.479 && mGammaGamma>60. && mGammaGamma<120. && pho1Pt>30 && pho2Pt>20";

//EBEE
//TString cut = "pho1passEleVeto == 0 && pho2passEleVeto == 0 && pho1passIso == 1 && pho2passIso == 1 && ( ( abs( pho1Eta ) < 1.479 && abs( pho2Eta ) > 1.479 ) || (abs( pho1Eta ) > 1.479 && abs( pho2Eta ) < 1.479 ) ) && ( HLTDecision[30] == 1 || HLTDecision[31] == 1 ) && mGammaGamma>60. && mGammaGamma<120.";

//EEEE
//TString cut = "pho1passEleVeto == 0 && pho2passEleVeto == 0 && pho1passIso == 1 && pho2passIso == 1 && abs( pho1Eta ) > 1.479 && abs( pho2Eta ) > 1.479 && ( HLTDecision[30] == 1 || HLTDecision[31] == 1 ) && mGammaGamma>60. && mGammaGamma<120.";


//MC
//GammaGamma
//TString cut_mc = "MR > 0.0 && t1Rsq > 0.0 && abs( pho1Eta ) < 1.48 && abs( pho2Eta ) < 1.48 && ( pho1Pt > 40. || pho2Pt > 40. ) && pho1Pt > 25. && pho2Pt> 25. && pTGammaGamma>20 && mGammaGamma>103 && mGammaGamma<160 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1passIso == 1 && pho2passIso == 1";
//GammaGamma HighMass
TString cut_mc = "abs( pho1Eta ) < 1.48 && abs( pho2Eta ) < 1.48 && pho1Pt > 25. && pho2Pt> 25. && pTGammaGamma>0 && mGammaGamma>230 && mGammaGamma<1230 && pho1passEleVeto == 1 && pho2passEleVeto == 1 && pho1passIso == 1 && pho2passIso == 1";

//Zee
//EBEB
//TString cut_mc = "pho1passEleVeto == 0 && pho2passEleVeto == 0 && pho1passIso == 1 && pho2passIso == 1 && abs( pho1Eta ) < 1.479 && abs( pho2Eta ) < 1.479 && mGammaGamma>60. && mGammaGamma<120. && pho1Pt>30 && pho2Pt>20";

//EBEE
//TString cut_mc = "pho1passEleVeto == 0 && pho2passEleVeto == 0 && pho1passIso == 1 && pho2passIso == 1 && ( ( abs( pho1Eta ) < 1.479 && abs( pho2Eta ) > 1.479 ) || (abs( pho1Eta ) > 1.479 && abs( pho2Eta ) < 1.479 ) )  && ( HLTDecision[30] == 1 || HLTDecision[31] == 1 ) && mGammaGamma>60. && mGammaGamma<120.";

//EEEE
//TString cut_mc = "pho1passEleVeto == 0 && pho2passEleVeto == 0 && pho1passIso == 1 && pho2passIso == 1 && abs( pho1Eta ) > 1.479 && abs( pho2Eta ) > 1.479  && ( HLTDecision[30] == 1 || HLTDecision[31] == 1 ) && mGammaGamma>60. && mGammaGamma<120.";


//---------------------
//T r i g g e r   C u t 
//---------------------
//photons
//TString triggerCut = "(HLTDecision[63] || HLTDecision[64] || HLTDecision[65] || HLTDecision[66] || HLTDecision[67] || HLTDecision[68] || HLTDecision[69] || HLTDecision[74]) && (Flag_HBHENoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1)";
//Electrons
//TString triggerCut = "( HLTDecision[30] == 1 || HLTDecision[31] == 1 ) && (Flag_HBHENoiseFilter == 1 && Flag_CSCTightHaloFilter == 1 && Flag_goodVertices == 1 && Flag_eeBadScFilter == 1)";
TString triggerCut = "1";
//--------------------------------
//D i p h o t o n  M a s s   C u t 
//--------------------------------
TString mggCut = "1";

#define _debug 1

int main ( int argc, char* argv[] )
{
  std::cout << "[INFO]: Initializing program" << std::endl;
  std::cout << "[INFO]: Hgg Branching Fraction = " << HggRazorClass::GetHggBF() << std::endl;
  
  //Map Containing the lists for different processes 
  std::map< std::string, std::string > mapList;
  std::string inputFile = ParseCommandLine( argc, argv, "-inputFile=" );
  if (  inputFile == "" )
    {
      std::cerr << "[ERROR]: please provide an input file using --inputFile=<path_to_file>" << std::endl;
      return -1;
    }
  
  std::string run = ParseCommandLine( argc, argv, "-run=" );
  if (  run == "" )
    {
      std::cout << "[WARNING]: please provide a valid run, use --run=<run1/run2>" << std::endl;
      run = "run1";
    }

  std::string treeType = ParseCommandLine( argc, argv, "-treeType=" );
  if (  treeType == "" )
    {
      std::cout << "[WARNING]: please provide a valid treeType, use --treeType=<inclusive/category>" << std::endl;
      treeType = "inclusive";
    }

  //provides shape comparison
  std::string shapeOnly = ParseCommandLine( argc, argv, "-shapeOnly=" );
  bool _shapeOnly = false;
  if (  shapeOnly == "yes" )
    {
      std::cout << "[INFO]: re-scaling all histograms to unity" << std::endl;
      _shapeOnly = true;
    }
  //uses k-factors, defined above
  std::string useKF = ParseCommandLine( argc, argv, "-useKF=" );
  bool _useKF = false;
  if (  useKF == "yes" )
    {
      std::cout << "[INFO]: Using k-factor(s) hardcoded in main application" << std::endl;
      _useKF = true;
    }

  //plots mc and signal shapes 
  std::string signalPlot = ParseCommandLine( argc, argv, "-signalPlot=" );
  bool _signalPlot = false;
  if (  signalPlot == "yes" )
    {
      std::cout << "[INFO]: Will produce MC and signal shape plots" << std::endl;
      _signalPlot = true;
    }
  
  std::cout << "=================================" << std::endl;
  std::cout << "===========set parameters========" << std::endl;
  std::cout << "[INFO]: input file: " << inputFile << std::endl;
  std::cout << "[INFO]: run: " << run << std::endl;
  std::cout << "=================================" << std::endl;
  
  FillMapList( mapList, inputFile );
  if ( _debug ) std::cout << "[DEBUG]: map size: " << mapList.size() << std::endl;
  
  for( auto& myMap : mapList )
    {
      if ( _debug ) std::cout << "[DEBUG]: first: " << myMap.first << " second: " << myMap.second << std::endl;
    }
  
  TFile* f;
  TTree* tree;
  TChain* chain;
  TTree* cutTree;
  HggRazorClass* hggclass;
  THStack* stack;
  TLegend* leg;
  TLegend* leg2;
  TH1D* data;
  TH1D* signal;
  TH1D* mc;
  TH1D* mc2 = new TH1D();

  int map_size = mapList.size();
  const int nprocesses = 4;//mc+data
  //check nprocesses and map_size consistency
  if( map_size != nprocesses )
    {
      std::cerr << "[FATAL ERROR]: map size and nprocesses values are inconsistent!!, Please change nprocesses to map size: " << map_size << std::endl;
      exit( EXIT_FAILURE );
    }
  const int nplots = 4;
  double k_f = 1.37;//Difference in data/mc normalization
  const double lumi_frac = 1.0; // (5./19.8)
  const double lumi = 2317.0;
  const int mod = 0; 
  if ( treeType == "inclusive" )
    {
      std::cout << "[INFO]: running inclusive tree mode" << std::endl;
      int ctr = 0;
      Histos histos[nprocesses];
      for( const auto& process : Process() )
	{
	  std::string processName = GetProcessString( process );
	  //DY control region
	  //	  if ( !(process == Process::data || process == Process::dy) ) continue;
	  //HggRazor
	  /*if ( !(process == Process::data || process == Process::diphoton || process == Process::gammaJet
	    || process == Process::ggH || process == Process::vbfH || process == Process::vH || process == Process::ttH) ) continue;*/
	  //highmass
	  if ( !(process == Process::data || process == Process::diphoton || process == Process::gammaJet || process == Process::qcd) ) continue;
	  //Hggrazor with Signal
	  /*if ( !(process == Process::data || process == Process::signal || process == Process::diphoton || process == Process::gammaJet
		 || process == Process::ggH  || process == Process::vbfH || process == Process::vH || process == Process::ttH) ) continue;
		 std::cout << "[INFO] PROCESS: " << processName << " ,process #: " << ctr << std::endl;*/
	  //-----------------------------
	  // R e t r i e v i n g  T r e e
	  //-----------------------------
	  chain   = new TChain( "HggRazor" );
	  AddTChain( chain, mapList[processName] );
	  //need to create temporary root file to store cutTree
	  TFile* tmp = new TFile("tmp.root","recreate");
	  
	  //if ( !(process == Process::data || process == Process::diphoton || process == Process::gammaJet || process == Process::signal) ) continue;

	  /*if ( !(process == Process::data || process == Process::diphoton || process == Process::gammaJet || process == Process::qcd
	    || process == Process::ggH  || process == Process::vbfH || process == Process::vH || process == Process::ttH) ) continue;*/

	  /*if ( !(process == Process::data || process == Process::diphoton || process == Process::gammaJet
	    || process == Process::ggH  || process == Process::vbfH || process == Process::vH || process == Process::ttH) ) continue;*/
	  
	  //if ( !(process == Process::data || process == Process::diphoton || process == Process::gammaJet) ) continue;

	  
	  if ( chain == NULL )
	    {
	      std::cout << "[WARNING]: Empty selected tree in process: " << processName << std::endl;
	      continue;
	    }
	  //------------------------
	  //A p p l y i n g  C u t s
	  //------------------------
	  if ( process == Process::data )
	    {
	      cutTree = (TTree*)chain->CopyTree( cut + " && " + mggCut + " && " + triggerCut );
	    }
	  else
	    {
	      cutTree = (TTree*)chain->CopyTree( cut_mc + " && " + mggCut + " && " + triggerCut );
	    }
	  
	  if ( cutTree == NULL )
	    {
	      std::cout << "[WARNING]: Empty selected tree in process: " << processName << std::endl;
	      continue;
	    }

	  std::cout << "[INFO]: reduced TTree has been created" << std::endl;
	  //------------------------------------------------
	  //C r e a t in g   S e l e c t i o n   O b j e c t
	  //------------------------------------------------
	  hggclass = new HggRazorClass( cutTree, processName, "INCLUSIVE", true, true );
	  hggclass->InitMrRsqCustomHisto( N_HighRes, MR_HighRes, N_HighRes, Rsq_HighRes );
	  //Creating Histos
	  hggclass->Loop();
	  //Assigning Histos
	  histos[ctr].process = process;
	  //-----------------------------
	  //Assigning Histograms to Array
	  //-----------------------------
	  std::cout << "DEB3" << std::endl;
	  for ( const auto& htmp : HistoTypes() )
	    {
	      std::cout << GetHistoTypesString( htmp ) << std::endl;
	      TH1F h_scale = hggclass->GetHisto( htmp );
	      //if ( run == "run2" ) h_scale.Scale( k_f ); 
	      histos[ctr].AssignHisto( htmp, h_scale );
	    }
	  std::cout << "DEB4" << std::endl;
	  ctr++;
	  delete hggclass;
	}
      //---------------
      //P l o t t i n g
      //---------------
      std::cout << "PLOTTING" << std::endl;
      for ( const auto& htmp : HistoTypes() )
	{
	  std::string histoName = GetHistoTypesString( htmp );
	  //std::cout << "histoName: " << histoName << std::endl;
	  stack = new THStack( "hs" , "Hgg Stack " );
	  leg = new TLegend( 0.7, 0.58, 0.93, 0.89, NULL, "brNDC" );
	  leg2 = new TLegend( 0.7, 0.58, 0.93, 0.89, NULL, "brNDC" );
	  bool _isFirstMC = true;
	  //std::cout << "deb1: " << histoName << std::endl;
	  float NormFactor = 1.0;//Scale mc to unity if required
	  for (  int i  = 0; i < nprocesses; i++ )
	    {
	      TH1F* tmp_h = new TH1F( histos[i].GetHisto( htmp ) );
	      TH1D* h_s = GetStyledHisto( (TH1D*)tmp_h, histos[i].process );
	      if ( histos[i].process == Process::data )
		{
		  data = new TH1D ( *h_s );
		  if ( _shapeOnly ) data->Scale(1.0/data->Integral());
		}
	      else if ( histos[i].process != Process::signal )
		{
		  h_s->Scale( lumi );
		  if ( _useKF && (histos[i].process == Process::diphoton || histos[i].process == Process::gammaJet) ) h_s->Scale( k_f );
		  std::cout << "stacking " << GetProcessString( histos[i].process ) << std::endl;
		  if ( mc == NULL || _isFirstMC )
		    {
		      mc = new TH1D( *h_s );
		      _isFirstMC = false;
		    }
		  else
		    {
		      mc->Add( h_s );
		    }
		}
	      else
		{
		  signal = new TH1D ( *h_s );
		  if ( _shapeOnly ) signal->Scale(1.0/signal->Integral());
		}
	      //std::cout << i << " " << GetProcessString( histos[i].process ) << std::endl;
	      //if ( histos[i].process == Process::data )std::cout << "histo: " << histoName << "data->" << data->Integral() << std::endl;
	      //else std::cout << histoName << "-> " << mc->Integral() << std::endl;
	      
	      AddLegend( h_s, leg, histos[i].process );
	      if (  histos[i].process != Process::data ) AddLegend( h_s, leg2, histos[i].process );
	    }
	  std::cout << "===================================" << std::endl;
	  std::cout << "data-> " << data->Integral() << std::endl;
	  std::cout << "MC-> " << mc->Integral() << std::endl;
	  std::cout << "===================================" << std::endl;
	  NormFactor = mc->Integral();
	  if ( _shapeOnly ) mc->Scale(1.0/NormFactor);
	  for (  int i  = 0; i < nprocesses; i++ )
	    {
	      TH1F* tmp_h = new TH1F( histos[i].GetHisto( htmp ) );
	      TH1D* h_s = GetStyledHisto( (TH1D*)tmp_h, histos[i].process );
	      h_s->Scale( lumi );
	      if ( _useKF && (histos[i].process == Process::diphoton || histos[i].process == Process::gammaJet) ) h_s->Scale( k_f );
	      if ( _shapeOnly ) h_s->Scale(1.0/NormFactor);
	      if ( histos[i].process != Process::data && histos[i].process != Process::signal ) stack->Add( h_s, "histo" );
	    }
	  if ( run == "run2" )
	    {
	      if ( _signalPlot ) MakeStackPlotSignal( stack, signal, histoName, "plots/" + histoName + "_" + "Signal", leg2 );
	      MakeStackPlot( stack, data, mc, histoName, "plots/" + histoName + "_" + "INCLUSIVE", leg );
	    }
	}
      std::cout << "deleting hggclass object" << std::endl;
      delete hggclass;
      return -1;
    }
  else if ( treeType == "category" )
    {
      for( const auto& box : Boxes() )
	{
	  std::string boxName = GetBoxString( box );
	  int ctr = 0;
	  Histos histos[nprocesses];
	  
	  for( const auto& process : Process() )
	    {
	      std::string processName = GetProcessString( process );
	      if ( process == Process::data && run == "run2" )
		{
		  std::cout << "[INFO]: run2 will skip data category" << std::endl;
		  continue;
		}
	      if ( process == Process::qcd ) continue;
	      //if ( process == Process::qcd || process == Process::gammaJet || process == Process::diphoton ) continue;
	      std::cout << "====================================" << std::endl;
	      std::cout << "[INFO]: process name: " << processName << std::endl;
	      std::cout << "====================================" << std::endl;
	      
	      
	      if ( process == Process::gammaJet || process == Process::diphoton || process == Process::qcd )
		{
		  //13/8 TeV
		  k_f = hres_k[mod]*lumi_frac;
		  if ( box == Boxes::HighPt ) k_f = hpt_k[mod]*lumi_frac;
		  if ( box == Boxes::LowRes ) k_f = lres_k[mod]*lumi_frac;
		}
	      
	      // R e t r i e v i n g  T r e e
	      //-----------------------------
	      chain   = new TChain( boxName.c_str() );
	      AddTChain( chain, mapList[processName] );
	      
	      //need to create temporary root file to store cutTree
	      TFile* tmp = new TFile("tmp","recreate");
	      //A p p l y i n g  C u t s
	      //------------------------
	      cutTree = (TTree*)chain->CopyTree( cut + " && " + mggCut + " && " + triggerCut );
	      if ( cutTree == NULL )
		{
		  std::cout << "[WARNING]: Empty selected tree: " << boxName << std::endl;
		  continue;
		}
	      //C r e a t in g   S e l e c t i o n   O b j e c t
	      //------------------------------------------------
	      hggclass = new HggRazorClass( cutTree, processName, boxName, false, false );
	      if ( box == Boxes::HighPt )
		{
		  hggclass->InitMrRsqCustomHisto( N_HighPt, MR_HighPt, N_HighPt, Rsq_HighPt );
		}
	      else if ( box == Boxes::HighRes || box == Boxes::LowRes )
		{
		  hggclass->InitMrRsqCustomHisto( N_HighRes, MR_HighRes, N_HighRes, Rsq_HighRes );
		}
	      else if( box == Boxes::Hbb || box == Boxes::Zbb )
		{
		  hggclass->InitMrRsqCustomHisto( N_Hbb, MR_Hbb, N_Hbb, Rsq_Hbb );
		}
	      else
		{
		  std::cout << "[WARNING]: Undefined box->" << std::endl;
		}
	      //Creating Histos
	      hggclass->Loop();
	      //Assigning Histos
	      histos[ctr].process = process;
	      for ( const auto& htmp : HistoTypes() )
		{
		  TH1F h_scale = hggclass->GetHisto( htmp );
		  //if ( run == "run2" ) h_scale.Scale( k_f ); 
		  histos[ctr].AssignHisto( htmp, h_scale );
		}
	      ctr++;
	      //hggclass->WriteOutput( boxName );
	      //Cosmetics
	    }
	  //Plotting
	  for ( const auto& htmp : HistoTypes() )
	    {
	      std::string histoName = GetHistoTypesString( htmp );
	      std::cout << "making " <<  histoName << std::endl;
	      stack = new THStack( "hs" , "Hgg Stack " );
	      leg = new TLegend( 0.7, 0.58, 0.93, 0.89, NULL, "brNDC" );
	      bool _isFirstMC = true;
	      for (  int i  = 0; i < nprocesses; i++ )
		{
		  std::cout << "DEB "<< std::endl;
		  TH1F* tmp_h = new TH1F( histos[i].GetHisto( htmp ) );
		  std::cout << "DEB "<< std::endl;
		  TH1D* h_s = GetStyledHisto( (TH1D*)tmp_h, histos[i].process );
		  std::cout << "DEB "<< std::endl;
		  if ( histos[i].process == Process::data )
		    {
		      std::cout << "DEBdata "<< std::endl;
		      data = new TH1D ( *h_s ); 
		    }
		  else
		    {
		      stack->Add( h_s, "histo" );
		      if ( mc == NULL || _isFirstMC )
			{
			  std::cout << "creating mc" << std::endl;
			  mc = new TH1D( *h_s );
			  _isFirstMC = false;
			}
		      else
			{
			  std::cout << "DEBmc "<< std::endl;
			  mc->Add( h_s );
			}
		    }
		  std::cout << i << " " << GetProcessString( histos[i].process ) << std::endl;
		  AddLegend( h_s, leg, histos[i].process );
		}
	      if ( run == "run2" )
		{
		  //MakeStackPlot( stack, histoName, "plots/13TeV/" + histoName + "_" + boxName + "_Inclusive_Resonant", leg );
		  //MakeStackPlot( stack, histoName, "plots/13TeV/" + histoName + "_" + boxName + "_Mr250Rsq0p05_Resonant", leg );
		  //MakeStackPlot( stack, histoName, "plots/13TeV/Hybrid/" + histoName + "_" + boxName + "_Inclusive_Resonant", leg );
		  //MakeStackPlot( stack, histoName, "plots/13TeV/Hybrid/Resonant/" + histoName + "_" + boxName + "_Mr400_Rsq0p05_Resonant", leg );
		  //MakeStackPlot( stack, histoName, "plots/13TeV/Hybrid/Full/" + histoName + "_" + boxName + "_Mr200_Rsq0p02_Full", leg );
		  MakeStackPlot( stack, histoName, "plots/13TeV/Hybrid/Full/" + histoName + "_" + boxName + "_Inclusive_Full", leg );
		}
	      else
		{
		  //MakeStackPlot( stack, data, mc, histoName, "plots/8TeV/" + histoName + "_" + boxName + "_Mr250_Rsq0p035", leg );
		  MakeStackPlot( stack, data, mc, histoName, "plots/8TeV/" + histoName + "_" + boxName + "_Inclusive", leg );
		}
	      std::cout << "leaving " <<  histoName << std::endl;
	      delete leg;
	      delete stack;
	      delete mc;
	      //mc = NULL;
	      if ( run != "run2" ) delete data;
	    }
	}
    }
  else
    {
      std::cerr << "[ERROR]: undefined treeType, plese use --treeType<inclusive/category>" << std::endl;
      return -1;
    }
  
  return 0;
}
