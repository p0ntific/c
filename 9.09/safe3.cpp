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

int main() {
    try {
        Foo localFoos[5];
        std::unique_ptr<Foo[]> dynamicFoos(new Foo[5]);

        throw std::runtime_error("Исключение: динамический массив unique_ptr");

    } catch (const std::exception& e) {
        std::cout << "Перехвачено: " << e.what() << std::endl;
    }

    return 0;
}
