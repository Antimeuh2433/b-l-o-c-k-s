@echo off
echo Make sure to run this file from the downloaded repository folder and have installed MinGW64 7.3.0 (x64) [The version is IMPORTANT]
echo you can download it from the SFML website 
echo MinGW binaries must be added to your PATH, if it's not there, the compile will fail
echo.
set /p installDIR="Enter Install Path [.\bin\] : "

IF NOT DEFINED installDIR (SET installDIR=.\bin)

echo Installing to %installDIR%

echo Compiling, please wait...
g++ -Wall -c -I./include/ -o main.o src/main.cpp 
g++ -Wall -c -I./include/ -o graphics.o include/SFML/Graphics.hpp
g++ -Wall -L./lib/Windows -lsfml-graphics-2 -lsfml-window-2 -lsfml-system-2 -o main main.o
echo Cleaning up...
del .\*.o
echo Compiling Process Completed, moving Install into installation directory at %installDIR%
copy .\lib\Windows\*.dll %installDIR%\*.dll
move .\main.exe %installDIR%\main.exe
ren %installDIR%\*.exe b-l-o-c-k-s.exe
echo All Done! :D


