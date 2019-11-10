DSL 
============================================

Build instructions using CMake from the command line.

We are assuming that the DSL sources are in a folder: c:\libs\dsl

Visual Studio 2013
------------------

The build sequence is to build and install the DSL library, Third party libraries, and examples

Build the DSL library, Third Party libs (Poco, sqlite3, tinyxml, TClap) and examples
..............................................................................................................

1) Download Boost 1.61 from https://www.boost.org/users/history/version_1_61_0.html
and unpack to a suitable folder, e.g. c:\boost

2) Create an out of source folder for creating VS build files for DSL, e.g.
C:\vsbuilds\2013\dsl

3) Open a console and cd to the folder created in step 2). 

Create VS2013 build files by running cmake at the command line, e.g.:
> cmake -G"Visual Studio 12 2013" -DBOOST_ROOT=c:\libs\boost\boost_1_61_0 -DBOOST_ROOT_LIB=\boost\boost_1_61_0\stage\x32\lib  -DCMAKE_INSTALL_PREFIX=c:\vsbuild -S"c:\libs\dsl" -B.

To create x64 build, use the commandline:
> cmake -G"Visual Studio 12 2013 Win64" -DBOOST_ROOT=c:\libs\boost\boost_1_61_0 -DBOOST_ROOT_LIB=\boost\boost_1_61_0\stage\x64\lib -DCMAKE_INSTALL_PREFIX=c:\vsbuild -S"c:\libs\dsl" -B.

4a) To create a Debug version of the library, type:
MSBuild install.vcxproj

4b) To create a Release version, type:
MSBuild install.vcxproj /p:Configuration=Release





Copyright Dune Scientific, LLC 1995-2015, M. T. Karlsson

