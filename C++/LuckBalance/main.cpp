#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

vector<string> split_string(string);

// Complete the luckBalance function below.
int luckBalance(int k, vector<vector<int>> contests) {
    int luck = 0;
    for (int i = 0; i < contests.size(); i++) {
        if (contests[i][1] == 0) {
            luck += contests[i][0];
            contests.erase(contests.begin() + i);
            i--;
        }
    }

    sort(contests.begin(), contests.end(), [](vector<int> item1, vector<int> item2)
        {
            return item1[0] > item2[0];
        });

    for (int i = 0; i < contests.size(); i++) {
        if (k > 0 && contests[i][1] == 1) {
            k--;
            luck += contests[i][0];
        }
        else if (contests[i][1] == 0) {
            luck += contests[i][0];
        }
        else {
            luck -= contests[i][0];
        }
    }

    return luck;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    vector<vector<int>> contests(n);
    for (int i = 0; i < n; i++) {
        contests[i].resize(2);

        for (int j = 0; j < 2; j++) {
            cin >> contests[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = luckBalance(k, contests);

    //fout << result << "\n";

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
