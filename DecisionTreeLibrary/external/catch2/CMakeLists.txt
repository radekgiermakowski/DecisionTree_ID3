cmake_minimum_required(VERSION 3.10)

add_library(catch2 INTERFACE)
target_include_directories(catch2
        INTERFACE include
        )