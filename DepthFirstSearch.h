//
// Created by idantp on 1/9/19.
//

#ifndef ROYANDIDANPROJECT2_DEPTHFIRSTSEARCH_H
#define ROYANDIDANPROJECT2_DEPTHFIRSTSEARCH_H

#include "Searcher.h"
#include <stack>

using namespace std;
template<class T>
class DepthFirstSearch : public Searcher<T> {
    int numOfNodes;
    double totalPathCost;
public:

    DepthFirstSearch(){
        numOfNodes = 0;
        totalPathCost = 0;
    }

    /**
     * checks whether or not a node has already been visited during the algorithm.
     * @param nodesVec - vector consisting of nodes that have already been visited.
     * @param node - node to check if was visited.
     * @return - returns true if visited false otherwise.
     */
    bool hasNodeBeenVisited(vector<State<T> *> nodesVec, State<T> *node) {
        for (State<T> *state : nodesVec) {
            if (state->equalsTo(node)) {
                return true;
            }
        }
        return false;
    }

    vector<State<T> *> search(Searchable<T> *searchable) override {
        resetMembers();
        vector<State<T> *> nodesVisited;
        vector<State<T> *> tempVec;
        stack<State<T> *> stateStack;
        vector<State<T> *> path;
        State<T> *currentState = searchable->getInitialState();
        currentState->setCameFrom(currentState);
        nodesVisited.emplace_back(currentState);
        stateStack.push(currentState);
        //go over the stack of states.
        while (!stateStack.empty()) {
            currentState = stateStack.top();
            stateStack.pop();
            this->numOfNodes+=1;
            if (currentState->equalsTo(searchable->getGoalState())) {
                path.insert(path.begin(), currentState);
                this->totalPathCost += currentState->getCost();
                //restore the path and return it.
                while (!(currentState->equalsTo(
                        searchable->getInitialState()))) {
                    currentState = currentState->getCameFrom();
                    path.insert(path.begin(), currentState);
                    this->totalPathCost += currentState->getCost();
                }
                return path;
            }
            //if it wasn't visited, mark it as visited.
            if (!hasNodeBeenVisited(nodesVisited, currentState)) {
                nodesVisited.emplace_back(currentState);
            }
            //go over all the neighbors of this specific node.
            for (State<T> *adj : searchable->getPossibleStates(currentState)) {
                //already visited, move on to next iteration.
                if (hasNodeBeenVisited(nodesVisited, adj)) {
                    continue;
                }
                nodesVisited.emplace_back(adj);
                adj->setCameFrom(currentState);
                stateStack.push(adj);
            }
        }
        //could not find path from requested initial to goal.
        return tempVec;
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


#endif //ROYANDIDANPROJECT2_DEPTHFIRSTSEARCH_H
