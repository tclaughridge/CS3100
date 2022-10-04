/**
 * @file Wiring.cpp
 * @author Thomas Laughridge (tcl5tu@virginia.edu)
 * @brief Main file for the UVA CS3100 Wiring Assignment
 * @version 0.1
 * @date 2022-09-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

#include "Node.h"

using namespace std;

struct Compare {
    // For use in the Priority Queue Data Structure -- Taken from Stack Overflow
    // https://stackoverflow.com/questions/48840649/constructing-a-priority-queue-of-vectors?newreg=d1d8e282251647d29481c1ecf10f2e0c
    bool operator()(vector<string> const & a, vector<string> const & b) { 
        return stoi(a[2]) > stoi(b[2]);
    }
};

bool meetsRequirements(vector<string> dep) {
    // Checks if the dependency is valid

    if (dep[0].front() == 'o' && dep[1].front() == 'l') {
        return false;
    }

    return true;
}

void readFile(vector<Node*>& nodes, vector<vector<string> >& dependencies) {
    string in1, in2;
    cin >> in1 >> in2;

    int j = stoi(in1);
    int c = stoi(in2);

    for (int i = 0; i < j; i++) {
        string in3, in4;
        cin >> in3 >> in4;

        Node* node = new Node();
        node->name = in3;
        switch (in3[0]) {
            // Breaker
            case 'b':
                node->type = 'b';
                break;

            // Switch
            case 's':
                node->type = 's';
                break;

            // Light
            case 'l':
                node->type = 'l';
                break;
            
            // Outlet
            case 'o':
                node->type = 'o';
                break;
            
            // Junction
            case 'j':
                node->type = 'j';
                break;
        }
        nodes.push_back(node);
    }

    for (int i = 0; i < c; i++) {
        string in5, in6, in7;
        cin >> in5 >> in6 >> in7;
        vector<string> dep;
        dep.push_back(in5);
        dep.push_back(in6);
        dep.push_back(in7);
        if(meetsRequirements(dep)) {
            dependencies.push_back(dep);
        }
    }
}

unordered_map<Node*, vector<Node*> > buildGraph(vector<Node*> nodes, vector<vector<string> > dependencies) {
    unordered_map<Node*, vector<Node*> > graph;

    for (int i = 0; i < nodes.size(); i++) {
        graph.insert(make_pair(nodes[i], vector<Node*>()));
    }

    for (int i = 0; i < dependencies.size(); i++) {
        unordered_map<Node*, vector<Node*> >::iterator itr;
        for (itr = graph.begin(); itr != graph.end(); itr++) {
            if (itr->first->name == dependencies[i][0]) {
                for (int j = 0; j < nodes.size(); j++) {
                    if (nodes[j]->name == dependencies[i][1]) {
                        itr->second.push_back(nodes[j]);
                    }
                }
            }
            if (itr->first->name == dependencies[i][1]) {
                for (int j = 0; j < nodes.size(); j++) {
                    if (nodes[j]->name == dependencies[i][0]) {
                        itr->second.push_back(nodes[j]);
                    }
                }
            }
        }
    }

    return graph;
}

vector<Node*> generateAdj(Node* node, unordered_map<Node*, vector<Node*> > graph) {
    vector<Node*> adj;
    unordered_map<Node*, vector<Node*> >::iterator itr;
    for (itr = graph.begin(); itr != graph.end(); itr++) {
        if (itr->first->name == node->name) {
            for (int i = 0; i < itr->second.size(); i++) {
                adj.push_back(itr->second[i]);
            }
        }
    }
    return adj;
}

void addEdges(std::priority_queue<vector<string>, vector<vector<string> >, Compare>& pq, vector<vector<string> > dependencies, Node*& node, unordered_map<Node*, vector<Node*> > graph) {
    node->visited = true;

    vector<Node*> adj = generateAdj(node, graph);
    for (int i = 0; i < dependencies.size(); i++) {
        if (dependencies[i][0] == node->name) {
            for (int j = 0; j < adj.size(); j++) {
                if (dependencies[i][1] == adj[j]->name && adj[j]->visited == false) {
                    vector<string> edge;
                    edge.push_back(dependencies[i][0]);
                    edge.push_back(dependencies[i][1]);
                    edge.push_back(dependencies[i][2]);
                    pq.push(edge);
                }
            }
        }
    }
}

int generateMST(vector<Node*> nodes, vector<vector<string> > dependencies, unordered_map<Node*, vector<Node*> > graph, vector<Node*>& mst) {
    int sumMST, edgeCount = 0;
    int m = nodes.size() - 1;
    std::priority_queue<vector<string>, vector<vector<string> >, Compare> pq;

    for (int i = 0; i < nodes.size(); i++) {
        addEdges(pq, dependencies, nodes[i], graph);
    }
    for (int i = 0; i < pq.size(); i++) {
        cout << pq.top()[0] << " " << pq.top()[1] << " " << pq.top()[2] << endl;
        pq.pop();
    }


    addEdges(pq, dependencies, nodes[0], graph);
    mst.push_back(nodes[0]);

    while((!pq.empty()) && (edgeCount != m)) {
        vector<string> edge = pq.top();
        pq.pop();

        Node* curr;
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i]->name == edge[1]) {
                curr = nodes[i];
            }
        }

        if (curr->visited) {
            continue;
        }
        edgeCount++;
        mst.push_back(curr);
        sumMST += stoi(edge[2]);

        addEdges(pq, dependencies, curr, graph);
    }
    if (edgeCount != m) {
        return -1;
    }

    return sumMST;
}

int main() {
    // Initialize
    vector<Node*> nodes;
    vector<vector<string> > dependencies;

    // Read input file
    readFile(nodes, dependencies);

    // Build graph
    unordered_map<Node*, vector<Node*> > graph = buildGraph(nodes, dependencies);

    // Generate and sum MST
    vector<Node*> tree;
    int MST = generateMST(nodes, dependencies, graph, tree);
    if (MST == -1) {
        cout << "No Minimum Spanning Tree Exists" << endl;
    } else {
        cout << MST << endl;
    }

    return 0;
}