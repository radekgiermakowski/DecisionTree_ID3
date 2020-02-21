cmake_minimum_required(VERSION 3.10)
project(test)

set(PATH_TO_INCLUDE "${CMAKE_SOURCE_DIR}/include/")

configure_file(testFiles/attrTest.txt attrTest.txt COPYONLY)
configure_file(testFiles/entropyTest.txt entropyTest.txt COPYONLY)
configure_file(testFiles/testVector.txt testVector.txt COPYONLY)

add_executable(test unit/TestFunc.h unit/Test.cpp)

target_include_directories(test
        PRIVATE .
        )

target_link_libraries(test
        PRIVATE decisiontree)

