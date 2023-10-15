
#ifndef BLURRER_IMAGE_CONVERSIONS_H
#define BLURRER_IMAGE_CONVERSIONS_H

#include <vector>
#include <iostream>
using namespace std;

extern const vector<vector<double>> box_blur;
extern const vector<vector<double>> gaussian_blur;
extern const vector<vector<double>> big_gaussian_blur;
extern const vector<vector<double>> edge_detection;
extern const vector<vector<double>> sharpen;
extern const vector<vector<vector<double>>> kernel_array;
void print_bb();

#endif //BLURRER_IMAGE_CONVERSIONS_H
