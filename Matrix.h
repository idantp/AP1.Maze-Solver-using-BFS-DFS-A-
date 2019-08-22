//
// Created by roy on 08/01/19.
//

#ifndef ROYANDIDANPROJECT2_MATRIX_H
#define ROYANDIDANPROJECT2_MATRIX_H

#include <utility>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cmath>
#include "Searchable.h"
#include "Point.h"

#define FIRST_COLUMN 0
#define INFINITE_PATH -1
#define SPACE " "
#define LINE_DELIMITER "|"
#define MATRIX_POINTS_DELIMITER ";"
#define INDEXES_DELIMITER ","
#define SQUARE_TWO 2

class Matrix : public Searchable<Point> {
private:
    vector<vector<State<Point> *>> matrix;
    State<Point> *initialState;
    State<Point> *goalState;
    size_t rows{};
    size_t columns{};

public:

    Matrix(Point initial, Point goal, vector<vector<State<Point> *>> mat) {
        this->initialState = new State<Point>(initial);
        this->goalState = new State<Point>(goal);
        this->matrix = mat;
        this->goalState->setCost(mat[goal.getLeft()][goal.getRight()]->getCost());
        this->initialState->setCost(mat[initial.getLeft()][initial.getRight()]->getCost());
        this->rows = matrix.size();
        this->columns = matrix[FIRST_COLUMN].size();
    }

    vector<vector<State<Point> *>> &getMatrix() {
        return matrix;
    }

    State<Point> *getInitialState() override {
        return this->initialState;
    }

    State<Point> *getGoalState() override {
        return this->goalState;
    }

    State<Point> *getStateByPoint(Point p1) {
        return matrix[p1.getLeft()][p1.getRight()];

    }

    vector<State<Point> *> getPossibleStates(State<Point> *fromState) override {
        vector<State<Point> *> possibleStates;
        int i = fromState->getState().getLeft();
        int j = fromState->getState().getRight();
        //checks if the indexes are out of the matrix's bounds.
        if (i < 0 || j < 0 || i >= rows || j >= columns) {
            perror("Out of Bounds.");
            exit(1);
        }
        //not first row add above.
        if (i != 0 && matrix[i - 1][j]->getCost() != INFINITE_PATH) {
            Point tempPoint(i - 1, j);
            State<Point> *tempState = getStateByPoint(tempPoint);
            if (tempState->getCameFrom() == nullptr) {
                tempState->setCameFrom(fromState);
            }
            possibleStates.emplace_back(tempState);
        }
        //not first column add left.
        if (j != 0 && matrix[i][j - 1]->getCost() != INFINITE_PATH) {
            Point tempPoint(i, j - 1);
            State<Point> *tempState = getStateByPoint(tempPoint);
            if (tempState->getCameFrom() == nullptr) {
                tempState->setCameFrom(fromState);
            }
            possibleStates.emplace_back(tempState);
        }
        //not last column, add right
        if (j != this->columns - 1 && matrix[i][j + 1]->getCost() != INFINITE_PATH) {
            Point tempPoint(i, j + 1);
            State<Point> *tempState = getStateByPoint(tempPoint);
            if (tempState->getCameFrom() == nullptr) {
                tempState->setCameFrom(fromState);
            }
            possibleStates.emplace_back(tempState);
        }
        //not last row, add below
        if (i != this->rows - 1 && matrix[i + 1][j]->getCost() != INFINITE_PATH) {
            Point tempPoint(i + 1, j);
            State<Point> *tempState = getStateByPoint(tempPoint);
            if (tempState->getCameFrom() == nullptr) {
                tempState->setCameFrom(fromState);
            }
            possibleStates.emplace_back(tempState);
        }
        return possibleStates;
    }

    size_t getRows() const {
        return rows;
    }

    size_t getColumns() const {
        return columns;
    }

    //in order to write the problem into a file, we need to overload the string operator.
    operator string() const override {
        string problem;
        //creates a string of the indexes of each initial and goal state in the form - i1,j1,i2,j2.
        string indexes =
                to_string(initialState->getState().getLeft()) + INDEXES_DELIMITER + to_string
                        (initialState->getState().getRight()) + INDEXES_DELIMITER +
                to_string(goalState->getState().getLeft())
                + INDEXES_DELIMITER + to_string(goalState->getState().getRight());
        /*
         * Goes over the matrix and saves it as a string following the rules below:
         * Each node is separated by a SPACE.
         * Each line is separated by a OR operator - |
         * Between the matrix and the indexes of inital and goal states is a semicolon ';'.
         */
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < columns; j++) {
                problem += to_string(matrix.at(i).at(j)->getCost());
                problem += SPACE;
            }
            problem += LINE_DELIMITER;
        }
        problem += MATRIX_POINTS_DELIMITER;
        problem += indexes;
        return problem;
    }

    //copy constructor.
    Matrix(const Matrix &matrix) {
        this->initialState = new State<Point>(*matrix.initialState);
        this->goalState = new State<Point>(*matrix.goalState);
        this->matrix = matrix.matrix;
        this->goalState->setCost(matrix.goalState->getCost());
        this->initialState->setCost(matrix.initialState->getCost());
        this->rows = matrix.rows;
        this->columns = matrix.columns;
    }

    double findDistance(State<Point> *state1, State<Point> *state2) override {
        double difX = abs(state1->getState().getLeft() - state2->getState().getLeft());
        double difY = abs(state1->getState().getRight() - state2->getState().getRight());
        double statesDistance = sqrt(pow((difX), SQUARE_TWO) + pow(difY, SQUARE_TWO));
        return statesDistance;
    }

    //destructor
    ~Matrix() {
        delete (initialState);
        delete (goalState);
    }
};


#endif //ROYANDIDANPROJECT2_MATRIX_H
