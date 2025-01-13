#include "game_map.h"

GameMap::GameMap(int width, int height) : width_(width), height_(height) {
    grid_ = std::vector<std::vector<char>>(height_, std::vector<char>(width_, '.'));

    std:srand(std::time(0));    
    placePlayer();
    placeGoal();
}

void GameMap::display() const {
    for (const auto& row : grid_) {
        for (char cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << std::endl;
    }
}

void GameMap::placePlayer() {
    player_x_ = std::rand() % width_;
    player_y_ = std::rand() % height_;
    grid_[player_y_][player_x_] = 'X';
}

void GameMap::placeGoal() {
    goal_x_ = std::rand() % width_;
    goal_y_ = std::rand() % height_;
    if (goal_x_ == player_x_ && goal_y_ == player_y_) GameMap::placeGoal(); // get new goal location
    grid_[goal_y_][goal_x_] = '+';

}

void GameMap::movePlayer(char direction) {
    grid_[player_y_][player_x_] = '.';

    if (direction == 'w' && player_y_ > 0) player_y_--;         // Move up
    else if (direction == 's' && player_y_ < height_ - 1) player_y_++;  // Move down
    else if (direction == 'a' && player_x_ > 0) player_x_--;     // Move left
    else if (direction == 'd' && player_x_ < width_ - 1) player_x_++;  // Move right

    grid_[player_y_][player_x_] = 'X';
}

bool GameMap::checkGoal() {
    if (player_x_ == goal_x_ && player_y_ == goal_y_) {
        return true;
    }
    else {
        return false;
    }
}