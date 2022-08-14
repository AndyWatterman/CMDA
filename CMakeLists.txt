cmake_minimum_required(VERSION 3.5)

# Add modules
set(MODULES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
list(APPEND CMAKE_MODULE_PATH ${MODULES_PATH})
include(common)

# Set project options
project(CMDA VERSION 0.1.0 LANGUAGES CXX)
message(STATUS "${PROJECT_NAME} ${PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build to release
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose Release or Debug" FORCE)
endif()

#include(CTest)
#enable_testing()

# Download and unpack dependencies
# https://crascit.com/2015/07/25/cmake-gtest/

set(THIRD_PARTY_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/3rd")
set(THIRD_PARTY_BUILD_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/internal)

configure_file("cmake/CMakeLists.txt.in" "${THIRD_PARTY_BUILD_DIRECTORY}/CMakeLists.txt")

execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${THIRD_PARTY_BUILD_DIRECTORY}"
)
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${THIRD_PARTY_BUILD_DIRECTORY}"
)

# Compile dependencies
add_subdirectory("${THIRD_PARTY_BUILD_DIRECTORY}/spdlog/source"
                 "${THIRD_PARTY_BUILD_DIRECTORY}/spdlog/build"
)

# Disable build of Zydis's tools and examples
option(ZYDIS_BUILD_TOOLS "" OFF)
option(ZYDIS_BUILD_EXAMPLES "" OFF)

# build Zydis
add_subdirectory("${THIRD_PARTY_DIRECTORY}/zydis"
    "${THIRD_PARTY_BUILD_DIRECTORY}/zydis/build"
)

# Create library
add_library(CMDA_LIB
    STATIC
        src/cmda.cpp
        src/FileLoader.cpp
        src/CandidateManager.cpp
)

# Add include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${THIRD_PARTY_BUILD_DIRECTORY}/spdlog/source/include/
    ${THIRD_PARTY_BUILD_DIRECTORY}/LIEF/source/include/
    ${THIRD_PARTY_DIRECTORY}/zydis/include/
)

# Link libraries
target_link_directories(CMDA_LIB
    PUBLIC
        ${THIRD_PARTY_BUILD_DIRECTORY}/LIEF/source/lib/
)
target_link_libraries(CMDA_LIB
    PUBLIC LIEF
    PUBLIC Zydis
)

# Create executable
add_executable(CMDA main.cpp)

# Be sure executable depends on CMDA library
add_dependencies(CMDA CMDA_LIB)

# target_link_directories(CMDA
#     PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Link executable with CMDA library
target_link_libraries(CMDA
    PRIVATE
        CMDA_LIB
)

# #set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# #set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# #include(CPack)
