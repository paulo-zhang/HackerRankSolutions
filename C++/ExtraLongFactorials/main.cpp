#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'extraLongFactorials' function below.
 *
 * The function accepts INTEGER n as parameter.
 */

void extraLongFactorials(int n) {
    list<int> result(1, 1);
    int m = 1;
    while(++m <= n){
        int carrying = 0;
        for(auto it = result.rbegin(); it != result.rend(); ++it){
            int total = *it * m + carrying;
            carrying = total / 10;
            *it = total % 10;
        }

        while(carrying > 0)
        {
            result.insert(result.begin(), carrying % 10);
            carrying = carrying / 10;
        }
    }
    
    for(auto i : result){
        cout << i;
    }
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    extraLongFactorials(n);

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
