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

#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include "catch.h"

#include "../library/sender.h"


TEST_CASE("Basic functionality of sender", "[sender]") {

    SECTION("Sender ") {
      
      struct object_t {
        double distance;
        double angle;
        double yaw;

        object_t(double p_distance, double p_angle, double p_yaw)
          : distance(p_distance), angle(p_angle), yaw(p_yaw){};
      };
      

      object_t ob{42.3, 52.4, 62.5};
//      double blub = {2.0};
      unsigned port{4242};
//      std::string ip {"127.0.0.1"};
      std::string ip {"10.158.76.57"};

      // creation of sender object
      connector::sender<object_t> sndr{};
      sndr.init_sender_udp(port, ip);
 //     for(int i{0}; i < 1; ++i) {
      while(true) {
 //       auto start = std::chrono::system_clock::now();
        sndr.send_udp(&ob, sizeof(object_t));
//        ++blub;
//        auto end = std::chrono::system_clock::now();
//        std::chrono::duration<double> elapsed_seconds = end - start;
//        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds).count () << '\n';
      }
      std::cout << "Finished sending\n";
      REQUIRE(true);
    }
}
