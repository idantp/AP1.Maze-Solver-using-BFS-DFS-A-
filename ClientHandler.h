//
// Created by roy on 06/01/19.
//

#ifndef ROYANDIDANPROJECT2_CLIENTHANDLER_H
#define ROYANDIDANPROJECT2_CLIENTHANDLER_H

class ClientHandler{
public:
    virtual void handleClient(int socketID) = 0;
    virtual ~ClientHandler() = default;
};

#endif //ROYANDIDANPROJECT2_CLIENTHANDLER_H
