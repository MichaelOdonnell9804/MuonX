#!/bin/bash

#########################################################
# This script creates a set of sh files for G4 batch job submission.
#   usage:  
#   ./MTmakeBatch.sh
#
#   parameters in TEMPLATE FILES
#
# -- submit_TEMPLATE.sh
# XXXXJOBDIR       (eg: /lustre/work/vbradley/MuonSC8/mc_prototype1-b/BJOBS/bj001)
# XXXXRUNNUMBER    (eg: 001,002, etc.))
# XXXXSEQNUMBER    (eg: 001,002, etc.)
#
# -- run_batch_TEMPLATE.sh
# XXXXROOTFILE     (eg: ROOTFILES/g4data_001_n001.root)
# XXXXMACFILE      (eg: mac_batch_001_n001.mac)
#
# -- mac_batch_TEMPLATE.mac
# XXXXEVENTS       (eg: 1000)
#
#    directory structure
# (g4batchTOP)
#    BJOBS
#      bjxxxx    (xxxx: run number 0000-9999)
#         ROOTFILES
#         LOGS
#         (sh and mac files)
#      bjxxxx
#
#  
#########################################################


# [1] User needs to setup this section...
# JOBDIRTOP=/lustre/work/vbradley/MuonSC8/mc_prototype1-b/BJOBS
JOBDIRTOP=/home/michaeod/MuonX/g4sim/ICSIMtest/icsim_03_01/hpccBatch/BJOBS
RUNNUMBER=045
NJOBS=2          # number of jobs
NEVENTS=200    # number of events per job
# MACLIST=("C0RAA" "C0RRR" "C1RAA" "C1RRR" "C2RAA" "C2RRR" "C3RAA" "C3RRR")
MACLIST=("C0RAA" "C0RRR")

SUBMITtemp="submit_TEMPLATE.sh"


# [2] Job indepentend section. 
#     Modify this section,  if you knwo what you are doing...
# 
#   derived parameters...
jobdir="${JOBDIRTOP}/bj${RUNNUMBER}"

echo "jobdir= $jobdir"


if [ ! -d $JOBDIRTOP ];then
  mkdir $JOBDIRTOP
fi

if [ ! -d $jobdir ];then
  mkdir $jobdir
fi

if [ ! -d $jobdir/LOGS ];then
  mkdir $jobdir/LOGS
fi

if [ ! -d $jobdir/ROOTFILES ];then
  mkdir $jobdir/ROOTFILES
fi


zzfile=${jobdir}/zzsubmit.sh
echo "#!/bin/bash" > $zzfile


for ((seq=1; seq<($NJOBS+1); seq++))
do

for macfile in ${MACLIST[@]}; do
   echo "seq= $seq"
   # macfile="C0RAA"
   submitfile="${jobdir}/submit_${RUNNUMBER}_${seq}_${macfile}.sh"
   echo ${submitfile}
   echo ${macfile}
   cat $SUBMITtemp | sed -e "s#XXXXJOBNAME#is${seq}${macfile}#;s#XXXXJOBDIR#${jobdir}#;s#XXXXRUN#$RUNNUMBER#;s#XXXXSEQ#$seq#;s#XXXXEVENTS#$NEVENTS#;s#XXXXMAC#${macfile}#;s#XXXXJOBDIR#${jobdir}#" > $submitfile
   echo "sbatch submit_${RUNNUMBER}_${seq}_${macfile}.sh" >> $zzfile
   # cp $SUBMITtemp $submitfile
   # cp $RUNtemp    $batchfile
   # cp $MACtemp    $macfile

done
done

echo " "
echo "To submit jobs, run zzsubmit.sh in"
echo "${jobdir}"
echo " "

