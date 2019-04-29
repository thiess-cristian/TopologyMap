cmake_minimum_required(VERSION 3.0.0)
project(Graph)

file(GLOB srcs "*.cpp" "*.h" "*.hpp")
file(GLOB includes
	"${CMAKE_SOURCE_DIR}/includes/${PROJECT_NAME}/*.h"
	"${CMAKE_SOURCE_DIR}/includes/${PROJECT_NAME}/*.hpp"
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

include_directories("${CMAKE_SOURCE_DIR}/bin")

add_library(${PROJECT_NAME} ${srcs} ${includes})

target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_SOURCE_DIR}/includes/${PROJECT_NAME}/
	${CMAKE_SOURCE_DIR}/includes/
)