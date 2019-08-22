//
// Created by roy on 13/01/19.
//

#include <strings.h>
#include <cstring>
#include <sys/socket.h>
#include "ServerCommunication.h"
#include <stdlib.h>
#include <unistd.h>

#define SPACE ' '

/**
 * Writes the solution of a problem to the server.
 * @param socketNum - socket to write to.
 * @param info - path to write.
 */
void ServerCommunication::writeToServer(int socketNum, string info) {
    ssize_t n = write(socketNum, info.c_str(), (info.size()));
    if (n < 0) {
        perror("Could not write to Server.");
        exit(1);
    }
}

/**
 * Reads the problem from the server and returns it as a vector of strings.
 * @param socketNum - socket to read from.
 * @return - returns a vector of the problem.
 */
vector<string> ServerCommunication::readFromServer(int socketNum) {
    vector<string> problemInfo;
    char c;
    string temp;

    while (temp != END_PROBLEM)
    {
        ssize_t n = read(socketNum, &c, READ_CHAR);
        if (n < 0) {
            perror("Could not read from Server.");
        }
        //go over each line and put it into the vector.
        while(c != ENTER){
            if (c == SPACE){
                read(socketNum, &c, READ_CHAR);
                continue;
            }
            temp += c;
            read(socketNum, &c, READ_CHAR);
        }
        //temp == "end" means that the problem is finished and we can finish the function.
        if (temp == END_PROBLEM){
            break;
        }
        problemInfo.push_back(temp);
        temp.erase();
    }
    return problemInfo;
}
