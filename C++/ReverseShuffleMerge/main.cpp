#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

// Implement base on https://www.hackerrank.com/challenges/reverse-shuffle-merge/forum/comments/77705
// Complete the reverseShuffleMerge function below.
string reverseShuffleMerge(string s) {
    map<char, int> counts;
    string result;

    for (char c : s) {
        counts[c] ++;
    }

    for (auto it : counts) {
        counts[it.first] = it.second / 2;
    }

    int lastIndex = s.size();
    map<char, int> passedCounts, AddedCounts;
    for (int i = s.size() - 1; i >= 0 && result.size() < s.size() / 2; i--) {
        char c = s[i];

        passedCounts[c] ++;
        if (counts[c] == AddedCounts[c]) {
            continue;// Ignore
        }

        if (counts[c] < passedCounts[c] - AddedCounts[c]) {// Cannot afford to miss this one.
            char smallest;
            do {
                smallest = 'z' + 1;
                // Find the smallest wanted character
                int n = i;
                for (int j = lastIndex - 1; j >= i; j--) {
                    if (s[j] < smallest && AddedCounts[s[j]] < counts[s[j]]) {
                        smallest = s[j];
                        n = j;
                    }
                }

                result += smallest;
                AddedCounts[smallest] ++;
                lastIndex = n;
            } while (smallest != c);
        }
        else {
            char smallest = 0;
            for (auto it : counts) {
                if (it.second > AddedCounts[it.first]) {
                    // smallest wanted.
                    smallest = it.first;
                    break;
                }
            }

            if (smallest == c) {
                result += smallest;
                AddedCounts[smallest] ++;
                lastIndex = i;
            }
        }
    }

    return result;
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
