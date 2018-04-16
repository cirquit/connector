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

#ifndef CLIENT_H
#define CLIENT_H

// udp/tcp includes
#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <typeinfo>

#include <errno.h>
#include "util.h"

/** \brief connector namespace, which is the wrapper fo the connector library
 *
 */
namespace connector {

//! \todo
enum CONNECTOR_TYPE : size_t { TCP = 0, UDP = 1 };
/** \brief A templated CLIENT class with one template argument
 *
 * Template argument:
 * * `T` = Type of the object-to-send
 *
 * See examples at [tests/CLIENT_tests.cc](../../tests/CLIENT_tests.cc)
 */
template < CONNECTOR_TYPE T >  // T = object-to-send
class client {};

template <>
class client< TCP > {

        public:
    //! TCP constructor, client_count is default on 1
    client( const int port, const std::string ip)
        : _port( port ), _ip( ip ) {}

    // methods
        public:
    /**
     *! \todo
     * Modifying:
     *    * `_servAddr`
     *    * `_skt`
     *    * `_ip`
     *    * `_port`
     */
    int init( ) {
        // creating socket
        _skt = socket(AF_INET, SOCK_STREAM, 0);
        if ( _skt == -1 ) {
            DEBUG_MSG( "Error creating socket with -1" );
            return -1;
        } else {
            DEBUG_MSG( "Created socket!" );
        }
        // connecting to server
        inet_pton(AF_INET, _ip.c_str(), &(_servAddr.sin_addr));
        _servAddr.sin_family      = AF_INET;
        _servAddr.sin_port        = htons( _port );
        if ( connect(_skt, (sockaddr *)&_servAddr, sizeof(struct sockaddr_in)) == -1 ) {
            DEBUG_MSG( "Error binding with error: " << hstrerror(errno) );
            return -1;
        } else {
            DEBUG_MSG( "Binding successful to port " << _port << "!" );
        }
        return _skt;
    }


    //! \todo
    template < class U >
    void receive_tcp( U &out ) const {
        recv( _skt, static_cast< void * >( &out ), sizeof( U ), 0 );
    }

    //! \todo
    template < class U >
    void receive_tcp( U &out, const size_t buffer ) const {
        recv( _skt, static_cast< void * >( &out ), buffer, 0 );
    }

    //! \todo
    template < class U >
    void send_tcp( U &out ) const {
        send( _skt, &out, sizeof( U ), 0 );
    }

    //! \todo
    template < class U >
    void send_tcp( U &out, const size_t buffer ) const {
        send( _skt, static_cast< void * >( &out ), buffer, 0 );
    }

    // member
        private:
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
    int         _skt;
    int         _port;
    std::string _ip;
};

// template<>
// class CLIENT<UDP>
//{
/**
 * This function initializes the parameters needed for establishing a **UDP** connection with the
 * receiver
 * It takes a port (`int`) and an IP Adress(`std::string`) as Arguments and
 * only needs to be called once
 *
 * Modifying:
 *    * `_cliAddr`
 *    * `_skt`
 *    * `port`
 *    * `ip`
 */
//    void init_CLIENT_udp(const int port, const std::string ip) {
//        _skt = socket(AF_INET, SOCK_DGRAM, 0);
//        _cliAddr.sin_family = AF_INET;
//        _cliAddr.sin_port = htons(port);
//        inet_pton(AF_INET, ip.c_str(), &(_cliAddr.sin_addr));
//    }
//
//    /** \brief Main UDP function to send objects
//     *
//     * The `object_to_send` should be of the same type and size (`buffer`) as the object on the
//     [receiving](classconnector_1_1receiver.html) side
//     */
//    void send_udp(T * object_to_send, size_t buffer=2048) {
//
//        sendto(_skt, object_to_send, buffer, 0, (struct sockaddr *) &_cliAddr,
//        sizeof(sockaddr_in));
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
//    int listen_skt{0};
//};

}  // namespace connector
#endif  // CLIENT_H
