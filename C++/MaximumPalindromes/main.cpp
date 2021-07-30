#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'initialize' function below.
 *
 * The function accepts STRING s as parameter.
 */

string str;
void initialize(string s) {
    // This function is called once before all queries.
    str = s;
}

/*
 * Complete the 'answerQuery' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER l
 *  2. INTEGER r
 */

// https://www.hackerrank.com/challenges/maximum-palindromes/forum/comments/448266
// https://www.geeksforgeeks.org/fermats-little-theorem/

int answerQuery(int l, int r) {
    // Return the answer for this query modulo 1000000007.
    int evenLetterCount = 0; // n
    vector<int> restCounts(26, 0);
    
    for(int i = l - 1; i < r; ++i)
    {
        restCounts[str[i] - 'a'] ++;
        if(restCounts[str[i] - 'a'] == 2)
        {
            evenLetterCount ++;
        }
    }
    
    long result = 1;
    int n = evenLetterCount;
    // n!
    while(n > 1)
    {
        result = n * result;
        n --;
    }
    
    int letterCount = 0;
    for(int c : restCounts)
    {
        if(c % 2 != 0)
        {
            letterCount ++;
        }
        
        int even = c / 2;
        while(--even > 0)
        {
            result = evenLetterCount * result;
        }
    }
    
    if(letterCount > 0)
    {
        result = letterCount * result;
    }
    
    return result  % 1000000007;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    initialize(s);

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int l = stoi(first_multiple_input[0]);

        int r = stoi(first_multiple_input[1]);

        int result = answerQuery(l, r);

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
