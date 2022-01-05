#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

// https://www.programiz.com/dsa/longest-common-subsequence
// Complete the commonChild function below.
int commonChild(string s1, string s2)
{
    // https://www.geeksforgeeks.org/longest-common-substring-dp-29/
    vector<vector<int>> table(2, vector<int>(s2.size() + 1, 0));

    for (size_t i = 1; i <= s1.size(); i++)
    {
        for (size_t j = 1; j <= s2.size(); j++) {
            int row = i & 1;
            int preRow = row ^ 1;
            if (s1[i - 1] == s2[j - 1]) {
                table[row][j] = 1 + table[preRow][j - 1]; // Find a common child element, so the lcs increase by 1.
            }
            else {
                table[row][j] = max(table[row][j - 1], table[preRow][j]); // Not a common child element, so the lcs doesn't change.
            }
        }
    }

    return table[s1.size() & 1][s2.size()];
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
