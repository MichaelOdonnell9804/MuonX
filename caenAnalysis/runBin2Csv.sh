#!/bin/bash


indir=/lustre/work/sundleeb/TTUMuon/TimingMode09-27-22
subdir=("Run17_300Th_HV59_ChAll"
        "Run18_200Th_HV59_ChAll"
        "Run19_180Th_HV59_ChAll"
        "Run20_180Th_HV59_ChEven"
        "Run21_200Th_HV59_ChEven"
        "Run22_200Th_HV59_Ch0"
        "Run23_300Th_HV59_ChEven"
        "Run24_300Th_HV59_ChOdd"
        "Run25_300Th_HV59_ChNone"
        "Run26_180Th_HV59_ChNone"
        "Run27_200Th_HV59_ChNone"
)

echo ${indir}
echo ${subdir}

n=16
for sname in ${subdir[@]}; do
   n=$((n+1))
   echo ${n}
   echo "test ${sname}"
   fname="${indir}/${subdir}/Run${n}_list.dat"
   echo ${fname}
done
# ./BinToCsv  --bfile Run17_300Th_HV59_ChAll/Run17_list.dat
# ./BinToCsv  --bfile Run18_200Th_HV59_ChAll/Run18_list.dat
# ./BinToCsv  --bfile Run19_180Th_HV59_ChAll/Run19_list.dat
# ./BinToCsv  --bfile Run20_180Th_HV59_ChEven/Run20_list.dat
# ./BinToCsv  --bfile Run21_200Th_HV59_ChEven/Run21_list.dat
# ./BinToCsv  --bfile Run22_200Th_HV59_Ch0/Run17_22st.dat
# ./BinToCsv  --bfile Run23_300Th_HV59_ChEven/Run23_list.dat
# ./BinToCsv  --bfile Run24_300Th_HV59_ChOdd/Run24_list.dat
# ./BinToCsv  --bfile Run25_300Th_HV59_ChNone/Run25_list.dat
# ./BinToCsv  --bfile Run26_180Th_HV59_ChNone/Run26_list.dat





