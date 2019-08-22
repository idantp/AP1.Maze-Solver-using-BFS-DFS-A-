//
// Created by roy on 13/01/19.
//

#ifndef ROYANDIDANPROJECT2_MATRIXCLIENTHANDLER_H
#define ROYANDIDANPROJECT2_MATRIXCLIENTHANDLER_H


#include "ClientHandler.h"
#include "CacheManager.h"
#include "MatrixSolver.h"
#include <vector>
#include "Point.h"
#include "Matrix.h"
#include "ServerCommunication.h"
#include "FileCacheManager.h"

#define MATRIX_CACHE_FILE "MatrixCache.txt"
#define COMMA_DELIMITER ','

class MatrixClientHandler : public ClientHandler {
    //members
    ServerCommunication serverCommunication;
    MatrixSolver matrixSolver;
    CacheManager<Matrix, string>* cacheManager;
public:
    //constructor
    MatrixClientHandler(MatrixSolver matrixSolver) : matrixSolver(matrixSolver){
        this->cacheManager = new FileCacheManager<Matrix, string>(MATRIX_CACHE_FILE);
    }
    //copy constructor
    MatrixClientHandler(const MatrixClientHandler& mCH) : matrixSolver(mCH.matrixSolver){
        this->cacheManager = new FileCacheManager<Matrix,string>(MATRIX_CACHE_FILE);

    }
    void handleClient(int socketID) override;
    Matrix* lexer(vector<string> problemInfo);
    string getMatrixSolution(Matrix matrix);

    ~MatrixClientHandler() override;

private:
    vector<int> splitString(string info);

};


#endif //ROYANDIDANPROJECT2_MATRIXCLIENTHANDLER_H
