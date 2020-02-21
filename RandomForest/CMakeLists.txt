cmake_minimum_required(VERSION 3.10)
project(forest)

configure_file(agaricus-lepiota.data agaricus-lepiota.data COPYONLY)
configure_file(testFile.data testFile.data COPYONLY)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.60.0 REQUIRED COMPONENTS thread system)
find_package(DecisionTreeLibrary 1.0.0 REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(forest randomForest.cpp main.cpp threadPool.cpp)
    set_target_properties(forest PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
            )
    target_link_libraries(forest DecisionTreeLibrary::DecisionTree ${Boost_LIBRARIES})
endif()



