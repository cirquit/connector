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

//udp/tcp includes
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include <string>
#include <typeinfo>

#include "util.h"

/** \brief connector namespace, which is the wrapper fo the connector library
 *
 */
namespace connector {

    //! \todo
    enum CONNECTOR_TYPE : size_t
    { 
        TCP = 0, UDP = 1
    };
    /** \brief A templated Sender class with one template argument
     *
     * Template argument:
     * * `T` = Type of the object-to-send
     *
     * See examples at [tests/sender_tests.cc](../../tests/sender_tests.cc)
     */
    template<CONNECTOR_TYPE T> // T = object-to-send
        class sender 
        { };

    template<> 
        class sender<TCP>
        {

            public:
                //! TCP constructor, client_count is default on 1
                sender (const int port, const std::string ip, const int client_count = 1) 
                    : _port(port), 
                    _ip(ip),
                    _client_count(client_count)
            { }

                // methods
            public:
                /**
                 *! \todo 
                 * Modifying:
                 *    * `_cliAddr`
                 *    * `_skt`
                 *    * `_ip`
                 *    * `_port`
                 */
                int init() {
                    // creating socket
                    _listen_socket = socket(AF_INET, SOCK_STREAM, 0);
                    if(_listen_socket == -1)
                    {
                        DEBUG_MSG("Error creating socket with -1");
                        return -1;
                    } else
                    {
                        DEBUG_MSG("Created socket!");
                    }

                    // binding port
                    _servAddr.sin_family = AF_INET;
                    _servAddr.sin_addr.s_addr = INADDR_ANY;
                    _servAddr.sin_port = htons(_port);
                    _bnd = bind(_listen_socket,(struct sockaddr *) &_servAddr, sizeof(_servAddr));
                    if(_bnd < 0)
                    {
                        DEBUG_MSG("Error binding with error: " << _bnd);
                        return -1;
                    } else
                    {
                        DEBUG_MSG("Binding successful to port " << _port << "!");
                    }

                    // waiting for _skt clients to connect (blocking)
                    listen(_listen_socket, _client_count);
                    _len = sizeof(struct sockaddr_in);
                    _skt = accept(_listen_socket, (struct sockaddr *) &_cliAddr, (socklen_t*) &_len);
                    if(_skt < 0)
                    {
                        DEBUG_MSG("Connection accept failed with error: " << _skt);
                        return -1;
                    } else
                    {
                        DEBUG_MSG("All clients (" << _client_count << ") connected!");
                    }
                    return _skt;
                }

                //! \todo
                template<class U>
                    void send_tcp(U & out) const
                    {
                        send(_skt, &out, sizeof(U), 0);
                    }

                //! \todo
                template<class U>
                    void send_tcp(U & out, const size_t buffer) const
                    {
                        send(_skt, static_cast<void*>(&out), buffer, 0);
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

                /** \brief A container to store server information
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
                /** \brief The socket to send data to the client from
                */
                int _skt;
                int _port;
                int _bnd;
                std::string _ip;
                int _listen_socket;
                int _client_count;
                int _len;
        };


    //template<>
    //class sender<UDP>
    //{
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
    //    void init_sender_udp(const int port, const std::string ip) {
    //        _skt = socket(AF_INET, SOCK_DGRAM, 0);
    //        _cliAddr.sin_family = AF_INET;
    //        _cliAddr.sin_port = htons(port);
    //        inet_pton(AF_INET, ip.c_str(), &(_cliAddr.sin_addr));
    //    }
    //
    //    /** \brief Main UDP function to send objects
    //     * 
    //     * The `object_to_send` should be of the same type and size (`buffer`) as the object on the [receiving](classconnector_1_1receiver.html) side
    //     */
    //    void send_udp(T * object_to_send, size_t buffer=2048) {
    //
    //        sendto(_skt, object_to_send, buffer, 0, (struct sockaddr *) &_cliAddr, sizeof(sockaddr_in));
    //    }
    //
    //    // member
    //    private:
    //    /** \brief A container to store client information
    //     *
    //     * Members:
    //     *  * `short` sin_family
    //     *  * `unsigned short` sin_port
    //     *  * `struct` in_addr sin_addr
    //     *  * `char` sin_zero[0]
    //     *
    //     * Needed include: `<netinet/in.h>`
    //     */
    //    struct sockaddr_in _cliAddr;
    //    /** \brief The socket to send data to the client from
    //    */
    //    int _skt{0};
    //    int listen_socket{0};
    //};

} // namespace connector
#endif // SENDER_H
