#include <iostream>
//LOCAL
#include "AssortedFunctions.hh"

 
void GetLimit(Limit &limit, std::string fname, float ssFactor )
{
  limit.exp = 5;
};
std::pair<float, float> GetMasses(std::string fname)
{
  return std::make_pair( 1, 1);
};
float GetCrossSectionLimit( float ssLimit, float msb )
{
  return -1;
};
