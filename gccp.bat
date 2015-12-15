@echo off

set "file=%~1%" 
set "directory=%~dp0%" 
set "newvar=%directory%%file%"

echo compiling C++ using -ansi -pedantic-errors -Wall
g++ -ansi -pedantic-errors -Wall -o orbit %directory%\source_files\orbit.cpp -lmingw32 -lSDLmain -lSDL