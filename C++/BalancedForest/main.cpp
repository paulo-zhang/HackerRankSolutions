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
 
 struct Node{
    bool visited;
    vector<int> adj_nodes; 
 };
 
 // Make nodes for easier access.
 void MakeNodes(vector<vector<int>> &edges, vector<Node> &nodes){
     for(auto e : edges){
         nodes[e[0] - 1].adj_nodes.push_back(e[1] - 1);
         nodes[e[1] - 1].adj_nodes.push_back(e[0] - 1);
     }
 }
 
 // DFS to calculate sum of tree whose root index is nodeIndex
 long DFS_Sum(vector<int> &c, vector<Node> &nodes, int nodeIndex, multiset<long> &sums){
     long sum = c[nodeIndex];
     nodes[nodeIndex].visited = true;
     
     for(auto i : nodes[nodeIndex].adj_nodes){
         if(!nodes[i].visited){
             sum += DFS_Sum(c, nodes, i, sums);
         }
     }
     
     sums.insert(sum);
     cout << nodeIndex << ": " << sum << endl;
     return sum;
 }
 
 // We got all the sums here, time to solve the problem.
 int solveProblem(multiset<long> &sums, long totalSum){
     // We need to find two equal sums (sumA & sumA), which are bigger than the rest (sumB = totalSum - 2 * sumA), the difference between sumA & sumB is the node we need to add to make 3 balanced trees.
    // So sumA must satisfy: 3 * sumA > totalSum && 2 * sumA <  totalSum. sumB must satisfy: 3 * sumB < totalSum && (totalSum - sumB) % 2 == 0.
    // The added value to make balanced trees is: 3 * sumA - totalSum, or (totalSum - sumB) / 2 - sumB.
    // There are 3 scenarios:
    // 1. There exist two sumA in sums, the rest is sumB. 
    // 2. There is a sumA and a tree sum that equals to 2 * sumA (sumA must belong to that tree, if not, it'd violate 3 * sumA > totalSum).
    // 3. There is a sumB and a tree sum that equals to sumA = (totalSum - sumB) / 2. (so we can cut sumA & sumB out.).
    // So let's do it ...

    int cw = INT_MAX; // The final minimum added node value.
    
    for(auto it = sums.begin();it != sums.end(); it++){
        long sumA = *it;
        long &sumB = sumA; // The concept of sumA and sumB are asymmetric.

        if(3 * sumA > totalSum && 2 * sumA <  totalSum){
            if(sums.count(sumA) == 2 || // scenario 1.
                sums.find(2 * sumA) != sums.end() // scenario 2.
            ){ 
                cw = min((long)cw, 3 * sumA - totalSum);
            }
        }
        else if(3 * sumB < totalSum && (totalSum - sumB) % 2 == 0){
            if(sums.find((totalSum - sumB) / 2) != sums.end()){ // scenario 3.
                cw = min((long)cw, (totalSum - sumB) / 2 - sumB);
            }
        }
        
    }
    
    return cw == INT_MAX ? -1 : cw;
 }

int balancedForest(vector<int> &c, vector<vector<int>> &edges) {
    // https://www.hackerrank.com/challenges/balanced-forest/forum/comments/255504
    multiset<long> sums; // All the sums for sub-trees.
    vector<Node> nodes(c.size());
    
    // Make nodes.
    MakeNodes(edges, nodes);
    
    // DFS to calculate sums of all sub-trees.
    long totalSum = DFS_Sum(c, nodes, 0, sums);
    
    // Solve the problem.
    return solveProblem(sums, totalSum);
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

        cout << "\nanswer: " << result << "\n";
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
