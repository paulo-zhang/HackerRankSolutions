#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

vector<string> split_string(string);
//For this problem we want to store the Max Sum possible for each position in the array.
//
//(Since we need to skip adjacent elements we can't just iterate directly through the array)
//    1. We need to figure out the max values for the first 2 positions manually.
//    2. The max position for the first value can only be the first value(since the problem specifies it must be a subset of the array)
//    3. The max position for the second value can only be either the current value or the previous value.
//    4. From there we need to iterate over the remain values, and calulate their max possible sum(Hint: don't start you loop at the 0 index)
//
//The max possible value for the current position can only be 3 things.
//    1. The Current Element Plus the Max Value from 2 positions ago(This handles the Adjacent)
//    2. The last max Value e.g(imagine the first value in the array was negative, and the second value was positive, and the current value is 0)
//    3. The current element e.g(the max value from 2 positions ago could have been negative)

//    Correction: 3 is not true as an example of -2 -3 -1 is deemed as 0 i.e. substring could be 0 in length

// Complete the maxSubsetSum function below.
int maxSubsetSum(vector<int> arr) {
    if (arr.size() <= 1)return max(arr[0], 0);

    int pre1, pre2;

    pre1 = max(arr[0], 0);
    pre2 = max(arr[0], arr[1]);
    for (int i = 2; i < arr.size(); i++) {
        int v1 = arr[i] + pre1;
        pre1 = pre2;
        pre2 = max(arr[i], max(v1, pre2));
    }

    return pre2;
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));
    ifstream fin("input23.txt");

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

    int res = maxSubsetSum(arr);

    cout << res << "\n";

    // fout.close();

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
