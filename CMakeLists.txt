# Copyright 2018 municHMotorsport e.V. <info@munichmotorsport.de>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required (VERSION 3.5.1)

set(PROJECT_NAME Connector)
set(CONN_LIB_NAME  connector)
set(TEST_NAME_SERVER server_test)
set(TEST_NAME_CLIENT client_test)

project (${PROJECT_NAME})

# define library version 
# Note that the library version is set via FORCE. This prevents users changing the value in the CMakeCache.txt
set(CONNECTOR_VERSION_MAJOR 1 CACHE STRING "major version" FORCE)
set(CONNECTOR_VERSION_MINOR 0 CACHE STRING "minor version" FORCE)
set(CONNECTOR_VERSION ${CONNECTOR_VERSION_MAJOR}.${CONNECTOR_VERSION_MINOR} CACHE STRING "version" FORCE)

#set(bin_dest "bin")
set(include_dest "include/connector-${CONNECTOR_VERSION}")
set(main_lib_dest "lib/connector-${CONNECTOR_VERSION}")

install(FILES connector-config.cmake DESTINATION ${main_lib_dest})
# Sets the correct version number which find_package() will look for
configure_file(connector-config-version.cmake ${CMAKE_CURRENT_BINARY_DIR}/connector-config-version.cmake @ONLY)
install(FILES connector-config.cmake ${CMAKE_CURRENT_BINARY_DIR}/connector-config-version.cmake DESTINATION ${main_lib_dest})
install(EXPORT ${CONN_LIB_NAME} DESTINATION "${main_lib_dest}")

## this flag is used to set the compiler flags and should be used in the code
## with #if DEBUG_MODE <code> #else <code> #endif OR the debug print macro
OPTION(DEBUG_MODE "Enables the DEBUG messages and -O0 flags" 1)

# set compiler flags
set(CMAKE_CXX_COMPILER=g++)

## Compile as C++14
add_compile_options(-std=c++14)

# Compile differently if DEBUG_MODE is active
if(DEBUG_MODE)
  message("DEBUG_MODE is ON - no optimizations enabled, console output ENABLED")
    add_definitions(-DDEBUG_MODE=1)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -pthread -Wall -Wextra -Wfatal-errors -pedantic -g -fPIC")
else()
    message("DEBUG_MODE is OFF - O2 optimizations enabled, no console output")
    add_definitions(-DDEBUG_MODE=0)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -pthread -Wall -Wextra -Werror -Wfatal-errors -pedantic -fPIC")
endif()

# add the actual code
add_subdirectory (library)
add_subdirectory (tests)
