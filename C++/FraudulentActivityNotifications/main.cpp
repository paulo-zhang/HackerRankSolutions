#include <string>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

vector<string> split_string(string);

// Complete the activityNotifications function below.
int activityNotifications(vector<int> expenditure, int d) {
    int totalNotifications = 0;
    multiset<int> trailingNums;
    queue<multiset<int>::iterator> q;
    int d1 = (d - 1) / 2, d2 = d / 2;

    for (size_t i = 0; i < expenditure.size(); i++) {
        if (i >= d) {
            auto it1 = trailingNums.begin();
            advance(it1, d1);
            auto it2 = it1;
            if (d1 != d2) {
                advance(it2, d2 - d1);
            }

            int doubleMedian = *it1 + *it2;
            if (expenditure[i] >= doubleMedian) {
                totalNotifications++;
            }
        }

        if (trailingNums.size() < d || expenditure[i] != expenditure[i - d]) {
            auto it = trailingNums.insert(expenditure[i]);
            q.push(it);
        }

        if (q.size() > d) {
            auto it = q.front();
            q.pop();
            trailingNums.erase(it);
        }
    }

    return totalNotifications;
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));
    ifstream fin("input01.txt");

    string nd_temp;
    getline(fin, nd_temp);

    vector<string> nd = split_string(nd_temp);

    int n = stoi(nd[0]);

    int d = stoi(nd[1]);

    string expenditure_temp_temp;
    getline(fin, expenditure_temp_temp);

    vector<string> expenditure_temp = split_string(expenditure_temp_temp);

    vector<int> expenditure(n);

    for (int i = 0; i < n; i++) {
        int expenditure_item = stoi(expenditure_temp[i]);

        expenditure[i] = expenditure_item;
    }

    int result = activityNotifications(expenditure, d);

    // fout << result << "\n";

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
