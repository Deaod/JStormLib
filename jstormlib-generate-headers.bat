:: Disable printing my own commands
@echo off

:: path to javah executable
:: currently assumes you have a jdk in your PATH variable
set JAVAH=javah

:: Store old working directory for later use
set OLD_DIR=%CD%

:: Where to load the java classes from
set CLASS_DIR=%CD%\Java\JStormLib\target\classes\

:: where to put resulting .h files
set OUTPUT_DIR=%CD%\Native\JStormLib

:: individual classes that have natives in them
set MPQARCHIVE=de.deaod.jstormlib.MPQArchive
set MPQFILE=de.deaod.jstormlib.MPQFile
set MPQSEARCH=de.deaod.jstormlib.MPQSearch
set MPQCOMP=de.deaod.jstormlib.MPQCompression

set OUT_MPQARCHIVE=%OUTPUT_DIR%\MPQArchive.h
set OUT_MPQFILE=%OUTPUT_DIR%\MPQFile.h
set OUT_MPQSEARCH=%OUTPUT_DIR%\MPQSearch.h
set OUT_MPQCOMP=%OUTPUT_DIR%\MPQCompression.h

:: switch to the appropriate directory
cd "%CLASS_DIR%"

"%JAVAH%" -verbose -force -o "%OUT_MPQARCHIVE%" "%MPQARCHIVE%"
"%JAVAH%" -verbose -force -o "%OUT_MPQFILE%" "%MPQFILE%"
"%JAVAH%" -verbose -force -o "%OUT_MPQSEARCH%" "%MPQSEARCH%"
"%JAVAH%" -verbose -force -o "%OUT_MPQCOMP%" "%MPQCOMP%"

pause