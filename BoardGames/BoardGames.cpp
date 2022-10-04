/**
 * @file BoardGames.cpp
 * @author Thomas Laughridge (tcl5tu@virginia.edu)
 * @version 0.1
 * @date 2022-09-07
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

void reverseStr(string& str) {
    int n = str.length();
    for (int i = 0; i < n / 2; i++) {
        swap(str[i], str[n - i - 1]);
    }
}

vector<string> readFile() {
    vector<string> lines;
    lines.push_back("");
    lines.push_back("");
    cin >> lines[0];
    cin >> lines[1];
    int nodes = stoi(lines[0]);
    int edges = stoi(lines[1]);

    for (int i = 0; i < edges; i++) {
        string td, td2;
        cin >> td;
        cin >> td2;
        td += " " +td2;
        lines.push_back(td);
    }

    string dangerous;
    cin >> dangerous;
    lines.push_back(dangerous);
    for (int i = 0; i < stoi(dangerous); i++) {
        string td;
        cin >> td;
        lines.push_back(td);
    }
    return lines;
}

unordered_map<int, vector<int> > generateAdjList(vector<string> v, int nodes, int edges) {
    unordered_map<int, vector<int> > adjList;

    for (int i = 0; i < nodes; i++) {
        adjList.insert(make_pair(i, vector<int>()));
    }
    for (int i = 2; i < edges+2; i++) {
        string front = v[i].substr(0, v[i].find(" "));
        string back = v[i].substr(v[i].find(" ") + 1, v[i].length());
        int k = stoi(back);
        int l = stoi(front);
        if (!count(adjList[stoi(front)].begin(), adjList[stoi(front)].end(), k)) {
            adjList[stoi(front)].push_back(k);
        }
        if (!count(adjList[stoi(back)].begin(), adjList[stoi(back)].end(), l)) {
            adjList[stoi(back)].push_back(l);
        }
    }

    return adjList;
}

void printGraph(unordered_map<int, vector<int> > adjList) {
    for (unordered_map<int, vector<int> >::iterator i = adjList.begin(); i != adjList.end(); i++) {
        cout << i->first << " -> ";
        for (int j = 0; j < i->second.size(); j++) {
            cout << i->second[j] << " ";
        }
        cout << endl;
    }
}

vector<int> generateAdj(unordered_map<int, vector<int> > graph, int node) {
    vector<int> ret = graph.at(node);
    std::sort(ret.begin(), ret.end());
    return ret;
}

void dfs(unordered_map<int, vector<int> > graph, int node, int targetNode, vector<int> visited, vector<int> danger, vector<string> path, vector<vector<string> >& out) {
    visited.push_back(node);
    path.push_back(to_string(node));

    if (node == targetNode) {
        out.push_back(path);
        path.clear();
    }
    vector<int> temp = generateAdj(graph, node);
    for (int i = 0; i < temp.size(); i++) {
        if (!std::count(visited.begin(), visited.end(), temp[i])) {
            if (!std::count(danger.begin(), danger.end(), temp[i])) {
                dfs(graph, temp[i], targetNode, visited, danger, path, out);
            }
        }
    }
}

int main() {

    // Read file into vector
    vector<string> lines = readFile();
    int nodes = stoi(lines[0]);
    int edges = stoi(lines[1]);

    // Generate graph
    unordered_map<int, vector<int> > graph = generateAdjList(lines, nodes, edges);

    // Generate dangerous nodes
    vector<int> dangerousNodes;
    for (int i = edges + 3; i < lines.size(); i++) {
        dangerousNodes.push_back(stoi(lines[i]));
    }

    // Print graph
    printGraph(graph);
    cout << "-----------------" << endl;

    // Generate path
    vector<vector<string> > path;
    dfs(graph, 0, nodes-1, vector<int>(), dangerousNodes, vector<string>(), path);

    for (int i = 0; i < path.size(); i++) {
        for (int j = 0; j < path[i].size(); j++) {
            if (j != path[i].size() - 1) {
                cout << path[i][j] << "-";
            } else {
                cout << path[i][j];
            }
        }
        cout << endl;
    }

    return 0;
}