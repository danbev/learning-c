cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(cmake-example VERSION 0.1)

add_executable(hello src/hello.c)

message(STATUS "summary of build options:

    Package version: ${CMAKE_PROJECT_VERSION}
    Install prefix:  ${CMAKE_INSTALL_PREFIX}
    Target system:   ${CMAKE_SYSTEM_NAME}
    Compiler:
      C compiler:     ${CMAKE_C_COMPILER}
      CFLAGS:         ${CMAKE_C_FLAGS_${_build_type}} ${CMAKE_C_FLAGS}
")
