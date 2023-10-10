
#ifndef BLURRER_IMAGE_CONVERSIONS_H
#define BLURRER_IMAGE_CONVERSIONS_H

#include <vector>
#include <iostream>
using namespace std;

extern const vector<vector<double>> box_blur;
extern const vector<vector<double>> gaussian_blur;
extern const vector<vector<double>> edge_detection;
extern const vector<vector<double>> sharpen;
void print_bb();

#endif //BLURRER_IMAGE_CONVERSIONS_H
