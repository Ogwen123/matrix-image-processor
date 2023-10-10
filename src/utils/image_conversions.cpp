#include "image_conversions.h"

//box blur
double box_value = (float) 1/ (float) 9;
const vector<vector<double>> box_blur = {
        {box_value, box_value, box_value},
        {box_value, box_value, box_value},
        {box_value, box_value, box_value}
};

// gaussian blur
double gaussian_value_1 = (float) 1 / (float) 4;
double gaussian_value_2 = (float) 1 / (float) 8;
double gaussian_value_3 = (float) 1 / (float) 16;
const vector<vector<double>> gaussian_blur = {
        {gaussian_value_3, gaussian_value_2, gaussian_value_3},
        {gaussian_value_2, gaussian_value_1, gaussian_value_2},
        {gaussian_value_3, gaussian_value_2, gaussian_value_3}
};

// edge detection
const vector<vector<double>> edge_detection = {
        {-1, -1, -1},
        {-1, 8, -1},
        {-1, -1, -1}
};

const vector<vector<double>> sharpen = {
        {0, -1, 0},
        {-1, 5, -1},
        {0, -1, 0}
};

void print_bb() { // debugging
    for (int i = 0; i < box_blur.size(); i++) {
        for (int j = 0; j < box_blur[0].size(); j++) {
            cout << box_blur[i][j];
        }
        cout << endl;
    }
}
