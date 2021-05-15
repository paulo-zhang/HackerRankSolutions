#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'minimumMoves' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING_ARRAY grid
 *  2. INTEGER startX
 *  3. INTEGER startY
 *  4. INTEGER goalX
 *  5. INTEGER goalY
 */
 
 struct CooValue{
     int x;
     int y;
     int val;
 };

int minimumMoves(vector<string> grid, int startX, int startY, int goalX, int goalY) {
    // https://www.hackerrank.com/challenges/castle-on-the-grid/forum/comments/107995
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid.size(), false));
    queue<CooValue> q;
    visited[startX][startY] = true;
    q.push(CooValue() = {startX, startY, 0});
    while(!q.empty()){
        auto item = q.front();
        q.pop();
        
        if(item.x == goalX && item.y == goalY){
            return item.val;
        }
        
        // Update left
        int x = item.x;
        while(--x >= 0 && grid[x][item.y] != 'X'){
            if(visited[x][item.y]) continue;
            
            visited[x][item.y] = true;
            q.push(CooValue() = {x, item.y, item.val + 1});
        }
        //Update right
        x = item.x;
        while(++x < grid.size() && grid[x][item.y] != 'X'){
            if(visited[x][item.y]) continue;
            visited[x][item.y] = true;
            q.push(CooValue() = {x, item.y, item.val + 1});
        }
        //Update top
        int y = item.y;
        while(--y >= 0 && grid[item.x][y] != 'X'){
            if(visited[item.x][y]) continue;
            
            visited[item.x][y] = true;
            q.push(CooValue() = {item.x, y, item.val + 1});
        }
        //Update bottom
        y = item.y;
        while(++y < grid.size() && grid[item.x][y] != 'X'){
            if(visited[item.x][y]) continue;
            
            visited[item.x][y] = true;
            q.push(CooValue() = {item.x, y, item.val + 1});
        }
    }
    
    return -1; // Error
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int startX = stoi(first_multiple_input[0]);

    int startY = stoi(first_multiple_input[1]);

    int goalX = stoi(first_multiple_input[2]);

    int goalY = stoi(first_multiple_input[3]);

    int result = minimumMoves(grid, startX, startY, goalX, goalY);

    cout << result << "\n";

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
