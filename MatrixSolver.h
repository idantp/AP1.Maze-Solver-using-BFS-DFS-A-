//
// Created by idantp on 1/12/19.
//

#ifndef ROYANDIDANPROJECT2_MATRIXSOLVER_H
#define ROYANDIDANPROJECT2_MATRIXSOLVER_H

#include <string>
#include "Solver.h"
#include "Searchable.h"
#include "Searcher.h"

#define UP "Up"
#define DOWN "Down"
#define LEFT "Left"
#define RIGHT "Right"
#define NO_PATH "-1"
#define COMMA ", "

class MatrixSolver : public Solver<Searchable<Point> *, string> {
    Searcher<Point> *searchAlgorithm{};

    string getNextStep(Point previous, Point next);

    string getPathInstructions(vector<State<Point> *> path);

public:
    MatrixSolver(Searcher<Point> *searchAlgorithm);

    string solve(Searchable<Point> *problem) override;

    string NodesCostsSolution(Searchable<Point> *problem);

};


#endif //ROYANDIDANPROJECT2_MATRIXSOLVER_H
