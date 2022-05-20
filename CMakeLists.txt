cmake_minimum_required(VERSION 3.14)
project(suisei)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSION off)

# Boost Coroutine
include(cmake/findBoost.cmake)

add_executable(main src/main.cc)

add_executable(coroutine src/coroutine.cc)
target_link_libraries(coroutine 
    ${CMAKE_DL_LIBS} 
    ${Boost_LIBRARIES})