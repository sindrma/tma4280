enable_language(C)
cmake_minimum_required(VERSION 2.6)
project(sum)

add_definitions(-std=c99 -lm)

link_libraries(-lm)

add_executable(sum sum.c sumlib.c)
