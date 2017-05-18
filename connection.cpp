#include "connection.h"

void myerror(string msg) {
  printf("%s\n", msg.c_str());
  exit(-1);
}

Connection::Connection(short port) {
  struct sockaddr_in echoServAddr; /* Echo server address */
  struct  hostent  *ptrh;
  
  /* Create a reliable, stream socket using TCP */
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    myerror("socket() failed");
  
  /* Construct the server address structure */
  memset(&echoServAddr, 0, sizeof(echoServAddr));     /* Zero out structure */
  echoServAddr.sin_family      = AF_INET;             /* Internet address family */
  echoServAddr.sin_port = htons(port);                /* Server port */

  ptrh = gethostbyname("localhost");

  memcpy(&echoServAddr.sin_addr, ptrh->h_addr, ptrh->h_length);
  
  /* Establish the connection to the echo server */
  if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
    myerror("connect() failed");

}

bool Connection::sendMsg(string msg) {
  int res = send(sock, msg.c_str(), msg.size(), 0);
  if (res < 0) 
    myerror("Unable to send");
  string answer = readLine();
  return answer == "ok";
}

string Connection::readLine() {
  string msg;  
  char ch;
  while (true) {
    recv(sock, &ch, 1, 0);
    if (ch == '\n')
      break;
    msg.push_back(ch);
  }
  return msg;
}
