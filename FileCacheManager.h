//
// Created by roy on 06/01/19.
//

#ifndef ROYANDIDANPROJECT2_FILECACHEMANAGER_H
#define ROYANDIDANPROJECT2_FILECACHEMANAGER_H


#include "CacheManager.h"
#include <map>
#include <string>
#include <fstream>

#define PROB_SOL_DELIMITER '$'
using namespace std;

template<class P, class S>
class FileCacheManager : public CacheManager<P, S> {
    string fileName;
    std::map<std::string, std::string> cacheMap;
public:
    FileCacheManager(const string &fileName) : fileName(fileName) {
        //loads all the problems with their solutions to cacheMap.
        loadFromFile();
    }

    // checks whether or not the problem has already been solved.
    bool solutionExists(P problem) override {
        if (this->cacheMap.find((string) problem) == cacheMap.end()) {
            return false;
        } else {
            return true;
        }
    }

    //returns the solution to a specific problem.
    string getSolution(P problem) override {
        if (solutionExists(problem)) {
            return cacheMap.at(problem);
        } else {
            perror("No solution for given Problem.");
            return "";
        }
    }

    ~FileCacheManager() override = default;


    //saves a solution and a problem in the map.
    void saveSolution(P problem, S solution) override {
        this->cacheMap.insert(make_pair(problem, solution));
        writeToFile(problem, solution);
    }

    /**
     * writes a pair (problem and its solution) to the cache text File.
     * @param problem describes problem
     * @param solution describes solution
     */
    void writeToFile(P problem, S solution) {
        ofstream outputStream;
        outputStream.open(fileName, ios::out | ios::app);
        if (outputStream.is_open()) {
            outputStream << (string) problem << PROB_SOL_DELIMITER << (string) solution << endl;
            outputStream.close();
        } else {
            perror("couldn't open cache File");
            exit(1);
        }
    }

    /**
     * loads all the problems and their solutions from cache text file to the map.
     */
    void loadFromFile() {
        ifstream inputStream;
        inputStream.open(fileName);
        if (!inputStream.bad()) {
            //reads from file each line and loads it to the map.
            for (string probSolution; getline(inputStream, probSolution);) {
                string thisProblem = probSolution.substr(0, probSolution.find(PROB_SOL_DELIMITER));
                string thisSolution = probSolution.substr(
                        (probSolution.find(PROB_SOL_DELIMITER) + 1),
                        probSolution.size() -
                        (thisProblem.size() + 1));
                //creates a pair of problem and solution to add to the map.
                this->cacheMap.insert(make_pair(thisProblem, thisSolution));
            }
            inputStream.close();
        } else {
            perror("couldn't open cache File");
            exit(1);
        }
    }
};

#endif //ROYANDIDANPROJECT2_FILECACHEMANAGER_H
