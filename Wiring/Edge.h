#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

class Edge {
public:
    Edge();
    
    Node* from;
    Node* to;
    int cost;
    bool visited;
};

#endif