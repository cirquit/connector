
set(SOURCES client.h server.h util.h)

add_library(${CONN_LIB_NAME} ${SOURCES})
target_include_directories(${CONN_LIB_NAME} PUBLIC $<BUILD_INTERFACE:${CONNECTOR_SOURCE_DIR}/library> # for headers when building
                                              $<INSTALL_INTERFACE:${include_dest}> # for client in install mode
                                              )
target_link_libraries(${CONN_LIB_NAME} )
set_target_properties(${CONN_LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
#install(TARGETS ${CONN_LIB_NAME} DESTINATION "${main_lib_dest}")
install(FILES ${SOURCES} DESTINATION "${include_dest}")
install(TARGETS ${CONN_LIB_NAME} EXPORT ${CONN_LIB_NAME} DESTINATION "${main_lib_dest}")
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/config_impl.hpp DESTINATION "${include_dest}") # for binary installation
