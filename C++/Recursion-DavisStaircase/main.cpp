#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

// For every step: solution[x] = solution[x] + solution[x - step]
// Question 9: https://www.educative.io/blog/crack-amazon-coding-interview-questions
int stepPerms(int n) {
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    for(int i = 1;i < dp.size(); ++i){
        int n = i - 1;
        dp[i] += dp[n];
        
        n = i - 2;
        if(n >= 0){
            dp[i] += dp[n];
        }
        
        n = i - 3;
        if(n >= 0){
            dp[i] += dp[n];
        }
    }
    
    return dp.back();
}

/*
// dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
int stepPerms(int n) {
    if(n == 1)return 1;
    if(n == 2)return 2;
    if(n == 3)return 4;
    
    int i = 3;
    int a1 = 1, a2 = 2, a3 = 4;
    while(i++ < n){
        int temp = a1 + a2 + a3;
        a1 = a2;
        a2 = a3;
        a3 = temp;
    }
    
    return a3;
}
*/

/* // Recursive solution.
int recursivePerms(vector<int> &memorized, int n){
    if(n == 0){memorized[n] = 1; return 1;}
    if(n < 0) return 0;
    
    if(memorized[n] > 0) return memorized[n];
    
    memorized[n] = recursivePerms(memorized, n - 1) + recursivePerms(memorized, n - 2) + recursivePerms(memorized, n - 3);
    return memorized[n];
}

int stepPerms(int n) {
    vector<int> memorized(n + 1, 0);
    
    return recursivePerms(memorized, n);
}
*/

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s_temp;
    getline(cin, s_temp);

    int s = stoi(ltrim(rtrim(s_temp)));

    for (int s_itr = 0; s_itr < s; s_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        int res = stepPerms(n);

        fout << res << "\n";
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
