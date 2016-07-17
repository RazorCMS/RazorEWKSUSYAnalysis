#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <assert.h>
//LOCAL INCLUDES
#include "CommandLineInput.hh"
#include "HggAux.hh"


int main( int argc, char* argv[] )
{
  
  // primary list -- file with path to combine output root file
  std::string inputList = ParseCommandLine( argc, argv, "-inputList=" );
  if (  inputList == "" )
    {
      std::cerr << "[ERROR]: please provide an input file using --inputList=<path_to_file>" << std::endl;
      return -1;
    }
  
  // file containing nominal cross sections for models
  std::string xsecFile = ParseCommandLine( argc, argv, "-xsecFile=" );
  if ( xsecFile == "" ) {
    std::cerr << "[ERROR]: please provide an xsec file using --xsecFile=<path_to_file>" << std::endl;
    return -1;
  }

  std::ifstream ifs( inputList.c_str(), std::fstream::in );
  if ( ifs.is_open() )
    {
      std::string fname;
      while ( ifs.good() )
	{
	  ifs >> fname;
	  if ( ifs.eof() ) break;
	  std::cout << "[INFO]: fname-> " << fname << std::endl;
	}
    }
  else
    {
      std::cout << "Unable to open binning lookup table" << std::endl;
    }
  
  
  return 0;
}
