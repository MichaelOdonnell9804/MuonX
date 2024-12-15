#!/bin/bash
#SBATCH -J is99C0RAA
#SBATCH -N 1
#SBATCH --ntasks-per-node=1
#SBATCH -o LOGS/%x.%j.out
#SBATCH -e LOGS/%x.%j.err
#SBATCH -p quanah

exefile=/home/skunori/MuonX/g4sim/ICSIMtest/icsim_02_02/sim/Linux-g++/exampleB4a
setupfile="/home/skunori/MuonX/g4sim/ICSIMtest/icsim_02_02/sim/muonSetupMacHPCC.sh"
# macfile="/home/skunori/MuonX/g4sim/ICSIMtest/icsim_02_02/hpccBatch/macfiles/v01/batch_run_C0RAA_01.mac"
macfile="/home/skunori/MuonX/g4sim/ICSIMtest/icsim_02_02/hpccBatch/macfiles/v02/batch_run_C0RAA_01.mac"
jobdir="/home/skunori/MuonX/g4sim/ICSIMtest/icsim_02_02/hpccBatch/BJOBS/bj013/ROOTFILES"


echo "starting ICSIM batch job."
pwd
echo "macfile=${macfile}"

thisdir=$PWD

source ${setupfile}

cd ${jobdir}
echo "ICSIM batch- job directory."
pwd

${exefile} -b ${macfile} -numberOfEvents 2000000 -runNumber 013 -runSeq 99 -createNtuple false -chamberSizeX 2.0 -chamberSizeY 2.0 -chamberSizeZ 2.0 -passagePosY 11.0

echo "ending ICSIM batch job."
cd ${thisdir}
pwd
echo "   "

