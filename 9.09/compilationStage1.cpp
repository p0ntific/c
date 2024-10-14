#include <iostream>

constexpr unsigned int power(unsigned int base, unsigned int exp) {
    return (exp == 0) ? 1 : base * power(base, exp - 1);
}

constexpr unsigned int x = 3;
constexpr unsigned int y = 4;
constexpr unsigned int result = power(x, y);

int main() {
    std::cout << x << "^" << y << " = " << result << std::endl;
    return 0;
}
