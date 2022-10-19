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
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// Min of two floats
float min(float x, float y) { 
    return (x < y)? x : y; 
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

// Closest points in strip
float closestInStrip(vector<Point> strip, int size, float width) {
    float min = width;
    std::sort(strip.begin(), strip.end(), compareY());

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
float closestRecurse(vector<Point> input, int size) {
    if (size <= 3) {
        return bruteForce(input);
    }
    
    int mid = size / 2;
    Point midPoint = input[mid];

    float wleft = closestRecurse(input, mid);
    input.push_back(midPoint);
    float wright = closestRecurse(input, size - mid);

    float width = min(wleft, wright);

    vector<Point> strip;
    for (int i = 0; i < size; i++) {
        if (abs(input[i].x - midPoint.x) < width) {
            strip.push_back(input[i]);
        }
    }

    return min(width, closestInStrip(strip, strip.size(), width));
}

// Find closest pair of points
float closest(vector<Point> input, int n) {
    std::sort(input.begin(), input.end(), compareX());
    return closestRecurse(input, n);
}

int main() {
    auto start = high_resolution_clock::now();

    int size = -1;
    while (size != 0) {

        cin >> size;
        cout << size << endl;
        if (size == 0) {
            break;
        }

        vector<Point> input;
        readInput(input, size);
        int s = sizeof(input) / sizeof(input[0]);
        float result = closest(input, s);

        if (result > 10000) {
            cout << "infinity" << endl;
        } else {
            cout << fixed << setprecision(4) << result << endl;
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << endl << "Operation took: " << duration.count() << " microseconds" << endl;

    return 0;
}