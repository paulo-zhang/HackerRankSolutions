#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

vector<string> split_string(string);

// Complete the almostSorted function below.
void almostSorted(vector<int> arr) {
    int l = -1, r = -1;
    int ascending = 0;

    for (size_t i = 0; i < arr.size() - 1; i++) {
        if (l == -1) {
            // Step 1: find l
            if (arr[i] > arr[i + 1]) {
                l = i;
            }
        }
        else if (ascending == 0) { // Step2: decide ascending or descending in the middle
            if (arr[i] < arr[i + 1]) {
                ascending = 1;// ascending
            }
            else if (arr[i] > arr[i + 1]) {
                ascending = -1; // descending
            }
        }
        else if (r == -1) {
            // Step3: find r 
            if (ascending == 1) {
                if (arr[i] > arr[i + 1]) {
                    r = ++i;
                }
            }
            else if (arr[i] < arr[i + 1]){
                r = i;
            }
        }
        else if (arr[i] > arr[i + 1]) {
            // Step 4: make sure the rest are ordered.
            cout << "no";
            return;
        }
    }

    if (l == -1) { // Step 1 not finished.
        cout << "yes";
    }
    else if (ascending == 0) {// Step 2 not finished: all equal.
        r = l + 1;
    }
    else if (r == -1) {
        if (ascending == 1) {
            r = l + 1;// Only possibility for r is the next number.
        }
        else {
            r = arr.size() - 1; // r is the last number
        }
    }
    
    // Try reserse
    if (ascending == -1 && r - l > 2 &&
        (l == 0 || arr[r] >= arr[l - 1]) && (r == arr.size() - 1 || arr[l] <= arr[r + 1])) {
        cout << "yes" << endl << "reverse " << l + 1 << " " << r + 1;
        return;
    }

    // Try swap with l & r
    if ((l == 0 || arr[r] >= arr[l - 1]) &&
        (arr[r] <= arr[l + 1] &&
        arr[l] >= arr[r - 1] || r - l > 1 )&&
        (r == arr.size() - 1 || arr[l] <= arr[r + 1])) {
        cout << "yes" << endl << "swap " << l + 1 << " " << r + 1;
        return;
    }

    cout << "no";
}

int main()
{
    ifstream fin("input22.txt");
    int n;
    fin >> n;
    fin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(fin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    almostSorted(arr);

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char& x, const char& y) {
        return x == y and x == ' ';
        });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
