cmake_minimum_required(VERSION 2.8) 

project(test)				

set(SOURCE_EXE test.cpp)			

add_executable(test ${SOURCE_EXE})	

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

target_link_libraries(test Encoder_lib)	
target_link_libraries(test gtest)