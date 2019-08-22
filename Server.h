//
// Created by roy on 06/01/19.
//

#ifndef ROYANDIDANPROJECT2_SERVER_H
#define ROYANDIDANPROJECT2_SERVER_H


#include "ClientHandler.h"

namespace server_side {
    class Server {
    public:
        virtual void open(int portNum, ClientHandler &clientHandler) = 0;

        virtual void stop() = 0;

        virtual void handle(int clientSocket, ClientHandler &clientHandler) = 0;

        virtual void start(int serverSocket, ClientHandler &clientHandler) = 0;

    };
}

#endif //ROYANDIDANPROJECT2_SERVER_H
