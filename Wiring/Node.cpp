#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

Node::Node() {
    type = ' ';
    name = "";
    cost = 0;
    next = NULL;
    visited = false;
}