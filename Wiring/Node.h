#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

using namespace std;

class Node {
public:
    Node();
    
    char type;
    string name;
    int cost;
    Node* next;
    bool visited;
};

#endif