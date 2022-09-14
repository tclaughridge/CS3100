/**
 * @file tasks.cpp
 * @author Thomas Laughridge (tcl5tu@virginia.edu)
 * @version 0.1
 * @date 2022-08-29
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>

#include "graph.h"
#include "node.h"

using namespace std;

// FORWARD DECLARATIONS
vector<int> extractIntegers(string str);
void generateGraph(graph& g, int t, int d, vector<string> v);
void dfs(graph g, node* curr, list<node*>& out);

int main(int argc, char** argv) {

    graph g;
    int t, d;

    // VERIFY CORRECT INPUT
    if (argc != 2) {
        cout << "Must supply the input file name as the one and only parameter" << endl;
        exit(1);
    }

    // READ INPUT FILE
    ifstream input;
    vector<string> lines;
    input.open(argv[1]);
    string line;
    if (input.is_open()) {
        while (input) {
            std::getline (input, line);
            lines.insert(lines.end(), line);
        }
    } else { cout << "Couldn't open file\n"; }
    lines.pop_back();

    t = extractIntegers(lines.front())[0];
    d = extractIntegers(lines.front())[1];

    // GENERATE NODES AND DEPENDENCIES
    generateGraph(g, t, d, lines);

    // TOPOLOGICAL SORT
    list<node*> v;
    dfs(g, g.getNode(0), v);

    // PRINT OUTPUT
    for (list<node*>::iterator it = v.begin(); it != v.end(); it++) {
        cout << (*it)->value << " ";
    }
    cout << endl;

    return 0;
}

vector<int> extractIntegers(string str) {
    vector<int> vec;
    stringstream ss;
    ss << str;
 
    string temp;
    int found;
    while (!ss.eof()) {
        ss >> temp;
        if (stringstream(temp) >> found) {
            vec.push_back(found);
        }
        temp = "";
    }

    return vec;
}

void generateGraph(graph& g, int t, int d, vector<string> v) {
    // GENERATE NODES AND DEPENDENCIES
    for (int i = 1; i <= t; i++) {
        // Create new Nodes
        node* n = new node;
        n->value = v[i];
        g.addNode(n);

        for (int j = t+1; j < v.size(); j++) {
            // Create Node dependencies
            vector<string> dep;

            if (v[j].find(" ") != 0) {
                dep.push_back(v[j].substr(0, v[j].find(" ")));
                dep.push_back(v[j].substr(v[j].find(" ")+1, v[j].length()));
            }
            if (dep.front() == n->value) {
                n->next = new node;
                n->next->value = dep.back();
                n = n->next;
            }
        }
    }
}

void dfs(graph g, node* curr, list<node*>& out) {
    if (curr->perm == true) {
        // Sort Done
        return;
    } 
    else if (curr->temp == true) {
        // Cycle Exists
        cout << "IMPOSSIBLE" << endl;
        exit(1);
    } 
    else {
        // Recurse
        curr->temp = true;
        vector<node*> adj = g.generateAdj(curr);
        for (int i = 0; i < adj.size(); i++) {
            dfs(g, adj[i], out);
        }
        curr->temp = false;
        curr->perm = true;
        out.push_front(curr);
    }
}