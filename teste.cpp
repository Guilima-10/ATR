#include <iostream>
#include <thread>
#include <chrono>

int main() {
    std::cout << "Esperando 2 segundos..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Pronto!" << std::endl;
    return 0;
}
