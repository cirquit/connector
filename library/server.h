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

#ifndef SERVER_H
#define SERVER_H

// udp/tcp includes
#include <arpa/inet.h>
#include <iostream>
#include <memory>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "util.h"

/** \brief connector namespace, which is the wrapper fo the connector library
 *
 */
namespace connector {

/** \brief A templated server class with one template argument
 *
 * Template argument:
 * * `T` = Type of the object-to-receive
 *
 * See examples at [tests/server_tests.cc](../../tests/server_tests.cc)
 */
template < CONNECTOR_TYPE T >  // T = object-to-receive
class server {};

template <>
class server< TCP > {
        public:
    //! TCP constructor, client_count is default on 1
    server( const int port ) : _port( port ) {}
    //! TCP destructor, closing socket
    ~server(){
        close(_skt);
    }

    // methods
        public:
    int init( ) {
        // creating socket
        _listen_socket = socket( AF_INET, SOCK_STREAM, 0 );
        if ( _listen_socket == -1 ) {
            DEBUG_MSG( "Error creating socket with -1" );
            return -1;
        } else {
            DEBUG_MSG( "Created socket!" );
        }

        // binding port
        _ourAddr.sin_family      = AF_INET;
        _ourAddr.sin_addr.s_addr = INADDR_ANY;
        _ourAddr.sin_port        = htons( _port );
        _bnd = bind( _listen_socket, (struct sockaddr *)&_ourAddr, sizeof( _ourAddr ) );
        if ( _bnd < 0 ) {
            DEBUG_MSG( "Error binding with error: " << _bnd );
            return -1;
        } else {
            DEBUG_MSG( "Binding successful to port " << _port << "!" );
        }

        // waiting for _skt clients to connect (blocking)
        listen( _listen_socket, 1 );
        _len = sizeof( struct sockaddr_in );
        _skt = accept( _listen_socket, (struct sockaddr *)&_cliAddr, (socklen_t *)&_len );
        if ( _skt < 0 ) {
            DEBUG_MSG( "Connection accept failed with error: " << _skt );
            return -1;
        } else {
            DEBUG_MSG( "All clients ("
                       << "1"
                       << ") connected!" );
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
        send( _skt, static_cast< const void * >( &out ), sizeof( U ), 0 );
    }

    //! \todo
    template < class U >
    void send_tcp( U &out, const size_t buffer ) const {
        send( _skt, static_cast< const void * >( &out ), buffer, 0 );
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
    struct sockaddr_in _ourAddr;
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
    unsigned _len{0};  // Length of ipAdress
    int      _listen_socket;

    //! \todo
    int _port;
};

template <>
class server< UDP > {
    
    public:
    //! UDP constructor
    server( const int port ) : _port( port ) {}
    //! UDP destructor, closing socket
    ~server(){
        close(_skt);
    }
    // methods
    public:
    int init( ) {
        // bind socket to local server port
        _ourAddr.sin_family      = AF_INET;
        _ourAddr.sin_addr.s_addr = htonl( INADDR_ANY );
        _ourAddr.sin_port        = htons( _port );

        // create a UDP socket
        _skt = socket( AF_INET, SOCK_DGRAM, 0 );
        if ( _skt < 0 ) {
            DEBUG_MSG( "Connection accept failed with error: " << _skt );
            return -1;
        } else {
            DEBUG_MSG( "Some clients connected!" );
        }

        // binding socket
        _bnd = bind( _skt, (struct sockaddr *)&_ourAddr, sizeof( struct sockaddr_in ) );
        if ( _bnd < 0 ) {
            DEBUG_MSG( "Error binding with error: " << _bnd );
            return -1;
        } else {
            DEBUG_MSG( "Binding successful to port " << _port << "!" );
        }
        return _skt;
    }

    //! \todo
    template < class U >
    void receive_udp( U &out ) {
        recvfrom( _skt, static_cast< void * >( &out ), sizeof( U ), 0, (struct sockaddr *) &_cliAddr, &sockaddr_len);
    }

    //! \todo
    template < class U >
    void receive_udp( U &out, const size_t buffer ) {
        recvfrom( _skt, static_cast< void * >( &out ), buffer,  0, (struct sockaddr *) &_cliAddr, &sockaddr_len);
    }

    //! \todo
    template< class U >
    void send_udp(U & out) const {
        sendto(_skt, static_cast< const void * >( &out ), sizeof(U), 0, (struct sockaddr *) &_cliAddr, sockaddr_len);
    }

    //! \todo
    template< class U >
    void send_udp(U & out, const size_t buffer) const {
        sendto(_skt, static_cast< const void * >( &out ), buffer, 0, (struct sockaddr *) &_cliAddr, sockaddr_len);
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
    struct sockaddr_in _ourAddr;

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
    //! The socket to send data to the client from
    int _skt{0};
    //! Return value of `bind()`
    int _bnd{0};
    //! \todo
    int _port;
    socklen_t sockaddr_len { sizeof(struct sockaddr_in) };
};
}  // namespace connector
#endif  // SERVER_H
