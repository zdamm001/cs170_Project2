#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>
#include <limits>
#include <cmath>
#include <ctime>

using namespace std;

struct object {
    double label;
    vector<double> features;
    object(double l) : label(l) { };
};

double squared(double x) {return x * x;}
string setToString(set<int>&);
void forwardSelection(vector<object>&);
void backwardElimination(vector<object>&);
double leaveOneOutCrossValidation(vector<object>&,set<int>&);

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
    clock_t start = clock();
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
    clock_t end = clock();
    cout << "Total time to complete: " << (end - start) / (double)CLOCKS_PER_SEC << " seconds." << endl;
    return 0;
}

string setToString(set<int>& s) {
    string x = "{";
    if (!s.size()) return x + "}";
    for (auto i : s) x+=to_string(i+1) + ",";
    x.back() = '}';
    return x;
}

void forwardSelection(vector<object>& data) {
    int numFeatures = data.front().features.size();
    set<int> features;
    set<int> bestFeatures;
    double bestAccuracy = -1;
    cout << "Beginning Search." << endl;
    for (int i = 0; i < numFeatures; ++i) {
        cout << "On the " << i + 1 << "th level of the search tree" << endl;
        int bestFeature = -1;
        double currBestAccuracy = -1;
        for (int j = 0; j < numFeatures; ++j) {
            if (features.find(j) != features.end()) continue;
            cout << "Considering adding the " << j + 1 << " feature" << endl;
            features.insert(j);
            double accuracy = leaveOneOutCrossValidation(data,features);
            cout << "Using feature(s) " << setToString(features) << " accuracy is " << accuracy << "%" << endl;
            features.erase(j);
            if (accuracy > currBestAccuracy) {
                currBestAccuracy = accuracy;
                bestFeature = j;
            }
        }
        features.insert(bestFeature);
        cout << "On level " << i + 1 << " I added feature " << bestFeature + 1 << " to current set." << endl;
        if (currBestAccuracy > bestAccuracy) {
            bestAccuracy = currBestAccuracy;
            bestFeatures = features;
        }
        cout << "Feature set " << setToString(features) << " was best, accuracy is " << currBestAccuracy << "%" << endl;
    }
    cout << "Finished search!! The best feature subset is " << setToString(bestFeatures) << ", which has an accuracy of " << bestAccuracy << "%" << endl;
}

void backwardElimination(vector<object>& data) {
    int numFeatures = data.front().features.size();
    set<int> features;
    set<int> bestFeatures;
    double bestAccuracy = -1;
    for (int i = 0; i < numFeatures; ++i) {
        features.insert(i);
    }
    bestAccuracy = leaveOneOutCrossValidation(data, features);
    bestFeatures = features;
    cout << "Using feature(s) " << setToString(bestFeatures) << " accuracy is " << bestAccuracy << "%" << endl;
    cout << "Beginning Search." << endl;
    for (int i = numFeatures - 1; i > 0; --i) {
        cout << "On the " << i + 1 << "th level of the search tree" << endl;
        int bestFeature = -1;
        double currBestAccuracy = -1;
        for (int j = 0; j < numFeatures; ++j) {
            if (features.find(j) == features.end()) continue;
            cout << "Considering removing the " << j + 1 << " feature" << endl;
            features.erase(j);
            double accuracy = leaveOneOutCrossValidation(data,features);
            cout << "Using feature(s) " << setToString(features) << " accuracy is " << accuracy << "%" << endl;
            features.insert(j);
            if (accuracy > currBestAccuracy) {
                currBestAccuracy = accuracy;
                bestFeature = j;
            }
        }
        features.erase(bestFeature);
        cout << "On level " << i + 1 << " I removed feature " << bestFeature + 1 << " from current set." << endl;
        if (currBestAccuracy > bestAccuracy) {
            bestAccuracy = currBestAccuracy;
            bestFeatures = features;
        }
        cout << "Feature set " << setToString(features) << " was best, accuracy is " << currBestAccuracy << "%" << endl;
    }
    cout << "Finished search!! The best feature subset is " << setToString(bestFeatures) << ", which has an accuracy of " << bestAccuracy << "%" << endl;
}

double leaveOneOutCrossValidation(vector<object>& data, set<int>& features) {
    int numCorrectlyClassified = 0;
    for (int i = 0; i < data.size(); ++i) {
        object objToClassify = data.at(i);
        double objToClassifyLabel = objToClassify.label;
        double nearestNeighborDistance = numeric_limits<double>::infinity();
        double nearestNeighborLocation = numeric_limits<double>::infinity();
        double nearestNeighborLabel = -1;
        for (int j = 0; j < data.size(); ++j) {
            if (j != i) {
                double distance = 0;
                for (int k = 0; k < objToClassify.features.size(); ++k) {
                    if (features.find(k) == features.end()) continue;
                    distance += squared(objToClassify.features.at(k) - data.at(j).features.at(k));
                }
                distance = sqrt(distance);
                if (distance < nearestNeighborDistance) {
                    nearestNeighborDistance = distance;
                    nearestNeighborLocation = j;
                    nearestNeighborLabel = data.at(j).label;
                }
            }      
        }     
        if (objToClassifyLabel == nearestNeighborLabel) { 
            ++numCorrectlyClassified;
        }
    }
    double accuracy = (double) numCorrectlyClassified / data.size();
    return accuracy * 100;
}