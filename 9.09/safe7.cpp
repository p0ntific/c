
#include <iostream>
#include <memory>
#include <array> 

class Foo {
public:
    Foo() {
        id = nextId++;
        std::cout << "Создан объект Foo с номером: " << id << std::endl;
    }

    Foo(const Foo& other) {
        id = other.id;
        std::cout << "Скопирован объект Foo с номером: " << id << std::endl;
    }

    Foo& operator=(const Foo& other) {
        if (other.id == 7) {
            throw std::runtime_error("присваивание с номером 7");
        }
        if (this != &other) {
            int old_id = id;
            id = other.id;
            std::cout << "Обьекту Foo с номером " << old_id << " присвоен объект Foo с номером: " << id << std::endl;
        }
        return *this;
    }

    ~Foo() {
        std::cout << "Уничтожен объект Foo с номером: " << id << std::endl;
    }

private:
    int id;
    static int nextId;
};

int Foo::nextId = 0;

template <typename T>
class Vector {
public:
    Vector(size_t size) : size(size), elements(new T[size]) {}

    Vector(const Vector& other) : size(other.size), elements(new T[other.size]) {
        for (size_t i = 0; i < size; ++i) {
            elements[i] = other.elements[i];
        }
    }

    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;
        if (other.size != size) {
            elements.reset(new T[other.size]);
            size = other.size;
        }
        for (size_t i = 0; i < size; ++i) {
            elements[i] = other.elements[i];
        }
        return *this;
    }

    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Индекс за пределами");
        }
        return elements[index];
    }

private:
    size_t size;
    std::unique_ptr<T[]> elements;
};

int main() {
    try {
        Vector<Foo> v1(10);
        Vector<Foo> v2(10);
        v2 = v1; 
    } catch (const std::exception& e) {
        std::cout << "Перехвачено исключение: " << e.what() << std::endl;
    }

    return 0;
}
