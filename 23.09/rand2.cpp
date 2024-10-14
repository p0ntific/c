#include <iostream>
#include <random>

int main() {
    int size = 100;
    std::mt19937 generator(static_cast<unsigned>(time(nullptr)));
    std::uniform_int_distribution<int> distribution(0, 1);
    
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << (distribution(generator) ? '*' : ' ');
        }
        std::cout << '\n';
    }

    return 0;
}
