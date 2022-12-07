#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <utility>
#include <algorithm>

using namespace std;

struct Compare {
    bool operator()(vector<string> const & a, vector<string> const & b) { 
        return stoi(a[1]) > stoi(b[1]); 
    }
};

void readInput(int &toMove, int &toTake, int &companies, vector<vector<string> > &companyList) {
    cin >> toMove >> toTake >> companies;

    for (int i = 0; i < companies; i++) {
        vector<string> company;
        string name, one, half;
        cin >> name >> one >> half;

        company.push_back(name);
        company.push_back(one);
        company.push_back(half);
        companyList.push_back(company);
    }
}

std::pair<string, int> core(vector<string> company, int toMove, int toTake) {
    int cost = 0;
    string name = company[0];
    int one = stoi(company[1]);
    int half = stoi(company[2]);

    while ((toMove - toTake) > toTake) {
        if (toMove % 2 == 0) {
            cost += half;
            toMove = (toMove / 2);
        } else {
            cost += half;
            toMove = ((toMove - 1) / 2);
        }
    }
    toMove -= toTake;
    cost += (toMove * one);

    std::pair<string, int> result = make_pair(name, cost);
    return result;
}

bool sortbysec(const pair<string,int> &a, const pair<string,int> &b) {
    if (a.second == b.second) {
        return (a.first < b.first);
    } else {
        return (a.second < b.second);
    }
}

int main() {
    int cases;
    cin >> cases;

    for (int i = 0; i < cases; i++) {
        int toMove, toTake, companies;
        vector<vector<string> > companyList;
        readInput(toMove, toTake, companies, companyList);

        vector<std::pair<string, int> > result;

        for (int j = 0; j < companyList.size(); j++) {
            std::pair<string, int> company = core(companyList[j], toMove, toTake);
            result.push_back(company);
        }

        cout << "Case " << i + 1 << endl;
        std::sort(result.begin(), result.end(), sortbysec);
        for (int j = 0; j < result.size(); j++) {
            cout << result[j].first << " " << result[j].second << endl;
        }
    }

    return 0;
}
