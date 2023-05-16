#ifndef RUN_PREFERENCELEARNING_H
#define RUN_PREFERENCELEARNING_H
#include "point_set.h"
#include "Partition.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include "s_node.h"
#include "cluster_t.h"
#include "../Others/QuadProg++.hh"
using namespace quadprogpp;



//@brief Used to find the estimated utility vector by max-min
//@param V          All the hyperplanes which bounds the possible utility range
//@return           The estimated utility vector
point_t *find_estimate(std::vector<point_t *> V);


//@brief Used to normalize the hyperplane so that ||H||=1
//@param hyper      The hyperplane
void hyperplane_nomarlize(hyperplane *hyper);


//@brief Used to normalized the point so that ||P||=1
//@param            The point
void point_nomarlize(point_t *p);


//@brief Used to calculate the cos() of angle of two vectors
//@param h1         The vector
//@param h2         The vector
//@return           The cos() of the angle
double cosine0(double *h1, double *h2, int dim);


//@brief Used to calculate the orthogonality of two vectors. 1 - |cos()|
//@param h1         The vector
//@param h2         The vector
//@return           The orthogonality
double orthogonality(double *h1, double *h2, int dim);


//@brief Used to calculate the largest orthogonality of the spherical cap w.r.t a vector
//@param n          The vector
//@param node       The spherical cap
//@return           The largest orthogonality
double upper_orthog(point_t *n, s_node *node);


//@brief Used to calculate the smallest orthogonality of the spherical cap w.r.t a vector
//@param n          The vector
//@param node       The spherical cap
//@return           The smallest orthogonality
double lower_orthog(point_t *n, s_node *node);


//@brief Used to classified the hyperplanes into L clusters by k-means
//         Note that by re-assign hyperplane into clusters, the number of clusters may <L finally
//@param hyper      All the hyperplanes
//@param clu        All the clusters obtained
void k_means_cosine(std::vector<hyperplane *> hyper, std::vector<cluster_t *> &clu);


//@brief Used to build the sphereical cap
//       1. Find the representative vector  2. Set the cos()
//@param            The spherical node
void cap_construction(s_node *node);


//@brief Used to build the spherical tree
//@param hyper      All the hyperplanes
//@param node       The node of the tree. For user, only set the root node to call this function
void build_spherical_tree(std::vector<hyperplane *> hyper, s_node *node);


//brief Used to prune the impossible spherical caps for searching
//@param q          The searching utility vector
//@param S          The spherical caps for searching
//@param Q          The spherical caps refined
void spherical_cap_pruning(point_t *q, std::vector<s_node *> S, std::vector<s_node *> &Q);


//@brief Used to find the hyperplane asking question through spherical tree based on estimated u
//@param node       The root of spherical tree
//@param q          The estimated u
//@param best       The best hyperplane found so far. For user, set best=NULL to call this function
//@return   The hyperplane used to ask user question
hyperplane *orthogonal_search(s_node *node, point_t *q, hyperplane *best);



point_t* PreferenceLearning(point_set *originalSet, point_set *realSet, point_t *u, int k, std::ofstream &fp);


#endif //RUN_PREFERENCELEARNING_H
