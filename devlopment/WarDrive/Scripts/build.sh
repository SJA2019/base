#! /bin/sh
echo "$0:begining.."

echo "$0:starting TestApp build.."
cd ../Source/TestApp/Build
cmake ..
cd -
echo "$0:done TestApp build.."

echo "$0:completed.."
