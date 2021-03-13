
project (TopologyMap)

set(Qt5_DIR "C:/Qt/5.15.2/msvc2019_64/lib/cmake/Qt5")
#set(Qt5_DIR "D:/qt2/5.11.1/msvc2015/lib/cmake/Qt5")

set(CMAKE_CXX_CLANG_TIDY "cpplint")

include_directories(${CMAKE_SOURCE_DIR}/includes)
set (CMAKE_EXPORT_COMPILE_COMMANDS 1)
add_subdirectory(src)