/**
 * @file node.h
 * @author Thomas Laughridge (tcl5tu@virginia.edu)
 * @version 0.1
 * @date 2022-08-29
 */

#ifndef node_h
#define node_h

#include <iostream>
using namespace std;

class node {
public:
    node();
    node* next;
    std::string value;
    bool temp, perm;
};

#endif