#set the cmake version.
cmake_minimum_required(VERSION 2.8.9)

#set the project name.
project(TestApp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#build dependancies first.
add_subdirectory(../Thirdparty/SDL ./SDL)
add_subdirectory(../Thirdparty/assimp ./assimp)
add_subdirectory(../SubSystems/InputManager ./InputManager )
add_subdirectory(../SubSystems/Core ./Core )
add_subdirectory(../SubSystems/Renderer ./Renderer )

#Specify the include folder.
include_directories(Src)
include_directories(../Thirdparty/GLM)
include_directories(../SubSystems/InputManager/Api)
include_directories(../SubSystems/Core/Api)
include_directories(../SubSystems/Renderer/Api)

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
target_link_libraries(TestAppExec RendererLib)
target_link_libraries(TestAppExec assimp)

add_custom_command(
        TARGET TestAppExec POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/Src/ColorFragmentShader.fragmentshader
                ${CMAKE_CURRENT_BINARY_DIR}/ColorFragmentShader.fragmentshader)

add_custom_command(
        TARGET TestAppExec POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/Src/TransformVertexShader.vertexshader
                ${CMAKE_CURRENT_BINARY_DIR}/TransformVertexShader.vertexshader)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/SR71 DESTINATION ${CMAKE_BINARY_DIR}/Assets)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/low-poly-vietnam-era-jeep DESTINATION ${CMAKE_BINARY_DIR}/Assets)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/metal-slug-rebel-tank-comic-style DESTINATION ${CMAKE_BINARY_DIR}/Assets)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/merkava-tank DESTINATION ${CMAKE_BINARY_DIR}/Assets)