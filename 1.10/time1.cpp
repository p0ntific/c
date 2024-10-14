#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <ctime>

int main() {
    while (true) {
        // Get current time as time_t object
        std::time_t currentTime = std::time(nullptr);

        // Convert to local time
        std::tm* localTime = std::localtime(&currentTime);

        // Clear the screen (adjust if necessary for your system)
        // system("clear"); // Use "cls" for Windows
        std::cout << "\r";

        // Print time in HH:MM:SS format
        std::cout << std::put_time(localTime, "%H:%M:%S") << std::flush;

        // Wait for one second
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
