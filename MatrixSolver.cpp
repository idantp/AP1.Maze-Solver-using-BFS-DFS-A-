//
// Created by idantp on 1/12/19.
//

#include "MatrixSolver.h"

//constructor.
MatrixSolver::MatrixSolver(Searcher<Point> *searchAlgorithm) : searchAlgorithm(searchAlgorithm) {}


/**
 * Solve the matrix and return a string of the path consisting of directions up down left or right.
 *
 * @param problem - problem to solve.
 * @return - path from initial to goal.
 */
string MatrixSolver::solve(Searchable<Point> *problem) {
    vector<State<Point> *> path;
    path = this->searchAlgorithm->search(problem);
    return getPathInstructions(path);
}

/**
 * returns which way in the matrix we need to go in order to get from the previous to the current node.
 *
 * @param previous - where we came from.
 * @param current  - where we are now.
 * @return - Left, Right, Up or Down
 */
string MatrixSolver::getNextStep(Point previous, Point current) {
    int previousLeft = previous.getLeft();
    int previousRight = previous.getRight();
    int currentLeft = current.getLeft();
    int currentRight = current.getRight();
    if (previousLeft > currentLeft) { return UP; }
    else if (previousLeft < currentLeft) { return DOWN; }
    else if (previousRight > currentRight) { return LEFT; }
    else { return RIGHT; }
}

/**
 * Goes over the whole path and converts it to directions, starting from the initial state to the goal state
 * using left right up or down divided by commas.
 *
 * @param path - path to convert.
 * @return - path made of words - Up, Down, Left or Right.
 */
string MatrixSolver::getPathInstructions(vector<State<Point> *> path) {
    if (path.empty()) { return NO_PATH; }
    string pathInstructions;
    unsigned long pathSize = path.size();
    /*
     * go over the path to send it to the directions function.
     * Excludes the last 2 since those are the initial and goal states.
    */
    for (unsigned long i = 1; i <= pathSize - 2; i++) {
        pathInstructions += getNextStep(path.at(i - 1)->getState(), path.at(i)->getState());
        //divide by a comma.
        pathInstructions += COMMA;
    }
    pathInstructions += getNextStep(path.at(pathSize - 2)->getState(), path.at(pathSize - 1)
            ->getState());
    return pathInstructions;
}
