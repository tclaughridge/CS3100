/**
 * @file graph.cpp
 * @author Thomas Laughridge (tcl5tu@virginia.edu)
 * @version 0.1
 * @date 2022-08-29
 */

#include <iostream>
#include <vector>
#include "graph.h"

using namespace std;

vector<node*> vec;

graph::graph() {}

void graph::addNode(node* n) {
    vec.push_back(n);
}

node* graph::getNode(int i) {
    return vec[i];
}

int graph::size() {
    return vec.size();
}

vector<node*> graph::generateAdj(node* n) {
    vector<node*> adj;
    while (n->next != NULL) {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i]->value == n->next->value) {
                adj.push_back(vec[i]);
            }
        }
        n = n->next;
    }
    return adj;
}

// Print method for checking graph (BROKEN)
void graph::print() {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i]->value;
        while (vec[i]->next != NULL) {
            cout << " -> " << vec[i]->next->value;
            vec[i] = vec[i]->next;
        }
        cout << endl;
    }
}