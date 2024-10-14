#include <iostream>
#include <fstream>
#include <stdexcept>

class NoFile : public std::runtime_error {
public:
    NoFile() : std::runtime_error("Файл не найден") {}
};

void readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw NoFile();
    }

    std::string line;
    std::cout << file.rdbuf();
}

int main() {
    std::string filename = "exception1";

    try {
        readFile(filename);
    } catch (const NoFile& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
