/**
 * @file graph.h
 * @author Thomas Laughridge (tcl5tu@virginia.edu)
 * @version 0.1
 * @date 2022-08-29
 */

#ifndef graph_h
#define graph_h

#include <vector>
#include "node.h"

class graph {
public:
    graph();
    vector<node*> vec;
    void addNode(node* n);
    node* getNode(int i);
    int size();
    vector<node*> generateAdj(node* n);
    void print();
};

#endif