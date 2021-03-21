#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <algorithm>

using namespace std;

vector<string> split_string(string);

// Complete the maximumToys function below.
int maximumToys(vector<int> prices, int k) {
    multiset<int> toyBasket;
    int totalValue = 0;
    for (auto it = prices.begin(); it != prices.end(); it++) {
        if (*it > k)continue;

        if (totalValue + *it <= k) {
            totalValue += *it;
            toyBasket.insert(*it);
            continue;
        }

        auto last = toyBasket.end();
        advance(last, -1);
        if (*it < *last) {
            totalValue += *it - *last;
            toyBasket.erase(last);
            toyBasket.insert(*it);
        }
    }

    return toyBasket.size();
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));
    fstream fin("input06.txt");

    string nk_temp;
    getline(fin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string prices_temp_temp;
    getline(fin, prices_temp_temp);

    vector<string> prices_temp = split_string(prices_temp_temp);

    vector<int> prices(n);

    for (int i = 0; i < n; i++) {
        int prices_item = stoi(prices_temp[i]);

        prices[i] = prices_item;
    }

    int result = maximumToys(prices, k);

    /*fout << result << "\n";

    fout.close();*/

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
