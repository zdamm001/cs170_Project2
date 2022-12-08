#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct object {
    double label;
    vector<double> features;
    object(double l) : label(l) { };
};

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
    vector<object> data;
    string currLine;
    double label, feature;
    while(getline(fin, currLine)) {
        istringstream ssin(currLine);
        ssin >> label;
        data.push_back(object(label));
        while(ssin >> feature) {
            data.back().features.push_back(feature);
        }
    }
    fin.close();
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