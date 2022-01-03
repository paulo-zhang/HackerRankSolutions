#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// Complete the abbreviation function below.
string abbreviation(string a, string b) {
    vector<vector<bool>> dp(b.size() + 1, vector<bool>(a.size() + 1, false));
    dp[0][0] = true;
    for(int i = 0;i <= b.size();i ++){
        for(int j = 1; j <= a.size(); j ++){
            if(i == 0){ // b is an empty string.
                dp[i][j] = dp[i][j - 1] && islower(a[j - 1]); // islower(a[j - 1]) = true means a[j - 1] can be deleted.
            }
            else {
                if(a[j - 1] == b[i - 1]){ // both upper case, cannot be deleted.
                    dp[i][j] = dp[i - 1][j - 1]; // depend on previous match result.
                }
                else if(toupper(a[j - 1]) == b[i - 1]){ // a[j - 1] is the same lower case letter.
                    dp[i][j] = dp[i][j - 1] // delete a[j - 1]
                    || dp[i - 1][j - 1]; // keep a[j - 1]
                }
                else if(islower(a[j - 1])) // a[j - 1] is a different letter, but is lower case.
                {
                    dp[i][j] = dp[i][j - 1];// only depend on deleted result.
                }
                else // not the same letter, we can also remove this branch.
                {
                    dp[i][j] = false; // neither deleting nor matching.
                }
            }
        }
    }
    
    return dp[b.size()][a.size()]?"YES":"NO";
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
