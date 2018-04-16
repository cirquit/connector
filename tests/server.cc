
// UDP includes
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <netdb.h>

#include <iostream>
// #include <memory>
// #include <string>

#include "../library/server.h"


int main() {

    const int port = 4444; 
    connector::server<connector::TCP> server(port);
    server.init();

    double x = 0;
    while(true)
    {   
        server.receive_tcp<double>(x);
        std::cout << "SERVER: Got - x = " << x << std::endl;
        server.send_tcp<double>(++x);
        std::cout << "SERVER: Send - x = " << x << std::endl;
    }
}
  // typedef struct {
  //   double distance;
  //   double angle;
  //   double yaw;
  // } object_t;

  // object_t object;
  // //std::vector<object_t> objlist;
  // //objlist.reserve(100);
  // unsigned port{4242};
  // // creation of receiver object
  // connector::receiver<object_t> rcvr{};
  // rcvr.init_receiver_udp(port);
  // while(true) {

  //   rcvr.receive_udp(object);
  //   std::cout << "Object received: \n" 
  //     << object.distance << '\t' << object.angle << '\t' << object.yaw << '\n';

  //   //decltype(received)::foo=1;
  // }

  //return 0;
