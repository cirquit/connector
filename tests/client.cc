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


#include <unistd.h>

#include "../library/client.h"


int main() {


    const int port = 4444;
//    const std::string ip = "10.158.73.248"; //alex
//    const std::string ip = "127.0.0.1";
    const std::string ip = "10.158.76.57";
    connector::client<connector::UDP> client(port, ip);
    client.init();

    std::string to_server = "PING";
//    char buffer[255];
    uint32_t x = 5;
    //uint8_t * x = (uint8_t*)malloc(sizeof(uint8_t) * 10);
    while(true)
    {   
//        client.send_udp<const char>(to_server.c_str()[0], 5 * sizeof(char));
//        std::cout << "CLIENT: Send -  = " << to_server << std::endl;
//        client.receive_udp<char>(buffer[0], 5 * sizeof(char));
        //client.receive_udp<uint32_t>(x, sizeof(uint32_t));
        client.send_udp<uint32_t>(x, sizeof(uint32_t));
//        std::cout << "CLIENT: Got -  buffer = " << buffer << std::endl;
        std::cout << "CLIENT: Sending x = " << x << std::endl;
        sleep(2);
    }



}


//   struct object_t {
//     double distance;
//     double angle;
//     double yaw;

//     object_t(double p_distance, double p_angle, double p_yaw)
//       : distance(p_distance), angle(p_angle), yaw(p_yaw){};
//   };

//   std::vector<object_t> objectlist;
//   //objectlist.reserve(10);
//   for(unsigned i{0}; i != 10; ++i) {
//     objectlist.emplace_back(3.54 + i, 6.32 - i, 62.5 * i);
//   }

//   for(const auto & el : objectlist) {
//     std::cout << "Object: \n" << el.distance << '\t' 
//       << el.angle << '\t' << el.yaw << '\n';
//   }

//   unsigned port{4242};
//   std::string ip {"127.0.0.1"};
//   // creation of sender object
//   connector::sender<object_t> sndr{};
//   sndr.init_sender_udp(port, ip);
//   for(unsigned i{0}; i < objectlist.size(); ++i) {

//       sndr.send_udp(&objectlist.at(i));
//   }
//   sndr.close_socket_udp();
//   std::cout << "Finished Sending\n";
//   return 0;
// }
