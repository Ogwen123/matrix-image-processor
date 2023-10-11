//
// Created by Owen on 10/10/2023.
//

#ifndef BLURRER_STARTING_MATRICES_H
#define BLURRER_STARTING_MATRICES_H
#include <vector>

using namespace std;

vector<vector<double>> one = { // supposed to look like a number 1
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

#endif //BLURRER_STARTING_MATRICES_H
