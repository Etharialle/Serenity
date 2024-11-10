#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./lib/stb_image_write.h"
#include <iostream>
#include <vector>
#include <cstdlib>   // For rand() and srand()
#include <ctime>     // For time()

void createPNGFromArray(const std::vector<std::vector<int>>& map, const char* filename) {
    int rows = map.size();
    int cols = map[0].size();

    // Create a buffer to hold pixel data (3 bytes per pixel for RGB)
    std::vector<unsigned char> image(rows * cols * 3);

    // Seed the random number generator
    std::srand(std::time(0));

    // Fill the buffer based on the map
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int index = (i * cols + j) * 3; // Calculate the starting index for the RGB pixel

            if (map[i][j] == 1) {
                // Set a random green shade: RGB(0, random green value, 0)
                unsigned char greenShade = 100 + (std::rand() % 156); // Random value between 100 and 255
                image[index] = 0;           // R
                image[index + 1] = greenShade; // G
                image[index + 2] = 0;       // B
            } else {
                // Set walls as black: RGB(0, 0, 0)
                image[index] = 0;           // R
                image[index + 1] = 0;       // G
                image[index + 2] = 0;       // B
            }
        }
    }

    // Write the image as a PNG file (3 channels for RGB)
    if (stbi_write_png(filename, cols, rows, 3, image.data(), cols * 3)) {
        std::cout << "PNG file created successfully: " << filename << std::endl;
    } else {
        std::cerr << "Failed to create PNG file." << std::endl;
    }
}

int main() {
    // Example map (20x30) filled with walls (0) and a path (1)
    std::vector<std::vector<int>> map = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        // (more rows here)
        {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        // (more rows here)
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    createPNGFromArray(map, "../assets/overworld.png");

    return 0;
}
