#! /bin/bash

for i in `seq 0 20`;
do
    echo "#!/bin/sh " > submit/bash_submit_bin$i.sh
    echo cd $PWD >> submit/bash_submit_bin$i.sh
    echo "eval \`scramv1 run -sh\`;" >> submit/bash_submit_bin$i.sh
    echo combine -M MaxLikelihoodFit HggRazorCombinedCard_bin$i.txt --saveNormalizations --plots --saveShapes --saveWithUncertainties -n _bin$i --minimizerStrategy=2  --setPhysicsModelParameterRanges r=-20,20 >> submit/bash_submit_bin$i.sh
    bsub -q 1nh source $PWD/submit/bash_submit_bin$i.sh
    sleep 0.1
done
