//
// Created by roy on 07/01/19.
//

#ifndef ROYANDIDANPROJECT2_SEARCHABLE_H
#define ROYANDIDANPROJECT2_SEARCHABLE_H

#include "State.h"
#include "Point.h"
#include <vector>
#include <string>

using namespace std;

template<class T>
class Searchable {
public:
    virtual operator string() const = 0;

    virtual State<T> *getInitialState() = 0;

    virtual State<T> *getGoalState() = 0;

    virtual vector<State<T> *> getPossibleStates(State<T> *fromState) = 0;

    virtual double findDistance(State<T> *state1, State<T> *state2) = 0;


};


#endif //ROYANDIDANPROJECT2_SEARCHABLE_H
