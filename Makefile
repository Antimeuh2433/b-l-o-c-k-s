<<<<<<< HEAD
# Defining variables
OS := $(shell uname -o)


main : main.o graphics.o
	g++ -v -Wall -o main main.o

main.o : src/main.cpp include/SFML/Graphics.hpp include/SFML/Window.hpp include/SFML/System.hpp include/SFML/Config.hpp
	g++ -Wall -c -I./include/ -o main.o src/main.cpp

graphics.o : include/SFML/Graphics.hpp
	g++ -Wall -c -o graphics.o include/SFML/Graphics.hpp
=======
# Define os
ifeq ($(OS),WINDOWS_NT)
	OSFLAG=Windows
else
	UNAME_S:=$(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG=Linux
	else ifeq ($(UNAME_S),Darwin)
		OSFLAG=OSX
	endif
endif

# Change variables depending on the os
ifeq ($(OSFLAG),Windows)
	.LIBPATTERNS=lib%.dll
	CXX=g++
	EXECUTABLECXX=g++
else ifeq ($(OSFLAG),Linux)
	.LIBPATTERNS=lib%.so
	CXX=clang
	EXECUTABLECXX=clang
else ifeq ($(OSFLAG),OSX)
	.LIBPATTERNS=lib%.dylib
	CXX=clang
	EXECUTABLECXX=clang++
endif


main : main.o graphics.o
	$(EXECUTABLECXX) -Wall -L./lib/$(OSFLAG) -lsfml-graphics -lsfml-window -lsfml-system -o main main.o

main.o : src/Main.cpp include/SFML/Graphics.hpp include/SFML/Window.hpp include/SFML/System.hpp include/SFML/Config.hpp
	$(CXX) -Wall -c -I./include/ -o main.o src/main.cpp

graphics.o : include/SFML/Graphics.hpp
	$(CXX) -Wall -c -I./include/ -o graphics.o include/SFML/Graphics.hpp
>>>>>>> a185be9d3864b917d9bd6be232468535746d373f

clean :
	rm main *.o