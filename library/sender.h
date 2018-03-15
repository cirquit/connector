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

#ifndef SENDER_H
#define SENDER_H

// udp includes
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include <string>
#include <typeinfo>

namespace connector {

template<typename T> // T = objectlist
class sender {

    // typenames
    public:
        
    // constructors
    public:
//        Sender() = default;

    // methods
    public:
 //       void send_ros(const T & t);
      void init_sender_udp(const int port, const std::string ip) {
        _skt = socket(AF_INET, SOCK_DGRAM, 0);
        _cliAddr.sin_family = AF_INET;
        _cliAddr.sin_port = htons(port);
        inet_pton(AF_INET, ip.c_str(), &(_cliAddr.sin_addr));
      }

        void send_udp(T * object_to_send, unsigned buffer=2048) {

          sendto(_skt, object_to_send, buffer, 0, (struct sockaddr *) &_cliAddr, sizeof(sockaddr_in));
        }
/*
        const void close_udp_socket() const {
          close(_skt);
        }
        */

    // member
    public:

    // member
    private:
          struct sockaddr_in _cliAddr;
          int _skt{0};
};
} // namespace connector
#endif // SENDER_H
