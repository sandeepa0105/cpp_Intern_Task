#include <iostream>
#include <thread>
#include <vector>

using namespace std;

// Worker function to simulate processing a chunk
void processChunk(int threadID) {
    cout << "Processing chunk " << threadID << endl;
}

int main() {
    const int numThreads = 4;
    vector<thread> threads;

    // Create and start threads
    for (int i = 0; i < numThreads; ++i) {
        threads.push_back(thread(processChunk, i));
    }

    // Join threads to wait for completion
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
