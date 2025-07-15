#include <iostream>   // For std::cout and std::endl
#include <mutex>      // For std::mutex and std::lock_guard

std::mutex fileMutex;

void writeToFile(int threadId) {
    std::lock_guard<std::mutex> lock(fileMutex);  // Ensures only one thread writes at a time
    std::cout << "Thread " << threadId << " is writing to the file." << std::endl;
}
