#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
//LOCAL INCLUDES
#include "CommandLineInput.hh"

//std::string ntupleDir = "/Users/cmorgoth/Work/data/HggRazorRun2/Analysis13TeV/CMSSW_7_6_March15_Ntuples/";
std::string ntupleDir = "/Users/cmorgoth/Work/data/HggRazorRun2/MC/CMSSW_7_6_March15_Ntuples/";

int main( int argc, char* argv[] )
{
  
  // primary input file -- will take bin edges, yields, and systematics from here
  std::string inputCF = ParseCommandLine( argc, argv, "-inputCF=" );
  if (  inputCF == "" )
    {
      std::cerr << "[ERROR]: please provide an input file using --inputCF=<path_to_file>" << std::endl;
      return -1;
    }
  // secondary input file -- will take yields from here and add them to the primary input file yields
  std::string secondInputCF = ParseCommandLine( argc, argv, "-secondInputCF=" );
  if ( secondInputCF != "" ) {
      std::cerr << "[INFO]: secondary input config file provided: " << secondInputCF << std::endl;
  }

  std::string dataFile = ParseCommandLine( argc, argv, "-dataFile=" );
  if (  dataFile == "" )
    {
      std::cerr << "[ERROR]: please provide an input data file using --dataFile=<path_to_file>" << std::endl;
      return -1;
    }

  std::string smhFile = ParseCommandLine( argc, argv, "-smhFile=" );
  if (  smhFile == "" )
    {
      std::cerr << "[ERROR]: please provide an input SMH file using --smhFile=<path_to_file>" << std::endl;
      return -1;
    }
  
  std::string signalFile = ParseCommandLine( argc, argv, "-signalFile=" );
  if (  signalFile == "" )
    {
      std::cerr << "[ERROR]: please provide an input SIGNAL file using --signalFile=<path_to_file>" << std::endl;
      return -1;
    }

  std::string sModel = ParseCommandLine( argc, argv, "-sModel=" );
  if (  sModel == "" )
    {
      std::cerr << "[ERROR]: please provide an input sModel name --sModel=<signalModelName>" << std::endl;
      return -1;
    }
  
  std::ifstream ifs( inputCF.c_str(), std::ifstream::in );
  assert(ifs);
  // get secondary input stream, if provided
  std::ifstream ifs2;
  if ( secondInputCF != "" ) {
      ifs2.open( secondInputCF.c_str(), std::ifstream::in );
  }
  
  std::string configCardName;
  int binNumber = 0;
  // while( ifs.good() )
  // {
      std::string category, MR_l, MR_h, Rsq_l, Rsq_h, SMH, Signal, Bkg_f1;
      Bkg_f1 = "singleExp";
      //  ifs >> configCardName;
      //if( ifs.eof() ) break;
      std::cerr << "[INFO]: opening configDataCard: "<< inputCF << std::endl;
      //std::ifstream tmpF( inputCF.c_str(), std::ifstream::in );
      //assert(tmpF);
      while( ifs.good() )
	{
	  std::stringstream SMH_sys;
	  std::stringstream Signal_sys;
          // first 6 items are: category, MR range, Rsq range, SM Higgs yield
	  ifs >> category >> MR_l >> MR_h >> Rsq_l >> Rsq_h >> SMH;
	  if ( category.find("#") != std::string::npos ) continue;
	  std::string tmp1;
	  SMH_sys << "\"";
          // the next 68 items are the systematics on SM Higgs (put in quotes, separated by spaces)
	  for ( int i = 0; i < 68; i++ )
	    {
	      ifs >> tmp1;
	      if ( i < 67 ) SMH_sys << tmp1 << " ";
	      else SMH_sys << tmp1 << "\"";
	    }
          // next is the signal yield
	  ifs >> Signal;
	  Signal_sys << "\"";
          // the next 68 items are the systematics on the signal (put in quotes, separated by spaces)
	  for ( int i = 0; i < 68; i++ )
	    {
	      ifs >> tmp1;
	      if ( i < 67 ) Signal_sys << tmp1 << " ";
	      else Signal_sys << tmp1 << "\"";
	    }
	  if ( ifs.eof() ) break;

          // if available, get line from secondary input source
          if ( secondInputCF != "" ) {
              if ( ifs2.good() ) {
                  std::string category2, MR_l2, MR_h2, Rsq_l2, Rsq_h2, SMH2, Signal2;
                  ifs2 >> category2 >> MR_l2 >> MR_h2 >> Rsq_l2 >> Rsq_h2 >> SMH2;
                  // make sure input is sane and warn if not
                  if ( !(category == category2 && MR_l == MR_l2 && MR_h == MR_h2 && Rsq_l == Rsq_l2 
                              && Rsq_h == Rsq_h2) ) {
                      std::cerr << "WARNING: bin definition is not the same in the two input files!\n"
                          << "File 1: " << category << " " << MR_l << " " << MR_h << " " << Rsq_l 
                          << " " << Rsq_h << std::endl
                          << "File 2: " << category2 << " " << MR_l2 << " " << MR_h2 << " " 
                          << Rsq_l2 << " " << Rsq_h2 << std::endl;
                  }

                  std::string tmp2;
                  // ignore the systematics values from this input file
                  for ( int i = 0; i < 68; i++ ) ifs2 >> tmp2;
                  // get the signal yield
                  ifs2 >> Signal2;
                  // ignore the systematics values from this input file
                  for ( int i = 0; i < 68; i++ ) ifs2 >> tmp2;

                  // add the SM Higgs yields together
                  SMH = std::to_string( atof(SMH.c_str()) + atof(SMH2.c_str()) );
                  // add the signal yields together
                  Signal = std::to_string( atof(Signal.c_str()) + atof(Signal2.c_str()) );
              }
              else {
                  std::cerr << "WARNING: secondary input file " << secondInputCF 
                      << " is out of input!" << std::endl;
              }
          }
	 
	  Bkg_f1 = "singleExp";
	  if ( binNumber == 3 || binNumber == 5 ) Bkg_f1 = "poly2";
	  if ( binNumber == 9 || binNumber == 16 ) Bkg_f1 = "poly3";
	  if ( binNumber == 15 ) Bkg_f1 = "modExp";
	  /*std::cout << category << "\t" << MR_l << "\t" << MR_h << "\t" << Rsq_l << "\t" << Rsq_h << "\t" << SMH << "\t" << SMH_sys.str()
	    << "\t" << Signal << "\t"  << Signal_sys.str() << std::endl; 
	  */
	  
	  std::cout << "./MakeFitRun2 " 
		    << "--inputFile=" << dataFile
		    << " --inputFileSignal=" << signalFile
		    << " --inputFileSMH=" << smhFile
		    << " --treeName=HggRazor --runPeriod=run2 --dataMode=data+signal --fitMode=datacard --category=" << category<< " --LowMRcut=" << MR_l 
		    << " --HighMRcut=" << MR_h << " --LowRSQcut=" << Rsq_l << " --HighRSQcut=" << Rsq_h << " --f1=" << Bkg_f1
		    << " --SMH_Yield=" << SMH << " --SMH_CL=" << SMH_sys.str()
		    << " --Signal_Yield=" << Signal << " --Signal_CL=" << Signal_sys.str()
		    << " --sModel=" << sModel
		    << " --binNumber=" << binNumber << " --detector=ebeb" << std::endl;
	  binNumber++;
	}
      //tmpF.close();
      //}
  ifs.close();
  if ( secondInputCF != "" ) {
      ifs2.close();
  }

  return 0;
}
