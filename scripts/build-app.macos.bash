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

echo -n "Compiling ... "
clang++ -std=c++11 -Wall -c -I./include -I./frameworks -D __BUILD_APPLICATION_OSX__ -o main.o ./src/main.cpp
clang++ -std=c++11 -Wall -c -I./include -o block.o ./src/block.cpp
clang++ -std=c++11 -Wall -L./lib/OSX -rpath ./lib/OSX/extlibs -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -F./frameworks -framework CoreFoundation -o b-l-o-c-k-s main.o block.o
echo -n "done"
echo
echo -n "Cleaning up ... "
rm *.o
echo -n "done"
echo
echo -n "Creating application ... "
mkdir -p b-l-o-c-k-s.app/Contents/MacOS
mv b-l-o-c-k-s b-l-o-c-k-s.app/Contents/MacOS
echo -n "done"
echo
echo -n "Copying libraries ... "
cp ./lib/OSX/*.dylib ./b-l-o-c-k-s.app/Contents/MacOS
echo -n "& content files ... "
cd ./b-l-o-c-k-s.app/Contents
mkdir Resources
cd ../
cd ../
cp ./content/*.ogg b-l-o-c-k-s.app/Contents/Resources
cp ./content/*.png b-l-o-c-k-s.app/Contents/Resources
cp -r ./content/tiles b-l-o-c-k-s.app/Contents/Resources
echo -n "& Info.plist ... "
cp ./content/OSX/Info.plist ./b-l-o-c-k-s.app/Contents
echo -n "done"
echo
echo -n "Changing dependencies location ... "
install_name_tool -change ./lib/OSX/libsfml-graphics.2.5.1.dylib @executable_path/libsfml-graphics.2.5.1.dylib b-l-o-c-k-s.app/Contents/MacOS/b-l-o-c-k-s
install_name_tool -change ./lib/OSX/libsfml-window.2.5.1.dylib @executable_path/libsfml-window.2.5.1.dylib b-l-o-c-k-s.app/Contents/MacOS/b-l-o-c-k-s
install_name_tool -change ./lib/OSX/libsfml-system.2.5.1.dylib @executable_path/libsfml-system.2.5.1.dylib b-l-o-c-k-s.app/Contents/MacOS/b-l-o-c-k-s
install_name_tool -change ./lib/OSX/libsfml-audio.2.5.1.dylib @executable_path/libsfml-audio.2.5.1.dylib b-l-o-c-k-s.app/Contents/MacOS/b-l-o-c-k-s

install_name_tool -change /usr/local/opt/sfml/lib/libsfml-graphics.2.5.dylib @executable_path/libsfml-graphics.2.5.1.dylib b-l-o-c-k-s.app/Contents/MacOS/b-l-o-c-k-s
install_name_tool -change /usr/local/opt/sfml/lib/libsfml-window.2.5.dylib @executable_path/libsfml-window.2.5.1.dylib b-l-o-c-k-s.app/Contents/MacOS/b-l-o-c-k-s
install_name_tool -change /usr/local/opt/sfml/lib/libsfml-system.2.5.dylib @executable_path/libsfml-system.2.5.1.dylib b-l-o-c-k-s.app/Contents/MacOS/b-l-o-c-k-s
install_name_tool -change /usr/local/opt/sfml/lib/libsfml-audio.2.5.dylib @executable_path/libsfml-audio.2.5.1.dylib b-l-o-c-k-s.app/Contents/MacOS/b-l-o-c-k-s
echo -n "done"
echo