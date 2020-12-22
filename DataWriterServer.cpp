#include "DataWriterServer.h"

/****************************************************
 * Function Name:       constructor.
 * The Input:           char* h : host ip.
 *                      int p : port number.
 * The Output:
 * Function Operation:  constructs a DataWriterServer object.
 ****************************************************/
DataWriterServer::DataWriterServer(char* h, int p) {
    this->host = h;
    this->port = p;
    this->sockfd = 0;
}

/****************************************************
 * Function Name:       connectToServer
 * The Input:
 * The Output:
 * Function Operation:  function connects to server using the port and the host ip.
 *                      if there are problems with connection, error will be thrown.
 ****************************************************/
void DataWriterServer::connectToServer() {
    struct sockaddr_in serv_addr;
    struct hostent *server;
    // create socket point.
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    server = gethostbyname(this->host);
    if (server == nullptr) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char*)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, (size_t) server->h_length);
    serv_addr.sin_port = htons(this->port);
    // connect to server.
    if (connect(this->sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }
}

/****************************************************
 * Function Name:       writeToServer
 * The Input:           char* message : user's message.
 * The Output:          char* response : server's response.
 * Function Operation:  receives the interpreted command as a char* message, and sends it to the server.
 *                      the command will be operated in the simulator.
 ****************************************************/
string DataWriterServer::writeToServer(char* message) {
    int n = 0;
    char response[1024] = {};
    // send the message to the server.
    n = (int) write(this->sockfd, message, strlen(message));
    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }
    // read server's response.
    bzero(response ,1024);
    n = (int) read(this->sockfd, response, 1023);
    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }
    return response;
}

/****************************************************
 * Function Name:       shutDown
 * The Input:
 * The Output:
 * Function Operation:  closes sockfd.
 ****************************************************/
void DataWriterServer::shutDown(){
    close(this->sockfd);
}

/****************************************************
 * Function Name:       destructor.
 * The Input:
 * The Output:
 * Function Operation:  deletes char* host.
 ****************************************************/
DataWriterServer::~DataWriterServer(){
    delete[](this->host);
}
