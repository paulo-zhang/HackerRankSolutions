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
 
 bool searchValueInTree(vector<unsigned long> &sums, vector<vector<int>> &edges, int root, int excludeTree, unsigned long val){
     queue<int> q;
     q.push(root);
     vector<bool> visited(sums.size(), false);
     
     while(!q.empty()){
         int a = q.front();
         q.pop();
         
         if(sums[a - 1] == val){
             return true;
         }
         visited[a - 1] = true;
         
         for(int i = root;i < edges.size();i ++){
             if(edges[i][1] == excludeTree) continue;
             
             if(edges[i][0] == a && !visited[edges[i][1] - 1]){
                 q.push(edges[i][1]);
             }
         }
     }
     
     return false;
 }

int balancedForest(vector<int> c, vector<vector<int>> edges) {
    // https://www.hackerrank.com/challenges/balanced-forest/forum/comments/557372
    vector<unsigned long> sums(c.size());
    copy(c.begin(), c.end(), sums.begin());
    int minVal = INT_MAX;
    
    for(int i = edges.size() - 1;i >= 0;i --){
        sums[edges[i][0] - 1] += sums[edges[i][1] - 1];
    }
    
    unordered_map<unsigned long, int> m;
    for(int i = 1;i < sums.size();i ++){
        // Case 1: Find two equal trees and a smaller one.
        int val = (int)(sums[i] - (sums[0] - 2 * sums[i]));
        if(val > 0){
            int n = m[sums[i]];
            if(n > 0){
                // Found one.
                minVal = min(minVal, val);
            }
            else{
                // Keep track.
                m[sums[i]] = i;
            }
            
            continue;
        }
        // Case 2: One big tree that can split into two bigger equal trees(Big tree has a subtree that holds half of its value), and a smaller one.
        val = (int)(sums[i] / 2 - sums[0] - sums[i]);
        if(sums[i] % 2 == 0 && val > 0){
            if(searchValueInTree(sums, edges, i + 1, i + 1, sums[i] / 2)){
                // Found one.
                minVal = min(minVal, val);
            }

            continue;
        }
        // Case 3: Removing a smaller subtree and the rest tree has a subtree hold half of its total value.
        val = sums[0] - sums[i];
        if(val % 2 == 0){
            int diff = (int)(val / 2 - sums[i]);
            if(diff > 0){
                // Found one.
                if(searchValueInTree(sums, edges, 1, i + 1, val / 2)){
                    minVal = min(minVal, diff);
                }
            }
        }
    }
    
    return minVal == INT_MAX ? -1 : minVal;
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

        cout <<"result: "<< result << "\n";
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
