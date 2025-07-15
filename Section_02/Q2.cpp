#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <string>
#include <chrono>
#include <random>

// Shared task queue and mutex
std::queue<int> taskQueue;
std::mutex queueMutex;
std::mutex logMutex;

// Simulate error-prone processing
void processTask(int taskId, int threadId) {
    try {
        // Randomly throw error for demonstration
        if (taskId % 5 == 0) {
            throw std::runtime_error("Failed to process task " + std::to_string(taskId));
        }

        // Simulate processing time
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Successful processing log
        std::lock_guard<std::mutex> lock(logMutex);
        std::cout << "Thread " << threadId << " processed task " << taskId << std::endl;
    } catch (const std::exception& e) {
        // Log error safely
        std::lock_guard<std::mutex> lock(logMutex);
        std::cerr << "Thread " << threadId << " error: " << e.what() << std::endl;
    }
}

// Worker function (simulates thread pool behavior)
void worker(int threadId) {
    while (true) {
        int taskId = -1;

        {
            std::lock_guard<std::mutex> lock(queueMutex);
            if (taskQueue.empty()) return; // Exit when no tasks remain

            taskId = taskQueue.front();
            taskQueue.pop();
        }

        processTask(taskId, threadId);
    }
}

int main() {
    const int numThreads = 4;
    const int numTasks = 20;

    // Fill the task queue
    for (int i = 1; i <= numTasks; ++i) {
        taskQueue.push(i);
    }

    // Launch thread pool
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(worker, i);
    }

    // Join all threads
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "All tasks processed." << std::endl;
    return 0;
}
