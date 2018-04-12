
set(SOURCES sender.h receiver.h util.h)

#find_package(LAPACK REQUIRED)
#link_directories(${LAPACK_LIBRARIES})
#include_directories(${LAPACK_INCLUDE_DIRS})

add_library(${CONN_LIB_NAME} ${SOURCES})
target_link_libraries(${CONN_LIB_NAME} )
set_target_properties(${CONN_LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
