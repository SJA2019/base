#set the cmake version.
cmake_minimum_required(VERSION 2.8.9)

#set the project name.
project(InputManager)

#set the build mode : TBD make this configurable.
set(CMAKE_BUILD_TYPE Release)

#Specify the include folder.
include_directories(Src Api)

#create a SOURCES parameter, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "Src/*.cpp")

#generate executable from the sources
add_library(InputManagerLib STATIC ${SOURCES})


