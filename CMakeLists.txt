cmake_minimum_required(VERSION 3.13)
project(RoyAndIdanProject2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(RoyAndIdanProject2 main.cpp Server.h ClientHandler.h Solver.h CacheManager.h FileCacheManager.h State.h Point.cpp Point.h Searchable.h Matrix.h Searcher.h SolverSearcher.h BreadthFirstSearch.h BestFirstSearch.h AStar.h DepthFirstSearch.h ParallelServer.cpp ParallelServer.h MatrixSolver.cpp MatrixSolver.h ServerCommunication.cpp ServerCommunication.h MatrixClientHandler.cpp MatrixClientHandler.h)