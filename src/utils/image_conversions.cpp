#include "image_conversions.h"

const float box_blur[3][3] = {{1/9, 1/9, 1/9}, {1/9, 1/9, 1/9}, {1/9, 1/9, 1/9}};
const float gaussian_blur[3][3] = {{1/16, 1/8, 1/16}, {1/8, 1/4, 1/8}, {1/16, 1/8, 1/16}};
