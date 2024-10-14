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

int Foo::nextId = 1;

Foo globalFoo;

Foo globalFoos[3];

int main() {
    Foo localFoo1;
    Foo localFoo2;

    static Foo staticFoo1;
    static Foo staticFoo2;

    Foo localFoos[2];

    static Foo staticFoos[2];

    return 0;
}
