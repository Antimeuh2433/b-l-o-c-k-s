#!/bin/bash
clang++ -Wall -I./include/ -c -g -o main.o ./src/main.cpp
clang++ -Wall -I./include/ -c -g -o graphics.o ./include/SFML/Graphics.hpp
clang++ -Wall -I./include/ -c -g -o block.o ./src/block.cpp
clang++ -Wall -L./lib/OSX -L/usr/local/Cellar/sfml/2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -g main.o block.o