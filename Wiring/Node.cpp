#include <iostream>
#include <string>
#include <vector>
#include "Node.h"

using namespace std;

Node::Node() {
    type = ' ';
    name = "";
    cost = 0;
    visited = false;
    parent = NULL;

    whichSwitch = NULL;

    edges = vector<string>();
}