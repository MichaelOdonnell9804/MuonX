#!/bin/bash

module load gnu geant4 root

jobdir="/home/skunori/MuonX/g4sim/ICSIMtest/icsim_03_01/hpccBatch/BJOBS/bj042/ROOTFILES"
runnumber="042"


hadd yyrun${runnumber}_10fs50all_C0RAA_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_5*_C0RAA*root
hadd yyrun${runnumber}_10fs50all_C0RRR_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_5*_C0RRR*root

hadd yyrun${runnumber}_10fs60all_C0RAA_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_6*_C0RAA*root
hadd yyrun${runnumber}_10fs60all_C0RRR_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_6*_C0RRR*root

hadd yyrun${runnumber}_10fs70all_C0RAA_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_7*_C0RAA*root
hadd yyrun${runnumber}_10fs70all_C0RRR_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_7*_C0RRR*root

hadd yyrun${runnumber}_10fs80all_C0RAA_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_8*_C0RAA*root
hadd yyrun${runnumber}_10fs80all_C0RRR_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_8*_C0RRR*root

hadd yyrun${runnumber}_30f506070all_C0RAA_${runnumber}_5m400.root yyrun${runnumber}_10fs50all_C0RAA_${runnumber}_5m400.root yyrun${runnumber}_10fs60all_C0RAA_${runnumber}_5m400.root yyrun${runnumber}_10fs70all_C0RAA_${runnumber}_5m400.root
hadd yyrun${runnumber}_30f506070all_C0RRR_${runnumber}_5m400.root yyrun${runnumber}_10fs50all_C0RRR_${runnumber}_5m400.root yyrun${runnumber}_10fs60all_C0RRR_${runnumber}_5m400.root yyrun${runnumber}_10fs70all_C0RRR_${runnumber}_5m400.root

hadd yyrun${runnumber}_100fs100all_C0RAA_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_1*_C0RAA*root
hadd yyrun${runnumber}_100fs100all_C0RRR_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_1*_C0RRR*root

hadd yyrun${runnumber}_100fs300all_C0RAA_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_3*_C0RAA*root
hadd yyrun${runnumber}_100fs300all_C0RRR_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_3*_C0RRR*root

hadd yyrun${runnumber}_200fs100300all_C0RAA_${runnumber}_5m400.root yyrun${runnumber}_100fs100all_C0RAA_${runnumber}_5m400.root yyrun${runnumber}_100fs300all_C0RAA_${runnumber}_5m400.root
hadd yyrun${runnumber}_200fs100300all_C0RRR_${runnumber}_5m400.root yyrun${runnumber}_100fs100all_C0RRR_${runnumber}_5m400.root yyrun${runnumber}_100fs300all_C0RRR_${runnumber}_5m400.root

hadd yyrun${runnumber}_400fs_allall_C0RAA_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_*_C0RAA*root
hadd yyrun${runnumber}_400fs_allall_C0RRR_${runnumber}_5m400.root ${jobdir}/mc_ICv2_run${runnumber}_*_C0RRR*root
