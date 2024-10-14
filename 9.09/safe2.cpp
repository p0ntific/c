#include <iostream>
#include <memory>
#include <array> 

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

int main() {
    try {
        std::unique_ptr<Foo[]> dynamicFoos(new Foo[5]);
        throw std::runtime_error("Исключение");
        Foo localFoos[5];

    } catch (const std::exception& e) {
        std::cout << "Перехвачено: " << e.what() << std::endl;
    }

    return 0;
}
