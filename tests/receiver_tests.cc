// Copyright 2018 municHMotorsport e.V. <info@munichmotorsport.de>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// UDP includes
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <iostream>
#include <string>
#include "catch.h"

#include "../library/receiver.h"


TEST_CASE("Basic functionality of receiver", "[receiver]") {

    SECTION("Receiver") {

      typedef struct {
        double distance;
        double angle;
        double yaw;
      } object_t;

      object_t recv_obj;
      recv_obj.distance = 0;
      recv_obj.angle = 0;
      recv_obj.yaw = 0;
      
      unsigned port{4242};
      // creation of receiver object
      connector::receiver<object_t> rcvr{};
      int skt = rcvr.init_receiver_udp(port);

      rcvr.receive_udp(recv_obj, skt, sizeof(object_t));
      REQUIRE(recv_obj.distance == 42.3);
      REQUIRE(recv_obj.angle == 42.4);
      REQUIRE(recv_obj.yaw == 42.5);
      
    }
}
