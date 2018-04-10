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

set(SOURCES_RECEIVER catch.h main.cc receiver_tests.cc)
set(SOURCES_SENDER catch.h main.cc sender_tests.cc)
#set(SOURCESRECEIVER receiver.cc)
#set(SOURCESSENDER sender.cc)


add_executable(${TEST_NAME_RECEIVER} ${SOURCES_RECEIVER})
target_link_libraries(${TEST_NAME_RECEIVER} ${CONN_LIB_NAME})

add_executable(${TEST_NAME_SENDER} ${SOURCES_SENDER})
target_link_libraries(${TEST_NAME_SENDER} ${CONN_LIB_NAME})


