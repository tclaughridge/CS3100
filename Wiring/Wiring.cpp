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
#include "Edge.h"

using namespace std;


struct Compare {
    // For use in the Priority Queue Data Structure -- Taken from Stack Overflow
    // https://stackoverflow.com/questions/48840649/constructing-a-priority-queue-of-vectors?newreg=d1d8e282251647d29481c1ecf10f2e0c
    bool operator()(Edge* const& a, Edge* const& b) { 
        return a->cost > b->cost;
    }
};


bool preSwitch(Node* n) {
    if (n->type == 'b' || n->type == 'j' || n->type == 'o') {
        return true;
    }
    return false;
}
bool postSwitch(Node* n) {
    if (n->type == 'l') {
        return true;
    }
    return false;
}
bool isSwitch(Node* n) {
    if (n->type == 's') {
        return true;
    }
    return false;
}


bool isConnectible(Edge* e) {
    if (preSwitch(e->from) && isSwitch(e->to)) {
        return true;
    }
    if (preSwitch(e->to) && isSwitch(e->from)) {
        return true;
    }


    if (isSwitch(e->from) && postSwitch(e->to)) {
        return true;
    }
    if (isSwitch(e->to) && postSwitch(e->from)) {
        return true;
    }


    if (postSwitch(e->to) && postSwitch(e->from)) {
        return true;
    }
    if (preSwitch(e->to) && preSwitch(e->from)) {
        return true;
    }
    if (isSwitch(e->to) && isSwitch(e->from)) {
        return true;
    }

    return false;
}


void readFile(vector<Node*>& nodes, vector<Edge*>& dependencies) {
    string in1, in2;
    cin >> in1 >> in2;

    int j = stoi(in1);
    int c = stoi(in2);

    for (int i = 0; i < j; i++) {
        string in3, in4;
        cin >> in3 >> in4;

        Node* node = new Node();
        node->name = in3;
        node->visited = false;
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

        Edge* e = new Edge();
        for (int i = 0; i < nodes.size(); i++){
            if (nodes[i]->name == in5) {
                e->from = nodes[i];
            }
            if (nodes[i]->name == in6) {
                e->to = nodes[i];
            }
        }
        e->cost = stoi(in7);

        if (isConnectible(e)) {
            dependencies.push_back(e);
        }
    }

    for (int i = 0; i < nodes.size(); i++) {
        for (int j = 0; j < dependencies.size(); j++) {
            if (dependencies[j]->from == nodes[i]) {
                nodes[i]->edges.push_back(dependencies[j]->from->name + dependencies[j]->to->name);
            }
        }

        if (nodes[i]->type == 'l') {
            for (int j = 0; j < dependencies.size(); j++) {
                if (dependencies[j]->from->type == 's' && dependencies[j]->to == nodes[i]) {
                    nodes[i]->whichSwitch = dependencies[j]->from;
                }
            }
        }
    }
}


void addEdges(Node*& n, priority_queue<Edge*, vector<Edge*>, Compare>& pq, vector<Edge*> dependencies) {
    n->visited = true;

    for (int i = 0; i < dependencies.size(); i++) {
        if (dependencies[i]->from == n && dependencies[i]->to->visited == false) {
            pq.push(dependencies[i]);
        }
        if (dependencies[i]->to == n && dependencies[i]->from->visited == false) {
            pq.push(dependencies[i]);
        }
    }
}


void prims(int& mstWeight, vector<Edge*>& mst, vector<Edge*> dependencies, Node* start) {
    priority_queue<Edge*, vector<Edge*>, Compare> pq;
    addEdges(start, pq, dependencies);

    while (!pq.empty()) {
        Edge* e = pq.top();
        pq.pop();

        if (e->from->visited == false) {
            mst.push_back(e);
            mstWeight += e->cost;
            addEdges(e->from, pq, dependencies);
        }
        if (e->to->visited == false) {
            mst.push_back(e);
            mstWeight += e->cost;
            addEdges(e->to, pq, dependencies);
        }
    }
}



int main() {
    vector<Node*> nodes;
    vector<Edge*> dependencies;

    readFile(nodes, dependencies);


    // Prims for PreSwitches
    int preSwitchCost = 0;
    vector<Edge*> preSwitchMST;
    vector<Edge*> preSwitchDependencies;
    Node* start = nodes[0];

    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i]->type == 'b') {
            start = nodes[i];
        }
    }

    for (int i = 0; i < dependencies.size(); i++) {
        if (preSwitch(dependencies[i]->from) && preSwitch(dependencies[i]->to)) {
            preSwitchDependencies.push_back(dependencies[i]);
        }
    }

    prims(preSwitchCost, preSwitchMST, preSwitchDependencies, start);

    // --------------------------------------------------------------------------------------------------------------------------------------------

    // Prims for Switches
    int switchCost = preSwitchCost;
    vector<Edge*> switchMST = preSwitchMST;
    vector<Edge*> switchDependencies = preSwitchDependencies;
    
    vector<Edge*> switches;
    for (int i = 0; i < dependencies.size(); i++) {
        if (dependencies[i]->from->type == 's' || dependencies[i]->to->type == 's') {
            switches.push_back(dependencies[i]);
        }
    }

    // for (int i = 0; i < switches.size(); i++) {
    //     if (switches[i]->from->type == 's') {
    //         start = switches[i]->from;
    //     }
    //     if (switches[i]->to->type == 's') {
    //         start = switches[i]->to;
    //     }
    // }

    for (int i = 0; i < dependencies.size(); i++) {
        if ((isSwitch(dependencies[i]->from) && preSwitch(dependencies[i]->to)) || (isSwitch(dependencies[i]->to) && preSwitch(dependencies[i]->from))) {
            switchDependencies.push_back(dependencies[i]);
        }
    }

    for (int i = 0; i < dependencies.size(); i++) {
        if ((postSwitch(dependencies[i]->from) && isSwitch(dependencies[i]->to)) || (postSwitch(dependencies[i]->to) && isSwitch(dependencies[i]->from))) {
            switchDependencies.push_back(dependencies[i]);
        }
        if (postSwitch(dependencies[i]->from) && postSwitch(dependencies[i]->to)) {
            switchDependencies.push_back(dependencies[i]);
        }
    }

    prims(switchCost, switchMST, switchDependencies, start);






    cout << switchCost + 1 << endl;

    // print mst
    // for (int i = 0; i < switchMST.size(); i++) {
    //     cout << switchMST[i]->from->name << " " << switchMST[i]->to->name << " " << switchMST[i]->cost << " ---> ";
    // }
    // cout << endl;

    return 0;
}