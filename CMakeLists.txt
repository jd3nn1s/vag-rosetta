cmake_minimum_required(VERSION 2.6)
project (vag-rosetta)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(SOURCES vag-rosetta.h vag-rosetta.c)

add_library(vag-rosetta ${SOURCES})
