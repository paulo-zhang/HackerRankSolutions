#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

// Get the cost to make a magic square.
int getCost(const vector<vector<int>> &s, const vector<vector<int>> &matrix){
    int result = 0;
    for(int i = 0;i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            result += abs(s[i][j] - matrix[i][j]);
        }
    }
    
    return result;
}

// A better performance way to rotate.
void rotateMatrix1(vector<vector<int>> &mat) {
    int N = mat.size();
    // Consider all squares one by one
    for (int x = 0; x < N / 2; x++) {
        // Consider elements in group
        // of 4 in current square
        for (int y = x; y < N - x - 1; y++) {
            // Store current cell in
            // temp variable
            int temp = mat[x][y];
 
            // Move values from right to top
            mat[x][y] = mat[y][N - 1 - x];
 
            // Move values from bottom to right
            mat[y][N - 1 - x]
                = mat[N - 1 - x][N - 1 - y];
 
            // Move values from left to bottom
            mat[N - 1 - x][N - 1 - y]
                = mat[N - 1 - y][x];
 
            // Assign temp to left
            mat[N - 1 - y][x] = temp;
        }
    }
}

// An easier way to rotate.
void rotateMatrix(vector<vector<int>> &mat) {
    int n = mat.size();
    int m = mat[0].size();
    vector<vector<int>> newMat(n, vector<int>(m));
    
    for(int i = 0;i < n; ++i){
        for(int j = 0;j < m; ++j){
            newMat[m - j - 1][i] = mat[i][j];
        }
    }
    
    mat.swap(newMat);
}

int formingMagicSquare(vector<vector<int>> s) {
    auto a1 = {8, 3, 4};
    auto a2 = {1, 5, 9};
    auto a3 = {6, 7, 2};
    
    vector<vector<int>> matrix{a1, a2, a3};
    int cost = getCost(s, matrix);
    
    rotateMatrix(matrix);
    cost = min(cost, getCost(s, matrix));
    
    rotateMatrix(matrix);
    cost = min(cost, getCost(s, matrix));
    
    rotateMatrix(matrix);
    cost = min(cost, getCost(s, matrix));
    // Flip
    swap(matrix[0], matrix[2]); 
    cost = min(cost, getCost(s, matrix));
    
    rotateMatrix(matrix);
    cost = min(cost, getCost(s, matrix));
    
    rotateMatrix(matrix);
    cost = min(cost, getCost(s, matrix));
    
    rotateMatrix(matrix);
    cost = min(cost, getCost(s, matrix));
    
    return cost;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    vector<vector<int>> s(3);

    for (int i = 0; i < 3; i++) {
        s[i].resize(3);

        string s_row_temp_temp;
        getline(cin, s_row_temp_temp);

        vector<string> s_row_temp = split(rtrim(s_row_temp_temp));

        for (int j = 0; j < 3; j++) {
            int s_row_item = stoi(s_row_temp[j]);

            s[i][j] = s_row_item;
        }
    }

    int result = formingMagicSquare(s);

    fout << result << "\n";

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
