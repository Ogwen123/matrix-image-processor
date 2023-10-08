#include <SDL.h>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

const int DELTA_TIME = 1000/30;
const int HEIGHT = 600;
const int WIDTH = 600;

vector<vector<float>> genPattern() {// make a checkerboard patten
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

vector<vector<float>> applyManipulationMatrix(vector<vector<float>> matrixToChange) {
    vector<vector<float>> new_matrix;
    return new_matrix;
}

int main(int argc, char* args []) {

    //vector<vector<float>> matrix = genPattern();
    vector<vector<float>> matrix = {
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
        int m = matrix.size();
        int n = matrix[0].size();
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
