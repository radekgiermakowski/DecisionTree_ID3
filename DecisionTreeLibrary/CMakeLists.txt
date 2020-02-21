cmake_minimum_required(VERSION 3.10)
project(libDecisionTree VERSION 1.0.0 LANGUAGES CXX)

include ( CMakePackageConfigHelpers )
set(CMAKE_CXX_STANDARD 17)
set(TREE_CMAKE_CONFIG_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/DecisionTreeLibrary")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(decisiontree
        src/Attribute.cpp
        src/Node.cpp
        src/ReadFile.cpp
        src/Tree.cpp
        )
add_library(DecisionTreeLibrary::decisiontree ALIAS decisiontree)

target_include_directories(decisiontree
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

include(GNUInstallDirs)
install(TARGETS decisiontree
        EXPORT decisiontree-target
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )
set_target_properties(decisiontree PROPERTIES EXPORT_NAME DecisionTree)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT decisiontree-target
        FILE  DecisionTreeLibraryTarget.cmake
        NAMESPACE DecisionTreeLibrary::
        DESTINATION "${TREE_CMAKE_CONFIG_DESTINATION}/cmake/DecisionTreeLibrary")


write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/DecisionTreeLibraryConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
        ${CMAKE_CURRENT_LIST_DIR}/DecisionTreeLibraryConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/DecisionTreeLibraryConfig.cmake
        INSTALL_DESTINATION
        ${TREE_CMAKE_CONFIG_DESTINATION}
)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/DecisionTreeLibraryConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/DecisionTreeLibraryConfigVersion.cmake
        DESTINATION ${TREE_CMAKE_CONFIG_DESTINATION}
        )

export(EXPORT decisiontree-target FILE ${CMAKE_CURRENT_BINARY_DIR}/DecisionTreeLibraryTarget.cmake NAMESPACE DecisionTreeLibrary::)
export(PACKAGE DecisionTreeLibrary)

add_subdirectory(test)
add_subdirectory(external)
