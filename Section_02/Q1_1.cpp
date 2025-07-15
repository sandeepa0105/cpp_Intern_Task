#include <iostream>
#include <thread>
#include <vector>

void processChunk(int threadId) {
    std::cout << "Processing chunk " << threadId << std::endl;
}

int main() {
    const int numThreads = 4;
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(processChunk, i);
    }

    for (auto& t : threads) {
        t.join();  // Wait for each thread to finish
    }

    return 0;
}
