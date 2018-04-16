
// UDP includes
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <netdb.h>

#include <iostream>
// #include <memory>
#include <string>
#include <ctime>

#include "../library/server.h"


void timeit_(std::function<void()> f)
{
      std::clock_t start = std::clock();
      f();
      std::cout << "Elapsed time: " << 1.0 / ((std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC) * 1000)  << "kHz\n";
}

int main() {

    const int port = 4444; 
    connector::server<connector::TCP> server(port);
    server.init();

    
    std::string to_send = "PONG";
    char buffer[255];  
    while(true)
    {   
        timeit_([&](){
            server.receive_tcp<char>(buffer[0], 5 * sizeof(char));
        });

        //std::cout << "SERVER: Got from client - buffer = " << buffer << std::endl;
        server.send_tcp<const char>(to_send.c_str()[0], 5 * sizeof(char));
        
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
