#! /bin/bash

signalDir=/Users/cmorgoth/Work/data/HggRazorRun2/july20MC_NewSmearing
smhDir=/Users/cmorgoth/Work/data/HggRazorRun2/july20MC_NewSmearing
outDir=data/lists/caltech/cp/80_X_With_bbH_photonEffSF

for i in $(ls $signalDir/HggRazor_SMS-T2bH_mSbottom-* | awk -F -T2bH_ '{ print $2 }' | awk -F _TuneCUETP8M1 '{print $1}');
do

    ###80_X
    echo -e "ggH\t"$smhDir/HggRazor_GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8_MiniAODv1_1pb_weighted.root > $outDir/list_$i.txt
    echo -e "vbfH\t"$smhDir/HggRazor_VBFHToGG_M125_13TeV_amcatnlo_pythia8_MiniAODv1_1pb_weighted.root >> $outDir/list_$i.txt
    echo -e "vH\t"$smhDir/HggRazor_VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8_MiniAODv1_1pb_weighted.root >> $outDir/list_$i.txt
    echo -e "ttH\t"$smhDir/HggRazor_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8_v2_MiniAODv1_1pb_weighted.root >> $outDir/list_$i.txt
    echo -e "bbH\t"$smhDir/HggRazor_bbHToGG_M-125_4FS_yb2_and_ybyt_13TeV_amcatnlo_MiniAODv1_1pb_weighted.root >> $outDir/list_$i.txt
    echo -e "signal\t"$signalDir/"HggRazor_SMS-T2bH_"$i"_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_MiniAODv1_1pb_weighted.root" >> $outDir/list_$i.txt

    ###76_X
    #echo -e "ggH\t"$smhDir/HggRazor_GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8_1pb_weighted.root > $outDir/list_$i.txt
    #echo -e "vbfH\t"$smhDir/HggRazor_VBFHToGG_M125_13TeV_amcatnlo_pythia8_1pb_weighted.root >> $outDir/list_$i.txt
    #echo -e "vH\t"$smhDir/HggRazor_VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8_1pb_weighted.root >> $outDir/list_$i.txt
    #echo -e "ttH\t"$smhDir/HggRazor_ttHJetToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8_v2_1pb_weighted.root >> $outDir/list_$i.txt
    #echo -e "bbH\t"$smhDir/HggRazor_bbHToGG_M-125_4FS_13TeV_amcatnlo_1pb_weighted.root >> $outDir/list_$i.txt
    #cho -e "signal\t"$signalDir/"HggRazor_SMS-T2bH_"$i"_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_1pb_weighted.root" >> $outDir/list_$i.txt

done
