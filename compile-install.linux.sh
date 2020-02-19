#!/bin/bash
echo "Make sure to run the script in the downloaded repo directory and as ROOT"
echo "Checking distrib version and pulling dependencies"
if [[ $(cat /etc/*-release | grep "ID_LIKE") = *debian* ]]; then
    apt-get update && apt-get install -y libsfml-dev
elif [[ $(cat /etc/*-release | grep "ID") = *arch* ]]; then
    pacman -Syy sfml --noconfirm
elif [[ $(cat /etc/*-release | grep "ID") = *fedora* ]]; then
    dnf check-update && dnf install -y compat-SFML16
else
    echo "Unable to automatically resolve dependencies due to incompatible distribution"
    echo "Please make sure to resolve dependencies manually if not already done"
    echo "SFML Libraries are available in the ./lib/Linux folder"
    echo "The build will continue"
fi

read -p 'Binary Install Directory [./bin]: ' INSTALLDIR
if [-z $INSTALLDIR]; then
    echo ./bin > $INSTALLDIR

wait 1

echo "Compiling, please wait..."
g++ -Wall -c -I./include/ -o main.o src/main.cpp 
g++ -Wall -c -I./include/ -o graphics.o include/SFML/Graphics.hpp
g++ -Wall -L/lib/ -L/usr/lib -lsfml-graphics -lsfml-window -lsfml-system -o main main.o
echo "Cleaning up..."
rm ./*.o
echo "Moving binaries to $INSTALLDIR"
mv ./main $INSTALLDIR/main
