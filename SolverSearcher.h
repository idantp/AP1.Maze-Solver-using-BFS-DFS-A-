//
// Created by roy on 08/01/19.
//

#ifndef ROYANDIDANPROJECT2_SOLVERSEARCHER_H
#define ROYANDIDANPROJECT2_SOLVERSEARCHER_H


#include "Solver.h"
#include <vector>
#include "Searchable.h"
#include "Searcher.h"

using namespace std;

template <class T>
class SolverSearcher : public Solver<Searchable<T>, vector<T>>{
private:
    Searcher<T> searcher;
public:
    SolverSearcher(Searchable<T> searcher){
        this->searcher = searcher;
    }

    vector<T> solve(Searchable<T> problem){
        return this->searcher.search(problem);
    }

};


#endif //ROYANDIDANPROJECT2_SOLVERSEARCHER_H
