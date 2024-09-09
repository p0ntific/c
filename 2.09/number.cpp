#include <iostream>
#include <stdexcept>

using namespace std;

enum class Operation: char {
    plus = '+',
    minus = '-',
    multiplication = '*',
    division = '/'
};

class Expression {
public:
    virtual double evaluate() = 0;
    virtual ~Expression() = default;
};

class Number : public Expression {
private:
    double value;  

public:
    Number(double val) : value(val) {}

    double evaluate() override {
        return value;
    }
};

class BinaryOperation : public Expression {
private:
    Expression* left; 
    Expression* right; 
    Operation operation;          

public:
    BinaryOperation(Expression* l, Operation oper, Expression* r)
        : left(l), operation(oper), right(r) {}

    ~BinaryOperation() {
        delete left;
        delete right;
    }

    double evaluate() override {
        double leftVal = left->evaluate();
        double rightVal = right->evaluate();
        
        switch (operation) {
            case Operation::plus:
                return leftVal + rightVal;
            case Operation::minus:
                return leftVal - rightVal;
            case Operation::multiplication:
                return leftVal * rightVal;
            case Operation::division:
                if (rightVal == 0) {
                    throw runtime_error("деление на ноль");
                }
                return leftVal / rightVal;
        }
    }
};
