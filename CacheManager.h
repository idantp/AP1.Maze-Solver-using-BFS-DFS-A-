//
// Created by roy on 06/01/19.
//

#ifndef ROYANDIDANPROJECT2_CACHEMANAGER_H
#define ROYANDIDANPROJECT2_CACHEMANAGER_H

#include <string>

using namespace std;

template <class P, class S>

class CacheManager{
public:
    virtual bool solutionExists(P problem) = 0;
    virtual S getSolution(P problem) = 0;
    virtual void saveSolution(P problem, S solution) = 0;
    virtual ~CacheManager() = default;

};

#endif //ROYANDIDANPROJECT2_CACHEMANAGER_H
