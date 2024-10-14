#include <iostream>
#include <stdexcept>

class OffTheField : public std::runtime_error {
public:
    OffTheField(const std::string& message, int x1, int y1) : std::runtime_error(message): x(x1), y(y1) {}
private:
    int x,y;
};

class IllegalCommand : public std::runtime_error {
public:
    IllegalCommand(const std::string& message, char command) : std::runtime_error(message) badInput(command) {}
private:
    char badInput;
};

class Robot {
public:
    Robot() : x(0), y(0) {}

    void move(char direction) {
        switch (direction) {
            case 'U':
                if (y == 0) throw OffTheField("Нельзя двигаться вверх: на границе поля", x, y);
                --y;
                break;
            case 'D':
                if (y == 9) throw OffTheField("Нельзя двигаться вниз: на границе поля", x, y);
                ++y;
                break;
            case 'L':
                if (x == 0) throw OffTheField("Нельзя двигаться влево: на границе поля", x, y);
                --x;
                break;
            case 'R':
                if (x == 9) throw OffTheField("Нельзя двигаться вправо: на границе поля", x, y);
                ++x;
                break;
            default:
                throw IllegalCommand("Недопустимая команда", direction);
        }
        std::cout << "Робот перемещен в позицию (" << x << ", " << y << ")" << std::endl;
    }

private:
    int x, y; 
};

int main() {
    Robot robot;
    
    while (true) {
        char command;
        std::cout << "Введите команду (U, D, L, R для движения, Q для выхода): ";
        std::cin >> command;

        if (command == 'Q') break;

        try {
            robot.move(command);
        } catch (const OffTheField& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        } catch (const IllegalCommand& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    }

    return 0;
}