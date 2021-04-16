#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

vector<string> split_string(string);

long get_min_days(vector<long>& machines, long low, long high, long goal) {
    if (low >= high)return high;

    long mid = (high - low) / 2 + low;

    long products = 0;
    for (long m : machines) {
        products += mid / m;
    }

    if (products >= goal) {
        return get_min_days(machines, low, mid, goal);
    }

    return get_min_days(machines, mid + 1, high, goal);
}

// Complete the minTime function below.
long minTime(vector<long> machines, long goal) {
    long max_m = 0, min_m = LONG_MAX;
    for (long m : machines) {
        max_m = max(m, max_m);
        min_m = min(m, min_m);
    }

    long min_days = goal * min_m / machines.size();
    long max_days = (goal * max_m + machines.size() - 1) / machines.size();

    cout << min_days << "-" << max_days << ";";
    return get_min_days(machines, min_days, max_days, goal);
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));

    string nGoal_temp;
    getline(cin, nGoal_temp);

    vector<string> nGoal = split_string(nGoal_temp);

    int n = stoi(nGoal[0]);

    long goal = stol(nGoal[1]);

    string machines_temp_temp;
    getline(cin, machines_temp_temp);

    vector<string> machines_temp = split_string(machines_temp_temp);

    vector<long> machines(n);

    for (int i = 0; i < n; i++) {
        long machines_item = stol(machines_temp[i]);

        machines[i] = machines_item;
    }

    long ans = minTime(machines, goal);

    cout << ans << "\n";

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
