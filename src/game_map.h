#ifndef SERENITY_GAME_MAP_H_
#define SERENITY_GAME_MAP_H_

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

class GameMap {
public:
    GameMap(int width, int height);
    void display() const;
    void movePlayer(char direction);
    bool checkGoal();

private:
    int width_;
    int height_;
    std::vector<std::vector<char>> grid_;

    int player_x_, player_y_;
    int goal_x_, goal_y_;

    void placeGoal();
    void placePlayer();
};

#endif // SERENITY_MAP_H_