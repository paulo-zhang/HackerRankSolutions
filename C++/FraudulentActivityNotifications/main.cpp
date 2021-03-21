#include <string>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

vector<string> split_string(string);

// Complete the activityNotifications function below.
int activityNotifications(vector<int> expenditure, int d) {
    int totalNotifications = 0;
    int d1 = (d - 1) / 2, d2 = d / 2; // Two indexs to get the double_median.
    // vector<int> trailingNums(d); // Ordered trailing nums.
    vector<int> count(201, 0); // Use counting sort concept.
    int minValue = 201, maxValue = -1; // value range of trailingNums.

    for (size_t i = 0; i < expenditure.size(); i++) {
        if (i >= d) {// Ready to use the previous d elements.
            /*
            // Counting sort previous d elements into trailingNums.
            // https://www.geeksforgeeks.org/counting-sort/
            for(int j = minValue, n = 0;j <= maxValue && n < d; j ++){
                int m = count[j];
                while(m > 0){// Orderly copy into trailingNums.
                    trailingNums[n] = j;
                    n ++;
                    m --;
                }
            }
            // End Counting sort previous d elements into trailingNums.

            int double_median = trailingNums[d1] + trailingNums[d2];
            */

            // Find double median, no need to put the number into an array, just find the trick;
            int double_median = 0;
            for (int j = minValue, n = 0; j <= maxValue && n < d; j++) {
                int m = count[j];
                if (n <= d1 && d1 < m + n) {
                    double_median += j;
                }
                if (n <= d2 && d2 < m + n) {
                    double_median += j;
                }

                n += m;
            }

            if (double_median <= expenditure[i]) { // One notification.
                totalNotifications++;
            }

            int oldestIndex = i - d;
            count[expenditure[oldestIndex]] --;// Remove the oldest from next sort.
            if (count[expenditure[oldestIndex]] == 0) {
                if (expenditure[oldestIndex] == minValue) { // minValue changed.
                    while (minValue < expenditure[i] && count[++minValue] == 0);
                }

                if (expenditure[oldestIndex] == maxValue) { // maxValue changed.
                    while (maxValue > expenditure[i] && count[--maxValue] == 0);
                }
            }
        }

        // Add element for next counting sort.
        count[expenditure[i]] ++;
        minValue = min(minValue, expenditure[i]);
        maxValue = max(maxValue, expenditure[i]);
    }

    return totalNotifications;
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));
    ifstream fin("input01.txt");

    string nd_temp;
    getline(fin, nd_temp);

    vector<string> nd = split_string(nd_temp);

    int n = stoi(nd[0]);

    int d = stoi(nd[1]);

    string expenditure_temp_temp;
    getline(fin, expenditure_temp_temp);

    vector<string> expenditure_temp = split_string(expenditure_temp_temp);

    vector<int> expenditure(n);

    for (int i = 0; i < n; i++) {
        int expenditure_item = stoi(expenditure_temp[i]);

        expenditure[i] = expenditure_item;
    }

    int result = activityNotifications(expenditure, d);

    // fout << result << "\n";

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
