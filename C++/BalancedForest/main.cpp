#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'balancedForest' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY c
 *  2. 2D_INTEGER_ARRAY edges
 */
 
 // Cut the tree
 bool canCutEqualTrees(vector<int> &c, vector<vector<int>> &edges, int cuttedEdge, int root, long weight){
     for(int i = 0;i < edges.size();i ++){
        if(i == cuttedEdge)continue;
         
        vector<bool> visited(c.size());
        queue<int> q;
        q.push(root);
        long SumTa = 0;
        while(!q.empty()){
            // BFS visit all nodes.
            int a = q.front();
            q.pop();
            
            SumTa += c[a - 1];
            visited[a - 1] = true;
            
            if(weight / 2 == SumTa)
                return true;// Find equal trees
            
            for(int j = 0;j < edges.size();j ++){
                if(i == j)continue;// This edge is cutted.
                
                if(a == edges[j][0] && !visited[edges[j][1] - 1]){
                    q.push(edges[j][1]);
                }
                if(a == edges[j][1] && !visited[edges[j][0] - 1]){
                    q.push(edges[j][0]);
                }
            }
        }
     }
     
    return false;
 }

int balancedForest(vector<int> c, vector<vector<int>> edges) {
    // https://www.hackerrank.com/challenges/balanced-forest/forum/comments/255504
    int Cw = INT_MAX;
    long totalWeight = accumulate(c.begin(), c.end(), 0);
    
    for(int i = 0;i < edges.size();i ++){
        // Try cut one edge, and make two trees Ta, Tb
        // Calculate sum of Ta
        vector<bool> visited(c.size());
        queue<int> q;
        q.push(edges[i][0]);
        long SumTa = 0;
        
        while(!q.empty()){
            // BFS visit all nodes.
            int a = q.front();
            q.pop();
            
            SumTa += c[a - 1];
            visited[a - 1] = true;
            
            for(int j = 0;j < edges.size();j ++){
                if(i == j)continue;// This edge is cutted.
                
                if(a == edges[j][0] && !visited[edges[j][1] - 1]){
                    q.push(edges[j][1]);
                }
                if(a == edges[j][1] && !visited[edges[j][0] - 1]){
                    q.push(edges[j][0]);
                }
            }
        }
        
        // Make sure Ta >= 2Tb or 2Ta <= Tb, so that we can cut the bigger tree into two equal trees and one is still bigger than the smaller tree.
        // The difference between one of the equal trees and the smaller tree is the added value.
        long SumTb = totalWeight - SumTa;
        if(SumTa >= 2 * SumTb && SumTa % 2 == 0){
            // Try cut Ta at any edge, and make the two trees equal
            if(canCutEqualTrees(c, edges, i, edges[i][0], SumTa)){
                Cw = min(Cw, (int)(SumTa / 2 - SumTb));
            }
        }
        
        if(SumTb >= 2 * SumTa && SumTb % 2 == 0){
            // Try cut Tb at any edge, and make the two trees equal
            if(canCutEqualTrees(c, edges, i, edges[i][1], SumTb)){
                Cw = min(Cw, (int)(SumTb / 2 - SumTa));
            }
        }
    }
    
    return Cw == INT_MAX ? -1 : Cw;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        string c_temp_temp;
        getline(cin, c_temp_temp);

        vector<string> c_temp = split(rtrim(c_temp_temp));

        vector<int> c(n);

        for (int i = 0; i < n; i++) {
            int c_item = stoi(c_temp[i]);

            c[i] = c_item;
        }

        vector<vector<int>> edges(n - 1);

        for (int i = 0; i < n - 1; i++) {
            edges[i].resize(2);

            string edges_row_temp_temp;
            getline(cin, edges_row_temp_temp);

            vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int edges_row_item = stoi(edges_row_temp[j]);

                edges[i][j] = edges_row_item;
            }
        }

        int result = balancedForest(c, edges);

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
