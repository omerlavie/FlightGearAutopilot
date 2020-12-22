#include "DataReaderServer.h"

/****************************************************
 * Function Name:       DataReaderServer
 * The Input:           int p: port, int h: host, VarCollection* vc
 * The Output:          null
 * Function Operation:  DataReaderServer constructor
 ****************************************************/
DataReaderServer::DataReaderServer(int p, int h) {
    this->port = p;
    this->herz = h;
    this->stop = false;
    this->newsockfd = 0;
    this->createPathToIndexInBufferMap();
}

/****************************************************
 * Function Name:       createPathToIndexInBufferMap
 * The Input:           null
 * The Output:          map<string, int> m: a map of all the paths
 * Function Operation:  The function creates a serial number to every path from the xml file
 ****************************************************/
void DataReaderServer::createPathToIndexInBufferMap() {
    this->bufferMap["/instrumentation/airspeed-indicator/indicated-speed-kt"] = 0;
    this->bufferMap["/instrumentation/altimeter/indicated-altitude-ft"] = 1;
    this->bufferMap["/instrumentation/altimeter/pressure-alt-ft"] = 2;
    this->bufferMap["/instrumentation/attitude-indicator/indicated-pitch-deg"] = 3;
    this->bufferMap["/instrumentation/attitude-indicator/indicated-roll-deg"] = 4;
    this->bufferMap["/instrumentation/attitude-indicator/internal-pitch-deg"] = 5;
    this->bufferMap["/instrumentation/attitude-indicator/internal-roll-deg"] = 6;
    this->bufferMap["/instrumentation/encoder/indicated-altitude-ft"] = 7;
    this->bufferMap["/instrumentation/encoder/pressure-alt-ft"] = 8;
    this->bufferMap["/instrumentation/gps/indicated-altitude-ft"] = 9;
    this->bufferMap["/instrumentation/gps/indicated-ground-speed-kt"] = 10;
    this->bufferMap["/instrumentation/gps/indicated-vertical-speed"] = 11;
    this->bufferMap["/instrumentation/heading-indicator/indicated-heading-deg"] = 12;
    this->bufferMap["/instrumentation/magnetic-compass/indicated-heading-deg"] = 13;
    this->bufferMap["/instrumentation/slip-skid-ball/indicated-slip-skid"] = 14;
    this->bufferMap["/instrumentation/turn-indicator/indicated-turn-rate"] = 15;
    this->bufferMap["/instrumentation/vertical-speed-indicator/indicated-speed-fpm"] = 16;
    this->bufferMap["/controls/flight/aileron"] = 17;
    this->bufferMap["/controls/flight/elevator"] = 18;
    this->bufferMap["/controls/flight/rudder"] = 19;
    this->bufferMap["/controls/flight/flaps"] = 20;
    this->bufferMap["/controls/engines/current-engine/throttle"] = 21;
    this->bufferMap["/engines/engine/rpm"] = 22;
}

/****************************************************
 * Function Name:       updateValues
 * The Input:           char* buffer, VarCollection* vc
 * The Output:          null
 * Function Operation:  The function find's a variable and update it value.
 ****************************************************/
void DataReaderServer::updateValues(char* buffer, VarCollection* vc) {
    map<string, pair<string, double>> varMap = vc->getVariablesMap();
    //We iterate over all the members in varMap
    for (auto var : varMap) {
        string varName = var.first;
        string varPath = var.second.first;
        //If there is no path to 'var' we just update it value.
        if (varPath != "") {
            // check if path exists in buffer map.
            bool pathExists = false;
            for(auto x : this->bufferMap) {
                if(varPath == x.first) {
                    pathExists = true;
                }
            }
            // if path exists, update value.
            if (pathExists) {
                int indexInBuffer = this->bufferMap[varPath];
                vector<string> bufferV = Lexer::splitBufferToVector(buffer);
                double newValue = Lexer::stringToDouble(bufferV[indexInBuffer]);
                vc->updateValue(varName, newValue);
            }
        }
    }
}

/****************************************************
 * Function Name:       openServer
 * The Input:           VarCollection* vc
 * The Output:          null
 * Function Operation:  The function opens a socket to a server
 ****************************************************/
void DataReaderServer::openServer(VarCollection* vc) {
    int n = 0, newsockfd = 0, clilen = 0;
    struct sockaddr_in serv_addr, cli_addr;
    char buffer[256];
    /* First call to socket() function */
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(this->port);
    /* Now bind the host address using bind() call.*/
    if (bind(this->sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }
    /* Now start listening for the clients, here process will
    * go in sleep mode and will wait for the incoming connection
    */
    listen(this->sockfd, 5);
    clilen = sizeof(cli_addr);
    /* Accept actual connection from the client */
    this->newsockfd = accept(this->sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);
    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }
    while (n == 0) {
        n = read(this->newsockfd, buffer, 255);
    }
}

/****************************************************
 * Function Name:       readFromServer
 * The Input:           VarCollection* vc : var collection.
 * The Output:          null
 * Function Operation:  reads data from the server while the script is still being read. when the loop ends,
 *                      the sockets are closed.
 ****************************************************/
void DataReaderServer::readFromServer(VarCollection* vc) {
    int n = 0;
    char buffer[256];
    while(!this->stop) {
        /* If connection is established then start communicating */
        bzero(buffer, 256);
        n = read(this->newsockfd, buffer, 255);
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        updateValues(buffer, vc);
        // sleep for 1 / herz seconds.
        sleep(1 / this->herz);
    }
}

/****************************************************
 * Function Name:           shutDown
 * The Input:
 * The Output:              null
 * Function Operation:      stop the loop of the reading from server.
 ****************************************************/
void DataReaderServer::shutDown(){
    // when the loop ends, close the sockets.
    close(this->sockfd);
    close(this->newsockfd);
    // stop the loop.
    this->stop = true;
}
