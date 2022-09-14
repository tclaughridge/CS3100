/**
 * @file node.cpp
 * @author Thomas Laughridge (tcl5tu@virginia.edu)
 * @version 0.1
 * @date 2022-08-29
 */

#include <iostream>
#include <string>
#include "node.h"

using namespace std;

node::node() {
    next = NULL;
    value = "";
    temp = false;
    perm = false;
}
