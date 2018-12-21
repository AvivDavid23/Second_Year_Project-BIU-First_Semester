//
// Created by aviv on 12/16/18.
//

#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>
#include "DataWriterClient.h"
#include "SymbolTable.h"


void DataWriterClient::setMessage(const std::string &message1) {
    globalMutex.lock();
    message = message1;
    globalMutex.unlock();
}

void DataWriterClient::createClient(int port, std::string address) {
    message = "";
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    server = gethostbyname(address.c_str());

    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    /* Now connect to the server */
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }

    while (true) {
        if(!message.empty()) {
            globalMutex.lock();
            /* Send message to the server */
            n = write(sockfd, message.c_str(), message.length());
            message = "";
            globalMutex.unlock();
            if (n < 0) {
                perror("ERROR writing to socket");
                exit(1);
            }
        }
    }
}