cmake_minimum_required(VERSION 3.8)
project(blatt_7_aufgabe_1_dasisteinteam)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES avlBaum/AvlBaum.cpp avlBaum/AvlBaum.h)
add_library(blatt_7_aufgabe_1_dasisteinteam ${SOURCE_FILES})