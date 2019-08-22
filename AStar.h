//
// Created by roy on 08/01/19.
//

#ifndef ROYANDIDANPROJECT2_ASTAR_H
#define ROYANDIDANPROJECT2_ASTAR_H

#include "Searcher.h"
#include <queue>

template<class T>
class AStar : public Searcher<T> {
    int numOfNodes;
    double totalPathCost;

    //inner class to use in the priority queue in the algorithm.
    class StateCompare {
    public:
        bool operator()(State<T> *left, State<T> *right) {
            return ((left->getDistance() + left->getPathCost()) >
                    (right->getDistance() + right->getPathCost()));
        }
    };

public:

    AStar() {
        numOfNodes = 0;
        totalPathCost = 0;
    }

    void resetMembers() {
        this->totalPathCost = 0;
        this->numOfNodes = 0;
    }

    /**
 * Checks whether or not a specific node has been visited during the BFS algorithm.
 * @param nodesVec - vector of nodes that have been visited.
 * @param node - node to check if visited.
 * @return - true if it is false otherwise.
 */
    bool hasNodeBeenVisited(vector<State<T> *> nodesVec, State<T> *node) {
        for (State<T> *state : nodesVec) {
            if (state->equalsTo(node)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Checks whether or not a specific state is in the priority queue. If so, returns true else false.
     */
    bool isNodeInQueue(
            priority_queue<State<T> *, vector<State<T> *>, StateCompare> priorityQueue,
            State<T> *node) {
        //goes over the queue until it's empty.
        while (!priorityQueue.empty()) {
            if (node->equalsTo(priorityQueue.top())) {
                return true;
            }
            priorityQueue.pop();
        }
        return false;
    }

    vector<State<T> *> search(Searchable<T> *searchable) override {
        resetMembers();
        //keeps the nodes we've already traveled in
        vector<State<T> *> nodesVisited;
        //keeps the nodes we need to travel in. sorts the nodes from the ones with the lowest
        // path-cost to the highest one
        priority_queue<State<T> *, vector<State<T> *>, StateCompare> open;
        //the final path from the source node to the destination node
        vector<State<T> *> path;
        State<T> *currentState = searchable->getInitialState();
        State<T> *goalState = searchable->getGoalState();
        currentState->setCameFrom(currentState);
        currentState->setPathCost(currentState->getCost());
        currentState->setDistance(searchable->findDistance(currentState, goalState));
        open.push(currentState);
        while (!open.empty()) {
            currentState = open.top();
            open.pop();
            if (!hasNodeBeenVisited(nodesVisited, currentState)) {
                this->numOfNodes += 1;
            }
            //if the are no more paths to check to the destination node then return the path to it
            if (currentState->equalsTo(searchable->getGoalState())) {
                path.insert(path.begin(), currentState);
                this->totalPathCost += currentState->getCost();
                while (!(currentState->equalsTo(searchable->getInitialState()))) {
                    currentState = currentState->getCameFrom();
                    path.insert(path.begin(), currentState);
                    this->totalPathCost += currentState->getCost();
                }
                return path;
            } else {
                //find all the adjacent nodes
                for (State<T> *adj : searchable->getPossibleStates(currentState)) {
                    //gets the current adjacent State
                    double adjPathCost = currentState->getPathCost() + adj->getCost();
                    double adjDistanceToGoal = searchable->findDistance(adj, goalState);
                    double adjHeuristic = adjPathCost + adjDistanceToGoal;
                    /*
                     * if the node was already visited and we dont need to find a cheaper
                     * way to it - continue, but if the node was already visited and we can to
                     * find a cheaper way to it - check
                     */
                    if (hasNodeBeenVisited(nodesVisited, adj) ||
                        isNodeInQueue(open, adj)) {
                        if (!hasNodeBeenVisited(nodesVisited, adj)
                            && isNodeInQueue(open, adj)) {
                            //compares the lowest heuristic of the same State with 2 different
                            // paths to it.
                            if (adjHeuristic < (adj->getPathCost() + adj->getDistance())) {
                                //if cheaper heuristic found - update adjacent State fields
                                adj->setCameFrom(currentState);
                                adj->setPathCost(adjPathCost);
                                adj->setDistance(adjDistanceToGoal);
                                open.emplace(adj);
                            }
                        }
                        continue;
                    } else {
                        //for a node we visit in the first time - update its information.
                        adj->setCameFrom(currentState);
                        adj->setPathCost(adjPathCost);
                        adj->setDistance(adjDistanceToGoal);
                        open.emplace(adj);
                    }
                }
                //insert the current node to nodesVisited to make sure we dont check it again
                nodesVisited.emplace_back(currentState);
            }
        }
        return path;
    }

    int getNumOfNodes() const {
        return numOfNodes;
    }

    double getTotalPathCost() const {
        return totalPathCost;
    }
};


#endif //ROYANDIDANPROJECT2_ASTAR_H
