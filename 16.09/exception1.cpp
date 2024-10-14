#include <iostream>
#include <stdexcept>

class DivisionByZero : public std::runtime_error {
public:
    DivisionByZero() : std::runtime_error("Деление на ноль") {}
};

int integerDivision(int a, int b) {
    if (b == 0) {
        throw DivisionByZero();
    }
    return a / b;
}

int main() {
    int a = 15, b = 1;
    try {
        int result = integerDivision(a, b);
        std::cout << "Результат: " << result << std::endl;
    } catch (const DivisionByZero& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}