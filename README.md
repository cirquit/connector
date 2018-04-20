
Connector
=========


### Build  
```bash
$ git clone git@gitlab.munichmotorsport.de:Justine/Connector.git 
$ mkdir build  
$ cd build  
$ cmake ..  
$ make  
```  

### Usage  
* Client/Server 
  * Include `client.h` and/or `server.h` in your project and `util.h`  
  * This Example shows a UDP connection, TCP works accordingly  
  * **Receive** any object like so:  

```c++
  // Create the object you want to send
  MyObject my_object;
  int port{4242}; // The port you want to receive the data at

  // creation of sender object
  connector::server< connector::UDP > receiver( port );
  receiver.init();  
  receiver.receive_udp< MyObject >( my_object );
```

  * **Send** any object like so:  

```c++
  // Construct an instance of the object you want to receive
  MyObject my_object;
  int port{4242}; // The port you want to receive data at
  std::string ip {"127.0.0.1"}; // The IP Adress of your receiver or 127.0.0.1 for localhost

  // creation of receiver object
  connector::client< connector::UDP > sender( port, ip );
  sender.init();
  sender.send_udp< MyObject >( my_object );
```

### Documentation  
Created with [doxygen](https://www.stack.nl/~dimitri/doxygen/ "Doxygen Website") (with Markdown support)  
  * [HTML](documentation/html/index.html)  
Ubuntu:  

```bash
$ firefox documentation/html/index.html
```


### Tip  
The `send_udp()`, `send_tcp()`, `receive_udp()` and `receive_tcp()` functions are overloaded, so you can set the buffer size yourself (e.g. when doing pointer magic):  
```c++
  void send_udp(U & object_to_send, const size_t buffer) const {}
  void send_tcp(U & object_to_send, const size_t buffer) const {}

  void receive_udp(U & object_to_receive, const size_t buffer) {}
  void receive_tcp(U & object_to_receive, const size_t buffer) const {}
```  
