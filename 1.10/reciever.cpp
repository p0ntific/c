#include <iostream>
#include <chrono>
#include <thread>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    std::string receivedMessage;
    const std::string signalFile = "signal";
    const int interval_ms = 1000; // Reception interval in milliseconds
    const int bitsToReceive = 7; // Number of bits expected

    std::cout << "Receiver started.\n";

    for (int i = 0; i < bitsToReceive; ++i) {
        auto start = std::chrono::steady_clock::now();

        // Check for the existence of the signal file
        if (fs::exists(signalFile)) {
            receivedMessage += '1';
            std::cout << "Received bit: 1\n";
        } else {
            receivedMessage += '0';
            std::cout << "Received bit: 0\n";
        }

        // Wait for the rest of the interval
        auto end = std::chrono::steady_clock::now();
        std::this_thread::sleep_for(
            std::chrono::milliseconds(interval_ms) - (end - start)
        );
    }

    std::cout << "Reception complete.\n";
    std::cout << "The secret message is: " << receivedMessage << "\n";

    return 0;
}
