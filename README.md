
Connector
=========


### Build  
```bash
git clone git@gitlab.munichmotorsport.de:Justine/Connector.git 
mkdir build  
cd build  
cmake ..  
make  
```  

### Usage  
* Sender  
  * Include `sender.h` in your project  
  * Send any object (besides `Strings`) like so:  
```c++  
  // Create the object you want to send  
  MyObject my_object;  

  unsigned port{4242}; // The port you want to send the data at  
  std::string ip {"127.0.0.1"}; // The IP Adress of your receiver or 127.0.0.1 for localhost  
  // creation of sender object  
  connector::sender<MyObject> sndr{};  
  sndr.init_sender_udp(port, ip);  
  sndr.send_udp(&my_object);  
```  

* Receiver  
  * Include `receiver.h` in your project  
  * Receive any object like so:  
```c++  
  // Construct an instance of the object you want to receive  
  MyObject my_object;  

  unsigned port{4242}; // The port you want to receive data at  
  // creation of receiver object  
  connector::receiver<MyObject> rcvr{};  
  rcvr.init_receiver_udp(port);  
  rcvr.receive_udp(my_object);  
```  

### Tip  
The `send_udp()` and `receive_udp()` functions have a default parameter where you can set the size of the buffer:  
```c++
  void send_udp(T * object_to_send, unsigned buffer=2048) {}

  void receive_udp(T & out, unsigned buffer=2048) {}
```  
