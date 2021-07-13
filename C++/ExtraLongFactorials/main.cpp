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
        for(auto it = result.rbegin(); it != result.rend(); ++it){
            *it *= m;
        }
        
        for(auto it = result.rbegin(); it != result.rend(); ++it){
            if(*it < 10)continue;
            
            int temp = *it / 10;
            *it = *it % 10;
            
            if(distance(it, result.rend()) == 1){
                result.insert(result.begin(), temp);
            }
            else{
                auto next = it;
                *(++next) += temp;
            }
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
