#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

vector<string> split_string(string);

// Complete the minimumPasses function below.
long minimumPasses(long long m, long long w, long long p, long long n) {
    long products = 0;
    long passes = 0, min_pass = LONG_MAX;

    do {
        // Either by all w/m or buy none.
        // (m > LLONG_MAX / w): Purely to deal with data overflow.
        long non_invest_steps = (m >= LONG_MAX / w) ? 1 : (n - products + w * m - 1) / (w * m); // If we don't buy any more w/m, how many more steps needed to fulfill the requirement?
        min_pass = min(min_pass, passes + non_invest_steps); // Can we use fewer steps to solve the problem without further calculation? Market down the minimum steps.
        long buy_none_steps = (m >= LONG_MAX / w) ? 1 : (p - products) / (w * m); // How many steps before being able to buy more w/m?
        buy_none_steps = min(buy_none_steps, non_invest_steps); // Fewer steps is chosen to meet the goal.
        if (buy_none_steps <= 0) {
            // Invest plan
            long wm = products / p;
            products = products % p;
            buy_none_steps = 1;

            // Invest
            if (m >= w + wm) {
                w += wm;
            }
            else if (w >= m + wm) {
                m += wm;
            }
            else {
                long total = m + w + wm;
                m = total / 2;
                w = total - m;
            }
        }

        passes += buy_none_steps;
        if (buy_none_steps * m >= LONG_MAX / w) { // Purely to deal with data overflow
            if (buy_none_steps * m >= LONG_MAX / w && buy_none_steps * m < LONG_MAX / w + 1) {
                // Really extreme cases when the newly added product is not enough to fill the requested n.
                // The test cases may never run into this area, but worth noting.
                long added = m * w * buy_none_steps; // New products, it's not overflowed.
                if (n - products > added) { // Avoid overflow over: products += added
                    products += added;
                    continue;
                }
            }
            break;
        }

        // Build product.
        products += m * w * buy_none_steps;
    } while (products < n);

    return min(passes, min_pass);
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));

    string mwpn_temp;
    getline(cin, mwpn_temp);

    vector<string> mwpn = split_string(mwpn_temp);

    long long m = stoll(mwpn[0]);

    long long w = stoll(mwpn[1]);

    long long p = stoll(mwpn[2]);

    long long n = stoll(mwpn[3]);

    long result = minimumPasses(m, w, p, n);

    cout << result << "\n";

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
