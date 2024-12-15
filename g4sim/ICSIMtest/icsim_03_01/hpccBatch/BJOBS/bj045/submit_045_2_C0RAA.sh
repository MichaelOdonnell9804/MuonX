#!/bin/bash
#SBATCH -J is2C0RAA
#SBATCH -N 1
#SBATCH --ntasks-per-node=1
#SBATCH -o LOGS/%x.%j.out
#SBATCH -e LOGS/%x.%j.err
#SBATCH -p nocona

exefile=/home/michaeod/MuonX/g4sim/ICSIMtest/icsim_03_01/sim/Linux-g++/exampleB4a
setupfile="/home/michaeod/MuonX/g4sim/ICSIMtest/icsim_03_01/sim/muonSetupMacHPCC.sh"
# macfile="/home/michaeod/MuonX/g4sim/ICSIMtest/icsim_02_02/hpccBatch/macfiles/v01/batch_run_C0RAA_01.mac"
macfile="/home/michaeod/MuonX/g4sim/ICSIMtest/icsim_03_01/hpccBatch/macfiles/v03/batch_run_C0RAAMAC_01.mac"
jobdir="JOBDIR/ROOTFILES"


echo "starting ICSIM batch job."
pwd
echo "macfile=${macfile}"

thisdir=$PWD

source ${setupfile}

cd ${jobdir}
echo "ICSIM batch- job directory."
pwd

${exefile} -b ${macfile} -numberOfEvents 10000EVENTS -runNumber 0001RUN -runSeq 0001SEQ -createNtuple false -chamberSizeX 1.0 -chamberSizeY 1.0 -chamberSizeZ 1.0 -passagePosY 7.0 -cameraWidth 2.0

echo "ending ICSIM batch job."
cd ${thisdir}
pwd
echo "   "

