#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class GameMap {
public:
    GameMap(int width, int height, int obstacleCount);
    ~GameMap();
    
    void render(SDL_Renderer* renderer, TTF_Font* font);
    void movePlayer(char direction);
    bool checkGoal();

private:
    int width_;
    int height_;
    std::vector<std::vector<char>> grid_;
    int player_x_, player_y_;
    int goal_x_, goal_y_;

    void placePlayer();
    void placeGoal();
    void placeObstacles(int count);
};

#endif // GAME_MAP_H
