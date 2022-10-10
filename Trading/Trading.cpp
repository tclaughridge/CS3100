/**
 * @file Trading.cpp
 * @author Thomas Laughridge (tcl5tu@virginia.edu)
 * @version 0.1
 * @date 2022-10-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void readInput(vector<pair<float, float> >& input, int size) {
    input.empty();
    for (int i = 0; i < size; i++) {
        float x, y;
        cin >> x >> y;
        input.push_back(make_pair(x, y));
    }
}

float findMin(vector<pair<float, float> >& input) {
    float min = 0;
    for (int i = 0; i < input.size(); i++) {
        if (input[i].first < input[min].first) {
            min = i;
        }
    }
    return min;
}

int closestPoints() {
    return 0;
}

int main() {

    int size = -1;
    while (size != 0) {

        cin >> size;
        if (size == 0) {
            break;
        }

        vector<pair<float, float> > input;
        readInput(input, size);
    }

    return 0;
}