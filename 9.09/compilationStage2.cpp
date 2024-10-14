#include <iostream>

constexpr unsigned int factorial(unsigned int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

constexpr unsigned int binomial_coefficient(unsigned int n, unsigned int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

constexpr unsigned int n = 5;
constexpr unsigned int k = 2;
constexpr unsigned int binom_result = binomial_coefficient(n, k);

int main() {
    std::cout << "C(" << n << ", " << k << ") = " << binom_result << std::endl;
    return 0;
}
