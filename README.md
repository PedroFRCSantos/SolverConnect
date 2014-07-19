SolverConnect
=============

Program to solve boards automatically of mobile games like: Flow Free
(https://play.google.com/store/apps/details?id=com.bigduckgames.flow&hl=pt-PT)
or Flow Frenzy: Connect for Free
(https://play.google.com/store/apps/details?id=slide.flowFrenzy&hl=pt-PT).

Build
=====

Prerequisite:

 * Unix: g++, make, pkg-config, boost (if use multi-threading)
 * Windows: supported compiler, boost (if use multi-threading)
 
Unix
----

- If you do not have g++ compiler start to install it.

    $ sudo apt-get update
    $ sudo apt-get install build-essential
	
- Create an empty file called stdafx.h.

    $ touch stdafx.h
	
### 1) Using multi-threading

- Install boost library.

	$ sudo apt-get install libboost-all-dev
	$ make
	$ ./SolverConnect

### 2) Do not use multi-threading

- Start to comment line 7 in GlobalData.hpp "#define USE_MULTI_THREAD".
- In Makefile change line 2 from "-lboost_thread -pthread" to
"#-lboost_thread -pthread".
- Compile and run program:

	$ make
	$ ./SolverConnect
	
Windows
-------

- Install Visual Studio compatible with C++.
- Create an C++ empty project in Visual Studio.
- Add code files to project

### 1) Using multi-threading

- Download boost, to be easier to you can use pre-build libraries for Windows, available
in http://boost.teeks99.com/.
- Configure paths in project (Debug x86). AdditionalIncludeDirectories: PathToBoost\boost_1_55_0;
AdditionalLibraryDirectories: E:\local\boost_1_55_0\lib32-msvc-11.0;
AdditionalDependencies: libboost_thread-vc110-mt-gd-1_55.lib
- Compile and Run program.

### 2) Do not use multi-threading

- Comment line 7 in GlobalData.hpp "#define USE_MULTI_THREAD".
- Compile and Run program.
