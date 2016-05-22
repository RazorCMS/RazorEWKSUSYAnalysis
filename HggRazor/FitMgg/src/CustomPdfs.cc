#include <iostream>
#include <math.h>
#include <TMath.h>

#include "CustomPdfs.hh"
#include <RooRealVar.h>
#include <RooRealConstant.h>

using namespace RooFit;
using namespace std; 

ClassImp(RooCB);

RooCB::RooCB(){};

RooCB::RooCB(const char *name, const char *title,
	     RooAbsReal& _x,
	     RooAbsReal& _mean,
	     RooAbsReal& _width,
	     RooAbsReal& _alpha,
	     RooAbsReal& _n,
              RooAbsReal& _theta
	     ) :
  RooAbsPdf(name,title),
  x("x","x",this,_x),
  mean("mean","mean",this,_mean),
  width("width","width",this,_width),
  alpha("alpha","alpha",this,_alpha),
  n("n","n",this,_n),
  theta("theta","theta",this,_theta)
{
};

RooCB::RooCB(const RooCB& other, const char* name) :
  RooAbsPdf(other,name),
  x("x",this,other.x),
  mean("mean",this,other.mean),
  width("width",this,other.width),
  alpha("alpha",this,other.alpha),
  n("n",this,other.n),
  theta("theta",this,other.theta)
{
};

double RooCB::evaluate() const
{
  double a = cos(theta)*alpha - sin(theta)*width;
  double w = sin(theta)*alpha + cos(theta)*width;

  double t = (x-mean)/w;
  if(a<0) t = -t;

  double absa = fabs((double)a);

  double A = TMath::Power(n/absa,n)*exp(-0.5*absa*absa);
  double B = n/absa-absa;

  if(t >= -absa){
    return exp(-0.5*t*t);
  }else{
    return A/TMath::Power(B-t,n);
  }
};

//HighMass Diphoton
ClassImp(RooHMDiphoton);

RooHMDiphoton::RooHMDiphoton(){};

RooHMDiphoton::RooHMDiphoton(const char *name, const char *title,
			     RooAbsReal& _x,
			     RooAbsReal& _a,
			     RooAbsReal& _b
			     ) :
  RooAbsPdf(name,title),
  x("x","x",this,_x),
  a("a","a",this,_a),
  b("b","b",this,_b)
  
{
};

RooHMDiphoton::RooHMDiphoton(const RooHMDiphoton& other, const char* name) :
  RooAbsPdf(other,name),
  x("x",this,other.x),
  a("a",this,other.a),
  b("b",this,other.b)
{
};

double RooHMDiphoton::evaluate() const
{
  if ( x < 0 ) return 0.0;
  return TMath::Power( x, a+b*TMath::Log(x) );
  
};

//RooDoubleCB
ClassImp(RooDoubleCB)

RooDoubleCB::RooDoubleCB( ){ };

RooDoubleCB::RooDoubleCB(const char *name, const char *title, 
			 RooAbsReal& _x,
			 RooAbsReal& _mean,
			 RooAbsReal& _width,
			 RooAbsReal& _alpha1,
			 RooAbsReal& _n1,
			 RooAbsReal& _alpha2,
			 RooAbsReal& _n2
			 ) :
  RooAbsPdf(name,title), 
  x("x","x",this,_x),
  mean("mean","mean",this,_mean),
  width("width","width",this,_width),
  alpha1("alpha1","alpha1",this,_alpha1),
  n1("n1","n1",this,_n1),
  alpha2("alpha2","alpha2",this,_alpha2),
  n2("n2","n2",this,_n2)
{ 
};


RooDoubleCB::RooDoubleCB(const RooDoubleCB& other, const char* name) :  
  RooAbsPdf(other,name), 
  x("x",this,other.x),
  mean("mean",this,other.mean),
  width("width",this,other.width),
  alpha1("alpha1",this,other.alpha1),
  n1("n1",this,other.n1),
  alpha2("alpha2",this,other.alpha2),
  n2("n2",this,other.n2)

{ 
};

double RooDoubleCB::evaluate() const 
{ 
  double t = (x-mean)/width;
  if( t >= -alpha1 && t <= alpha2 )
    {
      return exp(-0.5*t*t);
    }
  else if ( t < -alpha1 )
    {
      double A1 = pow(n1/fabs(alpha1),n1)*exp(-alpha1*alpha1/2);
      double B1 = n1/fabs(alpha1)-fabs(alpha1);
      return A1*pow(B1-t,-n1);
    }
  else if ( t > alpha2 )
    {
      double A2 = pow(n2/fabs(alpha2),n2)*exp(-alpha2*alpha2/2);
      double B2 = n2/fabs(alpha2)-fabs(alpha2);
      return A2*pow(B2+t,-n2);
    }
  else
    {
      cout << "ERROR evaluating range... t = " << t << endl;
      return 99;
    }
   
};

Int_t RooDoubleCB::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* range) const 
{
  if (matchArgs(allVars,analVars,x)) return 1;
  return 0;
};

Double_t RooDoubleCB::analyticalIntegral(Int_t code, const char* rangeName) const 
{
  assert(code==1) ;
 
  double central=0;
  double left=0;
  double right=0;
 
  static const Double_t root2 = sqrt(2) ;
  static const Double_t rootPiBy2 = sqrt(atan2(0.0,-1.0)/2.0);
  Double_t xscale = root2*width;
 
  //compute gaussian contribution
  double central_low =max(x.min(rangeName),mean - alpha1*width );
  double central_high=min(x.max(rangeName),mean + alpha2*width );
  if(central_low < central_high) // is the gaussian part in range?
    central = rootPiBy2*width*(TMath::Erf((central_high-mean)/xscale)-TMath::Erf((central_low-mean)/xscale));
 
  //compute left tail;
  double A1 = pow(n1/fabs(alpha1),n1)*exp(-alpha1*alpha1/2);
  double B1 = n1/fabs(alpha1)-fabs(alpha1);
 
  double left_low=x.min(rangeName);
  double left_high=min(x.max(rangeName),mean - alpha1*width);
  if(left_low < left_high){ //is the left tail in range?
    if(fabs(n1-1.0)>1.e-5)
      left = A1/(-n1+1.0)*width*(pow(B1-(left_low-mean)/width,-n1+1.)-pow(B1-(left_high-mean)/width,-n1+1.));
    else
      left = A1*width*(log(B1-(left_low-mean)/width) - log(B1-(left_high-mean)/width) );
  }
 
  //compute right tail;
  double A2 = pow(n2/fabs(alpha2),n2)*exp(-alpha2*alpha2/2);
  double B2 = n2/fabs(alpha2)-fabs(alpha2);
 
  double right_low=max(x.min(rangeName),mean + alpha2*width);
  double right_high=x.max(rangeName);
  if(right_low < right_high){ //is the right tail in range?
    if(fabs(n2-1.0)>1.e-5)
      right = A2/(-n2+1.0)*width*(pow(B2+(right_high-mean)/width,-n2+1.)-pow(B2+(right_low-mean)/width,-n2+1.));
    else
      right = A2*width*(log(B2+(right_high-mean)/width) - log(B2+(right_low-mean)/width) );
  }
     
  return left+central+right;
 
};

//RooDoubleCBInterpolate
ClassImp(RooDoubleCBInterpolate)

RooDoubleCBInterpolate::RooDoubleCBInterpolate( ){ };

RooDoubleCBInterpolate::RooDoubleCBInterpolate(const char *name, const char *title, 
					       RooAbsReal& _x,
					       RooAbsReal& _mass
					       ) :
  RooAbsPdf(name,title), 
  x("x","x",this,_x),
  mass("mass","mass",this, _mass)
{
};


RooDoubleCBInterpolate::RooDoubleCBInterpolate(const RooDoubleCBInterpolate& other, const char* name) :  
  RooAbsPdf(other,name), 
  x("x",this,other.x),
  mass("mass",this, other.mass)
{ 
};

Double_t RooDoubleCBInterpolate::getMean( Double_t m ) const
{
  if ( m  < 500 )
    {
      return 0.998226*m;
    }
  else if ( m >= 500. && m < 740. )
    {
      return ((737.55-499.113)/(740.-500.))*(m-500.) + 499.113;
    }
  else if ( m >= 740. && m < 745. )
    {
      return ((742.696-737.55)/(745.-740.))*(m-740.) + 737.55;
    }
  else if (  m >= 745. && m < 750. )
    {
      return ((747.501-742.696)/(750.-745.))*(m-745.) + 742.696;
    }
  else if (  m >= 750. && m < 755. )
    {
      return ((752.634-747.501)/(755.-750.))*(m-750.) + 747.501;
    }
  else if (  m >= 755. && m < 760. )
    {
      return ((757.577-752.634)/(760.-755.))*(m-755.) + 752.634;
    }
  else if (  m >= 760. && m < 1000. )
    {
      return ((995.441-757.577)/(1000.-760.))*(m-760.) + 757.577;
    }
  else if (  m >= 1000. && m < 1250. )
    {
      return  ((1242.48-995.441)/(1250.-1000.))*(m-1000.) + 995.441;
    }
  else if (  m >= 1250. && m < 1500. )
    {
      return ((1489.63-1242.48)/(1500.-1250.))*(m-1250.) + 1242.48;
    }
  else if (  m >= 1500. && m < 1750. )
    {
      return ((1736.32-1489.63)/(1750.-1500.))*(m-1500.) + 1489.63;
    }
  else if (  m >= 1750. && m < 2000. )
    {
      return ((1983.38-1736.32)/(2000.-1750.))*(m-1750.) + 1736.32;
    }
  else if (  m >= 2000. && m < 2250. )
    {
      return ((2230.57-1983.38)/(2250.-2000.))*(m-2000.) + 1983.38;
    }
  else if (  m >= 2250. && m < 2500. )
    {
      return ((2477.21-2230.57)/(2500.-2250.))*(m-2250.) + 2230.57;
    }
  else if (  m >= 2500. && m < 2750. )
    {
      return ((2723.35-2477.21)/(2750.-2500.))*(m-2500.) + 2477.21;
    }
  else if (  m >= 2750. && m < 3000. )
    {
      return ((2968.51-2723.35)/(3000.-2750.))*(m-2750.) + 2723.35;
    }
  else if (  m >= 3000. && m < 3250. )
    {
      return ((3214.51-2968.51)/(3250.-3000.))*(m-3000.) + 2968.51;
    }
  else if (  m >= 3250. && m < 3500. )
    {
      return ((3460.37-3214.51)/(3500.-3250.))*(m-3250.) + 3214.51;
    }
  else if (  m >= 3500. && m < 3750. )
    {
      return ((3706.29-3460.37)/(3750.-3500.))*(m-3500.) + 3460.37;
    }
  else if (  m >= 3750. && m < 4000. )
    {
      return ((3957.41-3706.29)/(4000.-3750.))*(m-3750.) + 3706.29;
    }
 return 0.9893525*m;
};

Double_t RooDoubleCBInterpolate::getSigma( Double_t m ) const
{
  if ( m  < 500 )
    {
      return 4.71304;
    }
  else if ( m >= 500. && m < 740. )
    {
      return ((6.95368-4.71304)/(740.-500.))*(m-500.) + 4.71304;
    }
  else if ( m >= 740. && m < 745. )
    {
      return ((7.03181-6.95368)/(745.-740.))*(m-740.) + 6.95368;
    }
  else if (  m >= 745. && m < 750. )
    {
      return ((7.03829-7.03181)/(750.-745.))*(m-745.) + 7.03181;
    }
  else if (  m >= 750. && m < 755. )
    {
      return ((7.24748-7.03829)/(755.-750.))*(m-750.) + 7.03829;
    }
  else if (  m >= 755. && m < 760. )
    {
      return ((6.93232-7.24748)/(760.-755.))*(m-755.) + 7.24748;
    }
  else if (  m >= 760. && m < 1000. )
    {
      return ((9.50926-6.93232)/(1000.-760.))*(m-760.) + 6.93232;
    }
  else if (  m >= 1000. && m < 1250. )
    {
      return  ((11.9767-9.50926)/(1250.-1000.))*(m-1000.) + 9.50926;
    }
  else if (  m >= 1250. && m < 1500. )
    {
      return ((14.5047-11.9767)/(1500.-1250.))*(m-1250.) + 11.9767;
    }
  else if (  m >= 1500. && m < 1750. )
    {
      return ((16.8543-14.5047)/(1750.-1500.))*(m-1500.) + 14.5047;
    }
  else if (  m >= 1750. && m < 2000. )
    {
      return ((19.6088-16.8543)/(2000.-1750.))*(m-1750.) + 16.8543;
    }
  else if (  m >= 2000. && m < 2250. )
    {
      return ((22.1248-19.6088)/(2250.-2000.))*(m-2000.) + 19.6088;
    }
  else if (  m >= 2250. && m < 2500. )
    {
      return ((25.0484-22.1248)/(2500.-2250.))*(m-2250.) + 22.1248;
    }
  else if (  m >= 2500. && m < 2750. )
    {
      return ((27.5967-25.0484)/(2750.-2500.))*(m-2500.) + 25.0484;
    }
  else if (  m >= 2750. && m < 3000. )
    {
      return ((30.546-27.5967)/(3000.-2750.))*(m-2750.) + 27.5967;
    }
  else if (  m >= 3000. && m < 3250. )
    {
      return ((33.7079-30.546)/(3250.-3000.))*(m-3000.) + 30.546;
    }
  else if (  m >= 3250. && m < 3500. )
    {
      return ((35.8802-33.7079)/(3500.-3250.))*(m-3250.) + 33.7079;
    }
  else if (  m >= 3500. && m < 3750. )
    {
      return ((39.1346-35.8802)/(3750.-3500.))*(m-3500.) + 35.8802;
    }
  else if (  m >= 3750. && m < 4000. )
    {
      return ((41.744-39.1346)/(4000.-3750.))*(m-3750.) + 39.1346;
    }
  
  return 0.01044*m;
};

Double_t RooDoubleCBInterpolate::getAlpha1( Double_t m ) const
{
  if ( m  < 500 )
    {
      return 1.24366;
    }
  else if ( m >= 500. && m < 740. )
    {
      return ((1.32445-1.24366)/(740.-500.))*(m-500.) + 1.24366;
    }
  else if ( m >= 740. && m < 745. )
    {
      return ((1.31705-1.32445)/(745.-740.))*(m-740.) + 1.32445;
    }
  else if (  m >= 745. && m < 750. )
    {
      return ((1.29296-1.31705)/(750.-745.))*(m-745.) + 1.31705;
    }
  else if (  m >= 750. && m < 755. )
    {
      return ((1.33272-1.29296)/(755.-750.))*(m-750.) + 1.29296;
    }
  else if (  m >= 755. && m < 760. )
    {
      return ((1.23588-1.33272)/(760.-755.))*(m-755.) + 1.33272;
    }
  else if (  m >= 760. && m < 1000. )
    {
      return ((1.2881-1.23588)/(1000.-760.))*(m-760.) + 1.23588;
    }
  else if (  m >= 1000. && m < 1250. )
    {
      return  ((1.29209-1.2881)/(1250.-1000.))*(m-1000.) + 1.2881;
    }
  else if (  m >= 1250. && m < 1500. )
    {
      return ((1.31867-1.29209)/(1500.-1250.))*(m-1250.) + 1.29209;
    }
  else if (  m >= 1500. && m < 1750. )
    {
      return ((1.27682-1.31867)/(1750.-1500.))*(m-1500.) + 1.31867;
    }
  else if (  m >= 1750. && m < 2000. )
    {
      return ((1.28911-1.27682)/(2000.-1750.))*(m-1750.) + 1.27682;
    }
  else if (  m >= 2000. && m < 2250. )
    {
      return ((1.22497-1.28911)/(2250.-2000.))*(m-2000.) + 1.28911;
    }
  else if (  m >= 2250. && m < 2500. )
    {
      return ((1.19581-1.22497)/(2500.-2250.))*(m-2250.) + 1.22497;
    }
  else if (  m >= 2500. && m < 2750. )
    {
      return ((1.12843-1.19581)/(2750.-2500.))*(m-2500.) + 1.19581;
    }
  else if (  m >= 2750. && m < 3000. )
    {
      return ((1.25584-1.12843)/(3000.-2750.))*(m-2750.) + 1.12843;
    }
  else if (  m >= 3000. && m < 3250. )
    {
      return ((1.22101-1.25584)/(3250.-3000.))*(m-3000.) + 1.25584;
    }
  else if (  m >= 3250. && m < 3500. )
    {
      return ((1.13156-1.22101)/(3500.-3250.))*(m-3250.) + 1.22101;
    }
  else if (  m >= 3500. && m < 3750. )
    {
      return ((1.08709-1.13156)/(3750.-3500.))*(m-3500.) + 1.13156;
    }
  else if (  m >= 3750. && m < 4000. )
    {
      return ((0.495629-1.08709)/(4000.-3750.))*(m-3750.) + 1.08709;
    }
  return 0.495629;
};

Double_t RooDoubleCBInterpolate::getN1( Double_t m ) const
{
  if ( m  < 500 )
    {
      return 2.81157;
    }
  else if ( m >= 500. && m < 740. )
    {
      return ((2.59159-2.81157)/(740.-500.))*(m-500.) + 2.81157;
    }
  else if ( m >= 740. && m < 745. )
    {
      return ((2.68365-2.59159)/(745.-740.))*(m-740.) + 2.59159;
    }
  else if (  m >= 745. && m < 750. )
    {
      return ((2.74203-2.68365)/(750.-745.))*(m-745.) + 2.68365;
    }
  else if (  m >= 750. && m < 755. )
    {
      return ((2.60803-2.74203)/(755.-750.))*(m-750.) + 2.74203;
    }
  else if (  m >= 755. && m < 760. )
    {
      return ((2.87792-2.60803)/(760.-755.))*(m-755.) + 2.60803;
    }
  else if (  m >= 760. && m < 1000. )
    {
      return ((2.78344-2.87792)/(1000.-760.))*(m-760.) + 2.87792;
    }
  else if (  m >= 1000. && m < 1250. )
    {
      return  ((2.83202-2.78344)/(1250.-1000.))*(m-1000.) + 2.78344;
    }
  else if (  m >= 1250. && m < 1500. )
    {
      return ((2.76646-2.83202)/(1500.-1250.))*(m-1250.) + 2.83202;
    }
  else if (  m >= 1500. && m < 1750. )
    {
      return ((2.97399-2.76646)/(1750.-1500.))*(m-1500.) + 2.76646;
    }
  else if (  m >= 1750. && m < 2000. )
    {
      return ((2.93861-2.97399)/(2000.-1750.))*(m-1750.) + 2.97399;
    }
  else if (  m >= 2000. && m < 2250. )
    {
      return ((3.24526-2.93861)/(2250.-2000.))*(m-2000.) + 2.93861;
    }
  else if (  m >= 2250. && m < 2500. )
    {
      return ((3.33493-3.24526)/(2500.-2250.))*(m-2250.) + 3.24526;
    }
  else if (  m >= 2500. && m < 2750. )
    {
      return ((3.70123-3.33493)/(2750.-2500.))*(m-2500.) + 3.33493;
    }
  else if (  m >= 2750. && m < 3000. )
    {
      return ((2.78014-3.70123)/(3000.-2750.))*(m-2750.) + 3.70123;
    }
  else if (  m >= 3000. && m < 3250. )
    {
      return ((2.9969-2.78014)/(3250.-3000.))*(m-3000.) + 2.78014;
    }
  else if (  m >= 3250. && m < 3500. )
    {
      return ((3.17137-2.9969)/(3500.-3250.))*(m-3250.) + 2.9969;
    }
  else if (  m >= 3500. && m < 3750. )
    {
      return ((3.30329-3.17137)/(3750.-3500.))*(m-3500.) + 3.17137;
    }
  else if (  m >= 3750. && m < 4000. )
    {
      return ((3.71696-3.30329)/(4000.-3750.))*(m-3750.) + 3.30329;
    }  
  return 3.71696;
};

Double_t RooDoubleCBInterpolate::getAlpha2( Double_t m ) const
{
  if ( m  < 500 )
    {
      return 1.71965;
    }
  else if ( m >= 500. && m < 740. )
    {
      return ((1.74497-1.71965)/(740.-500.))*(m-500.) + 1.71965;
    }
  else if ( m >= 740. && m < 745. )
    {
      return ((1.8299-1.74497)/(745.-740.))*(m-740.) + 1.74497;
    }
  else if (  m >= 745. && m < 750. )
    {
      return ((1.80373-1.8299)/(750.-745.))*(m-745.) + 1.8299;
    }
  else if (  m >= 750. && m < 755. )
    {
      return ((1.83062-1.80373)/(755.-750.))*(m-750.) + 1.80373;
    }
  else if (  m >= 755. && m < 760. )
    {
      return ((1.72937-1.83062)/(760.-755.))*(m-755.) + 1.83062;
    }
  else if (  m >= 760. && m < 1000. )
    {
      return ((1.88932-1.72937)/(1000.-760.))*(m-760.) + 1.72937;
    }
  else if (  m >= 1000. && m < 1250. )
    {
      return  ((1.83134-1.88932)/(1250.-1000.))*(m-1000.) + 1.88932;
    }
  else if (  m >= 1250. && m < 1500. )
    {
      return ((2.02476-1.83134)/(1500.-1250.))*(m-1250.) + 1.83134;
    }
  else if (  m >= 1500. && m < 1750. )
    {
      return ((1.53062-2.02476)/(1750.-1500.))*(m-1500.) + 2.02476;
    }
  else if (  m >= 1750. && m < 2000. )
    {
      return ((2.09688-1.53062)/(2000.-1750.))*(m-1750.) + 1.53062;
    }
  else if (  m >= 2000. && m < 2250. )
    {
      return ((2.06856-2.09688)/(2250.-2000.))*(m-2000.) + 2.09688;
    }
  else if (  m >= 2250. && m < 2500. )
    {
      return ((2.155-2.06856)/(2500.-2250.))*(m-2250.) + 2.06856;
    }
  else if (  m >= 2500. && m < 2750. )
    {
      return ((2.24434-2.155)/(2750.-2500.))*(m-2500.) + 2.155;
    }
  else if (  m >= 2750. && m < 3000. )
    {
      return ((2.21766-2.24434)/(3000.-2750.))*(m-2750.) + 2.24434;
    }
  else if (  m >= 3000. && m < 3250. )
    {
      return ((2.17426-2.21766)/(3250.-3000.))*(m-3000.) + 2.21766;
    }
  else if (  m >= 3250. && m < 3500. )
    {
      return ((1.94443-2.17426)/(3500.-3250.))*(m-3250.) + 2.17426;
    }
  else if (  m >= 3500. && m < 3750. )
    {
      return ((2.09163-1.94443)/(3750.-3500.))*(m-3500.) + 1.94443;
    }
  else if (  m >= 3750. && m < 4000. )
    {
      return ((0.678367-2.09163)/(4000.-3750.))*(m-3750.) + 2.09163;
    } 
  return 0.678367;
};

Double_t RooDoubleCBInterpolate::getN2( Double_t m ) const
{
  if ( m  < 500 )
    {
      return 4.52615;
    }
  else if ( m >= 500. && m < 740. )
    {
      return ((4.9256-4.52615)/(740.-500.))*(m-500.) + 4.52615;
    }
  else if ( m >= 740. && m < 745. )
    {
      return ((4.25446-4.9256)/(745.-740.))*(m-740.) + 4.9256;
    }
  else if (  m >= 745. && m < 750. )
    {
      return ((4.29415-4.25446)/(750.-745.))*(m-745.) + 4.25446;
    }
  else if (  m >= 750. && m < 755. )
    {
      return ((4.98554-4.29415)/(755.-750.))*(m-750.) + 4.29415;
    }
  else if (  m >= 755. && m < 760. )
    {
      return ((5.09606-4.98554)/(760.-755.))*(m-755.) + 4.98554;
    }
  else if (  m >= 760. && m < 1000. )
    {
      return ((4.39101-5.09606)/(1000.-760.))*(m-760.) + 5.09606;
    }
  else if (  m >= 1000. && m < 1250. )
    {
      return  ((5.15418-4.39101)/(1250.-1000.))*(m-1000.) + 4.39101;
    }
  else if (  m >= 1250. && m < 1500. )
    {
      return ((4.14705-5.15418)/(1500.-1250.))*(m-1250.) + 5.15418;
    }
  else if (  m >= 1500. && m < 1750. )
    {
      return ((108.872-4.14705)/(1750.-1500.))*(m-1500.) + 4.14705;
    }
  else if (  m >= 1750. && m < 2000. )
    {
      return ((3.94784-108.872)/(2000.-1750.))*(m-1750.) + 108.872;
    }
  else if (  m >= 2000. && m < 2250. )
    {
      return ((5.10298-3.94784)/(2250.-2000.))*(m-2000.) + 3.94784;
    }
  else if (  m >= 2250. && m < 2500. )
    {
      return ((4.87344-5.10298)/(2500.-2250.))*(m-2250.) + 5.10298;
    }
  else if (  m >= 2500. && m < 2750. )
    {
      return ((4.64861-4.87344)/(2750.-2500.))*(m-2500.) + 4.87344;
    }
  else if (  m >= 2750. && m < 3000. )
    {
      return ((4.8015-4.64861)/(3000.-2750.))*(m-2750.) + 4.64861;
    }
  else if (  m >= 3000. && m < 3250. )
    {
      return ((5.93429-4.8015)/(3250.-3000.))*(m-3000.) + 4.8015;
    }
  else if (  m >= 3250. && m < 3500. )
    {
      return ((10.7216-5.93429)/(3500.-3250.))*(m-3250.) + 5.93429;
    }
  else if (  m >= 3500. && m < 3750. )
    {
      return ((7.2023-10.7216)/(3750.-3500.))*(m-3500.) + 10.7216;
    }
  else if (  m >= 3750. && m < 4000. )
    {
      return ((133.548-7.2023)/(4000.-3750.))*(m-3750.) + 7.2023;
    } 
  return 133.548;
};

double RooDoubleCBInterpolate::evaluate() const 
{
  double mean   = getMean( mass );
  double width  = getSigma( mass );
  double n1     = getN1( mass );
  double alpha1 = getAlpha1( mass );
  double n2     = getN2( mass );
  double alpha2 = getAlpha2( mass );
  
  double t = (x-mean)/width;
  if( t >= -alpha1 && t <= alpha2 )
    {
      return exp(-0.5*t*t);
    }
  else if ( t < -alpha1 )
    {
      double A1 = pow(n1/fabs(alpha1),n1)*exp(-alpha1*alpha1/2);
      double B1 = n1/fabs(alpha1)-fabs(alpha1);
      return A1*pow(B1-t,-n1);
    }
  else if ( t > alpha2 )
    {
      double A2 = pow(n2/fabs(alpha2),n2)*exp(-alpha2*alpha2/2);
      double B2 = n2/fabs(alpha2)-fabs(alpha2);
      return A2*pow(B2+t,-n2);
    }
  else
    {
      cout << "ERROR evaluating range... t = " << t << endl;
      return 99;
    }
   
};

Int_t RooDoubleCBInterpolate::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* range) const 
{
  if (matchArgs(allVars,analVars,x)) return 1;
  return 0;
};

Double_t RooDoubleCBInterpolate::analyticalIntegral(Int_t code, const char* rangeName) const 
{
  assert(code==1) ;
  //
  double mean   = getMean( mass );
  double width  = getSigma( mass );
  double n1     = getN1( mass );
  double alpha1 = getAlpha1( mass );
  double n2     = getN2( mass );
  double alpha2 = getAlpha2( mass );
  //
  
  double central=0;
  double left=0;
  double right=0;
 
  static const Double_t root2 = sqrt(2) ;
  static const Double_t rootPiBy2 = sqrt(atan2(0.0,-1.0)/2.0);
  Double_t xscale = root2*width;
 
  //compute gaussian contribution
  double central_low =max(x.min(rangeName),mean - alpha1*width );
  double central_high=min(x.max(rangeName),mean + alpha2*width );
  if(central_low < central_high) // is the gaussian part in range?
    central = rootPiBy2*width*(TMath::Erf((central_high-mean)/xscale)-TMath::Erf((central_low-mean)/xscale));
 
  //compute left tail;
  double A1 = pow(n1/fabs(alpha1),n1)*exp(-alpha1*alpha1/2);
  double B1 = n1/fabs(alpha1)-fabs(alpha1);
 
  double left_low=x.min(rangeName);
  double left_high=min(x.max(rangeName),mean - alpha1*width);
  if(left_low < left_high){ //is the left tail in range?
    if(fabs(n1-1.0)>1.e-5)
      left = A1/(-n1+1.0)*width*(pow(B1-(left_low-mean)/width,-n1+1.)-pow(B1-(left_high-mean)/width,-n1+1.));
    else
      left = A1*width*(log(B1-(left_low-mean)/width) - log(B1-(left_high-mean)/width) );
  }
 
  //compute right tail;
  double A2 = pow(n2/fabs(alpha2),n2)*exp(-alpha2*alpha2/2);
  double B2 = n2/fabs(alpha2)-fabs(alpha2);
 
  double right_low=max(x.min(rangeName),mean + alpha2*width);
  double right_high=x.max(rangeName);
  if(right_low < right_high){ //is the right tail in range?
    if(fabs(n2-1.0)>1.e-5)
      right = A2/(-n2+1.0)*width*(pow(B2+(right_high-mean)/width,-n2+1.)-pow(B2+(right_low-mean)/width,-n2+1.));
    else
      right = A2*width*(log(B2+(right_high-mean)/width) - log(B2+(right_low-mean)/width) );
  }
     
  return left+central+right;
 
};

ClassImp(RooFermi) 

RooFermi::RooFermi(){};

RooFermi::RooFermi(const char *name, const char *title, 
		   RooAbsReal& _x,
		   RooAbsReal& _cutOff,
		       RooAbsReal& _beta
		   ) :
  RooAbsPdf(name,title), 
  x("x","x",this,_x),
  cutOff("cutOff","cutOff",this,_cutOff),
  beta("beta","beta",this,_beta)
{ 
};


RooFermi::RooFermi(const RooFermi& other, const char* name) :  
  RooAbsPdf(other,name), 
  x("x",this,other.x),
  cutOff("cutOff",this,other.cutOff),
  beta("beta",this,other.beta)

{ 
};



double RooFermi::evaluate() const 
{ 
  return 1.0/(exp((cutOff-x)/beta)+1);
};

ClassImp(RooRelBW)

RooRelBW::RooRelBW(){};

RooRelBW::RooRelBW(const char *name, const char *title, 
		   RooAbsReal& _x,
		   RooAbsReal& _mean,
		   RooAbsReal& _width,
		       RooAbsReal& _n
		   ) :
  RooAbsPdf(name,title), 
  x("x","x",this,_x),
  mean("mean","mean",this,_mean),
  width("width","width",this,_width),
  n("n","n",this,_n)
{ 
};


RooRelBW::RooRelBW(const RooRelBW& other, const char* name) :  
  RooAbsPdf(other,name), 
  x("x",this,other.x),
  mean("mean",this,other.mean),
  width("width",this,other.width),
  n("n",this,other.n)

{ 
}; 



double RooRelBW::evaluate() const 
{ 
  return pow(x*x,n)/((x*x-mean*mean)*(x*x-mean*mean)+pow(x*x/(mean*mean),2*n)*mean*mean*width*width);
};


ClassImp(Triangle)

Triangle::Triangle(){};

Triangle::Triangle(const char *name, const char *title,                
		   RooAbsReal& _m,
		   RooAbsReal& _start,
		   RooAbsReal& _turn,
		      RooAbsReal& _stop
		   ):
  RooAbsPdf(name, title),
  m("m", "Dependent", this, _m),
  start("start","start",this,_start),
  turn("turn","turn",this,_turn),
  stop("stop","stop",this,_stop)
{
};

Triangle::Triangle(const Triangle& other, const char* name) :
  RooAbsPdf(other, name), m("m", this, other.m),start("start", this, other.start), turn("turn", this, other.turn), stop("stop", this, other.stop)
{
};

Double_t Triangle::evaluate() const 
{
  //std::cout << m << " "<<1.+(start-m)/turn << " " << 1+(turn-m)/stop << std::endl;
  if(m<turn  && m > turn+start)
    return 1.+(turn-m)/start;
  if(m>=turn && m < turn+stop)
    return 1.+(turn-m)/stop;
  
  return 0;
};


Int_t Triangle::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* range) const 
{
  if (matchArgs(allVars,analVars,m)) return 1;
  return 0;
};

Double_t Triangle::analyticalIntegral(Int_t code, const char* rangeName) const 
{

  // WARNING, ASSSUMES TURN TO BE IN INTERVAL
  assert(code==1) ;
  //whole triangle
  Double_t sumleft = sqrt(1+ (turn+start)*(turn+start) ) ;
  Double_t sumright= sqrt(1+ (turn+stop)*(turn+stop) );


  if(m.min() < turn+start)// correct for left missing bit
    sumleft -= sumleft*(m.min()-(turn+start))/fabs(start);


  if(m.max() > turn+stop)// correct for right missing bit
    sumright -= sumright*(turn+stop -m.max())/fabs(stop);

  

  return sumleft+sumright;    
};




ClassImp(RooLevelledExp)

RooLevelledExp::RooLevelledExp(){};

RooLevelledExp::RooLevelledExp(const char *name, const char *title,
			       RooAbsReal& _x,
			       RooAbsReal& _sigma, 
			       RooAbsReal& _alpha,
			       RooAbsReal& _m,
			       RooAbsReal& _theta):
  RooAbsPdf(name,title),
  x("x","x",this,_x),
  sigma("sigma","sigma",this,_sigma),
  alpha("alpha","alpha",this,_alpha),
  m("m","m",this,_m),
  //  k("k","k",this,_k),
  theta("theta","theta",this,_theta)
{
};

RooLevelledExp::RooLevelledExp(const RooLevelledExp& other, const char* name) :
  RooAbsPdf(other,name),
  x("x",this,other.x),
  sigma("sigma",this,other.sigma),
  alpha("alpha",this,other.alpha),
  m("m",this,other.m),
  theta("theta",this,other.theta)
{
};

double RooLevelledExp::evaluate() const
{
  double res=0.0;
  double s = cos(theta)*sigma - sin(theta)*alpha;
  double a = sin(theta)*sigma + cos(theta)*alpha;
    
  //original
  double t = fabs(x-m);
  double den = (s + a*t);
  res=exp(-1.0*t/den);
  

  return res;
};
