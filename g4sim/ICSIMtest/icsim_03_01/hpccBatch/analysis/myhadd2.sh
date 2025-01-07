#!/bin/bash

module load gnu geant4 root

jobdir="/home/skunori/MuonX/g4sim/ICSIMtest/icsim_03_01/hpccBatch/BJOBS/bj033/ROOTFILES"
runnumber="033"

hadd y100s300all_C0RAA_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_3*_C0RAA*root
hadd y100s300all_C0RRR_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_3*_C0RRR*root
