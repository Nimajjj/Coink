cmake_minimum_required(VERSION 3.21)
project(CoinkEngine)

set(CMAKE_CXX_STANDARD 20)

set(SDL2_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/SDL2)
set(SDL2_LIB_DIR ${CMAKE_SOURCE_DIR}/lib/SDL2)
include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

set(COINK_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/Coink)
include_directories(${COINK_INCLUDE_DIR})


file(GLOB_RECURSE SOURCES_ENGINE ${PROJECT_SOURCE_DIR}/src/engine/*.cpp)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/appicon.rc")

#add_library(${PROJECT_NAME} ${SOURCES_ENGINE})
add_executable(${PROJECT_NAME} ${SOURCES} ${APP_ICON_RESOURCE_WINDOWS})

target_link_libraries(${PROJECT_NAME} mingw32 SDL2main SDL2 SDL2_image SDL2_ttf)
