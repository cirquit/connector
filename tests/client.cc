
// udp/tcp includes
#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <typeinfo>
#include <iostream>
#include <unistd.h>
// #include <string>
// #include "catch.h"

#include "../library/client.h"


int main() {


    const int port = 4444;
    //const std::string ip = "10.158.73.248";
    const std::string ip = "127.0.0.1";
    connector::client<connector::UDP> client(port, ip);
    client.init();

    std::string to_server = "PING";
    char buffer[255];
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
