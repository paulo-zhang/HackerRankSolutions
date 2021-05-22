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
    vector<int> count(201, 0); // Use counting sort concept.

    for (size_t i = 0; i < expenditure.size(); i++) {
        if (i >= d) {// Ready to use the previous d elements.
            // Find double median;
            int double_median = 0;
            int p = 0;
            for (int j = 0; j <= count.size(); j++) {
                if (count[j] == 0)continue;
                p += count[j];
                if (p * 2 == d) {
                    int n = j; // j is the 'middle number' of the even list. d is a even number.
                    while (count[++n] == 0); // The next number is the other 'middle number' of the even list.
                    double_median = j + n;
                    break;
                }
                else if (p * 2 > d) {
                    double_median = 2 * j; // The two middle numbers must be j, regardless of d being an odd or even number.
                    break;
                }
            }

            if (double_median <= expenditure[i]) { // One notification.
                totalNotifications++;
            }

            count[expenditure[i - d]] --;// Remove the oldest from next sort.
        }

        // Add element for next counting sort.
        count[expenditure[i]] ++;
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
