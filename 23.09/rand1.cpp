
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <cmath>
#include <functional>

// Функция для вычисления средней частоты и дисперсии
std::pair<double, double> calculateStatistics(const std::vector<int>& frequencies) {
    double mean = 0.0;
    for (int frequency : frequencies) {
        mean += frequency;
    }
    mean /= frequencies.size();

    double variance = 0.0;
    for (int frequency : frequencies) {
        variance += (frequency - mean) * (frequency - mean);
    }
    variance /= frequencies.size();

    return {mean, variance};
}

// Генерация и вывод частот
void generate_and_display(const std::string& method_name, const std::function<int()>& gen_func, int count, int range) {
    std::vector<int> frequencies(range, 0);

    for (int i = 0; i < count; ++i) {
        ++frequencies[gen_func()];
    }

    auto [mean, variance] = calculateStatistics(frequencies);

    std::cout << method_name << ":\n";
    for (int i = 0; i < range; ++i) {
        std::cout << i << ": " << frequencies[i] << '\n';
    }
    std::cout << "Средняя частота: " << mean << "\nДисперсия: " << variance << "\n\n";
}

int main() {
    int range = 101;
    int count = 1000000;

    srand(static_cast<unsigned>(time(nullptr)));  // Случайное начальное значение

    // Метод масштабирования
    auto rand_scaled = [range]() -> int {
        return static_cast<int>(rand() / (1.0 + RAND_MAX) * range);
    };

    // Метод по модулю
    auto rand_modulo = [range]() -> int {
        return rand() % range;
    };

    // Используем генераторы из <random>
    std::uniform_int_distribution<int> dist(0, range - 1);
    std::mt19937 mt_gen(static_cast<unsigned>(time(nullptr)));
    std::minstd_rand minstd_gen(static_cast<unsigned>(time(nullptr)));
    std::ranlux48 ranlux_gen(static_cast<unsigned>(time(nullptr)));
    std::knuth_b knuth_gen(static_cast<unsigned>(time(nullptr)));
    std::random_device rd_gen;

    auto rand_mt = [&dist, &mt_gen] ()->int {
        return dist(mt_gen);
    };
    auto rand_minstd = [&dist, &minstd_gen]()->int {
        return dist(minstd_gen);
    };
    auto rand_ranlux = [&dist, &ranlux_gen]()->int {
        return dist(ranlux_gen);
    };;
    auto rand_knuth = [&dist, &knuth_gen]()->int {
        return dist(knuth_gen);
    };;
    auto rand_device = [&dist, &rd_gen]()->int {
        return dist(rd_gen);
    };;

    // Вызываем функции генерации и отображаем результат
    generate_and_display("Rand Scaled", rand_scaled, count, range);
    generate_and_display("Rand Modulo", rand_modulo, count, range);
    generate_and_display("MinStd_Rand", rand_minstd, count, range);
    generate_and_display("MT19937", rand_mt, count, range);
    generate_and_display("Ranlux48", rand_ranlux, count, range);
    generate_and_display("Knuth_B", rand_knuth, count, range);
    generate_and_display("Random Device", rand_device, count, range);

    return 0;
}
