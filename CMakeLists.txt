cmake_minimum_required(VERSION 3.5)
project( ParseTree VERSION 0.1.0 )

add_library(ParseTree STATIC src/ParseTree.c)

target_include_directories( ParseTree PUBLIC ${PROJECT_SOURCE_DIR}/include )
target_sources( ParseTree PRIVATE ${PROJECT_SOURCE_DIR}/src/ParseTree )
target_sources( ParseTree PUBLIC ${PROJECT_SOURCE_DIR}/include/ParseTree )

set_target_properties(ParseTree
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib"
	LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib"
	RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)

if(NOT TARGET LinkedList)
	add_subdirectory(${CMAKE_SOURCE_DIR}/ext/LinkedList ${CMAKE_SOURCE_DIR}/ext/LinkedList/build/bin)
endif(NOT TARGET LinkedList)
target_link_libraries(ParseTree LinkedList)

if(NOT TARGET Token)
	add_subdirectory(${CMAKE_SOURCE_DIR}/ext/Token ${CMAKE_SOURCE_DIR}/ext/Token/build/bin)
endif(NOT TARGET Token)
target_link_libraries(ParseTree Token)
