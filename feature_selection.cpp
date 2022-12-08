#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>

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
    cin >> testFile;
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
    cout << "This dataset has " << data.front().features.size() << " features (not including the class attribute), with " << data.size() << " instances." << endl;
    switch(choice) {
        case 1:
            forwardSelection(data);
            break;
        case 2:
            backwardElimination(data);
            break;
        default:
            break;
    }
    return 0;
}

string setToString(set<int>& s) {
    string x = "{";
    for (auto i : s) x+=to_string(i) + ",";
    x.back() = '}';
    return x;
}

void forwardSelection(vector<object>& data) {
    int numFeatures = data.front().features.size();
    set<int> features;
    set<int> bestFeatures;
    double bestAccuracy = 0;
    cout << "Beginning Search." << endl;
    for (int i = 0; i < numFeatures; ++i) {
        cout << "On the " << i + 1 << "th level of the search tree" << endl;
        int bestFeature;
        double currBestAccuracy = 0;

        for (int j = 0; j < numFeatures; ++i) {
            if (features.find(j) != features.end()) continue;
            cout << "Considering adding the " << j + 1 << "feature" << endl;
            features.insert(j);
            double accuracy = leaveOneOutCrossValidation(data,features);
            cout << "Using feature(s) " << setToString(features) << " accuracy is " << accuracy << "%" << endl;
            features.erase(j);
            if (accuracy > currBestAccuracy) {
                currBestAccuracy = accuracy;
                bestFeature = j;
            }
        }
        cout << "On level " << i + 1 << " I added feature " << bestFeature << " to current set." << endl;
        if (currBestAccuracy > bestAccuracy) {
            bestAccuracy = currBestAccuracy;
            bestFeatures = features;
        }
        cout << "Feature set " << setToString(features) << " was best, accuracy is " << currBestAccuracy << "%" << endl;
    }
    cout << "Finished search!! The best feature subset is " << setToString(bestFeatures) << ", which has an accuracy of " << bestAccuracy << "%" << endl;
}

void backwardElimination(vector<object>& data) {

}

double leaveOneOutCrossValidation(vector<object>& data, set<int>& features) {

}