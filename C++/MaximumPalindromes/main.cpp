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

int M = 1000000007;
vector<vector<int>> letters;
vector<ulong> factorials;
void initialize(string s) {
    // This function is called once before all queries.
    factorials.resize(s.size());
    int i = 0;
    for_each(s.begin(), s.end(), [](auto c){
        if(i == 0){
            letters.push_back(vector<int>(26));
            factorials[i] = 1;
        }
        else{
            letters.push_back(letters[i - 1]);
            factorials[i] *= (i + 1);
        }

        letters[i ++][c - 'a'] ++;
    });
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
// So the goal is to caculate: {X * (A + B + C ...)! / (A! * B! * C! ...) % M
// or {X * (A + B + C ...)! * [A^(M-2) % M] * [B^(M-2) % M] * [B^(M-2) % M]} % M
// Where A, B, C is the count of pair of one letter, X is the number of single letter (middle letter in a palindrome), M = 1000000007.

int answerQuery(int l, int r) {
    // Return the answer for this query modulo 1000000007
    int evenPairCount = 0, // A, B, C ...
    singleLetterCount = 0; // X
    ulong denunminator = 1; // (A! * B! * C! ...)
    for(int i = 0; i < 26; i++){
        int letterCount = letters[r - 1][i] - letters[l - 1][i];
        evenPairCount += letterCount / 2;
        singleLetterCount += letterCount % 2;
        denunminator *= factorials[evenPairCount - 1];
    }

    return (singleLetterCount * factorials[evenPairCount] / denunminator) % M;
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
