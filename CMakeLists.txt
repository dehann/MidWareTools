cmake_minimum_required(VERSION 2.8.6) # for UseJava.cmake

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -Wreturn-type -Wuninitialized -Wunused-variable -std=c++0x")

project(midwaretools)


# pull in the pods macros. See cmake/pods.cmake for documentation
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(INCLUDE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/include)

set(MIDWARETOOLS_LIBRARIES ${INCLUDE_OUTPUT_PATH}/libMidWareTools.so)

add_subdirectory(src)

#install(FILES matlab/setup_datafusion.m DESTINATION matlab)
