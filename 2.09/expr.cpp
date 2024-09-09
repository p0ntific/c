#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class Expr {
public:
    virtual ~Expr() = default;
    virtual void print()=0;
    virtual double eval(double x) = 0;
    virtual Expr* der() = 0;
    virtual Expr* clone() = 0;
};

class Const : public Expr {
private:
    double value;

public:
    Const(double val) : value(val) {}

    void print() override {
        if(value < 0){
            cout << '(' << value << ')';
        }
        else{
            cout << value;
        }
    }

    double eval(double x) override {
        return value;
    }

    Expr* der() override {
        return new Const(0);
    }

    Expr* clone() override {
        return new Const(value);
    }
};

class Var : public Expr {
public:
    void print() override {
        cout << "x";
    }

    double eval(double x) override {
        return x;
    }

    Expr* der() override {
        return new Const(1);
    }

    Expr* clone() override {
        return new Var();
    }
};



class Sum : public Expr {
private:
    Expr* left;
    Expr* right;

public:
    Sum(Expr* l, Expr* r) : left(l), right(r) {}

    void print() override {
        cout << "(";
        left->print();
        cout << " + ";
        right->print();
        cout << ")";
    }

    double eval(double x) override {
        return left->eval(x) + right->eval(x);
    }

    Expr* der() override {
        return new Sum(left->der(), right->der());
    }

    Expr* clone() override {
        return new Sum(left->clone(), right->clone());
    }
    ~Sum() override{
        delete left;
        delete right;
    };

};

class Prod : public Expr {
private:
    Expr* left;
    Expr* right;

public:
    Prod(Expr* l, Expr* r) : left(l), right(r) {}

    void print() override {
        cout << "(";
        left->print();
        cout << " * ";
        right->print();
        cout << ")";
    }

    double eval(double x) override {
        return left->eval(x) * right->eval(x);
    }

    Expr* der() override {
        return new Sum(new Prod(left->der(), right->clone()), new Prod(left->clone(), right->der()));
    }

    Expr* clone() override {
        return new Prod(left->clone(), right->clone());
    }
    ~Prod() override{
        delete left;
        delete right;
    };

};

class Cos : public Expr {
private:
    Expr* expr;

public:
    Cos(Expr* e) : expr(e) {}

    void print() override ;
    double eval(double x) override;

    Expr* der() override;

    Expr* clone() override;
    ~Cos() override;
};

class Sin : public Expr {
private:
    Expr* expr;

public:
    Sin(Expr* e) : expr(e) {}

    void print() override {
        cout << "sin(";
        expr->print();
        cout << ")";
    }

    double eval(double x) override {
        return sin(expr->eval(x));
    }

    Expr* der() override {
        return new Prod(new Cos(expr->clone()), expr->der());
    }

    Expr* clone() override {
        return new Sin(expr->clone());
    }
    ~Sin() override{
        delete expr;
    };
};



void Cos::print() {
    cout << "cos(";
    expr->print();
    cout << ")";
}

Cos::~Cos() {
    delete expr;
}

double Cos::eval(double x) {
    return cos(expr->eval(x));
}

Expr* Cos::der() {
    return new Prod(new Const(-1), new Prod(new Sin(expr->clone()), expr->der()));
}

Expr* Cos::clone() {
    return new Cos(expr->clone());
}


int main() {
    Expr* expr1 = new Prod(new Sin(new Var()), new Cos(new Var()));
    Expr* expr2 = new Prod(new Sum(new Const(3), new Var()), new Sum(new Prod(new Const(2), new Var()), new Const(1)));

    cout << "выражение 1: ";
    expr1->print();
    cout << " = " << expr1->eval(1) << endl;

    cout << "выражение 2: ";
    expr2->print();
    cout << " = " << expr2->eval(1) << endl;
    Expr* derExpr1 = expr1->der();
    Expr* derExpr2 = expr2->der();

    cout << "производная 1: ";
    derExpr1->print();
    cout << endl;

    cout << "производная 2: ";
    derExpr2->print();
    cout << endl;

    delete expr1;
    delete expr2;
    delete derExpr1;  
    delete derExpr2;   

    return 0;
}
