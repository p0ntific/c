class Expression {
public:
    virtual double evaluate() = 0;
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
    char op;          

public:
    BinaryOperation(Expression* l, char oper, Expression* r)
        : left(l), op(oper), right(r) {}

    ~BinaryOperation() {
        delete left;
        delete right;
    }

    double evaluate() override {
        double leftVal = left->evaluate();
        double rightVal = right->evaluate();
        
        switch (op) {
            case '+':
                return leftVal + rightVal;
            case '-':
                return leftVal - rightVal;
            case '*':
                return leftVal * rightVal;
            case '/':
                return leftVal / rightVal;
        }
    }
};
