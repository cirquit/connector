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

#include "../library/server.h"
#include "../library/client.h"
#include "../library/autogen-CONNECTOR-macros.h"

int main()
{
    using namespace std::chrono_literals;
    const int receive_port = 4444;
    const int send_port    = 4445;
    const std::string ip ( "127.0.0.1" );
    connector::server< connector::UDP > receiver( receive_port );
    connector::client< connector::UDP > sender( send_port, ip );
    sender.init();
    receiver.init();

    uint32_t ping = 1;
    uint32_t pong = 2;
    uint32_t received = 0;

    // initial pong
    sender.send_udp< uint32_t >( ping );

    while( true )
    {
        receiver.receive_udp< uint32_t >( received );
        std::this_thread::sleep_for(200ms);
        if ( received == pong )
        {
            DEBUG_MSG_CONNECTOR(" Got PONG -> Sending PING\n");
            sender.send_udp< uint32_t >( ping );
        }
    }
}
