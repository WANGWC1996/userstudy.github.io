#include <algorithm>
#include <fstream>
#include <vector>
#include "PreferenceLearning/preferenceLearning.h"

point_set *normalize_points(std::vector<std::vector<double>> &points, std::vector<int> smallerBetter)
{
    int dim = points[0].size();
    point_set* norm_points = new point_set();
    std::vector<double> max_vals(dim, 0), min_vals(dim, INF);

    for(int i = 0; i < points.size(); ++i)
    {
        point_t* point = new point_t(dim, i);  // dim = dim, id = i
        for(int j = 0; j < dim; ++j)
        {
            double val = points[i][j];
            max_vals[j] = std::max(max_vals[j], val);
            min_vals[j] = std::min(min_vals[j], val);
            point->attr[j] = val;
        }
        norm_points->points.push_back(point);
    }

    for(int i = 0; i < points.size(); ++i)
    {
        for(int j = 0; j < dim; ++j)
        {
            double norm_val = (norm_points->points[i]->attr[j] - min_vals[j]) / (max_vals[j] - min_vals[j]);
            if(smallerBetter[j])
                norm_val = 1 - norm_val;
            norm_points->points[i]->attr[j] = norm_val;
        }
    }

    return norm_points;
}

class AlgorithmRunner {
public:
    int M, dim;
    point_set *points_norm;
    std::vector<point_t *> V;
    point_t *estimate_u;
    point_t *last_u;
    double accuracy = 0;
    int numOfQuestion = 1;
    point_set *pset;
    int p_idx, q_idx;


    AlgorithmRunner(std::vector<std::vector<double>> &candidates, std::vector<int> &smallerBetter, int cmp_option)
    {
        points_norm = normalize_points(candidates, smallerBetter); // all the new points

        /**
         * p_set: randomly choose 1000 points
         */
        pset = new point_set();
        if (points_norm->points.size() < 1000)
        {
            M = points_norm->points.size();
            for (int i = 0; i < M; i++)
                pset->points.push_back(points_norm->points[i]);
            pset->random(0.5);
        }
        else
        {
            int cco = 0;
            for (int i = 0; i < 1100; i++)
            {
                int ide = rand() % points_norm->points.size();
                bool is_same = false;
                for (int j = 0; j < pset->points.size(); j++)
                {
                    if (pset->points[j]->is_same(points_norm->points[ide]))
                    {
                        is_same = true;
                        break;
                    }
                }
                if (!is_same)
                {
                    pset->points.push_back(points_norm->points[ide]);
                    cco++;
                    if (cco >= 1000)
                    {
                        break;
                    }
                }
            }
            //point_random(p_set);
        }

        dim = pset->points[0]->dim;
        M = pset->points.size();


        //the normal vectors
        for (int i = 0; i < dim; i++)
        {
            point_t *b = new point_t(dim);
            for (int j = 0; j < dim; j++)
            {
                if (i == j)
                {
                    b->attr[j] = 1;
                } else
                {
                    b->attr[j] = 0;
                }
            }
            V.push_back(b);
        }

        //initial
        estimate_u = find_estimate(V);
        point_nomarlize(estimate_u);

        point_t* p_minus_q = new point_t(dim);
        double min = INF;
        for (int j = 0; j < pset->points.size(); j++)
        {
            for (int k = j + 1; k < pset->points.size(); k++)
            {
                for (int i = 0; i < dim; i++)
                {
                    p_minus_q->attr[i] = pset->points[j]->attr[i] - pset->points[k]->attr[i];
                }

                double v = cosine0(estimate_u->attr, p_minus_q->attr, dim);

                if (abs(v) < min)
                {
                    min = abs(v);
                    p_idx = j;
                    q_idx = k;
                }
                //std::cout << p_idx << "  " << q_idx << "  " << abs(v) <<"\n" ;
            }
        }
        delete p_minus_q;
    }



    int getNumQuestion()
    {
        return numOfQuestion;
    }

    ~AlgorithmRunner() {delete points_norm;}


    std::vector<int> nextPair()
    {
        std::vector<int> indices;
        indices.push_back(pset->points[p_idx]->id);
        indices.push_back(pset->points[q_idx]->id);
        return indices;
    }


    double choose(int option)
    {
        point_t *pt = new point_t(dim);
        if (option == 1)
        {
            for (int i = 0; i < dim; i++)
            {
                pt->attr[i] = pset->points[p_idx]->attr[i] - pset->points[q_idx]->attr[i];
            }
        }
        else
        {
            for (int i = 0; i < dim; i++)
            {
                pt->attr[i] = - pset->points[p_idx]->attr[i] + pset->points[q_idx]->attr[i];
            }
        }
        V.push_back(pt);
        estimate_u = find_estimate(V);
        for (int i = 0; i < dim; i++)
        {
            estimate_u->attr[i] = estimate_u->attr[i] < 0 ? 0 : estimate_u->attr[i];
        }
        point_nomarlize(estimate_u);
        if(numOfQuestion == 1)
            accuracy = 0;
        else
        {
            accuracy = cosine0(last_u->attr, estimate_u->attr, dim);
        }
        last_u = estimate_u;

        point_t* p_minus_q = new point_t(dim);
        double min = INF;
        for (int j = 0; j < pset->points.size(); j++)
        {
            for (int k = j + 1; k < pset->points.size(); k++)
            {
                for (int i = 0; i < dim; i++)
                {
                    p_minus_q->attr[i] = pset->points[j]->attr[i] - pset->points[k]->attr[i];
                }

                double v = cosine0(estimate_u->attr, p_minus_q->attr, dim);

                if (abs(v) < min)
                {
                    min = abs(v);
                    p_idx = j;
                    q_idx = k;
                }
            }
        }
        delete p_minus_q;
        numOfQuestion++;

        //std::cout << accuracy <<"\n";
        return accuracy;
    }


    std::vector<int> getRanking()
    {
        point_set *top_current = new point_set();
        pset->findTopk(estimate_u, pset->points.size() - 1, top_current);
        std::vector<int> indices;
        for(int i =0 ; i < top_current->points.size(); ++i)
            indices.push_back(top_current->points[i]->id);
        return indices;
    }

    //obtain the score of each point based on the learned preference
    std::vector<double> getScore()
    {
        point_set *top_current = new point_set();
        pset->findTopk(estimate_u, pset->points.size() - 1, top_current);
        std::vector<double> scores;
        for(int i =0 ; i < top_current->points.size(); ++i)
            scores.push_back(top_current->points[i]->dot_product(estimate_u));
        return scores;
    }
};




#ifdef EMSCRIPTEN

#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(my_module) {

    register_vector<int>("VectorInt");
    register_vector<double>("VectorDouble");
    register_vector<std::vector<double>>("VecVecDouble");

    class_<AlgorithmRunner>("AlgorithmRunner")
        .constructor<std::vector<std::vector<double>> &, std::vector<int> &, int>()
        .function("nextPair", &AlgorithmRunner::nextPair)
        .function("choose", &AlgorithmRunner::choose)
        .function("getNumQuestion", &AlgorithmRunner::getNumQuestion)
        .function("getRanking", &AlgorithmRunner::getRanking)
        .function("getScore", &AlgorithmRunner::getScore);
        ;


}

#else

int main() {

    return 0;
}

#endif
