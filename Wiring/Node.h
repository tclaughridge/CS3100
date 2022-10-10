#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node {
public:
    Node();
    
    char type;
    string name;
    int cost;
    bool visited;
    Node* parent;

    Node* whichSwitch;

    vector<string> edges;
};

#endif