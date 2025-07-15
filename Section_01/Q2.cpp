#include <iostream>
using namespace std;

class Queue {
private:
    int* arr;       // dynamic array for queue elements
    int front;    //index pointers
    int rear;    //index pointers
    int capacity;   // maximum size of the queue

public:
    // Constructor - Initializes array size and index values
    Queue(int size) {
        capacity = size;
        arr = new int[capacity];
        front = 0;
        rear = -1;
        cout << "Queue created with capacity " << capacity << endl;
    }

    // Copy Constructor  - Creates a deep copy of the queue object
    Queue(const Queue& other) {
        capacity = other.capacity;
        front = other.front;
        rear = other.rear;
        arr = new int[capacity];
        for (int i = front; i <= rear; i++) {
            arr[i] = other.arr[i];
        }
        cout << "Queue copied using copy constructor\n";
    }

    // Destructor - Frees the dynamically allocated array
    ~Queue() {
        delete[] arr;
        cout << "Queue destroyed\n";
    }

    // Enqueue function
    void enqueue(int value) {
        if (rear == capacity - 1) {
            cout << "Queue is full. Cannot enqueue " << value << endl;
            return;
        }
        rear++;
        arr[rear] = value;
        cout << "Enqueued: " << value << endl;
    }

    // Dequeue function
    void dequeue() {
        if (front > rear) {
            cout << "Queue is empty. Cannot dequeue.\n";
            return;
        }
        cout << "Dequeued: " << arr[front] << endl;
        front++;
    }

    // Display queue elements
    void display() {
        if (front > rear) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "Queue elements: ";
        for (int i = front; i <= rear; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

// Main function to demonstrate the Queue
int main() {
    Queue q1(5); // Create a queue of size 5

    q1.enqueue(10);
    q1.enqueue(20);
    q1.enqueue(30);
    q1.display();

    q1.dequeue();
    q1.display();

    // Demonstrate copy constructor
    Queue q2 = q1; // Copy q1 to q2
    q2.display();

    return 0;
}
