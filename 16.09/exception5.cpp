
#include <iostream>
#include <stdexcept>
#include <memory>

class OutOfMemory : public std::runtime_error {
public:
    OutOfMemory() : std::runtime_error("Недостаточно памяти") {}
};

class OutOfRange : public std::runtime_error {
public:
    OutOfRange() : std::runtime_error("Индекс за пределами") {}
};

class Vector {
public:
    Vector(int size) : size(size) {
        try {
            data = std::unique_ptr<double[]>(new double[size]);
        } catch (const std::bad_alloc&) {
            throw OutOfMemory();
        }
    }

    double& operator[](int index) {
        if (index >= size) {
            throw OutOfRange();
        }
        return data[index];
    }

    int getSize() const { return size; }

private:
    int size;
    std::unique_ptr<double[]> data;
};

int main() {
    int size;
    std::cout << "Введите размер вектора: ";
    std::cin >> size;

    try {
        Vector vec(size);

        int index;
        double value;
        std::cout << "Введите индекс и значение для назначения: ";
        std::cin >> index >> value;

        vec[index] = value;
        std::cout << "Вектор[" << index << "] = " << vec[index] << std::endl;
    } catch (const OutOfMemory& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    } catch (const OutOfRange& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
