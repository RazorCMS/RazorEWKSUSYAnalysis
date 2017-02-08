//C++ INCLUDES
#include <iostream>
#include <map>
//ROOT INCLUDES
#include <TString.h>
//LOCAL INCLUDES
#include "CommandLineInput.hh"
#include "ToysAndIntegralFunctions.hh"

#define _debug 1

int main ( int argc, char* argv[] )
{
  std::cout << "[INFO]: Initializing program" << std::endl;

  std::string inputFile = ParseCommandLine( argc, argv, "-inputFile=" );
  if (  inputFile == "" )
    {
      std::cerr << "[ERROR]: please provide an input file using --inputFile=<path_to_file>" << std::endl;
      return -1;
    }
  
  return 0;
}
