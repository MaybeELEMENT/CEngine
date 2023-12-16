cmake_minimum_required(VERSION 3.12)
project(2DEngine)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(2DEngine main.cc 
               Engine/Engine.cc Engine/Object.cc Engine/RoundObject.cc Engine/SquareObject.cc Engine/Camera.cc Engine/Input.cc)
if (WIN32)
target_link_libraries(2DEngine 
                        ${CMAKE_SOURCE_DIR}/lib/windows/box2d.lib 
                        ${CMAKE_SOURCE_DIR}/lib/windows/glfw.lib 
                        ${CMAKE_SOURCE_DIR}/lib/windows/glad.lib 
                        ${CMAKE_SOURCE_DIR}/lib/windows/imgui.lib)
endif()
if (APPLE)
target_link_libraries(2DEngine 
                        ${CMAKE_SOURCE_DIR}/lib/macos/libbox2d.a 
                        ${CMAKE_SOURCE_DIR}/lib/macos/libglfw.a 
                        ${CMAKE_SOURCE_DIR}/lib/macos/libglad.a 
                        ${CMAKE_SOURCE_DIR}/lib/macos/libimgui.a
                        "-framework Cocoa"
                        "-framework OpenGL"
                        "-framework IOKit"
                        "-framework CoreVideo")
endif()