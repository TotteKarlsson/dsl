#! /bin/bash
echo "Hello Bash"

echo "Arg1: "$1
echo "Arg2: "$2
echo "Arg3: "$3

OUTPUTDIR=`cygpath $1`
OUTPUTFILENAME=$2
BDSCOMMONDIR=$3

echo "OUTPUTDIR: "$OUTPUTDIR
echo "Outputfilename: "$OUTPUTFILENAME
echo "BDSCOMMONDIR: "$BDSCOMMONDIR

#Extract version
APPNAME=PluginManager
echo "Copy stuff"

pythonOut="$OUTPUTDIR/plugins"

if [ ! -d "$pythonOut" ]; then
    echo "Creating folder: "$pythonOut
    mkdir $pythonOut
fi

#LOCAL bin folder
#cp ./showTempHumidityPlugin.py      $pythonOut
cp ./getImageROI.py      $pythonOut
cp ./doPythonWork.py      $pythonOut

echo "Done"
