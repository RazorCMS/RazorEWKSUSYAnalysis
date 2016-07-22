#! /bin/bash

for i in `seq 0 13`;
do
    echo "#!/bin/sh " > submit/bash_submit_significance_bin$i.sh
    echo cd $PWD >> submit/bash_submit_significance_bin$i.sh
    echo "eval \`scramv1 run -sh\`;" >> submit/bash_submit_significance_bin$i.sh
    echo combine -M ProfileLikelihood --signif HggRazorCombinedCard_bin$i.txt -n _bin$i.nsigma --setPhysicsModelParameterRanges r=-20,20 --uncapped 1 >> submit/bash_submit_significance_bin$i.sh
    echo combine -M ProfileLikelihood --signif --pvalue HggRazorCombinedCard_bin$i.txt -n _bin$i.pvalue --setPhysicsModelParameterRanges r=-20,20 --uncapped 1 >> submit/bash_submit_significance_bin$i.sh
    echo hadd PL_nsigma_npvalue_bin$i.root higgsCombine_bin$i.nsigma.ProfileLikelihood.mH120.root higgsCombine_bin$i.pvalue.ProfileLikelihood.mH120.root >> submit/bash_submit_significance_bin$i.sh
    bsub -q 1nh source $PWD/submit/bash_submit_significance_bin$i.sh
    sleep 0.1
done
