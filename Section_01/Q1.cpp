#include <iostream>
#include <string>
using namespace std;

// Define the Book class
class Book {
private:
    string title;
    string author;
    string publisher;
    double price;

public:
    // Parameterized constructor
    Book(string t, string a, string p, double pr) {
        title = t;
        author = a;
        publisher = p;
        price = pr;
    }

    // Member function to display book details
    void displayDetails() {
        cout << "Title    : " << title << endl;
        cout << "Author   : " << author << endl;
        cout << "Publisher: " << publisher << endl;
        cout << "Price    : $" << price << endl;
        cout << "--------------------------" << endl;
    }
};

int main() {
    // Create an array of Book objects
    Book book1("The Catcher in the Rye", "J.D. Salinger", "Little, Brown and Company", 9.99);
    Book library[] = {
        Book("The Great Gatsby", "F. Scott Fitzgerald", "Scribner", 10.99),
        Book("1984", "George Orwell", "Harcourt", 8.99),
        Book("To Kill a Mockingbird", "Harper Lee", "J.B. Lippincott", 12.50)
    };

    int numBooks = sizeof(library) / sizeof(library[0]);

    // Display details of each book
    cout << "Library Book Records:\n";
    
    cout << "--------------------------" << endl;
    book1.displayDetails();
    
    for (int i = 0; i < numBooks; i++) {
        library[i].displayDetails();
    }

    return 0;
}
