#include <iostream>
#include <string>
#include <fstream>
#include <utility>

struct Limit
{
  float obs;
  float q2;
  float q16;
  float exp;
  float q68;
  float q96;
  float msb;
  float mlsp;
  float xsecL;
};


void GetLimit(Limit &limit, std::string fname, float ssFactor = 1.0 );
std::pair<float, float> GetMasses(std::string fname);
float GetCrossSectionLimit( float ssLimit, float msb );
