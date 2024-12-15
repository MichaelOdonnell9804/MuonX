#!/bin/bash
#SBATCH -J is92C0RAA
#SBATCH -N 1
#SBATCH --ntasks-per-node=1
#SBATCH -o LOGS/%x.%j.out
#SBATCH -e LOGS/%x.%j.err
#SBATCH -p quanah

exefile=/home/skunori/MuonX/g4sim/ICSIMtest/icsim_03_01/sim/Linux-g++/exampleB4a
setupfile="/home/skunori/MuonX/g4sim/ICSIMtest/icsim_03_01/sim/muonSetupMacHPCC.sh"
# macfile="/home/skunori/MuonX/g4sim/ICSIMtest/icsim_02_02/hpccBatch/macfiles/v01/batch_run_C0RAA_01.mac"
macfile="/home/skunori/MuonX/g4sim/ICSIMtest/icsim_03_01/hpccBatch/macfiles/v03/batch_run_C0RAA_01.mac"
jobdir="/home/skunori/MuonX/g4sim/ICSIMtest/icsim_03_01/hpccBatch/BJOBS/bj040/ROOTFILES"


echo "starting ICSIM batch job."
pwd
echo "macfile=${macfile}"

thisdir=$PWD

source ${setupfile}

cd ${jobdir}
echo "ICSIM batch- job directory."
pwd

${exefile} -b ${macfile} -numberOfEvents 5000000 -runNumber 040 -runSeq 92 -createNtuple false -chamberSizeX 4.0 -chamberSizeY 4.0 -chamberSizeZ 3.0 -passagePosY 7.0

echo "ending ICSIM batch job."
cd ${thisdir}
pwd
echo "   "

