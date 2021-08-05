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
 
 
// https://www.hackerrank.com/challenges/maximum-palindromes/forum/comments/448266
// https://www.geeksforgeeks.org/fermats-little-theorem/
// So the goal is to caculate: {X * (A + B + C ...)! / (A! * B! * C! ...) % M
// or {X * (A + B + C ...)! * [A^(M-2) % M] * [B^(M-2) % M] * [B^(M-2) % M]} % M
// Where A, B, C is the count of pair of one letter, X is the number of single letter (middle letter in a palindrome), M = 1000000007.

constexpr int M = 1000000007;
vector<vector<int>> letters;
vector<ulong> modularFactorials;
vector<ulong> ModularInverseOfFactorial;

ulong modularPower(ulong x, ulong y){
    // cout << "x: " << x << ", y: " << y << "\n";
    if(y < 0) return 0;
    if(y == 0) return 1;
    if(y == 1) return x;
    if(y % 2 == 0) return modularPower((x * x) % M, y / 2);
    else  return (x * modularPower((x * x) % M, (y - 1) / 2)) % M;
}

void initialize(string s) {
    // This function is called once before all queries.
    modularFactorials.resize(s.size());
    int i = 0;
    for_each(s.begin(), s.end(), [&i](auto c){
        if(i == 0){
            letters.push_back(vector<int>(26, 0));
            modularFactorials[i] = 1;
        }
        else{
            letters.push_back(letters[i - 1]);
            // N! % M = (N...(((1 % M) * 2) % M) % M ...) %M
            modularFactorials[i] = (modularFactorials[i - 1] * (i + 1)) % M;
        }

        letters[i][c - 'a'] ++;
        ModularInverseOfFactorial.emplace_back(modularPower(modularFactorials[i], M -2));
        // cout << "fact-mod: " << modularFactorials[i] << ", fact[" << i << "]: " << modularFactorials[i] << ", c: " << c << ", count: " << letters[i][c - 'a'] << "\n";
        i ++;
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

int answerQuery(int l, int r) {
    // Return the answer for this query modulo 1000000007
    ulong totalEvenPairCount = 0, // A, B, C ...
    singleLetterCount = 0; // X
    ulong multiplicativeInverse = 1; // [A^(M-2) % M] * [B^(M-2) % M] * [B^(M-2) % M]} % M
    for(int i = 0; i < 26; i++){
        int letterCount = l - 2 < 0 ? letters[r - 1][i] : letters[r - 1][i] - letters[l - 2][i];
        int evenPairCount = letterCount / 2;
        totalEvenPairCount += evenPairCount;
        singleLetterCount += letterCount % 2;
        if(evenPairCount > 0){
            multiplicativeInverse = (multiplicativeInverse * ModularInverseOfFactorial[evenPairCount - 1]) % M;
        }
    }
    
    if(singleLetterCount == 0) singleLetterCount = 1;
    ulong factorial = 1;
    if(totalEvenPairCount > 0){
        factorial = modularFactorials[totalEvenPairCount - 1];
    }

    // cout << "single: " << singleLetterCount << ", fact[" << totalEvenPairCount << "]: " << factorial << ", multi-inverse: " << multiplicativeInverse << "\n";
    
    // The same as: return (singleLetterCount * factorial * multiplicativeInverse) % M;
    return (singleLetterCount * ((factorial * multiplicativeInverse) % M)) % M; // Really big number.
}

int main()
{
    ofstream fout("output.txt");
    ifstream fin("input27.txt");

    string s;
    getline(fin, s);

    initialize(s);

    string q_temp;
    getline(fin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(fin, first_multiple_input_temp);

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
