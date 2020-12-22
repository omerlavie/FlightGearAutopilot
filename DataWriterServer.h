#ifndef MILESTONE1_DATAWRITERSERVER_H
#define MILESTONE1_DATAWRITERSERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <string>
#include <vector>
#include "thread"

using namespace std;

class DataWriterServer {
private:
    char* host;
    // server's port number.
    int port;
    // socket's number.
    int sockfd;

public:
    DataWriterServer(char* host, int port);
    void connectToServer();
    string writeToServer(char* s);
    void shutDown();
    ~DataWriterServer();
};



#endif //MILESTONE1_DATAWRITERSERVER_H
