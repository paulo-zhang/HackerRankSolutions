#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

vector<string> split_string(string);

// Complete the maximumSum function below.
long maximumSum(vector<long> a, long m) {
    // https://www.quora.com/What-is-the-logic-used-in-the-HackerRank-Maximise-Sum-problem
    // (a+b)%M=(a%M+b%M)%M  --- 1
    // (a−b)%M=(a%M−b%M)%M  --- 2
    // sumModular[i,j]=(prefix[j]−prefix[i−1]+M)%M  --3
    // If prefix[j] < prefix[i], we have: (prefix[i]−prefix[j]+M)%M=prefix[i]−prefix[j]<=prefix[i]
    long max_sum = 0;

    vector<long> prefix(a.size());
    set<long> ordered_prefix;
    prefix[0] = a[0] % m;
    ordered_prefix.insert(prefix[0]);

    for (int i = 1; i < a.size(); i++) {
        prefix[i] = (prefix[i - 1] + a[i]) % m;
        // This maybe the bigger one.
        max_sum = max(max_sum, prefix[i]);

        // Find the first prefix that is bigger than current one, because that's the only way to make a bigger sumModular[i,j].
        for (long p : ordered_prefix) {
            if (p > prefix[i]) {
                // Create a bigger module between prefixs[i] and p.
                max_sum = max(max_sum, (prefix[i] - p + m) % m);
                break;
            }
        }

        ordered_prefix.insert(prefix[i]);
    }

    return max_sum;
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string nm_temp;
        getline(cin, nm_temp);

        vector<string> nm = split_string(nm_temp);

        int n = stoi(nm[0]);

        long m = stol(nm[1]);

        string a_temp_temp;
        getline(cin, a_temp_temp);

        vector<string> a_temp = split_string(a_temp_temp);

        vector<long> a(n);

        for (int i = 0; i < n; i++) {
            long a_item = stol(a_temp[i]);

            a[i] = a_item;
        }

        long result = maximumSum(a, m);

        cout << result << "\n";
    }

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
