#include "game_map.h"
#include "FastNoiseLite.h"
#include <cstdlib>
#include <ctime>


GameMap::GameMap(int width, int height) : width_(width), height_(height), waterTileCount(0) {

    std::srand(std::time(0));
    grid_ = std::vector<std::vector<char>>(height_, std::vector<char>(width_, '.'));

    generateTerrain();
    //placeObstacles(obstacleCount);
    placePlayer();
    placeGoal();  // Add this line to place the goal
}

void GameMap::generateTerrain() {
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);  // Perlin noise
    noise.SetFrequency(0.1f);  // Control the smoothness of the terrain
    noise.SetSeed(static_cast<int>(std::time(0))); 

    // Clear the grid first, to reset the terrain
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            grid_[y][x] = '.'; // Reset to a default value (e.g., ground)
        }
    }

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            // Get the Perlin noise value at position (x, y)
            //float value = noise.GetNoise(static_cast<float>(x), static_cast<float>(y));
            float value = noise.GetNoise(static_cast<float>(x), static_cast<float>(y));
            
            // Assign terrain based on the noise value
            if (value < 0) {
                grid_[y][x] = 'W';  // Water (blue for rendering)
            } else if (value <= 0.3) {
                grid_[y][x] = '.';  // Overland (grass/ground)
            } else {
                grid_[y][x] = '#';  // Mountains (brown for rendering)
            }
        }
    }
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

int GameMap::movePlayer(char direction) {
    int new_x = player_x_;
    int new_y = player_y_;

    // Calculate the new position based on the direction
    if (direction == 'w' && player_y_ > 0) new_y--;
    else if (direction == 's' && player_y_ < height_ - 1) new_y++;
    else if (direction == 'a' && player_x_ > 0) new_x--;
    else if (direction == 'd' && player_x_ < width_ - 1) new_x++;

    // Check the type of tile at the new position
    char newTile = grid_[new_y][new_x];

    // If the new tile is not an obstacle, move the player
    if (newTile != '#') {
        // If the player is on an overland tile, reset the water tile count
        if (newTile == '.') {
            waterTileCount = 0;  // Reset the waterTileCount when moving to an overland tile
        } else if (newTile == 'W') {
            waterTileCount++;  // Increment waterTileCount if the player steps on a water tile
        }

        // If waterTileCount exceeds 5, the player drowns
        if (waterTileCount > 5) {
            // Handle drowning scenario (e.g., reset player position or end the game)
            std::cout << "You drowned!" << std::endl;
            // Optionally reset the game or do some other action
            return 1; //death by drowning
        }

        // Update the grid and player's position
        grid_[player_y_][player_x_] = '.';  // Clear old position
        player_x_ = new_x;
        player_y_ = new_y;
        grid_[player_y_][player_x_] = 'P';  // Place player at new position
    }
    return 0;
}


bool GameMap::checkGoal() {
    // Check if the player has reached the goal
    if (player_x_ == goal_x_ && player_y_ == goal_y_) {
        return true;
    } 
}

void GameMap::render(SDL_Renderer* renderer, TTF_Font* font) {
    int cellSize = 20;  // Size of each grid cell

    for (int y = 0; y < height_; y++) {
        for (int x = 0; x < width_; x++) {
            SDL_Rect cell = { x * cellSize, y * cellSize, cellSize, cellSize };

            if (grid_[y][x] == '#') {  // Mountain
                SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);  // Brown color
            } else if (grid_[y][x] == 'W') {  // Water
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  // Blue color
            } else if (grid_[y][x] == 'P') {  // Player
                SDL_SetRenderDrawColor(renderer, 255, 20, 147, 255);  // Pink color
            } else if (grid_[y][x] == 'G') {  // Goal
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black color
            } else {  // Ground (Overland)
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Green color
            }

            SDL_RenderFillRect(renderer, &cell);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black border
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
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


void GameMap::showGoalScreen(SDL_Renderer* renderer, TTF_Font* font, bool death) {
    // Clear the screen with black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black color
    SDL_RenderClear(renderer);

    // Render Death
    if (death == true) {
        renderText(renderer, font, "Death by drowning!", 100, 100);
    } else {
        // Render "Goal reached"
        renderText(renderer, font, "Goal Reached!", 100, 100);\
    }

    // Render options: Quit or Restart
    renderText(renderer, font, "Press Q to Quit or R to Restart", 50, 150);

    // Present the screen
    SDL_RenderPresent(renderer);
}

GameMap::~GameMap() {}
