#include <iostream>
#include <fstream>
#include <stdexcept>

class NoFile1 : public std::runtime_error {
public:
    NoFile1() : std::runtime_error("Первый файл не найден") {}
};

class File2Exists : public std::runtime_error {
public:
    File2Exists() : std::runtime_error("Второй файл уже существует") {}
};
// ошибка
void copyFile(const std::string& file1, const std::string& file2) {
    std::ifstream srcFile(file1);
    if (!srcFile) {
        throw NoFile1();
    }

    std::ofstream destFile(file2, std::ios::in);
    if (destFile.good()) {
        throw File2Exists();
    }

    destFile.clear(); 
    destFile.open(file2, std::ios::out);
    destFile << srcFile.rdbuf();
}

int main() {
    std::string file1 = "exception1", file2 = "file2.txt";

    try {
        copyFile(file1, file2);
        std::cout << "Файл скопирован успешно." << std::endl;
    } catch (const NoFile1& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    } catch (const File2Exists& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
    

    return 0;
}
