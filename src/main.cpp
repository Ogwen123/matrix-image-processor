#include <SDL.h>
#include <iostream>
#include <cmath>
#include <vector>

#include "utils/image_conversions.h"// can now use box_blur and gaussian_blur in code

using namespace std;

const int DELTA_TIME = 1000/30;
const int HEIGHT = 600;
const int WIDTH = 600;

__attribute__((unused)) vector<vector<float>> genPattern() {// make a checkerboard patten, clion told me to use __attribute__((unused))
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

vector<vector<double>> applyManipulationMatrix(vector<vector<double>> matrixToChange, vector<vector<double>> manipulator) {
    int m = (int) matrixToChange.size(); // height, rows
    int n = (int) matrixToChange[0].size(); // width, columns

    if (n < 3 || m < 3) {
        return matrixToChange;
    }

    vector<vector<double>> new_matrix = matrixToChange;

    for (int i = 1; i < n-1; i++) {
        for (int j = 1; j < m-1; j++) {
            double total = 0;
            for (int k = 0; k < manipulator.size(); k++) {
                for (int l = 0; l < manipulator[k].size(); l++) {
                    total += matrixToChange[j+(k-1)][i+(l-1)] * manipulator[k][l];
                }
            }
            new_matrix[j][i] = total;
            //cout << "done " << i*(m-1) + j << endl;
        }
    }
    return new_matrix;
}

int main(int argc, char* args []) {

    //vector<vector<double>> matrix = genPattern();
    vector<vector<double>> matrix = { // supposed to look like a number 1
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

    matrix = applyManipulationMatrix(matrix, box_blur);
    //matrix = applyManipulationMatrix(matrix, gaussian_blur);

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
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }
        }
        //SDL_SetRenderDrawColor(renderer, 100, 100, 180, 255); // Set the background color to purple
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
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
