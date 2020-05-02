#! /bin/sh

echo "usage: ./build.sh [-skip-cmake]"

echo "$0,$1:begining.."

option1=$1
if test "$option1" != "-skip-cmake" 
then
  rm -rf ../Source/TestApp/Build
  mkdir ../Source/TestApp/Build
  echo "running-cmake.."
  cd ../Source/TestApp/Build
  cmake ..
  cd -
fi 


cd ../Source/TestApp/Build
echo "starting TestApp build.."


echo "running-make.."
make clean
make

cd -

echo "done TestApp build.."
echo "$0:completed.."
