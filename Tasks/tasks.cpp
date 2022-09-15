/**
 * @file tasks.cpp
 * @author Thomas Laughridge (tcl5tu@virginia.edu)
 * @version 0.1
 * @date 2022-09-15
 * @copyright Copyright (c) 2022
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>
#include <algorithm>

using namespace std;

unordered_map<string, vector<string> > generateAdjList(vector<string> nodesIn, vector<string> edgesIn, int nodes, int edges) {
    unordered_map<string, vector<string> > adjList;

    for (int i = 0; i < nodes; i++) {
        vector<string> temp;
        for (int j = 0; j < edges; j++) {
            string front = edgesIn[j].substr(0, edgesIn[j].find(" "));
            string back = edgesIn[j].substr(edgesIn[j].find(" ") + 1, edgesIn[j].length());
            if (front == nodesIn[i]) {
                temp.push_back(back);
            }
        }
        adjList.insert(make_pair(nodesIn[i], temp));
    }

    return adjList;
}

vector<string> generateAdj(unordered_map<string, vector<string> > graph, string node) {
    return graph.at(node);
}

vector<string> noIncoming(vector<string> Nodes, vector<string> Edges) {
    vector<string> noIncoming;
    for (int i = 0; i < Nodes.size(); i++) {
        bool incoming = false;
        for (int j = 0; j < Edges.size(); j++) {
            string front = Edges[j].substr(0, Edges[j].find(" "));
            string back = Edges[j].substr(Edges[j].find(" ") + 1, Edges[j].length());
            if (back == Nodes[i]) {
                incoming = true;
            }
        }
        if (!incoming) {
            noIncoming.push_back(Nodes[i]);
        }
    }
    return noIncoming;
}


void topologicalSortUtil(unordered_map<string, vector<string> > graph , string node, vector<string>& visited, stack<string>& Stack) {

    visited.push_back(node);

    vector<string> adj = generateAdj(graph, node);
    for (int i = 0; i < adj.size(); i++) {
        if (find(visited.begin(), visited.end(), adj[i]) == visited.end()) {
            topologicalSortUtil(graph, adj[i], visited, Stack);
        }
    }
    Stack.push(node);
}
 
void topologicalSort(unordered_map<string, vector<string> > graph, vector<string>& visited, string node) {
    stack<string> Stack;

    for (auto i : graph) {
        if (count(visited.begin(), visited.end(), i.first) == 0) {
            topologicalSortUtil(graph, i.first, visited, Stack);
        }
    }
 

    while (Stack.empty() == false) {
        cout << Stack.top() << " ";
        Stack.pop();
    }
    cout << endl;
}

int main() {
    string param1, param2;
    cin >> param1 >> param2;

    int nodes = stoi(param1);
    int edges = stoi(param2);

    vector<string> nodesIn;
    vector<string> edgesIn;

    for (int i = 0; i < nodes; i++) {
        string node;
        cin >> node;
        nodesIn.push_back(node);
    }
    for (int i = 0; i < edges; i++) {
        string edge1, edge2, edge;
        cin >> edge1 >> edge2;
        edge = edge1 + " " + edge2;
        edgesIn.push_back(edge);
    }

    // Make graph
    unordered_map<string, vector<string> > graph = generateAdjList(nodesIn, edgesIn, nodes, edges);
    
    // Traverse graph
    vector<string> visited;
    topologicalSort(graph, visited, nodesIn[0]);

    return 0;
}