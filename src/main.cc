#include "game_map.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

std::string getAssetPath(const std::string& filename) {
    // Use the relative path that Bazel sets up at runtime.
    return "assets/" + filename;
}

void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y) {
    SDL_Color textColor = {255, 125, 125}; // Red text color
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (textSurface != nullptr) {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect textRect = { x, y, textSurface->w, textSurface->h };
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
}

void showGoalScreen(SDL_Renderer* renderer, TTF_Font* font) {
    // Clear the screen with black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black color
    SDL_RenderClear(renderer);

    // Render "Goal reached"
    renderText(renderer, font, "Goal Reached!", 100, 100);

    // Render options: Quit or Restart
    renderText(renderer, font, "Press Q to Quit or R to Restart", 50, 150);

    // Present the screen
    SDL_RenderPresent(renderer);
}

int runGame(){
    const int SCREEN_WIDTH = 400;
    const int SCREEN_HEIGHT = 400;

    //SDL_Init(SDL_INIT_VIDEO);
    //SDL_Window* window = SDL_CreateWindow("Serenity", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Serenity", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Load font
    // Usage
    std::string fontPath = getAssetPath("Merriweather-Regular.ttf");
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), 24);


    //TTF_Font* font = TTF_OpenFont("../assets/Merriweather-Regular.ttf", 24);  // Replace with your font path
    if (!font) {
        std::cerr << "Font could not be loaded! TTF_Error: " << TTF_GetError() << std::endl;
        return 1;
    }

    GameMap map(10, 10, 15);
    bool running = true;
    bool goalStatus = false;
    bool quit = false;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            goalStatus = map.checkGoal();
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (goalStatus == true) {
                std::cout << "goal reached";
                running = false;
                break;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_w: map.movePlayer('w'); break;
                    case SDLK_s: map.movePlayer('s'); break;
                    case SDLK_a: map.movePlayer('a'); break;
                    case SDLK_d: map.movePlayer('d'); break;
                    case SDLK_q: running = false; break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        map.render(renderer, font);
        SDL_RenderPresent(renderer);

        SDL_Delay(100);  // Slow down movement
    }

    while(!running && goalStatus && !quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            showGoalScreen(renderer, font);
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_r: TTF_CloseFont(font); SDL_DestroyRenderer(renderer); SDL_DestroyWindow(window); runGame(); break;
                    case SDLK_q: quit = true; break;
                }
            }
            SDL_Delay(100);  // Slow down movement
        }
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

int main() {

    runGame();

    TTF_Quit();
    SDL_Quit();

    return 0;
}

