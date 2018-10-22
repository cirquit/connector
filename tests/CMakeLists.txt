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

set(SOURCES_SERVER server.cc)
set(SOURCES_CLIENT client.cc)


add_executable(${TEST_NAME_SERVER} ${SOURCES_SERVER})
target_link_libraries(${TEST_NAME_SERVER} ${CPP_LIB_NAME})

add_executable(${TEST_NAME_CLIENT} ${SOURCES_CLIENT})
target_link_libraries(${TEST_NAME_CLIENT} ${CPP_LIB_NAME})


