//
// Created by roy on 08/01/19.
//

#ifndef ROYANDIDANPROJECT2_BREADTHFIRSTSEARCH_H
#define ROYANDIDANPROJECT2_BREADTHFIRSTSEARCH_H

#include "Searcher.h"
#include <queue>
#include <iostream>

using namespace std;

template<class T>
class BreadthFirstSearch : public Searcher<T> {
    int numOfNodes;
    double totalPathCost;
public:
    BreadthFirstSearch(){
        numOfNodes = 0;
        totalPathCost = 0;
    }

    /**
     * Checks if the node has already been visited during the BFS scan.
     * @param nodesVec - vector of nodes that have been visited.
     * @param node - node to check.
     * @return true / false .
     */
    bool hasNodeBeenVisited(vector<State<T> *> nodesVec, State<T> *node) {
        for (State<T> *state : nodesVec) {
            if (state->equalsTo(node)) {
                return true;
            }
        }
        return false;
    }
    //BFS algorithm.
    vector<State<T> *> search(Searchable<T> *searchable) override {
        resetMembers();
        vector<State<T> *> nodesVisited;
        vector<State<T> *> path;
        //set the current state to the initial we received from the problem.
        State<T> *currentState = searchable->getInitialState();
        currentState->setCameFrom(currentState);
        //put it into the nodes that have been visited.
        nodesVisited.emplace_back(currentState);
        State<T> *goalState = searchable->getGoalState();
        queue<State<T> *> stateQ;
        stateQ.push(currentState);
        //go over the state queue until it is empty.
        while (!stateQ.empty()) {

            currentState = stateQ.front();
            stateQ.pop();
            this->numOfNodes += 1;
            //the node we are currently on is the goal node.
            if (currentState->equalsTo(goalState)) {
                path.insert(path.begin(), currentState);
                this->totalPathCost += currentState->getCost();
                //restores the path from the initial to the goal.
                while (!(currentState->equalsTo(
                        searchable->getInitialState()))) {
                    currentState = currentState->getCameFrom();
                    path.insert(path.begin(), currentState);
                    this->totalPathCost += currentState->getCost();
                }
                //returns the path.
                return path;
            }

            //goes over all sons of the current state and expands them.
            for (State<T> *adj : searchable->getPossibleStates(currentState)) {
                //already visited, continue.
                if (hasNodeBeenVisited(nodesVisited, adj)) {
                    continue;
                }
                //otherwise, insert to the nodes visited , set it's cameFrom and insert into state queue.
                nodesVisited.emplace_back(adj);
                adj->setCameFrom(currentState);
                stateQ.push(adj);
            }
        }
        //could not find path from requested initial to goal.
        return path;
    }

    int getNumOfNodes() const {
        return numOfNodes;
    }

    double getTotalPathCost() const {
        return totalPathCost;
    }

    void resetMembers(){
        this->totalPathCost = 0;
        this->numOfNodes = 0;
    }

};


#endif //ROYANDIDANPROJECT2_BREADTHFIRSTSEARCH_H
