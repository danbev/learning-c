cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(cmake-example VERSION 0.1)

add_library(something STATIC somelib/src/something.c somelib/include/something.h)
target_include_directories(something PUBLIC somelib/include)

add_executable(hello src/hello.c somelib/include/something.h)
target_link_libraries(hello something)

option(CUSTOM_OPTION "A custom option to be pased using -DCUSTOM_OPTION=" FALSE)

message(STATUS "summary of build options:

    Package version: ${CMAKE_PROJECT_VERSION}
    Install prefix:  ${CMAKE_INSTALL_PREFIX}
    Target system:   ${CMAKE_SYSTEM_NAME}
    CUSTOM_OPTION:   ${CUSTOM_OPTION}
    Compiler:
      C compiler:     ${CMAKE_C_COMPILER}
      CFLAGS:         ${CMAKE_C_FLAGS_${_build_type}} ${CMAKE_C_FLAGS}
")
