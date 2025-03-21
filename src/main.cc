#include "game_map.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

std::string getAssetPath(const std::string& filename) {
    // Use the relative path that Bazel sets up at runtime.
    return "assets/" + filename;
}

bool runGame() {
    const int SCREEN_WIDTH = 1400;
    const int SCREEN_HEIGHT = 800;
    const int STATS_WIDTH = 200;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    SDL_Window* window = SDL_CreateWindow("Serenity", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Load font
    std::string fontPath = getAssetPath("Merriweather-Regular.ttf");
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), 24);
    if (!font) {
        std::cerr << "Font could not be loaded! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    GameMap map(60, 40);
    
    bool running = true;
    bool goalStatus = false;
    bool quit = false;
    bool death = false;
    
    // Main game loop
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            goalStatus = map.checkGoal();
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (goalStatus == true) {
                std::cout << "Goal reached!" << std::endl;
                running = false;
                break;
            } else if (e.type == SDL_KEYDOWN) {
                int moved = 0;
                switch (e.key.keysym.sym) {
                    case SDLK_w: moved = map.movePlayer('w'); if (moved == 1) {death = true; running = false;} break;
                    case SDLK_s: moved = map.movePlayer('s'); if (moved == 1) {death = true; running = false;} break;
                    case SDLK_a: moved = map.movePlayer('a'); if (moved == 1) {death = true; running = false;} break;
                    case SDLK_d: moved = map.movePlayer('d'); if (moved == 1) {death = true; running = false;} break;
                    case SDLK_q: running = false; break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White background
        SDL_RenderClear(renderer);
        map.render(renderer, font);
        SDL_RenderPresent(renderer);

        SDL_Delay(100);  // Slow down movement
    }

    // Goal screen loop (after the goal is reached)
    while(!running && goalStatus && !quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            map.showGoalScreen(renderer, font, death);
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_r: 
                        // Restart the game
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(window);
                        TTF_CloseFont(font);
                        return true;  // Return to main to restart the game
                    case SDLK_q: 
                        quit = true; 
                        break;
                }
            }
            SDL_Delay(100);  // Slow down movement
        }
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return !quit;  // Return false if quit was pressed, true if we want to restart
}

int main() {
    bool gameRestarted = false;

    // Loop to handle game restarts
    do {
        gameRestarted = runGame();
    } while (gameRestarted);  // Repeat the game if the player chooses to restart

    TTF_Quit();
    SDL_Quit();

    return 0;
}
