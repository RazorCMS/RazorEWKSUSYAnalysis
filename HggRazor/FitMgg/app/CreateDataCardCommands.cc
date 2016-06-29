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
  
  std::string inputCF = ParseCommandLine( argc, argv, "-inputCF=" );
  if (  inputCF == "" )
    {
      std::cerr << "[ERROR]: please provide an input file using --inputCF=<path_to_file>" << std::endl;
      return -1;
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
  
  std::string configCardName;
  int binNumber = 0;
  // while( ifs.good() )
  // {
      std::string category, MR_l, MR_h, Rsq_l, Rsq_h, SMH, Signal, Bkg_f1;
      Bkg_f1 = "singleExp";
      //  ifs >> configCardName;
      //if( ifs.eof() ) break;
      std::cout << "[INFO]: opening configDataCard: "<< inputCF << std::endl;
      //std::ifstream tmpF( inputCF.c_str(), std::ifstream::in );
      //assert(tmpF);
      while( ifs.good() )
	{
	  std::stringstream SMH_sys;
	  std::stringstream Signal_sys;
	  ifs >> category >> MR_l >> MR_h >> Rsq_l >> Rsq_h >> SMH;
	  if ( category.find("#") != std::string::npos ) continue;
	  std::string tmp1;
	  SMH_sys << "\"";
	  for ( int i = 0; i < 68; i++ )
	    {
	      ifs >> tmp1;
	      if ( i < 67 ) SMH_sys << tmp1 << " ";
	      else SMH_sys << tmp1 << "\"";
	    }
	  ifs >> Signal;
	  Signal_sys << "\"";
	  for ( int i = 0; i < 68; i++ )
	    {
	      ifs >> tmp1;
	      if ( i < 67 ) Signal_sys << tmp1 << " ";
	      else Signal_sys << tmp1 << "\"";
	    }
	  
	 
	  if ( ifs.eof() ) break;
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

  return 0;
}
