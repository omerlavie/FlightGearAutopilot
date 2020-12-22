#ifndef MILESTONE1_DATAREADERSERVER_H
#define MILESTONE1_DATAREADERSERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "thread"
#include <string.h>
#include "VarCollection.h"
#include "Lexer.h"

class DataReaderServer {
private:
    // server's port number.
    int port;
    // connections per seconds.
    int herz;
    // socket and new socket's numbers.
    int sockfd;
    int newsockfd;
    // loop stopper.
    bool stop;
    // mapping path to index in xml file.
    map<string, int> bufferMap;

public:
    DataReaderServer(int p, int h);
    void openServer(VarCollection* vc);
    void readFromServer(VarCollection* vc);
    void createPathToIndexInBufferMap();
    void updateValues(char* buffer, VarCollection* vc);
    void shutDown();
};

#endif //MILESTONE1_DATAREADERSERVER_H
