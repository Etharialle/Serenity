#include <iostream>
#include <vector>
#include <cstdlib>  // For system()
#include "include/drunkards_walk.h"  // Include the header file for the drunkardsWalk function
#include "include/create_map_png.h"      // Include the header file for the PNG creation function

int main() {
    int rows = 200;       // Map dimensions
    int cols = 300;
    int steps = 100000;     // Number of steps for the drunkard's walk

    std::cout << "height of map (pixels): ";
    std::cin >> rows;
    std::cout << "width of map (pixels): ";
    std::cin >> cols;

    // Initialize the map with walls (0)
    std::vector<std::vector<int>> map(rows, std::vector<int>(cols, 0));

    // Start the walk from the center of the map
    int startX = rows / 2;
    int startY = cols / 2;

    // Run the drunkard's walk algorithm to generate the map
    drunkardsWalk(map, startX, startY, steps);

    // Create the PNG from the generated map
    createPNGFromArray(map, "../assets/overworld.png");

    // Open the generated map
    system("xdg-open ../assets/overworld.png");

    return 0;
}
