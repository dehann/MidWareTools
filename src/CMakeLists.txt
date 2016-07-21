cmake_minimum_required(VERSION 2.8 FATAL_ERROR)


set(Boost_USE_MULTITHREADED ON)
find_package(Boost REQUIRED COMPONENTS system thread)
include_directories(${Boost_INCLUDE_DIRS})

find_package(LCM REQUIRED)

link_directories(${LIBRARY_OUTPUT_PATH}) # lcmtypes library in general project output
include_directories(${LCM_INCLUDE_DIRS})
include_directories(${CMAKE_BINARY_DIR}/include/)

set(srcs
  ThreadLoop.cpp
  )

add_library(midwaretools SHARED ${srcs})
target_link_libraries(midwaretools ${Boost_LIBRARIES})
set_target_properties(midwaretools PROPERTIES SOVERSION 1)


#add_executable(test01 test.cpp)
#target_link_libraries(test01 MidWareTools)

# pods_install_headers(
#   include/midwaretools/PracticalSocket.h
#   include/midwaretools/CompTimeUtil.hpp
#   include/midwaretools/MidWareTools.h
#   include/midwaretools/ThreadLoop.h
#   include/midwaretools/MessageQueueProducer.h
#   include/midwaretools/LCMThread.h
#   include/midwaretools/LCMSubscriber.h
#   include/midwaretools/Macros.h
#   include/midwaretools/QueueTypes.h
#   include/midwaretools/SharedPtrMacros.h
#   include/midwaretools/SynchronizedQueue.h
#   DESTINATION midwaretools)
