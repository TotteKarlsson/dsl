DSL 
============================================

Build instructions using CMake from the command line.

We are assuming that the DSL sources are in a folder: c:\libs\dsl

Visual Studio 2013
------------------

The build sequence is to build and install Third party libraries first, step A, and then
build and install the DSL library and examples, step B.

STEP A: Build DSL's ThirdParty libraries, i.e. Poco, sqlite3, tinyxml2 and TClap
................................................................................

1) Download Boost 1.61 from https://www.boost.org/users/history/version_1_61_0.html
and unpack to a suitable folder, e.g. c:\libs\Boost

2) Create a folder that will hold generated binaries and libraries, e.g. c:\vsbuild

3) Create an out of source folder for creating VS build files for DSL's ThirdParty libraries, e.g.
C:\vsbuilds\2013\dsl-tp

4) Open a console and cd to the folder created in step 2). 

Create VS2013 build files by running cmake at the command line, e.g.:

> cmake -G"Visual Studio 12 2013" -DCMAKE_INSTALL_PREFIX=c:\vsbuild -H"c:/libs/dsl/ThirdParties" -B.

To create x64 build, use the command line:
> cmake -G"Visual Studio 12 2013 Win64" -DCMAKE_INSTALL_PREFIX=c:/vsbuild -H"c:/libs/dsl/ThirdParties" -B.

5a) To create a Debug version of the ThirdParties, type
MSBuild install.vcxproj

5b) To create a Release version, type:
MSBuild install.vcxproj /p:Configuration=Release


STEP B: Build the DSL library and examples
..............................................................................................................

1) Create an out of source folder for creating VS build files for DSL, e.g.
C:\vsbuilds\2013\dsl

2) Open a console and cd to the folder created in step 1). 

Create VS2013 build files by running cmake at the command line, e.g.:
> cmake -G"Visual Studio 12 2013" -DBOOST_ROOT=c:\libs\boost\boost_1_61_0 -DCMAKE_INSTALL_PREFIX=c:\vsbuild -H"c:\libs\dsl" -B.

To create x64 build, use the commandline:
> cmake -G"Visual Studio 12 2013 Win64" -DBOOST_ROOT=c:\libs\boost\boost_1_61_0 -DCMAKE_INSTALL_PREFIX=c:\vsbuild -H"c:\libs\dsl" -B.

3a) To create a Debug version of the library, type:
MSBuild install.vcxproj

3b) To create a Release version, type:
MSBuild install.vcxproj /p:Configuration=Release





Copyright Dune Scientific, LLC 1995-2015, M. T. Karlsson

