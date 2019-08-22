#include <iostream>

using namespace std;

#include "Point.h"
#include "Matrix.h"
#include "Searcher.h"
#include "CacheManager.h"
#include "ClientHandler.h"
#include "DepthFirstSearch.h"
#include "Server.h"
#include "Solver.h"
#include "Searchable.h"
#include "BreadthFirstSearch.h"
#include "BestFirstSearch.h"
#include "MatrixSolver.h"
#include "MatrixClientHandler.h"
#include "Server.h"
#include "ParallelServer.h"
#include "AStar.h"

namespace boot{
    class Main{
    public:
        int main(int argc,char** argv){
            if(argc <= 1){
                perror("port input is missing !");
                return 0;
            }
            int portNum = stoi(argv[1]);
            Searcher<Point> *searchAlgorithm = new AStar<Point>();
            MatrixSolver matrixSolver(searchAlgorithm);
            MatrixClientHandler matrixClientHandler(matrixSolver);
            server_side::ParallelServer parallelServer;
            parallelServer.open(portNum, matrixClientHandler);
            delete(searchAlgorithm);
            return 0;
        }
    };
}

int main(int argc,char** argv) {
    boot::Main bootMain;
    bootMain.main(argc,argv);
    return 0;
}