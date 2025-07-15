#include <iostream>
#include <climits>  // for INT_MIN
using namespace std;

int main() {
    int size;

    // Step 1: Get the array size from the user
    cout << "Enter the size of the array: ";
    cin >> size;

    // Check for invalid sizes
    if (size < 2) {
        cout << "Array must contain at least two elements." << endl;
        return 0;
    }

    int arr[size];
    cout << "Enter " << size << " elements:\n";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    // Step 2: Find the largest and second largest
    int largest = INT_MIN;
    int secondLargest = INT_MIN;

    for (int i = 0; i < size; i++) {
        if (arr[i] > largest) {
            secondLargest = largest;
            largest = arr[i];
        } else if (arr[i] > secondLargest && arr[i] != largest) {
            secondLargest = arr[i];
        }
    }

    // Step 3: Display the result or handle edge cases
    if (secondLargest == INT_MIN) {
        cout << "There is no second largest element (all elements may be equal)." << endl;
    } else {
        cout << "The second largest element is: " << secondLargest << endl;
    }

    return 0;
}
