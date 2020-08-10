#! /bin/sh

usage="usage: ./build.sh [-h][-skip-cmake][-skip-clean][-debug]"

echo "begining stript:"
for arg in "$@"
do
  echo $arg
done
echo "..."

skip_clean=0
skip_cmake=0
build_mode="Release"

for arg in "$@"
do
    case $arg in
        -skip-cmake)
        skip_cmake=1
        ;;
        -skip-clean)
        skip_clean=1
        ;;
        -debug)
        build_mode="Debug"
        ;;
        -h)
        echo $usage
        exit 0
        ;;
    esac
done

## run CMAKE
#
if [ $skip_cmake -eq 0 ]
then
  rm -rf ../Source/TestApp/Build
  mkdir ../Source/TestApp/Build
  echo "running-cmake.."
  cd ../Source/TestApp/Build
  cmake -DCMAKE_BUILD_TYPE=$build_mode -DBUILD_SHARED_LIBS=false ..
  cd -
fi 

## build TestApp
#
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
