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

# set(SOURCES_SERVER catch.h main.cc server_tests.cc)
# set(SOURCES_CLIENT catch.h main.cc client_tests.cc)

set(SOURCES_SERVER_UDP server_udp.cc shared_structure.h)
set(SOURCES_CLIENT_UDP client_udp.cc shared_structure.h)

set(SOURCES_SERVER_TCP server_tcp.cc shared_structure.h)
set(SOURCES_CLIENT_TCP client_tcp.cc shared_structure.h)

set(SOURCES_PONGER ponger.cc)
set(SOURCES_PINGER pinger.cc)

add_executable(${TEST_NAME_SERVER_UDP} ${SOURCES_SERVER_UDP})
target_link_libraries(${TEST_NAME_SERVER_UDP} ${CPP_LIB_NAME})

add_executable(${TEST_NAME_CLIENT_UDP} ${SOURCES_CLIENT_UDP})
target_link_libraries(${TEST_NAME_CLIENT_UDP} ${CPP_LIB_NAME})

add_executable(${TEST_NAME_SERVER_TCP} ${SOURCES_SERVER_TCP})
target_link_libraries(${TEST_NAME_SERVER_TCP} ${CPP_LIB_NAME})

add_executable(${TEST_NAME_CLIENT_TCP} ${SOURCES_CLIENT_TCP})
target_link_libraries(${TEST_NAME_CLIENT_TCP} ${CPP_LIB_NAME})

add_executable(${TEST_NAME_PONGER} ${SOURCES_PONGER})
target_link_libraries(${TEST_NAME_PONGER} ${CPP_LIB_NAME})

add_executable(${TEST_NAME_PINGER} ${SOURCES_PINGER})
target_link_libraries(${TEST_NAME_PINGER} ${CPP_LIB_NAME})

