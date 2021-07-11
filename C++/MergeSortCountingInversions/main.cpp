#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

vector<string> split_string(string);

// Same as: https://www.hackerrank.com/challenges/insertion-sort/problem
// More slolutions: https://afteracademy.com/blog/inversion-count-in-an-array
long merge(vector<int>& arr, size_t left, size_t mid, size_t right, vector<int>& temp) {
    size_t i = left;
    size_t j = mid;
    size_t n = left;
    long count = 0;

    while (i < mid && j < right) {
        if (arr[i] > arr[j]) {
            temp[n++] = arr[j++];
            count += mid - i; // The trick!!!!
        }
        else {
            temp[n++] = arr[i++];
        }
    }

    while (i < mid) {
        temp[n++] = arr[i++];
    }

    while (j < right) {
        temp[n++] = arr[j++];
    }

    // copy
    while (n-- > left) {
        arr[n] = temp[n];
    }

    return count;
}

long mergeSort(vector<int>& arr, size_t left, size_t right, vector<int>& temp) {
    if (right - left <= 1)return 0;

    size_t mid = (right - left) / 2 + left;
    long count = 0;

    count += mergeSort(arr, left, mid, temp);
    count += mergeSort(arr, mid, right, temp);

    count += merge(arr, left, mid, right, temp);

    return count;
}

// Complete the countInversions function below.
long countInversions(vector<int> arr) {
    vector<int> temp(arr.size());

    long count = mergeSort(arr, 0, arr.size(), temp);
    return count;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string arr_temp_temp;
        getline(cin, arr_temp_temp);

        vector<string> arr_temp = split_string(arr_temp_temp);

        vector<int> arr(n);

        for (int i = 0; i < n; i++) {
            int arr_item = stoi(arr_temp[i]);

            arr[i] = arr_item;
        }

        long result = countInversions(arr);

        cout << result << "\n";
    }

    //fout.close();

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
