#!/bin/bash

module load gnu geant4 root

jobdir="/home/skunori/MuonX/g4sim/ICSIMtest/icsim_02_02/hpccBatch/BJOBS/bj014/ROOTFILES"
runnumber="014"

hadd all_C0RAA_${runnumber}.root ${jobdir}/mc_ICv2_run${runnumber}_*_C0RAA*root
hadd all_C0RRR_${runnumber}.root ${jobdir}/mc_ICv2_run${runnumber}_*_C0RRR*root
hadd all_C1RAA_${runnumber}.root ${jobdir}/mc_ICv2_run${runnumber}_*_C1RAA*root
hadd all_C1RRR_${runnumber}.root ${jobdir}/mc_ICv2_run${runnumber}_*_C1RRR*root
hadd all_C2RAA_${runnumber}.root ${jobdir}/mc_ICv2_run${runnumber}_*_C2RAA*root
hadd all_C2RRR_${runnumber}.root ${jobdir}/mc_ICv2_run${runnumber}_*_C2RRR*root
hadd all_C3RAA_${runnumber}.root ${jobdir}/mc_ICv2_run${runnumber}_*_C3RAA*root
hadd all_C3RRR_${runnumber}.root ${jobdir}/mc_ICv2_run${runnumber}_*_C3RRR*root
