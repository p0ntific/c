#include <iostream>
#include <memory>
#include <array> 

class Foo {
public:
    Foo() {
        if (nextId == 7) {
            throw std::runtime_error("Создано слишком много объектов Foo");
        }
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

int Foo::nextId = 1;

int main() {
    try {
        Foo localFoos[10];
    } catch (const std::exception& e) {
        std::cout << "Перехвачено исключение при создании массива: " << e.what() << std::endl;
    }

    return 0;
}
