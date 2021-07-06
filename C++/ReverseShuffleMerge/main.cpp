#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

// Implement base on https://www.hackerrank.com/challenges/reverse-shuffle-merge/forum/comments/77705
// Complete the reverseShuffleMerge function below.
string reverseShuffleMerge(string s) {
    int wantedCounts[26] = { 0 }, passedCounts[26] = { 0 }, AddedCounts[26] = { 0 };
    string result;

    for (char c : s) {
        wantedCounts[c - 'a'] ++;
    }

    for (int i = 0; i < 26; i++) {
        wantedCounts[i] = wantedCounts[i] / 2;
    }

    int lastIndex = s.size();
    for (int i = s.size() - 1; i >= 0 && result.size() < s.size() / 2; i--) {
        char c = s[i];
        int index = c - 'a';

        passedCounts[index] ++;
        if (wantedCounts[index] == AddedCounts[index]) {
            continue;// Ignore already filled.
        }

        if (wantedCounts[index] < passedCounts[index] - AddedCounts[index]) {// Cannot afford to miss this one.
            char smallest;
            do {
                smallest = 'z' + 1;
                // Find the smallest wanted character
                int n = i;
                for (int j = lastIndex - 1; j >= i; j--) {
                    if (s[j] < smallest && AddedCounts[s[j] - 'a'] < wantedCounts[s[j] - 'a']) {
                        smallest = s[j];
                        n = j;
                    }
                }

                result += smallest;
                AddedCounts[smallest - 'a'] ++;
                lastIndex = n;
            } while (smallest != c);// Until the cannot-afford-to-miss is added.
        }
        else {
            char smallest = 0;
            for (int i = 0; i < 26; i++) {
                if (wantedCounts[i] > AddedCounts[i]) {
                    // smallest wanted.
                    smallest = i + 'a';
                    break;
                }
            }

            if (smallest == c) {
                result += smallest;
                AddedCounts[smallest - 'a'] ++;
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
