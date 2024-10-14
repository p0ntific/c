#include <iostream>
#include <regex>
#include <string>
#include <vector>



void testCase(int number, std::string str, std::regex pattern_match, std::regex pattern_search){
    std::cout << 'Task number ' << number << std::endl;
    std::cout << std::regex_match(str, pattern_match) << std::regex_search(str, pattern_search) << std::endl;
}

void task1(std::string str) {
    std::cout << "Task1: " << std::endl;
    std::regex pattern_match("^.*000.*$");
    std::regex pattern_search("*.^.*000.*$.*");
}


// 2. Strings containing '101' occurring consecutively.
void task2() {
    std::string str;
    std::cout << "\nTask 2: Strings containing '101' occurring consecutively.\nEnter string: ";
    std::cin >> str;
    std::regex pattern("^.*101.*$");
    if (std::regex_match(str, pattern)) {
        std::cout << "String contains '101' consecutively.\n";
    } else {
        std::cout << "String does not contain '101' consecutively.\n";
    }
}

// 3. Strings that start or end with '101'.
void task3() {
    std::string str;
    std::cout << "\nTask 3: Strings that start or end with '101'.\nEnter string: ";
    std::cin >> str;
    std::regex pattern("^(101.*|.*101)$");
    if (std::regex_match(str, pattern)) {
        std::cout << "String starts or ends with '101'.\n";
    } else {
        std::cout << "String does not start or end with '101'.\n";
    }
}

// 4. Strings of digits containing '1'.
void task4() {
    std::string str;
    std::cout << "\nTask 4: Strings of digits containing '1'.\nEnter string: ";
    std::cin >> str;
    std::regex pattern("^[0-9]*1[0-9]*$");
    if (std::regex_match(str, pattern)) {
        std::cout << "String is digits and contains '1'.\n";
    } else {
        std::cout << "String is not valid or does not contain '1'.\n";
    }
}

// 5. Strings of digits not containing '1'.
void task5() {
    std::string str;
    std::cout << "\nTask 5: Strings of digits not containing '1'.\nEnter string: ";
    std::cin >> str;
    std::regex pattern("^(?!.*1)[0-9]+$");
    if (std::regex_match(str, pattern)) {
        std::cout << "String is digits and does not contain '1'.\n";
    } else {
        std::cout << "String is not valid or contains '1'.\n";
    }
}

// 6. Non-empty strings of digits where the first digit occurs elsewhere.
void task6() {
    std::string str;
    std::cout << "\nTask 6: Non-empty strings of digits where the first digit occurs somewhere else.\nEnter string: ";
    std::cin >> str;
    std::regex pattern("^([0-9]).*\\1.*$");
    if (std::regex_match(str, pattern)) {
        std::cout << "First digit occurs elsewhere in the string.\n";
    } else {
        std::cout << "First digit does not occur elsewhere in the string.\n";
    }
}

// 7. Non-empty strings of digits where the first digit does not occur elsewhere.
void task7() {
    std::string str;
    std::cout << "\nTask 7: Non-empty strings of digits where the first digit does not occur elsewhere.\nEnter string: ";
    std::cin >> str;
    std::regex pattern("^([0-9])(?!.*\\1)[0-9]*$");
    if (std::regex_match(str, pattern)) {
        std::cout << "First digit does not occur elsewhere in the string.\n";
    } else {
        std::cout << "First digit occurs elsewhere in the string.\n";
    }
}

// 8. Decimal integers (without leading zeros) with optional sign.
void task8() {
    std::string str;
    std::cout <<
"\nTask 8: Decimal integers (without leading zeros) with optional sign.\nEnter string: ";
    std::cin >> str;
    std::regex pattern("^[+-]?([1-9][0-9]*|0)$");
    if (std::regex_match(str, pattern)) {
        std::cout << "String is a valid decimal integer without leading zeros.\n";
    } else {
        std::cout << "String is not a valid decimal integer.\n";
    }
}

// 9. Octal integers (leading zero) with optional sign.
void task9() {
    std::string str;
    std::cout << "\nTask 9: Octal integers (leading zero) with optional sign.\nEnter string: ";
    std::cin >> str;
    std::regex pattern("^[+-]?0[0-7]*$");
    if (std::regex_match(str, pattern)) {
        std::cout << "String is a valid octal integer.\n";
    } else {
        std::cout << "String is not a valid octal integer.\n";
    }
}

// 10. Hexadecimal integers (starting with 0x) with optional sign.
void task10() {
    std::string str;
    std::cout << "\nTask 10: Hexadecimal integers (starting with 0x) with optional sign.\nEnter string: ";
    std::cin >> str;
    std::regex pattern("^[+-]?0[xX][0-9a-fA-F]+$");
    if (std::regex_match(str, pattern)) {
        std::cout << "String is a valid hexadecimal integer.\n";
    } else {
        std::cout << "String is not a valid hexadecimal integer.\n";
    }
}

// 11. Any integers (from previous three tasks) with optional sign.
void task11() {
    std::string str;
    std::cout << "\nTask 11: Any integers (decimal, octal, or hex) with optional sign.\nEnter string: ";
    std::cin >> str;
    std::regex pattern("^[+-]?((0[xX][0-9a-fA-F]+)|(0[0-7]*)|([1-9][0-9]*|0))$");
    if (std::regex_match(str, pattern)) {
        std::cout << "String is a valid integer (decimal, octal, or hex).\n";
    } else {
        std::cout << "String is not a valid integer.\n";
    }
}

// 12. Decimal floating-point numbers with optional sign.
void task12() {
    std::string str;
    std::cout << "\nTask 12: Decimal floating-point numbers with optional sign.\nEnter string: ";
    std::cin >> str;
    std::regex pattern("^[+-]?((\\d+\\.\\d*)|(\\d*\\.\\d+)|(\\d+))$");
    if (std::regex_match(str, pattern)) {
        std::cout << "String is a valid decimal floating-point number.\n";
    } else {
        std::cout << "String is not a valid decimal floating-point number.\n";
    }
}

// 13. String contains two zeros, between which number of characters is divisible by four.
void task13() {
    std::string str;
    std::cout << "\nTask 13: String contains two zeros, between which number of characters is divisible by four.\nEnter string: ";
    std::cin >> str;
    std::regex pattern("^.*0(?:.{4})*0.*$");
    if (std::regex_match(str, pattern)) {
        std::cout << "String contains two zeros with characters between them divisible by four.\n";
    } else {
        std::cout << "String does not meet the condition.\n";
    }
}

int main() {
    task
    return 0;
}