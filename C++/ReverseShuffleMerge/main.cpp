#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

string getMinString(string& A1, int index, string& s, int pos, vector<bool>& selected, string result) {
    pos = s.find(A1[index], pos);
    if (pos == string::npos || A1.size() - result.size() > s.size() - pos) {
        return result;
    };

    selected[index] = true;
    result += A1[index];
    pos++;

    if (result.size() == A1.size()) {
        return result;
    }

    for (int i = 0; i < A1.size(); i++) {
        if (selected[i]) continue;

        string str = getMinString(A1, i, s, pos, selected, result);
        if (str.size() == A1.size()) {
            return str;
        }
    }

    selected[index] = false;
    return result.erase(result.size() - 1, 1);
}

// Complete the reverseShuffleMerge function below.
string reverseShuffleMerge(string s) {
    string copy = s;
    sort(copy.begin(), copy.end());
    string A1;
    for (int i = 0; i < copy.size(); i += 2) {
        A1 += copy[i];
    }

    reverse(s.begin(), s.end());

    vector<bool> selected(A1.size(), false);

    for (int i = 0; i < A1.size(); i++) {
        string result = getMinString(A1, i, s, 0, selected, "");
        if (result.size() == A1.size()) {
            return result;
        }
    }

    return "No found.";
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = reverseShuffleMerge(s);

    cout << result << "\n";

    // fout.close();

    return 0;
}
