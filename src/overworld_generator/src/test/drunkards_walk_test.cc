#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest.h"
#include "../include/drunkards_walk.h"  // Include your header file or function declarations

TEST_CASE("Drunkard's Walk basic test") {
    int rows = 10;
    int cols = 10;
    int steps = 20;
    
    // Create a 2D vector initialized with 0s
    std::vector<std::vector<int>> map(rows, std::vector<int>(cols, 0));
    
    // Call the function with a starting position in the middle
    drunkardsWalk(map, rows / 2, cols / 2, steps);
    
    // Count the number of cells marked as part of the path (with value 1)
    int pathCount = 0;
    for (const auto& row : map) {
        for (int cell : row) {
            if (cell == 1) {
                ++pathCount;
            }
        }
    }
    
    // Check that the path exists and that it's within a reasonable range
    CHECK(pathCount > 0);  // Ensure some path was created
    CHECK(pathCount <= steps + 1);  // Ensure the path count is at most steps + 1 (start position included)
}
//
//TEST_CASE("Drunkard's Walk boundary test") {
//    int rows = 5;
//    int cols = 5;
//    int steps = 50;  // More steps than there are cells
//
//    // Create a 2D vector initialized with 0s
//    std::vector<std::vector<int>> map(rows, std::vector<int>(cols, 0));
//
//    // Call the function with a starting position at (0, 0)
//    drunkardsWalk(map, 0, 0, steps);
//
//    // Ensure that path does not extend beyond bounds
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            CHECK(map[i][j] == 0 || map[i][j] == 1);  // Ensure only 0s and 1s are in the map
//        }
//    }
//}

