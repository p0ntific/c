#include <iostream>

int fib_index(int fibonacci_number) {
    switch (fibonacci_number) {
        case 0: return 0;
        case 1: return 1;
        case 2: return 3;
        case 3: return 4;
        case 5: return 5;
        case 8: return 6;
        case 13: return 7;
        case 21: return 8;
        case 34: return 9;
        default: return -1; 
    }
}

int main() {
    int number = 21;
    int index = fib_index(number);
    if (index != -1) {
        std::cout << "Индекс числа " << number << " в последовательности Фибоначчи: " << index << std::endl;
    } else {
        std::cout << "Число не является известным числом Фибоначчи в списке." << std::endl;
    }
    return 0;
}
