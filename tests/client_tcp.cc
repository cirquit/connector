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

#include <thread> // std::this_thread::sleep_for
#include <string>
#include <vector>

#include "../library/client.h"
#include "../library/autogen-CONNECTOR-macros.h"
#include "shared_structure.h"

/** "Generic" send_vector with the connector library. T has to be default initializable and streamable because of debugging
  * IMPORTANT - never copy the connector::server/client by value, else the destructor gets called and we lose the ability to communicate
  */
template < class T >
void send_vector( connector::client< connector::TCP > & client, std::vector< T > & vec )
{
    // this is used for the sleep_for function
    using namespace std::chrono_literals;

    T current_vec_size = vec.size();
    DEBUG_MSG_CONNECTOR("Sending vec_size: " << current_vec_size << '\n');
    client.send_tcp< T >( current_vec_size );
    DEBUG_MSG_CONNECTOR("Sending vector:\n");
    for ( T & elem : vec )
    {
        DEBUG_MSG_CONNECTOR("    - " << elem << '\n');
        client.send_tcp< T >( elem );
        std::this_thread::sleep_for( 200ms );
    }
}

int main()
{
    // this is used for the sleep_for function
    using namespace std::chrono_literals;
    // the clients port
    const int port = 4444;
    // the ip to send to
    const std::string ip = "127.0.0.1";
    // call the client with it's constructor and the template parameter where we specify if we use TCP or TCP
    connector::client< connector::TCP > client( port, ip );
    // initialize the client (for TCP this has to run after the server starts)
    client.init();

    // initializing things to send
    // PODS
    char     c = 'c';
    uint32_t i = 12;
    double   d = 42.0 / 2.5 ;

    // structs
    struct structure::complex_struct cs = structure::init_complex_struct();
    cs.i = 42;
    cs.d = 1.0 / 1.3;
    sprintf(cs.message, "My complex structure message");

    // string (staticly allocated)
    std::string message_string( "My varied length message..." );
    uint32_t string_length = message_string.length();
    const uint32_t max_length = 255; // is fixed on compile time
    char message[max_length];
    sprintf(message, "%s", message_string.c_str());

    // c++ vector
    std::vector< uint32_t > vec;
    uint32_t vec_size = 5; // can be modified on runtime
    vec.reserve( vec_size );
    // we fill until the 4th element, send it, add one and send it again to show dynamic allocation
    for ( uint32_t i = 0; i < vec_size - 1; ++i )
    {
        vec.emplace_back(i);
    }

    // start receiving in predefined order
    // PODS
    DEBUG_MSG_CONNECTOR("Sending char: " << c << '\n');
    client.send_tcp< char >( c );
    std::this_thread::sleep_for(500ms);
    DEBUG_MSG_CONNECTOR("Sending uint32_t: " << i << '\n');
    client.send_tcp< uint32_t >( i );
    std::this_thread::sleep_for(500ms);
    DEBUG_MSG_CONNECTOR("Sending double: " << d << '\n');
    client.send_tcp< double >( d );
    std::this_thread::sleep_for(500ms);

    // struct
    DEBUG_MSG_CONNECTOR("Sending complex_struct.i: " << cs.i << '\n');
    DEBUG_MSG_CONNECTOR("Sending complex_struct.d: " << cs.d << '\n');
    DEBUG_MSG_CONNECTOR("Sending complex_struct.message: " << cs.message << '\n');
    client.send_tcp< struct structure::complex_struct >( cs );
    std::this_thread::sleep_for(500ms);

    // array with varied length (static)
    // if you want to reuse the buffer, reset the buffer before send
    DEBUG_MSG_CONNECTOR("Sending string_length: " << string_length << '\n');
    client.send_tcp< uint32_t >( string_length );
    DEBUG_MSG_CONNECTOR("Sending message: " << message << '\n');
    client.send_tcp< char >( message[0], sizeof(char) * string_length );
    std::this_thread::sleep_for(500ms);

    // c++ vector with varied length (dynamic) - very naive implementation where each member is send manually
    send_vector< uint32_t >( client, vec );
    vec.push_back( 100 );
    send_vector< uint32_t >( client, vec );
}