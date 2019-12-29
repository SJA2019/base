#! /bin/sh

echo "$0:begining.."

cd ../Source/TestApp/Build

echo "starting TestApp build.."

echo "make clean.."
make clean

echo "delete Build dir content.."
rm -rf ./*

echo "running-cmake.."
cmake ..

echo "running-make.."
make

cd -

echo "done TestApp build.."
echo "$0:completed.."
