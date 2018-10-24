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

#include <cstring> // std::memset
#include <vector>

#include "../library/server.h"
#include "../library/autogen-CONNECTOR-macros.h"
#include "shared_structure.h"

/** "Generic" receive_vector with the connector library. T has to be default initializable and streamable because of debugging
  * IMPORTANT - never copy the connector::server/client by value, else the destructor gets called and we lose the ability to communicate
  */
template < class T >
void receive_vector(connector::server< connector::TCP > & server, std::vector< T > & vec)
{   
    // remove all elements from the vector
    vec.clear();
    // preallocate the size "member"
    uint32_t current_vec_size = 0;
    server.receive_tcp< uint32_t >( current_vec_size );
    DEBUG_MSG_CONNECTOR("Got current vec_size: " << current_vec_size << '\n');
    // preallocate space
    vec.reserve(current_vec_size);
    DEBUG_MSG_CONNECTOR("Receiving vector:\n");
    T element_memory;
    for ( uint32_t i = 0; i < current_vec_size; ++i )
    {
        server.receive_tcp< T >( element_memory );
        vec.emplace_back(element_memory);
        DEBUG_MSG_CONNECTOR("    - " << element_memory << '\n');
    }
}

int main()
{
    // the server is defined through a port only
    const int port = 4444;
    // call the server with it's constructor and the template parameter where we specify if we use TCP or TCP
    connector::server< connector::TCP > server( port );
    // initialize the server (for TCP this has to run before attempted connects)
    server.init();

    // initializing receiving types

    // PODS
    char     c = 'a';
    uint32_t i = 0;
    double   d = 0.0;

    // structs
    struct structure::complex_struct cs = structure::init_complex_struct();

    // arrays with varied length (static allocation) - if you want to dynamically allocate, use a wrapper that splits your data in bite-size chunks and serialize them accordingly
    uint32_t string_length = 0;
    const uint32_t max_length   = 255; // may be anything, but both sides have to never exceed this limit
    char message[max_length];
    std::memset(message, '\0', max_length); // fill it with null delimiter

    // c++ vector (dynamic allocation)
    std::vector< uint32_t > vec;
    std::vector< uint32_t > vec2;

    // start receiving in predefined order
    // PODS
    server.receive_tcp< char >( c );
    DEBUG_MSG_CONNECTOR("Got char: " << c << '\n');
    server.receive_tcp< uint32_t >( i );
    DEBUG_MSG_CONNECTOR("Got uint32_t: " << i << '\n');
    server.receive_tcp< double >( d );
    DEBUG_MSG_CONNECTOR("Got double: " << d << '\n');

    // struct
    server.receive_tcp< struct structure::complex_struct >( cs );
    DEBUG_MSG_CONNECTOR("Got complex_struct.i: " << cs.i << '\n');
    DEBUG_MSG_CONNECTOR("Got complex_struct.d: " << cs.d << '\n');
    DEBUG_MSG_CONNECTOR("Got complex_struct.message: " << cs.message << '\n');

    // array with varied length
    // if you want to reuse the buffer, reset the buffer before receive
    server.receive_tcp< uint32_t >( string_length );
    DEBUG_MSG_CONNECTOR("Got string_length: " << string_length << '\n');
    server.receive_tcp< char >( message[0], sizeof(char) * string_length );
    std::string message_string( message ); 
    DEBUG_MSG_CONNECTOR("Got message: " << message_string << '\n');

    // c++ vector
    receive_vector< uint32_t >( server, vec );
    receive_vector< uint32_t >( server, vec );
}
