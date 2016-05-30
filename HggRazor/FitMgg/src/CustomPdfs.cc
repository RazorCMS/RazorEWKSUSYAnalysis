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


//-----------
//-----------

ClassImp(RooIntepolateDSCB_W0p014_Spin0_EBEB)

RooIntepolateDSCB_W0p014_Spin0_EBEB::RooIntepolateDSCB_W0p014_Spin0_EBEB( ){ };

RooIntepolateDSCB_W0p014_Spin0_EBEB::RooIntepolateDSCB_W0p014_Spin0_EBEB(const char *name, const char *title, 
					       RooAbsReal& _x,
					       RooAbsReal& _mass
					       ) :
  RooAbsPdf(name,title), 
  x("x","x",this,_x),
  mass("mass","mass",this, _mass)
{
};


RooIntepolateDSCB_W0p014_Spin0_EBEB::RooIntepolateDSCB_W0p014_Spin0_EBEB(const RooIntepolateDSCB_W0p014_Spin0_EBEB& other, const char* name) :  
  RooAbsPdf(other,name), 
  x("x",this,other.x),
  mass("mass",this, other.mass)
{ 
};

double RooIntepolateDSCB_W0p014_Spin0_EBEB::evaluate() const 
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

Int_t RooIntepolateDSCB_W0p014_Spin0_EBEB::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* range) const 
{
  if (matchArgs(allVars,analVars,x)) return 1;
  return 0;
};

Double_t RooIntepolateDSCB_W0p014_Spin0_EBEB::analyticalIntegral(Int_t code, const char* rangeName) const 
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

double RooIntepolateDSCB_W0p014_Spin0_EBEB::getMean( double m ) const
{
	if( m >=  500 && m < 740 ) return 0.995233*(m-500) + 499.561;
	if( m >=  740 && m < 745 ) return 1.01341*(m-740) + 738.417;
	if( m >=  745 && m < 750 ) return 0.957619*(m-745) + 743.484;
	if( m >=  750 && m < 755 ) return 1.01426*(m-750) + 748.272;
	if( m >=  755 && m < 760 ) return 0.98425*(m-755) + 753.344;
	if( m >=  760 && m < 1000 ) return 0.992843*(m-760) + 758.265;
	if( m >=  1000 && m < 1250 ) return 0.990799*(m-1000) + 996.547;
	if( m >=  1250 && m < 1500 ) return 0.990036*(m-1250) + 1244.25;
	if( m >=  1500 && m < 1750 ) return 0.989696*(m-1500) + 1491.76;
	if( m >=  1750 && m < 2000 ) return 0.990009*(m-1750) + 1739.18;
	if( m >=  2000 && m < 2250 ) return 0.989139*(m-2000) + 1986.68;
	if( m >=  2250 && m < 2500 ) return 0.988745*(m-2250) + 2233.97;
	if( m >=  2500 && m < 2750 ) return 0.98721*(m-2500) + 2481.15;
	if( m >=  2750 && m < 3000 ) return 0.986992*(m-2750) + 2727.96;
	if( m >=  3000 && m < 3250 ) return 0.983576*(m-3000) + 2974.7;
	if( m >=  3250 && m < 3500 ) return 0.986441*(m-3250) + 3220.6;
	if( m >=  3500 && m < 3750 ) return 0.981139*(m-3500) + 3467.21;
	return 0;
};

double RooIntepolateDSCB_W0p014_Spin0_EBEB::getSigma( double m ) const
{
	if( m >=  500 && m < 740 ) return 0.00509383*(m-500) + 2.47406;
	if( m >=  740 && m < 745 ) return 0.0153767*(m-740) + 3.69658;
	if( m >=  745 && m < 750 ) return -0.00723399*(m-745) + 3.77346;
	if( m >=  750 && m < 755 ) return 0.031826*(m-750) + 3.73729;
	if( m >=  755 && m < 760 ) return 0.00510904*(m-755) + 3.89642;
	if( m >=  760 && m < 1000 ) return 0.00543278*(m-760) + 3.92196;
	if( m >=  1000 && m < 1250 ) return 0.00573415*(m-1000) + 5.22583;
	if( m >=  1250 && m < 1500 ) return 0.00621868*(m-1250) + 6.65937;
	if( m >=  1500 && m < 1750 ) return 0.00601291*(m-1500) + 8.21404;
	if( m >=  1750 && m < 2000 ) return 0.00606272*(m-1750) + 9.71727;
	if( m >=  2000 && m < 2250 ) return 0.00782916*(m-2000) + 11.2329;
	if( m >=  2250 && m < 2500 ) return 0.00702413*(m-2250) + 13.1902;
	if( m >=  2500 && m < 2750 ) return 0.00721286*(m-2500) + 14.9463;
	if( m >=  2750 && m < 3000 ) return 0.00739916*(m-2750) + 16.7495;
	if( m >=  3000 && m < 3250 ) return 0.00962035*(m-3000) + 18.5993;
	if( m >=  3250 && m < 3500 ) return 0.0064117*(m-3250) + 21.0044;
	if( m >=  3500 && m < 3750 ) return 0.0118098*(m-3500) + 22.6073;
	return 0;
};

double RooIntepolateDSCB_W0p014_Spin0_EBEB::getN1( double m ) const
{
	if( m >=  500 && m < 740 ) return -0.000124128*(m-500) + 2.43985;
	if( m >=  740 && m < 745 ) return 0.00511854*(m-740) + 2.41006;
	if( m >=  745 && m < 750 ) return 0.00624646*(m-745) + 2.43565;
	if( m >=  750 && m < 755 ) return -0.0110372*(m-750) + 2.46688;
	if( m >=  755 && m < 760 ) return 0.0157781*(m-755) + 2.4117;
	if( m >=  760 && m < 1000 ) return 0.00050326*(m-760) + 2.49059;
	if( m >=  1000 && m < 1250 ) return 0.000769021*(m-1000) + 2.61137;
	if( m >=  1250 && m < 1500 ) return 0.00032275*(m-1250) + 2.80362;
	if( m >=  1500 && m < 1750 ) return 0.001056*(m-1500) + 2.88431;
	if( m >=  1750 && m < 2000 ) return 0.000843238*(m-1750) + 3.14831;
	if( m >=  2000 && m < 2250 ) return 0.000501159*(m-2000) + 3.35912;
	if( m >=  2250 && m < 2500 ) return 0.00102144*(m-2250) + 3.48441;
	if( m >=  2500 && m < 2750 ) return 0.000513676*(m-2500) + 3.73977;
	if( m >=  2750 && m < 3000 ) return -5.43402e-05*(m-2750) + 3.86819;
	if( m >=  3000 && m < 3250 ) return 0.00111297*(m-3000) + 3.8546;
	if( m >=  3250 && m < 3500 ) return -0.00029722*(m-3250) + 4.13285;
	if( m >=  3500 && m < 3750 ) return -0.000791708*(m-3500) + 4.05854;
	return 0;
};

double RooIntepolateDSCB_W0p014_Spin0_EBEB::getN2( double m ) const
{
	if( m >=  500 && m < 740 ) return -1.96607e-05*(m-500) + 2.71034;
	if( m >=  740 && m < 745 ) return -0.0447118*(m-740) + 2.70562;
	if( m >=  745 && m < 750 ) return 0.012665*(m-745) + 2.48206;
	if( m >=  750 && m < 755 ) return 0.0124647*(m-750) + 2.54538;
	if( m >=  755 && m < 760 ) return 0.00451816*(m-755) + 2.60771;
	if( m >=  760 && m < 1000 ) return -0.000291722*(m-760) + 2.6303;
	if( m >=  1000 && m < 1250 ) return 4.76262e-06*(m-1000) + 2.56028;
	if( m >=  1250 && m < 1500 ) return -0.000311196*(m-1250) + 2.56148;
	if( m >=  1500 && m < 1750 ) return 0.000951612*(m-1500) + 2.48368;
	if( m >=  1750 && m < 2000 ) return -0.00119126*(m-1750) + 2.72158;
	if( m >=  2000 && m < 2250 ) return 0.00111321*(m-2000) + 2.42377;
	if( m >=  2250 && m < 2500 ) return 0.000440332*(m-2250) + 2.70207;
	if( m >=  2500 && m < 2750 ) return 0.00156959*(m-2500) + 2.81215;
	if( m >=  2750 && m < 3000 ) return -0.000654391*(m-2750) + 3.20455;
	if( m >=  3000 && m < 3250 ) return 0.00245968*(m-3000) + 3.04095;
	if( m >=  3250 && m < 3500 ) return 0.00103691*(m-3250) + 3.65587;
	if( m >=  3500 && m < 3750 ) return 0.00270934*(m-3500) + 3.9151;
	return 0;
};

double RooIntepolateDSCB_W0p014_Spin0_EBEB::getAlpha1( double m ) const
{
	if( m >=  500 && m < 740 ) return 0.000122125*(m-500) + 1.02017;
	if( m >=  740 && m < 745 ) return 0.000180336*(m-740) + 1.04948;
	if( m >=  745 && m < 750 ) return -0.00409982*(m-745) + 1.05038;
	if( m >=  750 && m < 755 ) return 0.00608684*(m-750) + 1.02988;
	if( m >=  755 && m < 760 ) return -0.00175266*(m-755) + 1.06032;
	if( m >=  760 && m < 1000 ) return -0.000197785*(m-760) + 1.05155;
	if( m >=  1000 && m < 1250 ) return -0.000214956*(m-1000) + 1.00409;
	if( m >=  1250 && m < 1500 ) return -2.87657e-05*(m-1250) + 0.950346;
	if( m >=  1500 && m < 1750 ) return -0.000187497*(m-1500) + 0.943155;
	if( m >=  1750 && m < 2000 ) return -0.000143084*(m-1750) + 0.89628;
	if( m >=  2000 && m < 2250 ) return -3.99843e-05*(m-2000) + 0.860509;
	if( m >=  2250 && m < 2500 ) return -0.000157892*(m-2250) + 0.850513;
	if( m >=  2500 && m < 2750 ) return -0.00011494*(m-2500) + 0.811041;
	if( m >=  2750 && m < 3000 ) return -3.43362e-05*(m-2750) + 0.782306;
	if( m >=  3000 && m < 3250 ) return -1.16888e-05*(m-3000) + 0.773722;
	if( m >=  3250 && m < 3500 ) return -0.000160483*(m-3250) + 0.770799;
	if( m >=  3500 && m < 3750 ) return 0.000115844*(m-3500) + 0.730679;
	return 0;
};

double RooIntepolateDSCB_W0p014_Spin0_EBEB::getAlpha2( double m ) const
{
	if( m >=  500 && m < 740 ) return 0.000469855*(m-500) + 1.68028;
	if( m >=  740 && m < 745 ) return 0.0137783*(m-740) + 1.79305;
	if( m >=  745 && m < 750 ) return -0.00695327*(m-745) + 1.86194;
	if( m >=  750 && m < 755 ) return 0.00589827*(m-750) + 1.82717;
	if( m >=  755 && m < 760 ) return -0.00432675*(m-755) + 1.85666;
	if( m >=  760 && m < 1000 ) return 0.000232167*(m-760) + 1.83503;
	if( m >=  1000 && m < 1250 ) return 0.000298243*(m-1000) + 1.89075;
	if( m >=  1250 && m < 1500 ) return 0.000204203*(m-1250) + 1.96531;
	if( m >=  1500 && m < 1750 ) return -0.000120374*(m-1500) + 2.01636;
	if( m >=  1750 && m < 2000 ) return 0.000452141*(m-1750) + 1.98627;
	if( m >=  2000 && m < 2250 ) return 8.86976e-05*(m-2000) + 2.0993;
	if( m >=  2250 && m < 2500 ) return -0.00010566*(m-2250) + 2.12148;
	if( m >=  2500 && m < 2750 ) return -0.000160125*(m-2500) + 2.09506;
	if( m >=  2750 && m < 3000 ) return 0.000289497*(m-2750) + 2.05503;
	if( m >=  3000 && m < 3250 ) return -0.00038714*(m-3000) + 2.12741;
	if( m >=  3250 && m < 3500 ) return -0.000326643*(m-3250) + 2.03062;
	if( m >=  3500 && m < 3750 ) return -0.000183002*(m-3500) + 1.94896;
	return 0;
};

//-----------
//-----------

ClassImp(RooIntepolateDSCB_W0p014_Spin0_EBEE)

RooIntepolateDSCB_W0p014_Spin0_EBEE::RooIntepolateDSCB_W0p014_Spin0_EBEE( ){ };

RooIntepolateDSCB_W0p014_Spin0_EBEE::RooIntepolateDSCB_W0p014_Spin0_EBEE(const char *name, const char *title, 
					       RooAbsReal& _x,
					       RooAbsReal& _mass
					       ) :
  RooAbsPdf(name,title), 
  x("x","x",this,_x),
  mass("mass","mass",this, _mass)
{
};


RooIntepolateDSCB_W0p014_Spin0_EBEE::RooIntepolateDSCB_W0p014_Spin0_EBEE(const RooIntepolateDSCB_W0p014_Spin0_EBEE& other, const char* name) :  
  RooAbsPdf(other,name), 
  x("x",this,other.x),
  mass("mass",this, other.mass)
{ 
};

double RooIntepolateDSCB_W0p014_Spin0_EBEE::evaluate() const 
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

Int_t RooIntepolateDSCB_W0p014_Spin0_EBEE::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* range) const 
{
  if (matchArgs(allVars,analVars,x)) return 1;
  return 0;
};

Double_t RooIntepolateDSCB_W0p014_Spin0_EBEE::analyticalIntegral(Int_t code, const char* rangeName) const 
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

double RooIntepolateDSCB_W0p014_Spin0_EBEE::getMean( double m ) const
{
	if( m >=  500 && m < 740 ) return 0.997025*(m-500) + 499.727;
	if( m >=  740 && m < 745 ) return 0.962343*(m-740) + 739.013;
	if( m >=  745 && m < 750 ) return 0.993297*(m-745) + 743.825;
	if( m >=  750 && m < 755 ) return 1.00325*(m-750) + 748.791;
	if( m >=  755 && m < 760 ) return 1.00437*(m-755) + 753.808;
	if( m >=  760 && m < 1000 ) return 0.994681*(m-760) + 758.829;
	if( m >=  1000 && m < 1250 ) return 0.995925*(m-1000) + 997.553;
	if( m >=  1250 && m < 1500 ) return 0.993433*(m-1250) + 1246.53;
	if( m >=  1500 && m < 1750 ) return 0.990196*(m-1500) + 1494.89;
	if( m >=  1750 && m < 2000 ) return 0.993818*(m-1750) + 1742.44;
	if( m >=  2000 && m < 2250 ) return 0.991113*(m-2000) + 1990.9;
	if( m >=  2250 && m < 2500 ) return 0.988857*(m-2250) + 2238.67;
	if( m >=  2500 && m < 2750 ) return 0.993646*(m-2500) + 2485.89;
	if( m >=  2750 && m < 3000 ) return 0.990195*(m-2750) + 2734.3;
	if( m >=  3000 && m < 3250 ) return 0.986493*(m-3000) + 2981.85;
	if( m >=  3250 && m < 3500 ) return 1.00037*(m-3250) + 3228.47;
	if( m >=  3500 && m < 3750 ) return 0.994141*(m-3500) + 3478.56;
	return 0;
};

double RooIntepolateDSCB_W0p014_Spin0_EBEE::getSigma( double m ) const
{
	if( m >=  500 && m < 740 ) return 0.00764799*(m-500) + 3.65328;
	if( m >=  740 && m < 745 ) return 0.00815498*(m-740) + 5.4888;
	if( m >=  745 && m < 750 ) return 0.0506011*(m-745) + 5.52957;
	if( m >=  750 && m < 755 ) return -0.00620412*(m-750) + 5.78258;
	if( m >=  755 && m < 760 ) return -0.018742*(m-755) + 5.75156;
	if( m >=  760 && m < 1000 ) return 0.00759418*(m-760) + 5.65785;
	if( m >=  1000 && m < 1250 ) return 0.00810497*(m-1000) + 7.48045;
	if( m >=  1250 && m < 1500 ) return 0.00613537*(m-1250) + 9.50669;
	if( m >=  1500 && m < 1750 ) return 0.0109545*(m-1500) + 11.0405;
	if( m >=  1750 && m < 2000 ) return 0.0075094*(m-1750) + 13.7792;
	if( m >=  2000 && m < 2250 ) return 0.00628405*(m-2000) + 15.6565;
	if( m >=  2250 && m < 2500 ) return 0.0134128*(m-2250) + 17.2275;
	if( m >=  2500 && m < 2750 ) return 0.00826788*(m-2500) + 20.5807;
	if( m >=  2750 && m < 3000 ) return 0.0109576*(m-2750) + 22.6477;
	if( m >=  3000 && m < 3250 ) return 0.00908623*(m-3000) + 25.3871;
	if( m >=  3250 && m < 3500 ) return 0.00193595*(m-3250) + 27.6586;
	if( m >=  3500 && m < 3750 ) return 0.00677562*(m-3500) + 28.1426;
	return 0;
};

double RooIntepolateDSCB_W0p014_Spin0_EBEE::getN1( double m ) const
{
	if( m >=  500 && m < 740 ) return -0.00018166*(m-500) + 3.17382;
	if( m >=  740 && m < 745 ) return -0.0842916*(m-740) + 3.13022;
	if( m >=  745 && m < 750 ) return 0.0040361*(m-745) + 2.70876;
	if( m >=  750 && m < 755 ) return 0.0497264*(m-750) + 2.72894;
	if( m >=  755 && m < 760 ) return 0.0118946*(m-755) + 2.97758;
	if( m >=  760 && m < 1000 ) return 4.27835e-05*(m-760) + 3.03705;
	if( m >=  1000 && m < 1250 ) return 0.000210549*(m-1000) + 3.04732;
	if( m >=  1250 && m < 1500 ) return 0.00153572*(m-1250) + 3.09995;
	if( m >=  1500 && m < 1750 ) return -0.000657399*(m-1500) + 3.48388;
	if( m >=  1750 && m < 2000 ) return -0.000653139*(m-1750) + 3.31953;
	if( m >=  2000 && m < 2250 ) return 0.00291341*(m-2000) + 3.15625;
	if( m >=  2250 && m < 2500 ) return -0.00335439*(m-2250) + 3.8846;
	if( m >=  2500 && m < 2750 ) return -8.98483e-05*(m-2500) + 3.046;
	if( m >=  2750 && m < 3000 ) return -0.00133974*(m-2750) + 3.02354;
	if( m >=  3000 && m < 3250 ) return -9.63975e-05*(m-3000) + 2.68861;
	if( m >=  3250 && m < 3500 ) return 0.00116046*(m-3250) + 2.66451;
	if( m >=  3500 && m < 3750 ) return 0.000906946*(m-3500) + 2.95462;
	return 0;
};

double RooIntepolateDSCB_W0p014_Spin0_EBEE::getN2( double m ) const
{
	if( m >=  500 && m < 740 ) return 0.00101567*(m-500) + 3.3634;
	if( m >=  740 && m < 745 ) return -0.0068998*(m-740) + 3.60716;
	if( m >=  745 && m < 750 ) return -0.065187*(m-745) + 3.57266;
	if( m >=  750 && m < 755 ) return 0.0647723*(m-750) + 3.24673;
	if( m >=  755 && m < 760 ) return 0.0673129*(m-755) + 3.57059;
	if( m >=  760 && m < 1000 ) return -0.00382269*(m-760) + 3.90715;
	if( m >=  1000 && m < 1250 ) return 0.000752247*(m-1000) + 2.98971;
	if( m >=  1250 && m < 1500 ) return 0.000746126*(m-1250) + 3.17777;
	if( m >=  1500 && m < 1750 ) return 0.00268341*(m-1500) + 3.3643;
	if( m >=  1750 && m < 2000 ) return -0.00167498*(m-1750) + 4.03515;
	if( m >=  2000 && m < 2250 ) return 0.00784976*(m-2000) + 3.61641;
	if( m >=  2250 && m < 2500 ) return -0.00453351*(m-2250) + 5.57885;
	if( m >=  2500 && m < 2750 ) return 0.000448148*(m-2500) + 4.44547;
	if( m >=  2750 && m < 3000 ) return -0.0114426*(m-2750) + 4.55751;
	if( m >=  3000 && m < 3250 ) return 0.00919366*(m-3000) + 1.69686;
	if( m >=  3250 && m < 3500 ) return 0.00341344*(m-3250) + 3.99527;
	if( m >=  3500 && m < 3750 ) return 0.000518258*(m-3500) + 4.84863;
	return 0;
};

double RooIntepolateDSCB_W0p014_Spin0_EBEE::getAlpha1( double m ) const
{
	if( m >=  500 && m < 740 ) return 0.000154848*(m-500) + 1.04727;
	if( m >=  740 && m < 745 ) return 0.0129722*(m-740) + 1.08443;
	if( m >=  745 && m < 750 ) return 0.0135625*(m-745) + 1.14929;
	if( m >=  750 && m < 755 ) return -0.0129353*(m-750) + 1.21711;
	if( m >=  755 && m < 760 ) return -0.0055582*(m-755) + 1.15243;
	if( m >=  760 && m < 1000 ) return -1.31371e-05*(m-760) + 1.12464;
	if( m >=  1000 && m < 1250 ) return -0.000254834*(m-1000) + 1.12149;
	if( m >=  1250 && m < 1500 ) return -0.000230376*(m-1250) + 1.05778;
	if( m >=  1500 && m < 1750 ) return 0.00039943*(m-1500) + 1.00018;
	if( m >=  1750 && m < 2000 ) return -3.94059e-05*(m-1750) + 1.10004;
	if( m >=  2000 && m < 2250 ) return -0.000458439*(m-2000) + 1.09019;
	if( m >=  2250 && m < 2500 ) return 0.000728199*(m-2250) + 0.97558;
	if( m >=  2500 && m < 2750 ) return 2.30681e-05*(m-2500) + 1.15763;
	if( m >=  2750 && m < 3000 ) return 0.000130566*(m-2750) + 1.1634;
	if( m >=  3000 && m < 3250 ) return 3.27577e-05*(m-3000) + 1.19604;
	if( m >=  3250 && m < 3500 ) return -0.000561415*(m-3250) + 1.20423;
	if( m >=  3500 && m < 3750 ) return -0.000431754*(m-3500) + 1.06387;
	return 0;
};

double RooIntepolateDSCB_W0p014_Spin0_EBEE::getAlpha2( double m ) const
{
	if( m >=  500 && m < 740 ) return 0.000358977*(m-500) + 1.59417;
	if( m >=  740 && m < 745 ) return -0.0108386*(m-740) + 1.68033;
	if( m >=  745 && m < 750 ) return 0.0310258*(m-745) + 1.62614;
	if( m >=  750 && m < 755 ) return -0.00642566*(m-750) + 1.78126;
	if( m >=  755 && m < 760 ) return -0.00926719*(m-755) + 1.74914;
	if( m >=  760 && m < 1000 ) return 0.000476135*(m-760) + 1.7028;
	if( m >=  1000 && m < 1250 ) return 0.00058311*(m-1000) + 1.81707;
	if( m >=  1250 && m < 1500 ) return 0.000231203*(m-1250) + 1.96285;
	if( m >=  1500 && m < 1750 ) return 0.000273754*(m-1500) + 2.02065;
	if( m >=  1750 && m < 2000 ) return 3.41876e-05*(m-1750) + 2.08909;
	if( m >=  2000 && m < 2250 ) return -0.000575592*(m-2000) + 2.09764;
	if( m >=  2250 && m < 2500 ) return 0.00106999*(m-2250) + 1.95374;
	if( m >=  2500 && m < 2750 ) return 0.000241727*(m-2500) + 2.22124;
	if( m >=  2750 && m < 3000 ) return 0.00218827*(m-2750) + 2.28167;
	if( m >=  3000 && m < 3250 ) return -0.00205948*(m-3000) + 2.82873;
	if( m >=  3250 && m < 3500 ) return 0.000342669*(m-3250) + 2.31386;
	if( m >=  3500 && m < 3750 ) return -0.00129466*(m-3500) + 2.39953;
	return 0;
};

//---------------------

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
