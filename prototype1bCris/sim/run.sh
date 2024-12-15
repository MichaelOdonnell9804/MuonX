rm Muon*.root

. muonSetup.sh
make clean
make -j32

sh ./run_batch1.sh & batch1=$!
sh ./run_batch2.sh & batch2=$!
sh ./run_batch3.sh & batch3=$!
sh ./run_batch4.sh & batch4=$!
sh ./run_batch5.sh & batch5=$!
sh ./run_batch6.sh & batch6=$!
sh ./run_batch7.sh & batch7=$!
sh ./run_batch8.sh & batch8=$!
sh ./run_batch9.sh & batch9=$!
sh ./run_batch10.sh & batch10=$!
sh ./run_batch11.sh & batch11=$!
sh ./run_batch12.sh & batch12=$!
sh ./run_batch13.sh & batch13=$!
sh ./run_batch14.sh & batch14=$!
sh ./run_batch15.sh & batch15=$!
sh ./run_batch16.sh & batch16=$!
#sh ./run_batch17.sh & batch17=$!
#sh ./run_batch18.sh & batch18=$!
#sh ./run_batch19.sh & batch19=$!
#sh ./run_batch20.sh & batch20=$!
#sh ./run_batch21.sh & batch21=$!
#sh ./run_batch22.sh & batch22=$!
#sh ./run_batch23.sh & batch23=$!
#sh ./run_batch24.sh & batch24=$!
#sh ./run_batch25.sh & batch25=$!
#sh ./run_batch26.sh & batch26=$!
#sh ./run_batch27.sh & batch27=$!
#sh ./run_batch28.sh & batch28=$!
#sh ./run_batch29.sh & batch29=$!
#sh ./run_batch30.sh & batch30=$!
#sh ./run_batch31.sh & batch31=$!
#sh ./run_batch32.sh & batch32=$!

wait $batch1
wait $batch2
wait $batch3
wait $batch4
wait $batch5
wait $batch6
wait $batch7
wait $batch8
wait $batch9
wait $batch10
wait $batch11
wait $batch12
wait $batch13
wait $batch14
wait $batch15
wait $batch16
#wait $batch17
#wait $batch18
#wait $batch19
#wait $batch20
#wait $batch21
#wait $batch22
#wait $batch23
#wait $batch24
#wait $batch25
#wait $batch26
#wait $batch27
#wait $batch28
#wait $batch29
#wait $batch30
#wait $batch31
#wait $batch32

hadd -f Muon.root Muon*.root

cp Muon*.root /home/cristmor/work/g4/user/Muon/mc_test/ana
cd /home/cristmor/work/g4/user/Muon/mc_test/ana

cp Muon.root muonTree01.root
cp Muon.root cristmormsi_proto_1mill_1_leadbrick1cmV_1.root
. runana.sh
cp muonTree01hist.root Muonh.root
cp muonTree01hist.root cristmormsi_proto_1mill_1_leadbrick1cmV_1_hist.root

cd /home/cristmor/work/g4/user/Muon/threads
