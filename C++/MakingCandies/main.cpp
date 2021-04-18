#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

vector<string> split_string(string);

// Complete the minimumPasses function below.
long minimumPasses(long long m, long long w, long long p, long long n) {
    long long products = 0;
    long long passes = 0, min_pass = LLONG_MAX;
    
    do {
        // https://www.hackerrank.com/challenges/making-candies/forum/comments/516277?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=search
        // (m > LLONG_MAX / w): Purely to deal with data overflow.
        long long gaps = (m > LLONG_MAX / w) ? 1 : (n - products) / (w * m); // If we don't buy any more power, how many more steps needed?
        long long steps = (m > LLONG_MAX / w) ? 1 : (p - products) / (w * m); // How many steps to be able to buy more power?
        steps = min(steps, gaps);
        if (steps <= 0) {
            // Invest plan
            long more_power = products / p;
            products = products % p;
            steps = 1;

            // Invest
            if (m >= w + more_power) {
                w += more_power;
            }
            else if (w >= m + more_power) {
                m += more_power;
            }
            else {
                long total = m + w + more_power;
                m = total / 2;
                w = total - m;
            }
        }

        passes += steps;
        if (steps * m > LLONG_MAX / w) { // Purely to deal with data overflow
            break;
        }

        // Build product.
        products += m * w * steps;

        gaps = (n - products + w * m - 1) / (w * m); // If we don't buy any more power, how many more steps needed?
        min_pass = min(min_pass, passes + gaps);
        // cout << passes << "-" << min_pass << ":" << w << "*" << m << "=" << products << endl;
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
