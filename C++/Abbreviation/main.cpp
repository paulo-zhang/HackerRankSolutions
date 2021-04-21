#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// Complete the abbreviation function below.
string abbreviation(string a, string b) {
    a += 'z' + 1;
    b += 'z' + 1;
    vector<int> matches(b.size());

    int a_start = 0;
    for (int i = 0; i < b.size(); i++) {
        int j = a_start;
        for (; j < a.size(); j++) {
            if (a[j] == b[i] + 'a' - 'A' || a[j] == b[i]) {
                matches[i] = j;
                a_start = j + 1;
                // cout << "match: " << i << "-" << j << ", ";
                break;
            }
            else if (a[j] < 'a') {
                // Not matched uppercase.
                int k = i - 1;
                while (k >= 0)
                {
                    if (a[matches[k]] < 'a') {
                        j = matches[k];
                    }
                    else if (a[j] == b[k]) {
                        break;
                    }

                    k--;
                }

                if (k < 0) {
                    return "NO";
                }

                i = k; // back to k.
                matches[i] = j;
                a_start = j + 1;
                break;
            }
        }

        if (j >= a.size()) {
            return "NO";
        }
    }

    return "YES";
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));
    ifstream fin("input14.txt");

    int q;
    fin >> q;
    fin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string a;
        getline(fin, a);

        string b;
        getline(fin, b);

        string result = abbreviation(a, b);

        cout << result << "\n";
    }

    // fout.close();

    return 0;
}
