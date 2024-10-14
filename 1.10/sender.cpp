#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    std::string message = "1011001"; // The secret message to send
    const std::string signalFile = "signal";
    const int interval_ms = 1000; // Transmission interval in milliseconds

    std::cout << "Sender started.\n";

    for (char bit : message) {
        auto start = std::chrono::steady_clock::now();

        if (bit == '1') {
            // Create the signal file to represent '1'
            std::ofstream(signalFile);
            std::cout << "Sent bit: 1\n";
        } else {
            // Ensure the signal file does not exist to represent '0'
            if (fs::exists(signalFile)) {
                fs::remove(signalFile);
            }
            std::cout << "Sent bit: 0\n";
        }
// Wait for the rest of the interval
        auto end = std::chrono::steady_clock::now();
        std::this_thread::sleep_for(
            std::chrono::milliseconds(interval_ms) - (end - start)
        );
    }

    // Clean up at the end
    if (fs::exists(signalFile)) {
        fs::remove(signalFile);
    }
    std::cout << "Transmission complete.\n";

    return 0;
}