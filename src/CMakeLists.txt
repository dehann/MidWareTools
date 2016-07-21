cmake_minimum_required(VERSION 2.8 FATAL_ERROR)


set(Boost_USE_MULTITHREADED ON)
find_package(Boost REQUIRED COMPONENTS system thread)
include_directories(${Boost_INCLUDE_DIRS})

find_package(LCM REQUIRED)

link_directories(${LIBRARY_OUTPUT_PATH}) # lcmtypes library in general project output
include_directories(${LCM_INCLUDE_DIRS})
# include_directories(${CMAKE_BINARY_DIR}/include/)

include_directories(include)

set(srcs
  ThreadLoop.cpp
  )

# set(hdrs
#   ${PROJECT_BINARY_DIR}/includeMidWareTools/PracticalSocket.h
#   ${PROJECT_BINARY_DIR}/include/MidWareTools/CompTimeUtil.hpp
#   ${PROJECT_BINARY_DIR}/include/MidWareTools/MidWareTools.h
#   ${PROJECT_BINARY_DIR}/include/MidWareTools/ThreadLoop.h
#   ${PROJECT_BINARY_DIR}/include/MidWareTools/MessageQueueProducer.h
#   ${PROJECT_BINARY_DIR}/include/MidWareTools/LCMThread.h
#   ${PROJECT_BINARY_DIR}/include/MidWareTools/LCMSubscriber.h
#   ${PROJECT_BINARY_DIR}/include/MidWareTools/Macros.h
#   ${PROJECT_BINARY_DIR}/include/MidWareTools/QueueTypes.h
#   ${PROJECT_BINARY_DIR}/include/MidWareTools/SharedPtrMacros.h
#   ${PROJECT_BINARY_DIR}/include/MidWareTools/SynchronizedQueue.h
#   DESTINATION MidWareTools)

add_library(MidWareTools SHARED ${srcs})
target_link_libraries(MidWareTools ${Boost_LIBRARIES})
set_target_properties(MidWareTools PROPERTIES SOVERSION 0.1)

# install (TARGETS MidWareTools DESTINATION bin)
# install (FILES ${hdrs}
#          DESTINATION include)

#add_executable(test01 test.cpp)
#target_link_libraries(test01 MidWareTools)
