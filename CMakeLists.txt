cmake_minimum_required (VERSION 2.6)

project (TopologyMap)

set(Qt5_DIR "D:/qt-5.11/5.11.1/msvc2017_64/lib/cmake/Qt5")
#set(Qt5_DIR "D:/qt2/5.11.1/msvc2015/lib/cmake/Qt5")
include_directories(${CMAKE_SOURCE_DIR}/includes)

add_subdirectory(src)