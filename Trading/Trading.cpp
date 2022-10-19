/**
 * @file Trading.cpp
 * @author Thomas Laughridge (tcl5tu@virginia.edu)
 * @brief Closest Pair of Points Implementation
 * @version 0.1
 * @date 2022-10-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Point Object
struct Point {
    float x, y;
};

// Compare two points by y coordinate -- Solution found on StackOverflow (https://stackoverflow.com/questions/1380463/sorting-a-vector-of-custom-objects)
struct compareY {
    inline bool operator() (const Point& p1, const Point& p2) {
        return (p1.y < p2.y);
    }
};

// Compare two points by x coordinate -- Solution found on StackOverflow (https://stackoverflow.com/questions/1380463/sorting-a-vector-of-custom-objects)
struct compareX {
    inline bool operator() (const Point& p1, const Point& p2) {
        return (p1.x < p2.x);
    }
};

// Read Input
void readInput(vector<Point>& input, int size) {
    input.empty();
    for (int i = 0; i < size; i++) {
        float x, y;
        cin >> x >> y;
        Point p = {x, y};
        input.push_back(p);
    }
}

// X and Y Distance
float distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

// Brute force method
float bruteForce(vector<Point> input) {
    float min = distance(input[0], input[1]);
    for (int i = 0; i < input.size(); i++) {
        for (int j = i + 1; j < input.size(); j++) {
            float d = distance(input[i], input[j]);
            if (d < min) {
                min = d;
            }
        }
    }
    return min;
}

// Closest points in strip
float closestInStrip(vector<Point> strip, int size, float width) {
    float min = width;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; j++) {
            if (distance(strip[i], strip[j]) < min) {
                min = distance(strip[i], strip[j]);
            }
        }
    }
    return min;
}

// Recursive helper method to find smallest distance
float closestRecurse(vector<Point> sortedX, vector<Point> sortedY, int size) {
    if (size <= 3) {
        return bruteForce(sortedX);
    }
    
    int mid = size / 2;
    Point midPoint = sortedX[mid];

    vector<Point> sortedYLeft, sortedYRight;
    for (int i = 0; i < size; i++) {
        if (sortedY[i].x <= midPoint.x) {
            sortedYLeft.push_back(sortedY[i]);
        } else {
            sortedYRight.push_back(sortedY[i]);
        }
    }

    float wleft = closestRecurse(sortedX, sortedYLeft, mid);
    sortedX.push_back(midPoint);
    float wright = closestRecurse(sortedX, sortedYRight, size - mid);

    float width = std::min(wleft, wright);

    vector<Point> strip;
    for (int i = 0; i < size; i++) {
        if (abs(sortedY[i].x - midPoint.x) < width) {
            strip.push_back(sortedY[i]);
        }
    }

    return std::min(width, closestInStrip(strip, strip.size(), width));
}

// Find closest pair of points
float closest(vector<Point> input, int size) {
    vector<Point> sortedX = input;
    vector<Point> sortedY = input;

    std::sort(sortedX.begin(), sortedX.end(), compareX());
    std::sort(sortedY.begin(), sortedY.end(), compareY());
    
    return closestRecurse(sortedX, sortedY, size);
}

int main() {

    // auto start = high_resolution_clock::now();

    int size = -1;
    while (size != 0) {

        cin >> size;
        if (size == 0) {
            break;
        }

        vector<Point> input;
        readInput(input, size);
        int size = sizeof(input) / sizeof(input[0]);
        float result = closest(input, size);

        if (result > 10000) {
            cout << "infinity" << endl;
        } else {
            cout << fixed << setprecision(4) << result << endl;
        }
    }

    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<milliseconds>(stop - start);
    // cout << endl << "Operation took: " << duration.count() << " milliseconds" << endl;

    return 0;
}