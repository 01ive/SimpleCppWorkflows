# Simple example #
This project propose a very simple example for C++ developers. It implements a GitHub *workflows* that run Google tests on Windows and Ubuntu platforms.

GitHub workflows generate artifacts containing:
* Ubuntu binary, Googletest results and code coverage analysis
* Windows binary and Googletest results

------
Files:

- *.github/workflows/ccpp.yml* GitHub configuration file
- *.vscode* and *myApp.code-worksapce* Visual Studio Code worksapce file
- *CMakeList.txt.in* Googletest CMake file
- *CMakeList.txt* CMake file (including MinGW set-up)   
- *myApp.cpp* Simple example file
- lcov.bat and lcov.sh are scripts used to generate html coverage repport

------

Developement has been done using:
* Windows 10
* Visual Studio Code 1.42.1
  * CMake 0.0.17
  * CMake Tools 1.3.1
* CMake 3.16.4
* MinGW GCC-8.2.0-5
* Googletest-23b2a3b1

Visual code project is configure for clean, build, run, test and debug.
