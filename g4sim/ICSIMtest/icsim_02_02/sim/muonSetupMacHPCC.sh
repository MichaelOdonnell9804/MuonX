#!/bin/sh
echo File has been accessed
module load gnu geant4 root
echo modules loaded
echo "which python...  to check conda...  it should be off"
which python

export CRYHOME=/lustre/work/cristmor/MuonSC8/icsim_01_03/sim/include
export CRYDATAPATH=/lustre/work/perez90/hep/cry/cry_v1.7/data
echo cry loaded
. /opt/ohpc/pub/libs/gnu/geant4/10.04.p02/bin/geant4.sh
echo geant4.sh executed
export G4BASE=/opt/ohpc/pub/libs/gnu/geant4/10.04.p02
export G4INSTALL=/opt/ohpc/pub/libs/gnu/geant4/10.04.p02/share/Geant4-10.4.2/geant4make
source /opt/ohpc/pub/libs/gnu/geant4/10.04.p02/share/Geant4-10.4.2/geant4make/geant4make.sh
echo g4 make stuff
export G4BIN="$PWD"

