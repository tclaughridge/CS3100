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
        vector<int> temp;
        for (int j = 0; j < edges + 2; j++) {
            string front = v[j].substr(0, v[j].find(" "));
            string back = v[j].substr(v[j].find(" ") + 1, v[j].length());
            if (front == to_string(i)) {
                int k = stoi(back);
                if (!std::count(temp.begin(), temp.end(), k)) {
                    temp.push_back(k);
                }
            }
        }
        adjList.insert(make_pair(i, temp));
    }
    return adjList;
}

vector<int> generateAdj(unordered_map<int, vector<int> > graph, int node) {
    vector<int> ret = graph.at(node);
    sort(ret.begin(), ret.end());
    return ret;
}

void dfs(unordered_map<int, vector<int> > graph, int node, int targetNode, vector<int> visited, vector<int> danger, string path, vector<string>& out) {
    visited.push_back(node);
    path += to_string(node);

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

    // Generate path
    vector<string> path;
    dfs(graph, 0, nodes-1, vector<int>(), dangerousNodes, "", path);

    for (int i = 0; i < path.size(); i++) {
        for (int j = 0; j < path[i].length(); j++) {
            if (j != path[i].length() - 1) {
                cout << path[i][j] << "-";
            } else {
                cout << path[i][j];
            }
        }
        cout << endl;
    }

    return 0;
}