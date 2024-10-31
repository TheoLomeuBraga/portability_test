cmake_minimum_required(VERSION 3.16)
project(PortabilityTest)

#sdl
set(SDL_STATIC ON)
add_subdirectory(libs/SDL)

#test



include_directories(src libs/SDL/include)
SET(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++")

add_executable(test src/main.cpp)
find_package(OpenGL REQUIRED)
target_link_libraries(test SDL3::SDL3-static ${OPENGL_LIBRARIES})


if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX .html)
endif()