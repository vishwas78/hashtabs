cmake_minimum_required(VERSION 3.8)
project(hashtab)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES robinhood_hashtab.cpp)
add_executable(hashtab ${SOURCE_FILES})