#include <iostream>
#include <string>

using namespace std;

class Payment {
protected:
    string address;  // Адрес квартиры

public:
    Payment(const string addr) : address(addr) {}

    virtual ~Payment() = default;

    virtual double calculatePayment() = 0;
};

class Heat : public Payment {
private:
    double area;  

public:
    Heat(string addr, double a) : Payment(addr), area(a) {}

    double calculatePayment() override {
        return area * 50.0;
    }
};

class Water : public Payment {
private:
    int people;  

public:
    Water(string addr, int numPeople) : Payment(addr), people(numPeople) {}

    double calculatePayment() override {
        return people * 200.0;
    }
};


class Electricity : public Payment {
private:
    double kWh;  

public:
    Electricity(string addr, double hours) : Payment(addr), kWh(hours) {}

    double calculatePayment() override {
        return kWh * 5.0;
    }
};

int main() {
    int a;
    Heat heat1("Лабораторный проспект дом 20", 70.0);
    Heat heat2("Лабораторный проспект дом 21", 85.0);
    Water water1("Лабораторный проспект дом 22", 3);
    Water water2("Лабораторный проспект дом 23", 4);
    Water water3("Лабораторный проспект дом 25", 2);
    Electricity electricity1("Лабораторный проспект дом 27", 150.0);
    Electricity electricity2("Лабораторный проспект дом 28", 200.0);

    Payment* payments[7] = { &heat1, &heat2, &water1, &water2, &water3, &electricity1, &electricity2 };

    for (int i = 0; i < 7; ++i) {
        cout << "Оплата:" << payments[i]->calculatePayment() << endl;
    }
    cin >> a;
    return 0;
}
