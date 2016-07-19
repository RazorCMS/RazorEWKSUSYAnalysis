#!/usr/bin/env python

import subprocess, time, sys, os, shlex

inputFile = "/afs/cern.ch/work/z/zhicaiz/private/RazorHggRun1/CMSSW_7_6_3/src/RazorEWKSUSYAnalysis/HggRazor/FitMgg/eos/cms/store/group/phys_susy/razor/Run1Analysis/RazorHgg/DataPhotonRunABCD_May29_GoodLumi.root"
inputFileSignal = "/afs/cern.ch/work/z/zhicaiz/private/RazorHggRun1/CMSSW_7_6_3/src/RazorEWKSUSYAnalysis/HggRazor/FitMgg/eos/cms/store/group/phys_susy/razor/Run2Analysis/HggRazor/2016/V3p4_PhotonCorrJuly8_RegularSelectionSequence/HggRazor_SMS-T2bH_mSbottom-300_mLSP-1_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MiniAODv1_1pb_weighted.root"
inputFileSMH = "/afs/cern.ch/work/z/zhicaiz/private/RazorHggRun1/CMSSW_7_6_3/src/RazorEWKSUSYAnalysis/HggRazor/FitMgg/eos/cms/store/group/phys_susy/razor/Run1Analysis/RazorHgg/MC/ggH_8TeV.root"


outputDir = "/afs/cern.ch/work/z/zhicaiz/private/RazorHggRun1/CMSSW_7_6_3/src/RazorEWKSUSYAnalysis/HggRazor/FitMgg/mgg_fit/sb300_ggH/"



if __name__ == "__main__":
	bin_list_filename = sys.argv[1]
	
	pwd = os.getcwd()
	work_directory = pwd.replace("scripts","")

	os.system("mkdir -p "+outputDir)

	env_script_n = pwd + "/mgg_fit.sh"
	env_script_f = open(env_script_n, 'w')
        env_script_f.write("cd "+work_directory+" \n")
	
	with open(bin_list_filename,"r") as bin_list_file:
		for this_bin in bin_list_file:
			bin_array = shlex.split(this_bin)
			treeName = "HighRes"
			if bin_array[0]=="highpt":
				treeName = "HighPt"
			if bin_array[0]=="lowres":
				treeName = "LowRes"
			
			env_script_f.write("./MakeFitRun2 --inputFile="+inputFile+" --treeName="+treeName+" --LowMRcut="+bin_array[1]+" --HighMRcut="+bin_array[2]+" --LowRSQcut="+bin_array[3]+" --HighRSQcut="+bin_array[4]+" --dataMode=data+signal --category="+bin_array[0]+" --detector=ebeb --fitMode=sb --runPeriod=run1 --inputFileSignal="+inputFileSignal+" --inputFileSMH="+inputFileSMH+" --outputFile="+outputDir+bin_array[0]+ "_" +bin_array[1]+"_"+bin_array[3]+".root \n")
