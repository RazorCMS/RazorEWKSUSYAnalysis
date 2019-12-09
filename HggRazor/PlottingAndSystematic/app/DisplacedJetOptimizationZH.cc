#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <assert.h>
//ROOT INCLUDES
#include <TFile.h>
#include <TROOT.h>
//LOCAL INCLUDES
#include "HggRazorSystematics.hh"
#include "CommandLineInput.hh"

const bool _debug = true;

//----------------------------------------------
//New Binning From Significance Calculation 2016 
//----------------------------------------------
//HIGHPT
float bin_highpt0[4] = {600,0.025,10000,1};
float bin_highpt1[4] = {150,0.13,600,1};
float bin_highpt2[4] = {1250,0,10000,0.025};
float bin_highpt3[4] = {150,0,450,0.13};
float bin_highpt4[4] = {450,0,600,0.035};
float bin_highpt5[4] = {450,0.035,600,0.13};
float bin_highpt6[4] = {600,0,1250,0.015};
float bin_highpt7[4] = {600,0.015,1250,0.025};
std::vector<float*> SetBinning_highpt()
{
  std::vector<float*> myVec;
  myVec.push_back(bin_highpt0);
  myVec.push_back(bin_highpt1);
  myVec.push_back(bin_highpt2);
  myVec.push_back(bin_highpt3);
  myVec.push_back(bin_highpt4);
  myVec.push_back(bin_highpt5);
  myVec.push_back(bin_highpt6);
  myVec.push_back(bin_highpt7);
  return myVec;
};
//HZBB
float bin_hzbb0[4] = {150,0,10000,1};
std::vector<float*> SetBinning_hzbb()
{
  std::vector<float*> myVec;
  myVec.push_back(bin_hzbb0);
  return myVec;
};
//HIGHRES
float bin_highres0[4] = {600,0.01,10000,1};
float bin_highres1[4] = {150,0.175,600,1};
float bin_highres2[4] = {150,0,400,0.175};
float bin_highres3[4] = {400,0,600,0.025};
float bin_highres4[4] = {400,0.025,600,0.175};
float bin_highres5[4] = {600,0,950,0.01};
float bin_highres6[4] = {950,0,10000,0.01};
std::vector<float*> SetBinning_highres()
{
  std::vector<float*> myVec;
  myVec.push_back(bin_highres0);
  myVec.push_back(bin_highres1);
  myVec.push_back(bin_highres2);
  myVec.push_back(bin_highres3);
  myVec.push_back(bin_highres4);
  myVec.push_back(bin_highres5);
  myVec.push_back(bin_highres6);
  return myVec;
};
//LOWRES
float bin_lowres0[4] = {500,0.01,10000,1};
float bin_lowres1[4] = {150,0.15,500,1};
float bin_lowres2[4] = {150,0,400,0.15};
float bin_lowres3[4] = {400,0,500,0.015};
float bin_lowres4[4] = {400,0.015,500,0.15};
float bin_lowres5[4] = {500,0,800,0.01};
float bin_lowres6[4] = {800,0,10000,0.01};
std::vector<float*> SetBinning_lowres()
{
  std::vector<float*> myVec;
  myVec.push_back(bin_lowres0);
  myVec.push_back(bin_lowres1);
  myVec.push_back(bin_lowres2);
  myVec.push_back(bin_lowres3);
  myVec.push_back(bin_lowres4);
  myVec.push_back(bin_lowres5);
  myVec.push_back(bin_lowres6);
  return myVec;
};


//----------------
//Static Variables
//----------------
float HggRazorSystematics::NR_kf = 1.0;
int   HggRazorSystematics::n_PdfSys = 60;


//------------------------
struct nTags
{
  float bin_high[3];
  float bin_high_err[3];
  float bin_low[3];
  float bin_low_err[3];
  float tf[3];
  float tf_err[3];
};
//------------------------
struct punzi
{
  float significance;
  float signal[3];
  float signal_err[3];
  float bkg[3];
  float bkg_err[3];
  float tf[3];
  float tf_err[3];
};



int main( int argc, char* argv[] )
{

  gROOT->Reset();
  std::string inputList = ParseCommandLine( argc, argv, "-inputList=" );
  if (  inputList == "" )
    {
      std::cerr << "[ERROR]: please provide an input list file using --inputList=<path_to_list_file>" << std::endl;
      return -1;
    }
  
  std::ifstream ifs( inputList, std::ifstream::in );
  assert(ifs);
  std::cerr << "===========================================================================" << std::endl;
  std::cerr << "[INFO]: INPUT LIST of LIST--> " << inputList << std::endl;
  std::cerr << "===========================================================================" << std::endl;

  std::map<std::string,nTags> point_map;
  std::map<std::string, std::map<std::string,nTags> > process_map; 
  std::map<std::string, punzi > punzi_map;

  std::string process, process_file_name;
  while ( ifs.good() )
    {
      ifs >> process >> process_file_name;
      if ( ifs.eof() ) break;
      std::cout << process << " " << process_file_name << std::endl;
      
      //------------------------------------------
      //get sub-processes (per year contributions)
      //------------------------------------------
      std::ifstream ifs_process( process_file_name.c_str(), std::ifstream::in );
      assert(ifs_process);
      std::string sub_process_file_name;
      while ( ifs_process.good() )
	{
	  ifs_process >> sub_process_file_name;
	  if ( ifs_process.eof() ) break;
	  std::cout << "*****************************" << std::endl;
	  std::cout << sub_process_file_name << std::endl;
	  std::ifstream ifs_points( sub_process_file_name.c_str(), std::ifstream::in );
	  assert(ifs_points);
	  //variables
	  std::string f_name, z_pt, sf, ip, ta, alpha_max, full_events;
	  std::string ntag0_high, ntag0_high_err, ntag1_high, ntag1_high_err, ntag2_high, ntag2_high_err, ntag0_low, ntag0_low_err, ntag1_low, ntag1_low_err, ntag2_low, ntag2_low_err;
	  std::string tf0, tf0_err, tf1, tf1_err, tf2, tf2_err;
	  //----------------------------------------
	  //map to hold all set of cut an the values
	  //----------------------------------------
	  std::map<std::string,nTags> my_point_map;
	  while ( ifs_points.good() )
	    {
	      ifs_points >> f_name >> z_pt >> sf >> ip >> ta >> alpha_max >> full_events >> ntag0_high >> ntag0_high_err >> ntag0_low >> ntag0_low_err >> ntag1_high >> ntag1_high_err >> ntag1_low >> ntag1_low_err
		         >> ntag2_high >> ntag2_high_err >> ntag2_low >> ntag2_low_err >> tf0 >> tf0_err >>  tf1 >>  tf1_err >>  tf2 >> tf2_err;
	      if ( ifs_points.eof() ) break;
	      
	      /*std::cout << f_name << " " << z_pt << " " << sf << " " << ip << " " << ta << " " << alpha_max << " " << full_events << " " << ntag0_high << " " << ntag0_high_err << " " << ntag0_low << " " << ntag0_low_err 
			<< " " << ntag1_high << " " << ntag1_high_err << " " << ntag1_low << " " << ntag1_low_err << " " << ntag2_high << " " << ntag2_high_err << " " << ntag2_low << " " << ntag2_low_err << " "
			<< tf0 << " " << tf0_err << " " <<  tf1 << " " <<  tf1_err << " " <<  tf2 << " " << tf2_err << " " << std::endl;
	      
	      std::cout << z_pt+"_"+ip+"_"+ta+"_"+alpha_max << std::endl;
	      */
	      std::string key = z_pt+"_"+ip+"_"+ta+"_"+alpha_max;
	      if( my_point_map.find(key) != my_point_map.end() )
		{
		  //std::cout << "key found!" << std::endl;
		  //central value
		  
		  my_point_map[key].bin_high[0] = my_point_map[key].bin_high[0]+std::stof(ntag0_high);
		  my_point_map[key].bin_high[1] = my_point_map[key].bin_high[1]+std::stof(ntag1_high);
		  my_point_map[key].bin_high[2] = my_point_map[key].bin_high[2]+std::stof(ntag2_high);
		  //low
		  my_point_map[key].bin_low[0] = my_point_map[key].bin_low[0]+std::stof(ntag0_low);
		  my_point_map[key].bin_low[1] = my_point_map[key].bin_low[1]+std::stof(ntag1_low);
		  my_point_map[key].bin_low[2] = my_point_map[key].bin_low[2]+std::stof(ntag2_low);
		  //----uncentainty ----
		  my_point_map[key].bin_high_err[0] = sqrt( pow(my_point_map[key].bin_high_err[0], 2.0)+ pow(std::stof(ntag0_high_err), 2.0) );
		  my_point_map[key].bin_high_err[1] = sqrt( pow(my_point_map[key].bin_high_err[1], 2.0)+ pow(std::stof(ntag1_high_err), 2.0) );
		  my_point_map[key].bin_high_err[2] = sqrt( pow(my_point_map[key].bin_high_err[2], 2.0)+ pow(std::stof(ntag2_high_err), 2.0) );
		  //low
		  my_point_map[key].bin_low_err[0] = sqrt( pow(my_point_map[key].bin_low_err[0], 2.0)+ pow(std::stof(ntag0_low_err), 2.0) );
		  my_point_map[key].bin_low_err[1] = sqrt( pow(my_point_map[key].bin_low_err[1], 2.0)+ pow(std::stof(ntag1_low_err), 2.0) );
		  my_point_map[key].bin_low_err[2] = sqrt( pow(my_point_map[key].bin_low_err[2], 2.0)+ pow(std::stof(ntag2_low_err), 2.0) );

		  //-------------------------
		  //-----------TF------------
		  //-------------------------
		  my_point_map[key].tf[0] = my_point_map[key].bin_high[0]/my_point_map[key].bin_low[0];
		  my_point_map[key].tf[1] = my_point_map[key].bin_high[1]/my_point_map[key].bin_low[1];
		  my_point_map[key].tf[2] = my_point_map[key].bin_high[2]/my_point_map[key].bin_low[2];
		  //uncerntainty
		  my_point_map[key].tf_err[0]   = sqrt(pow(my_point_map[key].tf[0],2.0)*(pow(my_point_map[key].bin_high_err[0]/my_point_map[key].bin_high[0],2.0)+pow(my_point_map[key].bin_low_err[0]/my_point_map[key].bin_low[0],2.0)));
		  my_point_map[key].tf_err[1]   = sqrt(pow(my_point_map[key].tf[1],2.0)*(pow(my_point_map[key].bin_high_err[1]/my_point_map[key].bin_high[1],2.0)+pow(my_point_map[key].bin_low_err[1]/my_point_map[key].bin_low[1],2.0)));
		  my_point_map[key].tf_err[2]   = sqrt(pow(my_point_map[key].tf[2],2.0)*(pow(my_point_map[key].bin_high_err[2]/my_point_map[key].bin_high[2],2.0)+pow(my_point_map[key].bin_low_err[2]/my_point_map[key].bin_low[2],2.0)));
		  
		}
	      else
		{
		  //std::cout << "key not found!" << std::endl;
		  //std::cout << "key: " << key << std::endl;
		  nTags my_nTags;
		  //central value
                  my_nTags.bin_high[0] = std::stof(ntag0_high);
                  my_nTags.bin_high[1] = std::stof(ntag1_high);
		  my_nTags.bin_high[2] = std::stof(ntag2_high);
                  //low
                  my_nTags.bin_low[0] = std::stof(ntag0_low);
                  my_nTags.bin_low[1] = std::stof(ntag1_low);
		  my_nTags.bin_low[2] = std::stof(ntag2_low);
                  //----uncentainty ----
                  my_nTags.bin_high_err[0] = std::stof(ntag0_high_err);
		  my_nTags.bin_high_err[1] = std::stof(ntag1_high_err);
		  my_nTags.bin_high_err[2] = std::stof(ntag2_high_err);
                  //low
                  my_nTags.bin_low_err[0] = std::stof(ntag0_low_err);
                  my_nTags.bin_low_err[1] = std::stof(ntag1_low_err);
                  my_nTags.bin_low_err[2] = std::stof(ntag2_low_err);
		  
		  //-------------------------
                  //-----------TF------------
                  //-------------------------
		  my_nTags.tf[0] = my_nTags.bin_high[0]/my_nTags.bin_low[0];
                  my_nTags.tf[1] = my_nTags.bin_high[1]/my_nTags.bin_low[1];
                  my_nTags.tf[2] = my_nTags.bin_high[2]/my_nTags.bin_low[2];
                  //uncerntainty
                  my_nTags.tf_err[0]  = sqrt(pow(my_nTags.tf[0],2.0)*(pow(my_nTags.bin_high_err[0]/my_nTags.bin_high[0],2.0)+pow(my_nTags.bin_low_err[0]/my_nTags.bin_low[0],2.0)));
                  my_nTags.tf_err[1]  = sqrt(pow(my_nTags.tf[1],2.0)*(pow(my_nTags.bin_high_err[1]/my_nTags.bin_high[1],2.0)+pow(my_nTags.bin_low_err[1]/my_nTags.bin_low[1],2.0)));
                  my_nTags.tf_err[2]  = sqrt(pow(my_nTags.tf[2],2.0)*(pow(my_nTags.bin_high_err[2]/my_nTags.bin_high[2],2.0)+pow(my_nTags.bin_low_err[2]/my_nTags.bin_low[2],2.0)));
		  
		  //MAKE MAP ENTRY
		  my_point_map[key] = my_nTags;
		  
		}
	      //std::map<std::string,nTags> point_map;
	    }
	  
	  if( process_map.find(process) == process_map.end() )
	    {
	      process_map[process] = my_point_map;
	    }
	  else
	    {
	      std::cerr << "[ERROR]: Duplicated process: " << process << ". Exiting..." << std::endl;
	      //exit();
	    }
	}
      //std::cout << "*****************************" << std::endl;
    }

  //double bkg = 0;
  //double signal = 0;
  double significance= 0;
  std::vector<std::string> v_process;
  v_process.push_back("DY");
  v_process.push_back("TT");
  v_process.push_back("ST");
  v_process.push_back("VG");
  v_process.push_back("VV");
  v_process.push_back("Wjets");
  v_process.push_back("ZH");
  
  v_process.push_back("signal");
  
  for( auto& process: v_process )
    {
      std::cout << "process: " << process << std::endl;
      
    }
  
  std::vector<std::string> map_keys;
  
  for ( auto const& tmp_map : process_map["signal"] )
    {
      //std::cout << "map key: " << tmp_map.first  << std::endl;
      map_keys.push_back(tmp_map.first);
    }
  
  std::string best_key;
  double best_s, best_s_err, best_b, best_bkg_err, best_tf, best_tf_err;
  double best_dy_high, best_dy_high_err, best_dy_low, best_dy_low_err;
  for( auto key : map_keys )
    {
      //std::cout << "map: " << key << std::endl;
      double signal[3] = {0.0, 0.0, 0.0};
      double signal_err[3] = {0.0, 0.0, 0.0};
      double bkg[3]    = {0.0, 0.0, 0.0};
      double bkg_err[3]    = {0.0, 0.0, 0.0};
      
      double dy_high[3] = {0.0, 0.0, 0.0};
      double dy_high_err[3] = {0.0, 0.0, 0.0};
      double dy_low[3] = {0.0, 0.0, 0.0};
      double dy_low_err[3] = {0.0, 0.0, 0.0};
      
      double dy_tf[3]    = {0.0, 0.0, 0.0};
      double dy_tf_err[3]    = {0.0, 0.0, 0.0};

      for( auto const& my_map: process_map )
	{
	  if ( my_map.first == "signal" )
            {
              for ( int i = 0; i < 3; i++)
		{
		  signal[i]     += my_map.second.at(key).bin_high[i];
		  signal_err[i] += my_map.second.at(key).bin_high_err[i];
		}
            }
          else
            {
	      for ( int i = 0; i < 3; i++)
		{
		  bkg[i]    += my_map.second.at(key).bin_high[i];
		  bkg_err[i]    += my_map.second.at(key).bin_high_err[i];
		  if( my_map.first == "DY" )
		    {
		      dy_high[i]         = my_map.second.at(key).bin_high[i];
		      dy_high_err[i]     = my_map.second.at(key).bin_high_err[i];
		      dy_low[i]          = my_map.second.at(key).bin_low[i];
                      dy_low_err[i]      = my_map.second.at(key).bin_low_err[i];

		      dy_tf[i]     = my_map.second.at(key).tf[i];
		      dy_tf_err[i] = my_map.second.at(key).tf_err[i];
		    }
		}
            }
	}
      //std::cout << "map: " << key << " s: "  << signal << " bkg: " << bkg << std::endl;
      //double tmp_significance = signal[2]/sqrt(signal[2]+bkg[2]);
      double tmp_significance = signal[2]/(sqrt(bkg[2])+2.50);
      if ( tmp_significance > significance  && bkg[2]> 0 && dy_tf_err[2]/dy_tf[2] < 0.95  && dy_tf[2] > 0.0 )
        {
          significance = tmp_significance;
	  best_key = key;
	  best_s = signal[2];
	  best_s_err = signal_err[2];
	  best_b = bkg[2];
	  best_bkg_err = bkg_err[2];
	  best_tf = dy_tf[2];
	  best_tf_err = dy_tf_err[2];
	  best_dy_high = dy_high[2];
	  best_dy_high_err = dy_high_err[2];
	  best_dy_low = dy_low[2];
	  best_dy_low_err = dy_low_err[2];
        }
    }
  
  std::cout << "best_key: " << best_key << "\nbest signal:" << best_s << " +\- " << best_s_err << std::endl;
  std::cout << "best_bkg: "<< best_b << " +\- " << best_bkg_err << std::endl;
  std::cout << "best DY TF: " << best_tf << " +\- "  << best_tf_err << std::endl;
  std::cout << "best DY high: " << best_dy_high << " +\- "  << best_dy_high_err << std::endl;
  std::cout << "best DY low: " << best_dy_low << " +\- "  << best_dy_low_err << std::endl;
  /*
  for( auto const& m2 : process_map["signal"] )
    {
      
      double signal = 0.0;
      double bkg    = 0.0;
      //double signal = 0.0;
      for( auto const& mtemp : process_map )
	{
	  std::cout<< "process: " << mtemp.first << " key: " << key << std::endl;
	  if ( mtemp.first == "signal" )
	    {
	      signal += mtemp.second[key].bin_high[2];
	    }
	  else
	    {
	      bkg    += mtemp.second[key].bin_high[2];
	    }
	}
      double tmp_significance = signal/sqrt(signal+bkg);
      if ( tmp_significance > significance && bkg>0.5)
	{
	  significance = tmp_significance;
	} 
    }
  */
  std::cout << "significance: " << significance << std::endl;
  
  
  return 0;
};

