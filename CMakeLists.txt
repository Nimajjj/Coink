cmake_minimum_required(VERSION 3.21)
project(Engine)

set(CMAKE_CXX_STANDARD 20)

set(SDL2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/SDL2)
set(SDL2_LIB_DIR ${CMAKE_SOURCE_DIR}/lib/SDL2)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})


file(GLOB_RECURSE SOURCES
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        )

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} mingw32 SDL2main SDL2 SDL2_image SDL2_ttf)
