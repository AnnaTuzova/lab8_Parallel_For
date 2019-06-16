cmake_minimum_required(VERSION 2.8) 

project(Encoder_lib)				

set(SOURCE_LIB Encoder.cpp)	
set(HEADER_LIB Encoder.h)

set(ENCODER_LIB_DIR Encoder_lib)

add_library(Encoder_lib STATIC ${SOURCE_LIB} ${HEADER_LIB})

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")