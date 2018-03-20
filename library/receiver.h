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
      _skt < 0 ? std::cout << "Could not open Socket " << _skt << '\n' : std::cout << "Socket: " << _skt << '\n';
      _bnd = bind(_skt, (struct sockaddr *) &_servAddr, sizeof(_servAddr));
      _bnd < 0 ? std::cout << "Could not bind ports " << _bnd << '\n' : std::cout << "Bind: " << _bnd << '\n';
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
};
} // namespace connector
#endif // RECEIVER_H
