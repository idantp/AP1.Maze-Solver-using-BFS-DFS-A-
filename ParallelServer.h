//
// Created by idantp on 1/10/19.
//

#ifndef ROYANDIDANPROJECT2_MYSERVER_H
#define ROYANDIDANPROJECT2_MYSERVER_H

#include "Server.h"

#include <queue>
#include <thread>

namespace server_side {
    class ParallelServer : public Server {
    private:
        std::queue <std::thread> threadsQueue;
        int sockfd;
    public:
        ParallelServer(){
            this->sockfd = -1;
        }
        void open(int portNum, ClientHandler &clientHandler) override;

        void handle(int clientSocket, ClientHandler &clientHandler) override;

        void start(int serverSocket, ClientHandler &clientHandler) override;

        void stop() override;

    };
}

#endif //ROYANDIDANPROJECT2_MYSERVER_H
