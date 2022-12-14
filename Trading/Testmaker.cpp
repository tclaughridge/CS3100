/**
 * @file Testmaker.cpp
 * @author Thomas Laughridhe (tcl5tu)
 * @brief Program to create test cases for the Closest Pair of Points problem. Example usage: ./a.out 'filename.txt' 'number of points'
 * 
 */

#include <iostream>
#include <random>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {

    string filename = argv[1];
    int numpts = stoi(argv[2]);

    int LO = -50000;
    int HI = 50000;

    ofstream file(filename);

    // Write to the file
    file << numpts << endl;
    for (int i = 0; i < numpts; i++) {
        float r1 = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        float r2 = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        file << r1 << " " << r2 << endl;
    }
    file << 0;

    file.close();

    return 0;
}