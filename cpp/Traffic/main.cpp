#include <iostream>

const int WIDTH = 10;
const int HEIGHT = 10;
std::vector<std::vector<char>> map;

int main() {
    for(int x=0; x<WIDTH; x++) {
        for(int y=0; y<HEIGHT; y++) {
            map[x][y] = '.';
        }
    }

    return 0;
}