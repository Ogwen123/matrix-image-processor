//TODO make buttons on the screen to change which kernel gets used
//TODO after above it should be possible to make the window event driven and not have a loop (i think)

#include <SDL.h>
#include <iostream>
#include <cmath>
#include <vector>

#include "utils/image_conversions.h"// can now use box_blur and gaussian_blur in code
#include "utils/util.h"
#include "utils/starting_matrices.h"

using namespace std;

const int DELTA_TIME = 1000/30;
const int HEIGHT = 600;
const int WIDTH = 600;

__attribute__((unused)) vector<vector<float>> generate_pattern() {// make a checkerboard patten, clion told me to use __attribute__((unused))
    vector<vector<float>> matrix;
    for (int i = 0; i < 30; i++) {
        vector<float> row;
        for (int j = 0; j < 30; j++){
            if ((i+j) % 2 == 0) {
                row.push_back(0.25);
            }else{
                row.push_back(0.75);
                cout << 1/(i+j) << " ";
            }
        }
        matrix.push_back(row);
    }
    return matrix;
}

vector<vector<double>> apply_image_kernel(vector<vector<double>> matrixToChange, vector<vector<double>> kernel) {
    int m = (int) matrixToChange.size(); // height, rows
    int n = (int) matrixToChange[0].size(); // width, columns

    if (n < kernel[0].size() || m < kernel.size()) {
        return matrixToChange;
    }

    int m_adjust = floor(kernel.size()/2);
    int n_adjust = floor(kernel.size()/2);

    vector<vector<double>> new_matrix = matrixToChange;

    for (int i = n_adjust; i < n-(n_adjust); i++) {
        for (int j = m_adjust; j < m-(m_adjust); j++) {
            double total = 0;
            for (int k = 0; k < kernel.size(); k++) {
                for (int l = 0; l < kernel[k].size(); l++) {
                    total += matrixToChange[j+(k-m_adjust)][i+(l-n_adjust)] * kernel[k][l];
                }
            }
            new_matrix[j][i] = total;
        }
    }
    return new_matrix;
}

int main(int argc, char* args []) {
    int KERNEL_TRACKER = 0;
    int KERNEL_TRACKER_MAX = (int) kernel_array.size();
    int IMAGE_SCALE = 20;
    cout << KERNEL_TRACKER_MAX << endl;

    vector<vector<double>> matrix = one;
    vector<vector<double>> original_matrix = matrix_image_expander(matrix, IMAGE_SCALE);

    matrix = apply_image_kernel(matrix_image_expander(matrix, IMAGE_SCALE), kernel_array[KERNEL_TRACKER]);

    // SDL stuff below
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Blurrer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event Event;

    while (running) {
        while (SDL_PollEvent(&Event)) {
            if (Event.type == SDL_QUIT) {
                running = false;
                break;
            } else if (Event.type == SDL_KEYDOWN) {
                if (Event.key.keysym.sym == SDLK_SPACE) {
                    KERNEL_TRACKER = (KERNEL_TRACKER + 1) % (KERNEL_TRACKER_MAX + 1);
                    if (KERNEL_TRACKER == KERNEL_TRACKER_MAX) {matrix = original_matrix;  }
                    else {matrix = apply_image_kernel(original_matrix, kernel_array[KERNEL_TRACKER]);}
                }
            }
        }
        int m = (int) matrix.size();
        int n = (int) matrix[0].size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                SDL_Rect rect;
                rect.x = i*(WIDTH/n);
                rect.y = j*(HEIGHT/m);
                rect.w = WIDTH/n;
                rect.h = HEIGHT/m;
                int value = (int) round(matrix[j][i] * 255);
                // to go from grey scale to rgb just set each value of the rgb to the greyscale * 255
                SDL_SetRenderDrawColor(renderer, value, value, value, value);
                SDL_RenderFillRect(renderer, &rect);

            }
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(DELTA_TIME);
        SDL_RenderClear(renderer);
        //SDL_SetRenderDrawColor(renderer, 100, 100, 180, 255); // Set the background color to purple
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
