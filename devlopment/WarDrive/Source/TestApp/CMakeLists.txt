#set the cmake version.
cmake_minimum_required(VERSION 2.8.9)

#set the project name.
project(TestApp)

#build dependancies first.
add_subdirectory(../Thirdparty/SDL ./SDL)
add_subdirectory(../SubSystems/InputManager ./InputManager )
add_subdirectory(../SubSystems/Core ./Core )

#Specify the include folder.
include_directories(Src)
include_directories(../SubSystems/InputManager/Api)
include_directories(../SubSystems/Core/Api)

#create a SOURCES parameter, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "Src/*.cpp")

#generate executable from the sources
add_executable(TestAppExec ${SOURCES})
#target_link_libraries(TestAppExec SDL2main)
#-framework is apple specific.
SET(CMAKE_CXX_LINK_FLAGS "-framework OpenGL")
target_link_libraries(TestAppExec SDL2-static)
target_link_libraries(TestAppExec WarDriveLib)
target_link_libraries(TestAppExec InputManagerLib)

#add_custom_command(
#        TARGET TestAppExec POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#                Src/ColorFragmentShader.fragmentshader
#                ${CMAKE_CURRENT_BINARY_DIR}/ColorFragmentShader.fragmentshader)

#add_custom_command(
#        TARGET TestAppExec POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#                Src/TransformVertexShader.vertexshader
#                ${CMAKE_CURRENT_BINARY_DIR}/TransformVertexShader.vertexshader)
