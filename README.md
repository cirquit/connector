Connector
=========

A simple C++ wrapper around the TCP and UDP send/receive functionality in C. 

Written and developed by Justine Probst [[github](https://github.com/jusnelda)] and Alexander Isenko [[github](https://github.com/cirquit)] in the Formula Student Season 2018 for the [municHMotorsport](https://www.munichmotorsport.de/) club. 

If you see this on github - this is only a mirror of our internal repository, made public to allow recruits to easily clone it if they don't have any access yet. 

### Build
```bash
$ git clone git@gitlab.munichmotorsport.de:FSD/Connector.git 
$ mkdir build  
$ cd build  
$ cmake ..  
$ make  
$ sudo make install
```  

### Usage

If you want to use this library after the global installation add this line to your root `CMakeLists.txt` file:
```cmake
    find_package(connector 1.0 REQUIRED)
```

If you link against this library, add `connector` to `target_link_libraries`, e.g:
```cmake
    target_link_libraries(${your-awesome-file} ${your-awesome-library} connector )
```

Example usage can be found in [tests](tests) directory. This is a very simple [PING](tests/pinger.cc) / [PONG](tests/ponger.cc) server/client example:

```c++
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
```

### Documentation  
Created with [doxygen](https://www.stack.nl/~dimitri/doxygen/ "Doxygen Website") (with Markdown support)  
  * [HTML](documentation/html/index.html)
  * To generate it by yourselves - `doxygen doxygen.config` in the source directory

```

### Tip  
The `send_udp()`, `send_tcp()`, `receive_udp()` and `receive_tcp()` functions are overloaded, so you can set the buffer size yourself (e.g. when doing pointer magic):  
```c++
  void send_udp(U & object_to_send, const size_t buffer) const {}
  void send_tcp(U & object_to_send, const size_t buffer) const {}

  void receive_udp(U & object_to_receive, const size_t buffer) {}
  void receive_tcp(U & object_to_receive, const size_t buffer) const {}
```  
