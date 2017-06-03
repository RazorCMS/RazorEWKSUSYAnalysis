#! /bin/bash

while [[ $# -gt 1 ]]
do
    #echo blash $#
    key="$1"
    #echo $key " " $2
    
    case $key in
	-if|--inputFileDir)
	    inputfiledir="$2"
	    shift #past argument
	    ;;
	-i1|--inputDir1)
	    indir1="$2"
	    shift # past argument
	    ;;
	-i2|--inputDir2)
	    indir2="$2"
	    shift # past argument
	    ;;
	-o|--outputFile)
	    outfile="$2"
	    shift # past argument
	    ;;
	-d|--dataFile)
	    datafile="$2"
	    shift # past argument
	    ;;
	-smh|--smhFile)
	    smhfile="$2"
	    shift # past argument
	    ;;
	-s|--signalFile)
	    sfile="$2"
	    shift # past argument
	    ;;
	-b|--binningFile)
	    bfile="$2"
	    shift # past argument
	    ;;
	--default)
	    DEFAULT=YES
	    ;;
	*)
            # unknown option
	    ;;
    esac
    shift # past argument or value
done


#echo INPUT FILE  = $inputfiledir
#echo OUTFILE PREFIX = $outfile

extra_tag=EWK_Combination_31May
indir=TChiHH_HZ
br=BR9010

for j in $(ls $inputfiledir);
do
    name=`echo $j | awk -F "list_" '{print $2}' | awk -F ".txt" '{print $1}'`
    echo ./CreateDataCardCommands" --inputCF="$indir1$name".txt --outputFile=MakeDataCards_"${indir}${extra_tag}${br}$"_"$name".sh --dataFile="$datafile" --smhFile="$smhfile" --signalFile="$sfile"/SMS-TChiHHHZ_"${br}"_"${name}"_1pb_weighted.root --sModel="${indir}"_"${br}/${name}"_DataCards_"$extra_tag" --binningFile="$bfile --currentDir=$PWD
    echo bsub -q 8nh -e  $PWD/err/$name.err -o  $PWD/log/$name.out source MakeDataCards_${indir}${extra_tag}${br}"_"$name.sh
done


if [[ -n $1 ]]; then
    echo "Last line of file specified as non-opt/last argument:"
    tail -1 $1
fi


