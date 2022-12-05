/**
 * @file Moving.cpp
 * @author Thomas Laughridge (tcl5tu@virginia.edu)
 * @brief Moving Boxes Implementation
 * @version 0.1
 * @date 2022-10-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

struct Compare {
    bool operator()(vector<string> const & a, vector<string> const & b) { 
        return stoi(a[1]) > stoi(b[1]); 
    }
};

int main() {
    int numCases;
    cin >> numCases;

    for (int i = 0; i < numCases; i++) {
        vector<vector<string> > input;
        int b, m, c;
        cin >> b >> m >> c;
        for (int j = 0; j < c; j++) {
            vector<string> temp;
            string name, x, y;
            cin >> name >> x >> y;
            temp.push_back(name);
            temp.push_back(x);
            temp.push_back(y);
            input.push_back(temp);
        }
        int ship = b - m;

        priority_queue<vector<string>, vector<vector<string> >, Compare> pq;

        for (int j = 0; j < input.size(); j++) {

            string name = input[j][0];
            int one = stoi(input[j][1]);
            int half = stoi(input[j][2]);
            int cost = 0;

            vector<string> company;
            company.push_back(name);


            // WHILE LOOP HERE

            
            company.push_back(to_string(cost));
            pq.push(company);
        }

        cout << endl;
        cout << "Case " << i + 1 << endl;
        cout << "---------------------------------" << endl;
        while(!pq.empty()) {
            vector<string> temp = pq.top();
            cout << temp[0] << " " << temp[1] << endl;
            pq.pop();
        }
        pq.empty();
    }

    return 0;
}