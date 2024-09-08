class Expression {
public:
    // Виртуальный деструктор
    virtual ~Expression() = default;

    
    // Чисто виртуальный метод для вычисления значения выражения
    virtual double evaluate() const = 0;
};

class Number : public Expression {
private:
    double value;  // Значение числа

public:
    // Конструктор с параметром
    explicit Number(double val) : value(val) {}

    // Переопределенный метод для вычисления значения числа
    double evaluate() const override {
        return value;
    }
};

class BinaryOperation : public Expression {
private:
    Expression* left;  // Левый операнд
    Expression* right; // Правый операнд
    char op;           // Тип операции (+, -, *, /)

public:
    // Конструктор с параметрами
    BinaryOperation(Expression* l, char oper, Expression* r)
        : left(l), op(oper), right(r) {}

    // Деструктор для удаления операндов
    ~BinaryOperation() override {
        delete left;
        delete right;
    }

    // Переопределенный метод для вычисления значения бинарной операции
    double evaluate() const override {
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
            default:
                // Это должна быть ошибка, можно выбросить исключение или нечто подобное
                return 0.0;
        }
    }
};
