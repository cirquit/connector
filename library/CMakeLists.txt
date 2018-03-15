
set(SOURCES sender.h receiver.h)

#find_package(LAPACK REQUIRED)
#link_directories(${LAPACK_LIBRARIES})
#include_directories(${LAPACK_INCLUDE_DIRS})

add_library(${LIB_NAME} ${SOURCES})
target_link_libraries(${LIB_NAME} )
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
