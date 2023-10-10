#include "util.h"

// easier to test edge detection on large matrix and I didn't want to type the entire thing out, so I made this
vector<vector<double>> matrix_image_expander(vector<vector<double>> matrix_to_expand, int scale) {
    int m = (int) matrix_to_expand.size();
    int n = (int) matrix_to_expand[0].size();
    vector<vector<double>> new_matrix(m*scale, vector<double>(n*scale, 0)); // fill the vector

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < pow(scale, 2); k++) {
                // goofy matrix maths because I didn't want to have 4 nested for loops
                int x = (i*scale) + (k%scale);
                int y = (j*scale) + ((int) floor(k/scale));
                new_matrix[y][x] = matrix_to_expand[j][i];
            }
        }
    }

    return new_matrix;
}