#include "game_map.h"
#include <iostream>
#include <chrono>
#include <thread>

#ifdef _WIN32
    #include <conio.h>  // Windows-specific
    #include <windows.h>
    #define CLEAR_SCREEN "cls"
    #define SLEEP(ms) Sleep(ms)
#else
    #include <termios.h>
    #include <unistd.h>
    #define CLEAR_SCREEN "clear"
    #define SLEEP(ms) usleep((ms) * 1000)

    // Function to capture a single keypress without requiring Enter on Linux/macOS
    char getKeyPress() {
        struct termios oldt, newt;
        char ch;
        tcgetattr(STDIN_FILENO, &oldt);  // Get current terminal attributes
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode & echo
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // Apply new settings

        ch = getchar();  // Read single character

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Restore original settings
        return ch;
    }
#endif

#ifndef _WIN32
    // Ensure function is available on Windows too
    char getKeyPress();
#endif

int main() {
    GameMap map(50, 50);
    char input;

    // Main game loop
    while (true) {
        system(CLEAR_SCREEN);
        map.display();
        
        // check for win
        if (map.checkGoal() == true) {
            std::cout << "Reached the goal! \n";
            break;
        }

        std::cout << "Move with WASD.  Press 'q' to quit: \n";
        input = getKeyPress();

        if (input =='q') break;
        map.movePlayer(input);


        // SLEEP(100); // wait timer need a better implementation
    }

    return 0;
}