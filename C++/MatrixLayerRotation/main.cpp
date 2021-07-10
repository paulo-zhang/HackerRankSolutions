#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'matrixRotation' function below.
 *
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY matrix
 *  2. INTEGER r
 */
 
 // Get the 'strings' of the circles from outer layers to the inner layers.
vector<vector<int>> GetStrings(const vector<vector<int>> &matrix){
    vector<vector<int>> result;
    int n = 0, height = matrix.size(), width = matrix[0].size();
    
    while(n * 2 < height && n * 2 < width)
    {
        vector<int> v;
        // Top edge
        for(int i = n; i < width - n; ++i){
            v.push_back(matrix[n][i]);
            // cout << matrix[n][i] << " ";
        }
        
        // Right edge
        for(int i = n + 1; i < height - n; ++i){
            v.push_back(matrix[i][width - n - 1]);
            // cout << matrix[i][width - n - 1] << " ";
        }
        
        // Bottom edge
        for(int i = width - n - 2; i >= n; --i){
            v.push_back(matrix[height - n - 1][i]);
            // cout << matrix[height - n - 1][i] << " ";
        }
        
        // Left edge
        for(int i = height - n - 2; i > n; --i){
            v.push_back(matrix[i][n]);
            // cout << matrix[i][n] << " ";
        }
        
        // cout << "\n";
        result.push_back(v);
        ++n;
    }
    
    return result;
}

// Apply the rotated value to the new matrix from outer layers to the inner layers.
vector<vector<int>> rotateMatrix(int height, int width, int r, const vector<vector<int>> &strings){
    vector<vector<int>> result(height, vector<int>(width));
    int n = 0;
    while(n * 2 < height && n * 2 < width)
    {
        int strLen = strings[n].size();
        int start = r % strLen;
        // Top edge
        for(int i = n; i < width - n; ++i){
            result[n][i] = strings[n][start ++ % strLen];
        }
        
        // Right edge
        for(int i = n + 1; i < height - n; ++i){
            result[i][width - n - 1] = strings[n][start ++ % strLen];
        }
        
        // Bottom edge
        for(int i = width - n - 2; i >= n; --i){
            result[height - n - 1][i] = strings[n][start ++ % strLen];
        }
        
        // Left edge
        for(int i = height - n - 2; i > n; --i){
            result[i][n] = strings[n][start ++ % strLen];
        }
        
        ++n;
    }
    
    return result;
}

// Print matrix.
void printMatrix(const vector<vector<int>> &matrix){
    for(int i = 0;i < matrix.size(); ++ i){
        for(int j = 0;j < matrix[i].size(); ++j){
            cout << matrix[i][j] << " ";
        }
        
        cout << "\n";
    }
}

void matrixRotation(vector<vector<int>> &matrix, int r) {
    auto strings = GetStrings(matrix);
    printMatrix(rotateMatrix(matrix.size(), matrix[0].size(), r, strings));
}

int main()
{
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int m = stoi(first_multiple_input[0]);

    int n = stoi(first_multiple_input[1]);

    int r = stoi(first_multiple_input[2]);

    vector<vector<int>> matrix(m);

    for (int i = 0; i < m; i++) {
        matrix[i].resize(n);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < n; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    matrixRotation(matrix, r);

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
