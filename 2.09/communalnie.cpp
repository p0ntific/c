class Payment {
protected:
    std::string address;  // Адрес квартиры

public:
    // Конструктор, заполняющий адрес
    Payment(const std::string& addr) : address(addr) {}

    // Виртуальный деструктор
    virtual ~Payment() = default;

    // Чисто виртуальный метод для расчета платы
    virtual double calculatePayment() const = 0;
};

class Heat : public Payment {
private:
    double area;  // Площадь квартиры

public:
    // Конструктор с двумя параметрами
    Heat(const std::string& addr, double a) : Payment(addr), area(a) {}

    // Переопределенный метод для расчета платы
    double calculatePayment() const override {
        return area * 50.0;
    }
};

class Water : public Payment {
private:
    int numberOfPeople;  // Количество прописанных людей

public:
    // Конструктор с двумя параметрами
    Water(const std::string& addr, int numPeople) : Payment(addr), numberOfPeople(numPeople) {}

    // Переопределенный метод для расчета платы
    double calculatePayment() const override {
        return numberOfPeople * 200.0;
    }
};


// Класс Electricity - производный от Payment
class Electricity : public Payment {
private:
    double kWh;  // Количество киловатт-часов

public:
    // Конструктор с двумя параметрами
    Electricity(const std::string& addr, double kwh) : Payment(addr), kWh(kwh) {}

    // Переопределенный метод для расчета платы
    double calculatePayment() const override {
        return kWh * 5.0;
    }
};

int main() {
    // Создание объектов производных классов
    Heat heat1("123 Main St", 70.0);
    Heat heat2("456 Elm St", 85.0);
    Water water1("789 Oak St", 3);
    Water water2("101 Pine St", 4);
    Water water3("202 Maple St", 2);
    Electricity electricity1("303 Birch St", 150.0);
    Electricity electricity2("404 Spruce St", 200.0);

    // Массив указателей на Payment
    Payment* payments[7] = { &heat1, &heat2, &water1, &water2, &water3, &electricity1, &electricity2 };

    // Вывод платы за все услуги
    for (int i = 0; i < 7; ++i) {
        std::cout << "Payment for service at " << payments[i]->calculatePayment() << " rub." << std::endl;
    }

    return 0;
}
