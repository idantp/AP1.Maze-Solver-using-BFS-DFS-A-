//
// Created by roy on 07/01/19.
//

#ifndef ROYANDIDANPROJECT2_STATE_H
#define ROYANDIDANPROJECT2_STATE_H

template<class T>
class State {
private:
    T state;
    double cost;
    double pathCost;
    State<T> *cameFrom;
    double distance;


public:
    //constructor with only a state.
    explicit State(T state) : state(state) {
        this->pathCost = -1;
        this->cameFrom = nullptr;
    }

    //constructor also with a cost.
    State(T state, double cost) : state(state) {
        this->cost = cost;
        this->cameFrom = nullptr;
        this->pathCost = -1;
    }

    double getDistance() const {
        return this->distance;
    }

    void setDistance(double distance) {
        this->distance = distance;
    }

    //sets the path cost up to it from the initial state.
    void setPathCost(double pathCost) {
        State::pathCost = pathCost;
    }

    double getPathCost() const {
        return pathCost;
    }

    void setCost(double cost) {
        this->cost = cost;
    }

    //set it's father node.
    void setCameFrom(State *state) {
        this->cameFrom = state;
    }

    State<T> *getCameFrom() const {
        return cameFrom;
    }

    double getCost() const {
        return this->cost;
    }

    T getState() const {
        return this->state;
    }

    //checks equality between two states based on their state's.
    bool equalsTo(State *state2) {
        return (this->state == state2->getState());
    }

    //operator overloading below to check inequalities between the costs of each state.
    const bool operator==(const State &other) {
        return (this->cost == other.getCost());
    }

    const bool operator<(const State &other) {
        return (this->getCost() < other.getCost());
    }

    const bool operator>(const State &other) {
        return (this->getCost() > other.getCost());
    }

    const bool operator<=(const State &other) {
        return (this->getCost() <= other.getCost());
    }

    const bool operator>=(const State &other) {
        return (this->getCost() >= other.getCost());
    }
};


#endif //ROYANDIDANPROJECT2_STATE_H
