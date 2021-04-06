#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

// https://www.programiz.com/dsa/longest-common-subsequence
// Complete the commonChild function below.
int commonChild(string s1, string s2) {
    int lcs = 0;
    // We can actually do this with table(2), since we don't need to trace the subsequence string.
    // https://www.geeksforgeeks.org/longest-common-substring-dp-29/
    vector<vector<int>> table(s1.size() + 1);

    for (size_t i = 0; i <= s1.size(); i++) {
        table[i].resize(s2.size() + 1, 0);

        if (i == 0)continue;

        for (size_t j = 1; j <= s2.size(); j++) {
            if (s1[i - 1] == s2[j - 1]) {
                table[i][j] += 1 + table[i - 1][j - 1]; // Find a common child element, so the lcs increase by 1.
                lcs = max(table[i][j], lcs);// Is this the biggest?
            }
            else {
                table[i][j] = max(table[i][j - 1], table[i - 1][j]); // Not a common child element, so the lcs doesn't change.
            }
        }
    }

    return lcs;
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));

    string s1;
    getline(cin, s1);

    string s2;
    getline(cin, s2);

    int result = commonChild(s1, s2);

    cout << result << "\n";

    // fout.close();

    return 0;
}
