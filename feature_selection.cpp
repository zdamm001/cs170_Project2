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
    if (!s.size()) return x + "}";
    for (auto i : s) x+=to_string(i+1) + ",";
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

}

double leaveOneOutCrossValidation(vector<object>& data, set<int>& features) {
    return 0.001;
    //number_correctly_classfied = 0;
 
    //for i = 1 : size(data,1)
    //   object_to_classify = data(i,2:end); 
    //   label_object_to_classify = data(i,1);
    //   
    //   nearest_neighbor_distance = inf;
    //   nearest_neighbor_location = inf;
    //   for k = 1 : size(data,1)
    //       if k ~= i
    //            distance = sqrt(sum((object_to_classify - data(k,2:end)).^2));
    //            if  distance <   nearest_neighbor_distance
    //                   nearest_neighbor_distance = distance;
    //                   nearest_neighbor_location = k;
    //                   nearest_neighbor_label    = data(nearest_neighbor_location,1);
    //            end
    //       end        
    //   end 
    //           
    //   if label_object_to_classify == nearest_neighbor_label; 
    //        number_correctly_classfied = number_correctly_classfied + 1;
    //   end
    //   
    //end 
    //accuracy = number_correctly_classfied / size(data,1);
}