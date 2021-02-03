#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <stack>
#include <deque>

using namespace std;

vector<string> split_string(string);

// Complete the poisonousPlants function below.
int poisonousPlants(vector<int> p) {
    vector<int> days(p.size());
    int minPoison = p[0];
    int maxDay = 0;
    stack<int> traversedIndexs;

    traversedIndexs.push(0);

    for (int i = 1; i < p.size(); i++) // Start from index = 1
    {
        if (p[i] > p[i - 1]) {
            days[i] = 1; // Greater than the immediate left
        }

        minPoison = min(minPoison, p[i]);// Mark mallest.

        while (!traversedIndexs.empty() && p[traversedIndexs.top()] >= p[i]) // Less or equal than the immediate left
        {
            if (p[i] > minPoison) {// Bigger or equal than the smallest on the left
                days[i] = max(days[i], days[traversedIndexs.top()] + 1); // Die after all non-less numbers on its left die - the die day is the biggest die day on its left + 1.
            }

            traversedIndexs.pop(); // Remove trace, since this number won't be relevant to the numbers behind.
        }

        maxDay = max(maxDay, days[i]); // Is this the max day?
        traversedIndexs.push(i); // Mark trace for future number comparision.
    }

    return maxDay;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string p_temp_temp;
    getline(cin, p_temp_temp);

    vector<string> p_temp = split_string(p_temp_temp);

    vector<int> p(n);

    for (int i = 0; i < n; i++) {
        int p_item = stoi(p_temp[i]);

        p[i] = p_item;
    }

    int result = poisonousPlants(p);

    cout << result << "\n";

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
