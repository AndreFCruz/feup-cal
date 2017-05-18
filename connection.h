#ifndef _CONNECTION_
#define _CONNECTION_

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#include <string>
#include <iostream>

using namespace std;

class Connection {
 public:
  Connection(short port);

  bool sendMsg(string msg);
  string readLine();
 private: 
  int sock;

};

#endif
