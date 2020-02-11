# Defining variables
OS := $(shell uname -o)


main : main.o graphics.o
	g++ -v -Wall -o main main.o

main.o : src/main.cpp include/SFML/Graphics.hpp include/SFML/Window.hpp include/SFML/System.hpp include/SFML/Config.hpp
	g++ -Wall -c -I./include/ -o main.o src/main.cpp

graphics.o : include/SFML/Graphics.hpp
	g++ -Wall -c -o graphics.o include/SFML/Graphics.hpp

clean :
	rm main *.o