//
// Created by idantp on 1/10/19.
//
#include <netinet/in.h>
#include <thread>
#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <unistd.h>
#include <thread>
#include <iostream>
#include "ParallelServer.h"

using namespace std;
using namespace std::chrono;
using namespace std::chrono::_V2;

void server_side::ParallelServer::open(int portNum, ClientHandler &clientHandler) {
    int serverSockFD;
    //initialize the sockets variables
    struct sockaddr_in serv_addr;

    //First call to socket() function
    serverSockFD = socket(AF_INET, SOCK_STREAM, 0);

    int n = 1;
    setsockopt(serverSockFD, SOL_SOCKET, SO_REUSEADDR, (char *)&n, sizeof(int));
    if (serverSockFD < 0) {
        perror("ERROR Could Not Open Socket.");
        exit(1);
    }

    // Initialize socket structure
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portNum);


    /* Now bind the host address using bind() call.*/
    if (bind(serverSockFD, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */

    listen(serverSockFD, 5);
    this->sockfd = serverSockFD;
    start(serverSockFD,clientHandler);
}

void server_side::ParallelServer::stop() {
    //closes the socket.
    if (sockfd != -1){
        close(sockfd);
    }
    //join the threads and pop them from the queue.
    while (!this->threadsQueue.empty()){
        threadsQueue.front().join();
        threadsQueue.pop();
    }

}

/**
 * start connection to the server to handle the client.
 * @param serverSocket - socket to connect to.
 * @param clientHandler - specific client handler.
 */
void server_side::ParallelServer::start(int serverSocket, ClientHandler &clientHandler) {
    int newsockfd;
    int clilen;
    struct sockaddr_in cli_addr;
    clilen = sizeof(cli_addr);
    timeval timeOut;
    timeOut.tv_usec = 0;

    while(true){
        //setting the time out.
        timeOut.tv_sec = 0;


        /* Accept actual connection from the client */
        newsockfd = accept(serverSocket, (struct sockaddr *) &cli_addr,
                (socklen_t *) &clilen);

        if (newsockfd < 0) {
            //time out, close the server.
            if (errno == EWOULDBLOCK || errno == EAGAIN){
                break;
            }
            perror("ERROR Could Not Accept From Socket");
            exit(1);
        }

        if (setsockopt(newsockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeOut, sizeof(timeOut)) < 0)   {
            perror("ERROR on setting timeOut");
            exit(1);
        }
        //handle the client.
        handle(newsockfd,clientHandler);
        timeOut.tv_sec = 1;

        if (setsockopt(serverSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeOut, sizeof(timeOut)) < 0)   {
            perror("ERROR on setting timeOut");
            exit(1);
        }
    }
    //close the server and join threads.
    stop();
}

static void handleSpecificClient(int clientSocket, ClientHandler *clientHandler){
    clientHandler->handleClient(clientSocket);
}

void server_side::ParallelServer::handle(int clientSocket,
                                          ClientHandler &clientHandler) {
    this->threadsQueue.push(std::thread(handleSpecificClient,clientSocket,&clientHandler));
}