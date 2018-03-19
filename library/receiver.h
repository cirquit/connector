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

#ifndef RECEIVER_H
#define RECEIVER_H

// udp includes
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <iostream>
#include <memory>

namespace connector {

template<typename T> // T = objectlist
class receiver
{
    // typenames
  public:
        

    // methods
  public:
    
    // Initialise UDP Socket Data - (the UDP receiving part is mostly written in C)
    void init_receiver_udp(const int port) {
      // Bind socket to local Server Port
      _servAddr.sin_family = AF_INET;
      _servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
      _servAddr.sin_port = htons(port);
      // Create a UDP socket
      _skt = socket(AF_INET, SOCK_DGRAM, 0);
      _bnd = bind(_skt, (struct sockaddr *) &_servAddr, sizeof(_servAddr));
      _len = sizeof(_cliAddr); // needed to store length of the IP-Adress
    }

    void receive_udp(T & out, unsigned buffer=2048) {
      std::cout << "Receiving...\n";
      // in `out` we store our received data
      int data = recvfrom(_skt, &out, buffer, 0, (struct sockaddr *) &_cliAddr, &_len); 
      if(data > 0){
        std::cout << "Data received: " << data << '\n';
      } else {
        std::cout << "No Data received: " << data << '\n';
      }
    }
    /*
    T receive_udp(unsigned buffer=2048) {
//      void receive_udp(T * received_obj, unsigned buffer=2048) {

      T received_obj;
      std::cout << "Receiving...\n";
      // in `received_obj` we store our received data
      int data = recvfrom(_skt, &received_obj, buffer, 0, (struct sockaddr *) &_cliAddr, &_len); 
      if(data > 0) std::cerr << "Data received: " << data << '\n';

      return received_obj;
    }
*/
        
    // member
    public:

    // member
    private:
      struct sockaddr_in _servAddr;
      struct sockaddr_in _cliAddr;
      int _skt{0};  // Socket to receive data at
      int _bnd{0};  // Return value of binding function
      unsigned _len{0}; // Length of ipAdress
};
} // namespace connector
#endif // RECEIVER_H
