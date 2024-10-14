#include <iostream>

#define FIB_CASE(n, index) case n: return index;

int fib_index(int fibonacci_number) {
    switch (fibonacci_number) {
        FIB_CASE(0, 0)
        FIB_CASE(1, 1)
        FIB_CASE(2, 3)
        FIB_CASE(3, 4)
        FIB_CASE(5, 5)
        FIB_CASE(8, 6)
        FIB_CASE(13, 7)
        FIB_CASE(21, 8)
        FIB_CASE(34, 9)
        default: return -1;
    }
}

int main() {
    int number = 13;
    int index = fib_index(number);
    if (index != -1) {
        std::cout << "Индекс числа " << number << " в последовательности Фибоначчи: " << index << std::endl;
    } else {
        std::cout << "Число не является известным числом Фибоначчи в списке." <<
std::endl;
    }
    return 0;
}
