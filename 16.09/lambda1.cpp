#include <iostream>
#include <cmath> 

double rectangle_method(double a, double b, double (*f)(double)) {
    int n = 100; 
    double sum = 0;

    for (int i = 1; i <= n; ++i) {
        sum += f(a + (i - 0.5) * (b - a) / n); 
    }
    
    return sum * (b - a) / n; 
}

int main() {
    std::cout << rectangle_method(0, 1, [](double x) {
        return std::sin(x) * std::sin(x);
    }) << std::endl;  
    return 0;
}
