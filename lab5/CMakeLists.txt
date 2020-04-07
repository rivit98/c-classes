cmake_minimum_required(VERSION 3.8)
project(MyList4Students)

#common functions
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(common)
include(dima)

find_or_download_and_compile_gtest()

find_c_and_cpp_files("${CMAKE_CURRENT_SOURCE_DIR}/include" zadanie_includes)
find_c_and_cpp_files("${CMAKE_CURRENT_SOURCE_DIR}/src" zadanie_sources)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${zadanie_includes} ${zadanie_sources})

add_executable(MyList ${zadanie_includes} ${zadanie_sources})

target_include_directories(MyList PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(MyList PUBLIC gtest gtest_main pthread)

set_target_properties( MyList
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
set_target_properties(MyList PROPERTIES CXX_STANDARD 17)
set_target_properties(MyList PROPERTIES LINKER_LANGUAGE CXX)
