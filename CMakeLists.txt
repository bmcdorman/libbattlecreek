project(libbattlecreek)

cmake_minimum_required(VERSION 3.0)

file(GLOB BATTLECREEK_SOURCES src/*.cpp)

add_library(battlecreek SHARED ${BATTLECREEK_SOURCES})