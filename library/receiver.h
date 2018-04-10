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
#include <arpa/inet.h>
#include <iostream>
#include <memory>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

/** \brief connector namespace, which is the wrapper fo the connector library
 *
 */
namespace connector {

  /** \brief A templated Receiver class with one template argument
   *
   * Template argument:
   * * `T` = Type of the object-to-receive
   *
   * See examples at [tests/receiver_tests.cc](../../tests/receiver_tests.cc)
   */
  template<typename T> // T = object-to-receive
    class receiver
    {

      // methods
      public:
        int init_receiver_tcp(const int port, const int client_count) {
          // creating socket
          _listen_socket = socket(AF_INET, SOCK_STREAM, 0);
          if(_listen_socket == -1){
#if DEBUG_MODE
            std::cout << "-- Error creating socket with -1\n";
#endif
            return 1;
          } else {
#if DEBUG_MODE
            std::cout << "-- Created socket!\n";
#endif
          }
          // binding port
          _servAddr.sin_family = AF_INET;
          _servAddr.sin_addr.s_addr = INADDR_ANY;
          _servAddr.sin_port = htons(port);
          _bnd = bind(_listen_socket,(struct sockaddr *) &_servAddr, sizeof(_servAddr));
          if(_bnd < 0){
#if DEBUG_MODE
            std::cout << "-- Error binding with error: " << _bnd << '\n';
#endif
            return 1;
          } else {
#if DEBUG_MODE
            std::cout << "-- Binding successful!\n";
#endif
          }
          listen(_listen_socket, client_count);
          _len = sizeof(struct sockaddr_in);
          _client_socket = accept(_listen_socket, (struct sockaddr *) &_cliAddr, (socklen_t*) &_len);
          if(_client_socket < 0){
#if DEBUG_MODE
            std::cout << "-- Connection accept failed with error: " << _client_socket << '\n';
#endif
            return 1;
          } else {
#if DEBUG_MODE
            std::cout << "-- Client connected!\n";
#endif
          }
          return _client_socket;
        }

        // connecting to socket, allowing a client to connect
        void receive_tcp(T & out, const int socket, size_t buffer=2048) {
          int read_size = recv(socket, &out, buffer, 0);
        }

        /**
         * This function initializes the parameters needed for establishing a **UDP** connection with the sender
         * 
         * It takes a port (`int`) as Argument and only needs to be called once
         *
         * Modifying:
         *    * `_cliAddr`
         *    * `_servAddr`
         *    * `_bnd`
         *    * `port`
         *
         * Return:
         *    * socket
         */
        int init_receiver_udp(const int port) {
          // Bind socket to local Server Port
          _servAddr.sin_family = AF_INET;
          _servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
          _servAddr.sin_port = htons(port);
          // Create a UDP socket
          _skt = socket(AF_INET, SOCK_DGRAM, 0);
#if DEBUG_MODE
          _skt < 0 ? std::cout << "Could not open Socket " << _skt << '\n' : std::cout << "Socket: " << _skt << '\n';
#endif // DEBUG_MODE
          _bnd = bind(_skt, (struct sockaddr *) &_servAddr, sizeof(_servAddr));
#if DEBUG_MODE
          _bnd < 0 ? std::cout << "Could not bind ports " << _bnd << '\n' : std::cout << "Bind: " << _bnd << '\n';
#endif // DEBUG_MODE
          _len = sizeof(_cliAddr); // needed to store length of the IP-Adress
          return _skt;
        }

        /** \brief Main UDP function to receive objects
         * 
         * The **out** parameter should be of the same **type** and **size** (`buffer`) as the object on the [sender](classconnector_1_1sender.html) side
         *
         * Modifying:
         *    * `out`
         */
        void receive_udp(T & out, const int socket, unsigned buffer=2048) {
#if DEBUG_MODE
          std::cout << "Receiving...\n";
#endif
          // in `out` we store our received data
          int data = recvfrom(socket, &out, buffer, 0, (struct sockaddr *) &_cliAddr, &_len); 
#if DEBUG_MODE
          if(data > 0){
            std::cout << "Data received: " << data << " Socket: " << socket << '\n';
          } else {
            std::cout << "No Data received: " << data << " Socket: " << socket << '\n';
          }
#endif
        }

        // member
      private:
        /** \brief A container to store sender information
         *
         * Members:
         *  * `short` sin_family
         *  * `unsigned short` sin_port
         *  * `struct` in_addr sin_addr
         *  * `char` sin_zero[0]
         *
         * Needed include: `<netinet/in.h>`
         */
        struct sockaddr_in _servAddr;
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
        /** \brief Return value of `bind()`
        */
        int _bnd{0}; 
        /** \brief Length of IP-Adress
        */
        unsigned _len{0}; // Length of ipAdress
        int _listen_socket, _client_socket;
    };
} // namespace connector
#endif // RECEIVER_H
