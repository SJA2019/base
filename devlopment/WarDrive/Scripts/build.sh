#! /bin/sh

echo "usage: ./build.sh [-skip-cmake] [-skip-clean]"

echo "$0,$1:begining.."

skip_clean=0
skip_cmake=0


for arg in "$@"
do
    case $arg in
        -skip-cmake)
        skip_cmake=1
        ;;
        -skip-clean)
        skip_clean=1
        ;;
    esac
done

if [ $skip_cmake -eq 0 ]
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

if [ $skip_clean -eq 0 ]
then
echo "running make-clean.."
make clean
fi
echo "running-make.."
make

cd -

echo "done TestApp build.."
echo "$0:completed.."
