#!/bin/bash

## B-L-0-C-K-S - Proof of Concept block game inspired by Tetris
## Copyright (C) 2020  Justin BAX and Chris YANG
##
##    This program is free software: you can redistribute it and/or modify
##    it under the terms of the GNU General Public License as published by
##    the Free Software Foundation, either version 3 of the License, or
##    any later version.
##
##    This program is distributed in the hope that it will be useful,
##    but WITHOUT ANY WARRANTY; without even the implied warranty of
##    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##    GNU General Public License for more details.
##
##    You should have received a copy of the GNU General Public License
##    along with this program.  If not, see <https://www.gnu.org/licenses/>.

echo "Make sure to run the script in the downloaded repo directory and as a standard user"
echo "The required libraries are in ./lib/OSX, to run the program, specify the directory in the LD_LIBRARY_PATH variable"
echo "i.e.  $ LD_LIBRARY_PATH=./lib/OSX ./b-l-o-c-k-s"
echo "Clang/LLVM is required to compile this program, please make sure it's installed"
echo


read -p 'Binary Install Directory [./bin]: ' INSTALLDIR
if [[ -z $INSTALLDIR ]]; then
    INSTALLDIR="./bin"
fi

echo "Compiling, please wait..."
clang++ -Wall -c -Iinclude/ -o main.o src/main.cpp 
clang++ -Wall -c -Iinclude/ -o graphics.o include/SFML/Graphics.hpp
clang++ -Wall -L/usr/lib -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system -o main main.o
echo "Cleaning up..."
sudo rm ./*.o
echo "Compilation Process Completed, moving binaries to $INSTALLDIR"
sudo mv ./main $INSTALLDIR/b-l-o-c-k-s
echo "Updating permissions"
sudo chown root:admin $INSTALLDIR/b-l-o-c-k-s
sudo chmod 755 $INSTALLDIR/b-l-o-c-k-s
echo "All Done :D"
