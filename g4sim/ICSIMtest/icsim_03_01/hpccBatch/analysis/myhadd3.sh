#!/bin/bash

module load gnu geant4 root

jobdir="/home/skunori/MuonX/g4sim/ICSIMtest/icsim_03_01/hpccBatch/BJOBS/bj040/ROOTFILES"
runnumber="040"


hadd yyrun40_10fs50all_C0RAA_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_5*_C0RAA*root
hadd yyrun40_10fs50all_C0RRR_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_5*_C0RRR*root

hadd yyrun40_10fs60all_C0RAA_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_6*_C0RAA*root
hadd yyrun40_10fs60all_C0RRR_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_6*_C0RRR*root

hadd yyrun40_10fs70all_C0RAA_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_7*_C0RAA*root
hadd yyrun40_10fs70all_C0RRR_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_7*_C0RRR*root

hadd yyrun40_10fs80all_C0RAA_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_8*_C0RAA*root
hadd yyrun40_10fs80all_C0RRR_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_8*_C0RRR*root

hadd yyrun40_30f506070all_C0RAA_${runnumber}_5m400.root yyrun40_10fs50all_C0RAA_${runnumber}_5m400.root yyrun40_10fs60all_C0RAA_${runnumber}_5m400.root yyrun40_10fs70all_C0RAA_${runnumber}_5m400.root
hadd yyrun40_30f506070all_C0RRR_${runnumber}_5m400.root yyrun40_10fs50all_C0RRR_${runnumber}_5m400.root yyrun40_10fs60all_C0RRR_${runnumber}_5m400.root yyrun40_10fs70all_C0RRR_${runnumber}_5m400.root

hadd yyrun40_100fs100all_C0RAA_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_1*_C0RAA*root
hadd yyrun40_100fs100all_C0RRR_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_1*_C0RRR*root

hadd yyrun40_100fs300all_C0RAA_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_3*_C0RAA*root
hadd yyrun40_100fs300all_C0RRR_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_3*_C0RRR*root

hadd yyrun40_200fs100300all_C0RAA_${runnumber}_5m400.root yyrun40_100fs100all_C0RAA_${runnumber}_5m400.root yyrun40_100fs300all_C0RAA_${runnumber}_5m400.root
hadd yyrun40_200fs100300all_C0RRR_${runnumber}_5m400.root yyrun40_100fs100all_C0RRR_${runnumber}_5m400.root yyrun40_100fs300all_C0RRR_${runnumber}_5m400.root

hadd yyrun40_400fs_allall_C0RAA_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_*_C0RAA*root
hadd yyrun40_400fs_allall_C0RRR_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_*_C0RRR*root
