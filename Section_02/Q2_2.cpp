#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex writeMutex; // Mutex to protect shared resource

void safeWrite(int threadID) {
    lock_guard<mutex> lock(writeMutex); // locks mutex on creation, unlocks when goes out of scope
    cout << "Thread " << threadID << " is writing safely." << endl;
    // Code to write to shared file/database goes here
}

int main() {
    vector<thread> threads;

    for (int i = 0; i < 4; ++i) {
        threads.push_back(thread(safeWrite, i));
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
