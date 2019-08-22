//
// Created by roy on 08/01/19.
//

#ifndef ROYANDIDANPROJECT2_SEARCHER_H
#define ROYANDIDANPROJECT2_SEARCHER_H

#include <vector>
#include "Searchable.h"

template<class T>
class Searcher {

public:
    virtual std::vector<State<T>*> search(Searchable<T> *searchable) = 0;

    virtual double getTotalPathCost() const = 0;

    virtual int getNumOfNodes() const = 0;

    virtual ~Searcher() = default;

};

#endif //ROYANDIDANPROJECT2_SEARCHER_H
