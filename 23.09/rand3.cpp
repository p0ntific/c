#include <iostream>
#include <random>
#include <vector>

int main() {
    int size = 100;
    int num_points = 200;

    std::mt19937 generator(static_cast<unsigned>(time(nullptr)));
std::uniform_int_distribution<int> distribution(0, size - 1);

    std::vector<std::vector<char>> grid(size, std::vector<char>(size, ' '));

    for (int i = 0; i < num_points; ++i) {
        int x = distribution(generator);
        int y = distribution(generator);
        grid[x][y] = '*';
    }

    for (const auto& row : grid) {
        for (const auto& cell : row) {
            std::cout << cell;
        }
        std::cout << '\n';
    }

    return 0;
}