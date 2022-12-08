#include <iostream>
#include <fstream>

using namespace std;

int main() {
    string testFile;
    int choice;
    cout << "Welcome to Zachary Dammanns Feature Selection Algorithm." << endl;
    cout << "Type in the name of the file to test: " << flush;
    ifstream fin(testFile);
    if (!fin.is_open()) {
        cout << "Error opening " << testFile << "." << endl;
        exit(EXIT_FAILURE);
    }
    cout << "Type the number of the algorithm you want to run." << endl;
    cout << "1) Forward Selection" << endl;
    cout << "2) Backward Elimination" << endl;
    cin >> choice;
    cout << "This dataset has X features (not including the class attribute), with Y instances." << endl;
    switch(choice) {
        case 1:

            break;
        case 2:

            break;
        default:
            break;
    }
    return 0;
}