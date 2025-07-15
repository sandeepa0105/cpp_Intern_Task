#include <iostream>
#include <cstdio>     // for fopen(), fread(), fclose()
#include <string>     // for std::string

using namespace std;

string readFileContent(const char* filename) {
    // Step 1: Open the file in binary read mode
    FILE* file = fopen(filename, "rb");
    if (file == nullptr) {
        cerr << "Error opening file: " << filename << endl;
        return "";
    }

    // Step 2: Move file pointer to end to determine file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);  // get size
    rewind(file);                 // reset pointer to beginning

    // Step 3: Allocate memory to hold content
    char* buffer = new char[fileSize + 1];  // +1 for null terminator

    // Step 4: Read file content into buffer
    size_t bytesRead = fread(buffer, 1, fileSize, file);
    buffer[bytesRead] = '\0';  // ensure string is null-terminated

    // Step 5: Convert buffer to std::string
    string content(buffer);

    // Step 6: Cleanup
    delete[] buffer;
    fclose(file);

    return content;
}

int main() {
    const char* filename = "example.txt";
    string data = readFileContent(filename);

    if (!data.empty()) {
        cout << "File Content:\n" << data << endl;
    }

    return 0;
}
