#ifndef MAXUTILITY_H
#define MAXUTILITY_H

#include "structure/define.h"
#include "structure/data_struct.h"
#include "structure/data_utility.h"

#include <vector>
#include <algorithm>
#include "structure/rtree.h"
#include "Others/lp.h"
#include "Others/pruning.h"
#include "Others/operation.h"
#include <queue>
#define RANDOM 1
#define SIMPLEX 2

using namespace std;

int UHRandom(point_set *pset, point_set *realSet, point_t *u, int k, std::vector<point_set*> &TID,
             int *Ques, std::ofstream &fp);

int UHSimplex(point_set *pset, point_set *realSet, point_t *u, int k, std::vector<point_set*> &TID,
              int *Ques, std::ofstream &fp);

#endif