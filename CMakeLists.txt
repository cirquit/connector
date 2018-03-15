set(PROJECT_NAME Connector)
set(LIB_NAME  connector)
#set(EXEC_NAME connector_exec)
set(TEST_NAME_RECEIVER receiver_test)
set(TEST_NAME_SENDER sender_test)

project (${PROJECT_NAME})
cmake_minimum_required (VERSION 3.5.1)

## this flag is used to set the compiler flags and should be used in the code
## with #if DEBUG_MODE <code> #else <code> #endif OR the debug print macro
OPTION(DEBUG_MODE "Enables the DEBUG messages and -O0 flags" 1)

# set compiler flags
set(CMAKE_CXX_COMPILER=g++)

## Compile as C++14
add_compile_options(-std=c++14)

# Compile differently if DEBUG_MODE is active
if(DEBUG_MODE)
    message("DEBUG_MODE is ON - no optimizations enabled")
    add_definitions(-DDEBUG_MODE=1)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -pthread -Wall -Wextra -Wfatal-errors -pedantic -g -fPIC")
else()
    message("DEBUG_MODE is OFF - O2 optimizations enabled")
    add_definitions(-DDEBUG_MODE=0)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -pthread -Wall -Wextra -Werror -Wfatal-errors -pedantic -fPIC")
endif()

# add the actual code
add_subdirectory (library)
#add_subdirectory (src)
add_subdirectory (tests)
