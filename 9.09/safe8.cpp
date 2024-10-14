#include <iostream>
#include <memory>
#include <algorithm>  

class Foo {
public:
    Foo() {
        id = nextId++;
        std::cout << "Создан объект Foo с номером: " << id << std::endl;
    }

    ~Foo() {
        std::cout << "Уничтожен объект Foo с номером: " << id << std::endl;
    }
    Foo& operator=(const Foo&other){
        if (other.id == 12) {
            throw std::runtime_error("присваивание с номером 7");
        }
        if (this != &other) {
            int old_id = id;
            id = other.id;
            std::cout << "Обьекту Foo с номером " << old_id << " присвоен объект Foo с номером: " << id << std::endl;
        }
        return *this;
    }

private:
    int id;
    static int nextId;
};

int Foo::nextId = 0;

template <typename T>
class Matrix {
public:
    Matrix(size_t rows, size_t cols) 
        : rows(rows), cols(cols), elements(new T[rows * cols]) {}

    Matrix(const Matrix& other) 
        : rows(other.rows), cols(other.cols), elements(new T[other.rows * other.cols]) {
        std::copy(other.elements.get(), other.elements.get() + rows * cols, elements.get());
    }

    Matrix& operator=(const Matrix& other) {
        if (this == &other) return *this;

        if (rows != other.rows || cols != other.cols) {
            elements.reset(new T[other.rows * other.cols]);
            rows = other.rows;
            cols = other.cols;
        }

        std::copy(other.elements.get(), other.elements.get() + rows * cols, elements.get());

        return *this;
    }

    T& operator()(size_t row, size_t col) {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Индекс за пределами");
        }
        return elements[row * cols + col];
    }

private:
    size_t rows, cols;
    std::unique_ptr<T[]> elements;
};

int main() {
    try {
        Matrix<Foo> m1(3, 3); 
        Matrix<Foo> m2(3, 3); 

        m1 = m2;

    } catch (const std::exception& e) {
        std::cout << "Перехвачено исключение: " << e.what() << std::endl;
    }

    return 0;
}
