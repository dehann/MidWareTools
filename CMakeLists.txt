cmake_minimum_required(VERSION 2.8.6) # for UseJava.cmake

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -Wreturn-type -Wuninitialized -Wunused-variable -std=c++0x")

project(MidWareTools)


# pull in the pods macros. See cmake/pods.cmake for documentation
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE PATH
#    "Target directory for all executables")
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib CACHE PATH
    "Target directory for library")
set(INCLUDE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/include CACHE PATH
    "Target for all headers of library")

set(MIDWARETOOLS_LIBRARIES ${LIBRARY_OUTPUT_PATH}/libMidWareTools.so
    CACHE FILEPATH "Path to MidWareTools library")
#     PARENT_SCOPE)


message("MIDWARES PROJECT_SOURCE_DIR/include = ${PROJECT_SOURCE_DIR}/include")

add_subdirectory(src)

