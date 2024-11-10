#include <iostream>
#include <vector>
#include <cstdlib>   // For rand() and srand()
#include <ctime>     // For time()

void drunkardsWalk(std::vector<std::vector<int>>& map, int startX, int startY, int steps) {
    int rows = map.size();
    int cols = map[0].size();

    int x = startX;
    int y = startY;
    
    // Mark the starting point
    map[x][y] = 1;

    // Define possible movements (up, down, left, right)
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    std::srand(std::time(0)); // Seed the random number generator

    for (int i = 0; i < steps; ++i) {
        // Choose a random direction
        int direction = std::rand() % 4;
        
        // Update position
        int newX = x + dx[direction];
        int newY = y + dy[direction];

        // Ensure new position is within bounds
        if (newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
            x = newX;
            y = newY;
            map[x][y] = 1; // Mark the new position as part of the path
        }
    }
}

void displayMap(const std::vector<std::vector<int>>& map) {
    for (const auto& row : map) {
        for (const auto& cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << std::endl;
    }
}

int main() {
    int rows = 20;       // Map dimensions
    int cols = 30;
    int steps = 100;     // Number of steps for the drunkard's walk

    // Initialize the map with walls (0)
    std::vector<std::vector<int>> map(rows, std::vector<int>(cols, 0));

    // Start the walk from the center of the map
    int startX = rows / 2;
    int startY = cols / 2;

    // Run the drunkard's walk algorithm
    drunkardsWalk(map, startX, startY, steps);

    // Display the generated map
    displayMap(map);

    return 0;
}
