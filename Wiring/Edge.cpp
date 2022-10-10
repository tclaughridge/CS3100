#include <iostream>
#include <string>
#include "Edge.h"

using namespace std;

Edge::Edge() {
    from = NULL;
    to = NULL;
    cost = 0;
    visited = false;
}