#set the cmake version.
cmake_minimum_required(VERSION 2.8.9)

#set the project name.
project(WarDrive)

#Specify the include folder.
include_directories(Src)
include_directories(Api)
include_directories(../InputManager/Api)
include_directories(../Renderer/Api)
include_directories(../../Thirdparty/SDL/include)
include_directories(../../Thirdparty/GLM)
include_directories(../../Testapp/Build/assimp/include)
include_directories(../../Thirdparty/assimp/include)

#create a SOURCES parameter, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "Src/*.cpp")

#generate executable from the sources
add_library(WarDriveLib STATIC ${SOURCES})


