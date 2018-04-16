// UDP includes
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <netdb.h>

#include <iostream>
// #include <string>
// #include "catch.h"

#include "../library/client.h"

int main() {


    const int port = 4444;
    const std::string ip = "10.158.73.248";
    connector::client<connector::TCP> client(port, ip);
    client.init();

    std::string to_server = "PING";
    char buffer[255];
    while(true)
    {   
        client.send_tcp<const char>(to_server.c_str()[0], 5 * sizeof(char));
//        std::cout << "CLIENT: Send -  = " << to_server << std::endl;
        client.receive_tcp<char>(buffer[0], 5 * sizeof(char));
        std::cout << "CLIENT: Got -  buffer = " << buffer << std::endl;
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
