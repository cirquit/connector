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

/** \brief connector namespace, which is the wrapper fo the connector library
 *
 */
namespace connector {

/** \brief A templated Sender class with one template argument
 *
 * Template argument:
 * * `T` = Type of the object-to-send
 *
 * See examples at [tests/sender_tests.cc](../../tests/sender_tests.cc)
 */
template<typename T> // T = object-to-send
class sender {

    // methods
    public:
      /**
       * This function initializes the parameters needed for establishing a **UDP** connection with the receiver
       * It takes a port (`int`) and an IP Adress(`std::string`) as Arguments and
       * only needs to be called once
       *
       * Modifying:
       *    * `_cliAddr`
       *    * `_skt`
       *    * `port`
       *    * `ip`
       */
      void init_sender_udp(const int port, const std::string ip) {
        _skt = socket(AF_INET, SOCK_DGRAM, 0);
        _cliAddr.sin_family = AF_INET;
        _cliAddr.sin_port = htons(port);
        inet_pton(AF_INET, ip.c_str(), &(_cliAddr.sin_addr));
      }

      /** \brief Main UDP function to send objects
       * 
       * The `object_to_send` should be of the same type and size (`buffer`) as the object on the [receiving](classconnector_1_1receiver.html) side
       */
        void send_udp(T * object_to_send, unsigned buffer=2048) {

          sendto(_skt, object_to_send, buffer, 0, (struct sockaddr *) &_cliAddr, sizeof(sockaddr_in));
        }

    // member
    private:
        /** \brief A container to store client information
         *
         * Members:
         *  * `short` sin_family
         *  * `unsigned short` sin_port
         *  * `struct` in_addr sin_addr
         *  * `char` sin_zero[0]
         *
         * Needed include: `<netinet/in.h>`
         */
          struct sockaddr_in _cliAddr;
          /** \brief The socket to send data to the client from
           */
          int _skt{0};
};
} // namespace connector
#endif // SENDER_H
