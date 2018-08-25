cmake_minimum_required(VERSION 3.9)
project(gfm VERSION 1.0.0 DESCRIPTION "Typesafe Generic Flag Map")

include(GNUInstallDirs)

set(HEADER_FILES
  include/gfm/gfm.h
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pedantic -Wall -march=native")
set(VERSION "1.0")

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++17" HAVE_CPP17)
if (NOT HAVE_CPP17)
  message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER} has no C++17 support.")
endif()

foreach (i ${HEADER_FILES})
  install(FILES ${i} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/gfm)
endforeach()

# Examples
add_executable(example examples/example.cc)
target_include_directories(example PRIVATE include)

# Tests
option(BUILD_TESTS "Build tests" OFF)
if (BUILD_TESTS)
  enable_testing()
  find_package(Boost COMPONENTS unit_test_framework REQUIRED)
  include_directories (${Boost_INCLUDE_DIRS})
  add_executable(test_gfm test/test_gfm.cc)
  target_link_libraries(test_gfm ${Boost_LIBRARIES})
  target_include_directories(test_gfm PRIVATE include)
endif()
