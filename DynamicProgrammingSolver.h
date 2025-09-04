#ifndef DYNAMIC_PROGRAMMING_SOLVER_H
#define DYNAMIC_PROGRAMMING_SOLVER_H

#include "Instance.h"
#include "Solution.h"

class DynamicProgrammingSolver {
public:
    Solution solve(const Instance& instance);
};

#endif // DYNAMIC_PROGRAMMING_SOLVER_H