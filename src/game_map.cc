#include "game_map.h"
#include <cstdlib>
#include <ctime>


GameMap::GameMap(int width, int height, int obstacleCount) 
    : width_(width), height_(height) {

    std::srand(std::time(0));
    grid_ = std::vector<std::vector<char>>(height_, std::vector<char>(width_, '.'));

    placeObstacles(obstacleCount);
    placePlayer();
    placeGoal();  // Add this line to place the goal
}

void GameMap::placeObstacles(int count) {
    int placed = 0;
    while (placed < count) {
        int x = std::rand() % width_;
        int y = std::rand() % height_;

        if (grid_[y][x] == '.') {
            grid_[y][x] = '#';
            placed++;
        }
    }
}

void GameMap::placePlayer() {
    while (true) {
        int x = std::rand() % width_;
        int y = std::rand() % height_;

        if (grid_[y][x] == '.') {
            player_x_ = x;
            player_y_ = y;
            grid_[y][x] = 'P';
            break;
        }
    }
}

void GameMap::placeGoal() {
    while (true) {
        int x = std::rand() % width_;
        int y = std::rand() % height_;

        if (grid_[y][x] == '.') {
            goal_x_ = x;
            goal_y_ = y;
            grid_[y][x] = 'G';  // Mark the goal with 'G'
            break;
        }
    }
}

void GameMap::movePlayer(char direction) {
    int new_x = player_x_;
    int new_y = player_y_;

    if (direction == 'w' && player_y_ > 0) new_y--;
    else if (direction == 's' && player_y_ < height_ - 1) new_y++;
    else if (direction == 'a' && player_x_ > 0) new_x--;
    else if (direction == 'd' && player_x_ < width_ - 1) new_x++;

    if (grid_[new_y][new_x] != '#') {
        grid_[player_y_][player_x_] = '.';
        player_x_ = new_x;
        player_y_ = new_y;
        grid_[player_y_][player_x_] = 'P';
    }
}

bool GameMap::checkGoal() {
    // Check if the player has reached the goal
    return (player_x_ == goal_x_ && player_y_ == goal_y_);
}

void GameMap::render(SDL_Renderer* renderer, TTF_Font* font) {
    int cellSize = 40;
    for (int y = 0; y < height_; y++) {
        for (int x = 0; x < width_; x++) {
            SDL_Rect cell = { x * cellSize, y * cellSize, cellSize, cellSize };
            
            if (grid_[y][x] == '#') {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black for obstacles
            } else if (grid_[y][x] == 'P') {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue for player
            } else if (grid_[y][x] == 'G') {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green for goal
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White for ground
            }

            SDL_RenderFillRect(renderer, &cell);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black border
            SDL_RenderDrawRect(renderer, &cell);
        }
    }

    if (checkGoal()) {
        // Goal reached: display message
        SDL_Color textColor = {255, 125, 125}; // White text
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Goal Reached", textColor);
        if (textSurface != nullptr) {
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_Rect textRect = { width_ * cellSize / 2 - 100, height_ * cellSize / 2, 200, 50 };
            SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
        }
    }
}

GameMap::~GameMap() {}
