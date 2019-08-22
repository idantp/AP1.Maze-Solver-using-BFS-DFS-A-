//
// Created by roy on 06/01/19.
//

#ifndef ROYANDIDANPROJECT2_SOLVER_H
#define ROYANDIDANPROJECT2_SOLVER_H

template <class P, class S>
class Solver{
public:
    virtual S solve(P problem) = 0;

};

#endif //ROYANDIDANPROJECT2_SOLVER_H
