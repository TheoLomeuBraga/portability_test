cmake_minimum_required(VERSION 3.16)
project(PortabilityTest)

#sdl
set(SDL_STATIC ON)
add_subdirectory(libs/SDL)

#test



include_directories(src libs/SDL/include)
SET(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++")





if (ANDROID)
    add_library(core src/main.cpp)   
    target_link_libraries(core SDL3::SDL3-static ${GLESv3_LIB} android log EGL GLESv2)
else()
    add_executable(test src/main.cpp)
    find_package(OpenGL REQUIRED)
    target_link_libraries(test SDL3::SDL3-static ${OPENGL_LIBRARIES})
endif()


if (WIN32)
    SET(CMAKE_CXX_FLAGS  "-mwindows")
endif (WIN32)

if (ANDROID)
    include_directories(src)
endif ()

if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX .html)
endif()
