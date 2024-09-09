#include <iostream>
#include <string>

using namespace std;

class Payment {
protected:
    string address; 

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
    Payment* payments[7];
    payments[0] = new Heat("Лабораторный проспект дом 20", 70.0);
    payments[1] = new Heat("Лабораторный проспект дом 20", 70.0);
    payments[2] = new Water("Лабораторный проспект дом 20", 2);
    payments[3] = new Water("Лабораторный проспект дом 20", 3);
    payments[4] = new Water("Лабораторный проспект дом 20", 4);
    payments[5] = new Electricity("Лабораторный проспект дом 20", 70.0);
    payments[6] = new Electricity("Лабораторный проспект дом 20", 70.0);

    for (int i = 0; i < 7; ++i) {
        cout << "Оплата:" << payments[i]->calculatePayment() << endl;
        delete payments[i];
    }
    return 0;
}
