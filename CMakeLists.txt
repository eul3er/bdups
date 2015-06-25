cmake_minimum_required(VERSION 2.6)
project(bdups)
set (bdups_VERSION_MAJOR 0)
set (bdups_VERSION_MINOR 1)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # require at least gcc 4.9
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9)
        message(FATAL_ERROR "GCC version must be at least 4.9!")
    endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # require at least clang 3.4
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.4)
        message(FATAL_ERROR "Clang version must be at least 3.4!")
    endif()
else()
    message(WARNING "You are using an unsupported compiler! Compilation 
has only been tested with Clang and GCC.")
endif()

find_package(Boost 1.55 COMPONENTS filesystem system REQUIRED)
FIND_LIBRARY(CRYPTOPP cryptopp /usr/lib)

file(GLOB_RECURSE src_SOURCES "src/*.cpp")
file(GLOB_RECURSE src_HEADERS "src/*.h")

set (src_INCLUDE_DIRS "")
foreach (_headerFile ${src_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND src_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES src_INCLUDE_DIRS)

include_directories(${src_INCLUDE_DIRS})
add_executable(bdups ${src_SOURCES})

target_link_libraries(bdups boost_filesystem boost_system cryptopp pthread)
set_property(TARGET bdups PROPERTY CXX_STANDARD 14)
