#set the cmake version.
cmake_minimum_required(VERSION 2.8.9)

#set the project name.
project(InputManager)

#Specify the include folder.
include_directories(
Src
Api
../../Thirdparty/SDL/include
)

#create a SOURCES parameter, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "Src/*.cpp")

#generate executable from the sources
add_library(InputManagerLib STATIC ${SOURCES})


