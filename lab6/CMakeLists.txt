cmake_minimum_required(VERSION 3.8)
project(MyString4Students)

#common functions
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(common)
include(dima)

find_or_download_and_compile_gtest()

find_c_and_cpp_files("${CMAKE_CURRENT_SOURCE_DIR}/include" zadanie_includes)
find_c_and_cpp_files("${CMAKE_CURRENT_SOURCE_DIR}/src" zadanie_sources)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${zadanie_includes} ${zadanie_sources})

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")
endif()

add_executable(zadanie ${zadanie_includes} ${zadanie_sources})

target_include_directories(zadanie PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(zadanie PUBLIC gtest gtest_main pthread)

set_target_properties( zadanie
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
set_target_properties(zadanie PROPERTIES CXX_STANDARD 17)
set_target_properties(zadanie PROPERTIES LINKER_LANGUAGE CXX)

#gtest_add_tests(MyString src/MyStringTests.cpp)
