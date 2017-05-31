#! /bin/bash

signalDir=/eos/cms/store/group/phys_susy/razor/Run2Analysis/HggRazor/2016/V3p12_PhotonCorrDec06_JECSep23V3_20170219/FastsimSignal/combined/
outDir=/afs/cern.ch/work/c/cpena/public/combineDiphotonHM/CMSSW_7_4_7/src/RazorEWKSUSYAnalysis/HggRazor/PlottingAndSystematic/data/lists/EWKcombination/TChiHH_May13/

for i in $(ls $signalDir/SMS-TChiHH_*_1pb_weighted.root | awk -F SMS-TChiHH_ '{ print $2 }' | awk -F _1pb_weighted.root '{print $1}');
do
    echo -e "signal\t"$signalDir/"SMS-TChiHH_"$i"_1pb_weighted.root" > $outDir/list_$i.txt
done
