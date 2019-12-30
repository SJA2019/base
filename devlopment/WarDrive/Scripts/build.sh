#! /bin/sh

echo "$0:begining.."

rm -rf ../Source/TestApp/Build
mkdir ../Source/TestApp/Build

cd ../Source/TestApp/Build

echo "starting TestApp build.."

echo "running-cmake.."
cmake ..

echo "running-make.."
make clean
make

cd -

echo "done TestApp build.."
echo "$0:completed.."
