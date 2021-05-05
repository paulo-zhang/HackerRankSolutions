#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);
// Largest Rectangle area problem:
// https://www.geeksforgeeks.org/largest-rectangle-under-histogram/
// Complete the riddle function below.
vector<long> riddle(vector<long> arr) {
    // complete this function
    stack<long> s;
    vector<long> maxRiddle(arr.size(), 0);
    int i = 0;
    while(i < arr.size() || !s.empty()){
        if(s.empty() || i < arr.size() && arr[i] >= arr[s.top()]){
            s.push(i ++);
        }
        else {
            int n = s.top();
            s.pop();
            int range = s.empty() ? i : i - s.top() - 1;
            maxRiddle[range - 1] = max(maxRiddle[range - 1], arr[n]);
        }
    }
    
    for(int j = maxRiddle.size() - 2;j >= 0; j --){
        maxRiddle[j] = max(maxRiddle[j + 1], maxRiddle[j]);
    }
    
    return maxRiddle;
}

int main()
{
    ofstream fout("output");
    ifstream fin("input01.txt");

    int n;
    fin >> n;
    fin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(fin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<long> arr(n);

    for (int i = 0; i < n; i++) {
        long arr_item = stol(arr_temp[i]);

        arr[i] = arr_item;
    }

    vector<long> res = riddle(arr);

    for (int i = 0; i < res.size(); i++) {
        fout << res[i];

        if (i != res.size() - 1) {
            fout << " ";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
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
