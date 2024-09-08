class Expr {
public:
    // Виртуальный деструктор
    virtual ~Expr() = default;

    // Метод для вывода выражения
    virtual void print() const = 0;

    // Метод для вычисления значения выражения при значении переменной x
    virtual double eval(double x) const = 0;

    // Метод для нахождения производной выражения
    virtual Expr* der() const = 0;

    // Метод для копирования выражения
    virtual Expr* clone() const = 0;
};

class Const : public Expr {
private:
    double value;

public:
    explicit Const(double val) : value(val) {}

    void print() const override {
        std::cout << value;
    }

    double eval(double x) const override {
        return value;
    }

    Expr* der() const override {
        return new Const(0);
    }

    Expr* clone() const override {
        return new Const(value);
    }
};

class Var : public Expr {
public:
    void print() const override {
        std::cout << "x";
    }

    double eval(double x) const override {
        return x;
    }

    Expr* der() const override {
        return new Const(1);
    }

    Expr* clone() const override {
        return new Var();
    }
};



class Sum : public Expr {
private:
    Expr* left;
    Expr* right;

public:
    Sum(Expr* l, Expr* r) : left(l), right(r) {}

    ~Sum() override {
        delete left;
        delete right;
    }

    void print() const override {
        std::cout << "(";
        left->print();
        std::cout << " + ";
        right->print();
        std::cout << ")";
    }

    double eval(double x) const override {
        return left->eval(x) + right->eval(x);
    }

    Expr* der() const override {
        return new Sum(left->der(), right->der());
    }

    Expr* clone() const override {
        return new Sum(left->clone(), right->clone());
    }
};

class Prod : public Expr {
private:
    Expr* left;
    Expr* right;

public:
    Prod(Expr* l, Expr* r) : left(l), right(r) {}

    ~Prod() override {
        delete left;
        delete right;
    }

    void print() const override {
        std::cout << "(";
        left->print();
        std::cout << " * ";
        right->print();
        std::cout << ")";
    }

    double eval(double x) const override {
        return left->eval(x) * right->eval(x);
    }

    Expr* der() const override {
        return new Sum(new Prod(left->der(), right->clone()), new Prod(left->clone(), right->der()));
    }

    Expr* clone() const override {
        return new Prod(left->clone(), right->clone());
    }
};

class Sin : public Expr {
private:
    Expr* expr;

public:
    explicit Sin(Expr* e) : expr(e) {}

    ~Sin() override {
        delete expr;
    }

    void print() const override {
        std::cout << "sin(";
        expr->print();
        std::cout << ")";
    }

    double eval(double x) const override {
return std::sin(expr->eval(x));
    }

    Expr* der() const override {
        return new Prod(new Cos(expr->clone()), expr->der());
    }

    Expr* clone() const override {
        return new Sin(expr->clone());
    }
};

class Cos : public Expr {
private:
    Expr* expr;

public:
    explicit Cos(Expr* e) : expr(e) {}

    ~Cos() override {
        delete expr;
    }

    void print() const override {
        std::cout << "cos(";
        expr->print();
        std::cout << ")";
    }

    double eval(double x) const override {
        return std::cos(expr->eval(x));
    }

    Expr* der() const override {
        return new Prod(new Const(-1), new Prod(new Sin(expr->clone()), expr->der()));
    }

    Expr* clone() const override {
        return new Cos(expr->clone());
    }
};

int main() {
    // Создаем выражение для подвыражения sin(x) * cos(x)
    Expr* expr1 = new Prod(new Sin(new Var()), new Cos(new Var()));

    // Выражение: (3 + x) * (2 * x + 1)
    Expr* expr2 = new Prod(new Sum(new Const(3), new Var()), new Sum(new Prod(new Const(2), new Var()), new Const(1)));

    // Выводим и вычисляем значение для выражения expr1 и expr2 при x = 1
    std::cout << "expr1: ";
    expr1->print();
    std::cout << " = " << expr1->eval(1) << std::endl;

    std::cout << "expr2: ";
    expr2->print();
    std::cout << " = " << expr2->eval(1) << std::endl;

    // Находим производные выражений
    Expr* derExpr1 = expr1->der();
    Expr* derExpr2 = expr2->der();

    // Выводим производные
    std::cout << "der(expr1): ";
    derExpr1->print();
    std::cout << std::endl;

    std::cout << "der(expr2): ";
    derExpr2->print();
    std::cout << std::endl;

    // Очищаем память
    delete expr1;
    delete expr2;
    delete derExpr1;
    delete derExpr2;

    return 0;
}
