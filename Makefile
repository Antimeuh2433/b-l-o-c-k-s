# Defining variables
OSFLAG :=
CXX :=

# Define os
ifeq ($(OS),WINDOWS_NT)
	OSFLAG += Windows
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG += Unix
	endif
	ifeq ($(UNAME_S),Darwin)
		OSFLAG += Unix
	endif

# Change variables depending on the os
ifeq ($(OSFLAG),Windows)
	.LIBPATTERNS = lib%.dll
	CXX = g++
endif

ifeq ($(OSFLAG),Unix)
	.LIBPATTERNS = lib%.so
	CXX = clang

# Search paths
vpath %.cpp src
vpath %.hpp include/SFML


all:
	@echo $(OSFLAG)

main : main.o graphics.o
	$(CXX) -Wall -L/lib/$(OSFLAG) -lsfml-graphics -lsfml-window -lsfml-system -o main main.o

main.o : main.cpp Graphics.hpp Window.hpp System.hpp Config.hpp
	$(CXX) -Wall -c -I./include/ -o main.o src/main.cpp

graphics.o : Graphics.hpp
	$(CXX) -Wall -c -o graphics.o Graphics.hpp

clean :
	rm main *.o