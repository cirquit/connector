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
    int init_receiver_udp(const int port) {
      // Bind socket to local Server Port
      _servAddr.sin_family = AF_INET;
      _servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
      _servAddr.sin_port = htons(port);
      // Create a UDP socket
      _skt = socket(AF_INET, SOCK_DGRAM, 0);
      _skt < 0 ? std::cout << "Could not open Socket " << _skt << '\n' : std::cout << "Socket: " << _skt << '\n';
      _bnd = bind(_skt, (struct sockaddr *) &_servAddr, sizeof(_servAddr));
      _bnd < 0 ? std::cout << "Could not bind ports " << _bnd << '\n' : std::cout << "Bind: " << _bnd << '\n';
      _len = sizeof(_cliAddr); // needed to store length of the IP-Adress
      return _skt;
    }
    

   // void receive_udp(T & out, unsigned buffer=2048) {
    void receive_udp(T & out, const int socket, unsigned buffer=2048) {
      std::cout << "Receiving...\n";
      // in `out` we store our received data
      int data = recvfrom(socket, &out, buffer, 0, (struct sockaddr *) &_cliAddr, &_len); 
      if(data > 0){
        std::cout << "Data received: " << data << " Socket: " << socket << '\n';
      } else {
        std::cout << "No Data received: " << data << " Socket: " << socket << '\n';
      }
    }

    
    // member
    public:

    // member
    private:
      struct sockaddr_in _servAddr;
      struct sockaddr_in _cliAddr;
      int _skt{0};
      int _bnd{0};  // Return value of binding function
      unsigned _len{0}; // Length of ipAdress
};
} // namespace connector
#endif // RECEIVER_H
