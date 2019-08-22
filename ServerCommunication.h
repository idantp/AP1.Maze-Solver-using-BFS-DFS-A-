//
// Created by roy on 13/01/19.
//

#ifndef ROYANDIDANPROJECT2_SERVERCOMMUNICATION_H
#define ROYANDIDANPROJECT2_SERVERCOMMUNICATION_H

#include <string>
#include <vector>

#define READ_CHAR 1
#define END_PROBLEM "end"
#define ENTER '\n'
using namespace std;

class ServerCommunication {
public:
    ServerCommunication() = default;

    vector<string> readFromServer(int socketNum);

    void writeToServer(int socketNum, string info);
};


#endif //ROYANDIDANPROJECT2_SERVERCOMMUNICATION_H
