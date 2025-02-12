#$-V
#$-cwd
#$-S /bin/bash
#$-N g4cry_XXXXPARAM1
#$-o logs/$JOB_NAME.stdout$JOB_ID
#$-e logs/$JOB_NAME.stderr$JOB_ID
#$-q serial
#$-P grid
#   XSHFIT 0 for camera 1,  -40000 in mm= -40mm for camera 2, 40000 for camera 3
export G4CRYXSHIFT=0     # in mm
export G4CRYYSHIFT=0     # in mm
export G4CRYZSHIFT=1500  # in mm
export G4CRYPCUT=1    # in MeV
#export G4CRYOUTFILE=B4job1Room200cm100ev_XXXXPARAM1
#export CRYRANDOMSEED="$((1000 + RANDOM % 9999))"
# env
#export DYLD_LIBRARY_PATH=/Applications/root_v6.18.00/lib
export CaloXG4SeedA=1       # 0=default (fixed), 1 auto, >1 manual seed setting
export CaloXG4SeedB="$((1000 + RANDOM % 9999))"
export MuonXG4OutName="Muon10.root"

/home/cristmor/work/g4/user/Muon/threads/Linux-g++/exampleB4a -m batch_run.mac
