#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Rational: Find the number of the free time units freeCount from the deadline backward.
 * If the time units are not used, marke them as used.
 * The max overshoot lastMax = lastMax + m - freeCount.
 */

int lastMax = 0;
int start = 0;
vector<bool> freeUnits(100001, true);// All free units
int taskScheduling(int d, int m) {
    int freeCount = 0; // the number of free time units before deadline.
    int i = d - 1;
    for(; i >= start && freeCount < m; --i){
        if(freeUnits[i]){
            freeCount ++;
            freeUnits[i] = false; // Always occupy the largest possible time unit.
        }
    }
    
    if(i < start){
        start = d; // All previus time units are marked.
    }
    // cout << "d: " << d << ", m: " << m << ", free: " << freeCount << ", last: " << lastMax << "\n";
    lastMax += m - freeCount;
    
    return lastMax;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int d = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        int result = taskScheduling(d, m);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
