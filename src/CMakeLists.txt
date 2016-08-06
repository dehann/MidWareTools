cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(Boost_USE_MULTITHREADED ON)
find_package(Boost REQUIRED COMPONENTS system thread)
include_directories(${Boost_INCLUDE_DIRS})

find_package(LCM REQUIRED)

link_directories(${LIBRARY_OUTPUT_PATH}) # lcmtypes library in general project output
include_directories(${LCM_INCLUDE_DIRS})
#set(MIDWARE_INCLUDE_DIR ${CMAKE_BINARY_DIR}/include/)


message("CMAKE_CURRENT_SOURCE_DIR/include = ${CMAKE_CURRENT_SOURCE_DIR}/include ")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


set(srcs
  ThreadLoop.cpp
  PracticalSocket.cpp
  )


add_library(MidWareToolslib SHARED ${srcs})
set_property(TARGET MidWareToolslib PROPERTY OUTPUT_NAME MidWareTools)
target_link_libraries(MidWareToolslib ${Boost_LIBRARIES} ${LCM_LIBRARIES})
#set_target_properties(MidWareTools PROPERTIES SOVERSION 0.1)

# install (TARGETS MidWareTools DESTINATION bin)
# install (FILES ${hdrs}
#          DESTINATION include)

#add_executable(test01 test.cpp)
#target_link_libraries(test01 MidWareTools)

# install library
install(TARGETS MidWareToolslib
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE 
              GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
#install(EXPORT MidWareTools-targets DESTINATION lib/MidWareTools)

#install header files
install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/include/MidWareTools/ 
        DESTINATION include/MidWareTools/
        FILES_MATCHING PATTERN "*.h")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/include/MidWareTools/ 
        DESTINATION include/MidWareTools/
        FILES_MATCHING PATTERN "*.hpp")

set(MIDWARETOOLS_LIBRARIES ${LIBRARY_OUTPUT_PATH}/libMidWareTools.so)