#include <iostream>
#include <memory>

class Foo {
public:
    Foo() {
        id = nextId++;
        std::cout << "Создан объект Foo с номером: " << id << std::endl;
    }

    ~Foo() {
        std::cout << "Уничтожен объект Foo с номером: " << id << std::endl;
    }

private:
    int id;
    static int nextId;
};

int Foo::nextId = 0;

class Bar {
public:
    Bar() {
        std::cout << "Создание объекта Bar" << std::endl;
        foos = std::unique_ptr<Foo[]>(new Foo[10]);
    }

    ~Bar() {
        std::cout << "Уничтожение объекта Bar" << std::endl;
    }

private:
    std::unique_ptr<Foo[]> foos;
};

int main() {
    try {
        Bar bar;
    } catch (const std::exception& e) {
        std::cout << "Перехвачено исключение: " << e.what() << std::endl;
    }

    return 0;
}
