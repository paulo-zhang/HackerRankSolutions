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
    bool visited = false;
    bool traversed = false;
    vector<int> adj_nodes; 
    long sum;
 };
 
 // Make nodes for easier access.
 void makeNodes(vector<vector<int>> &edges, vector<Node> &nodes){
     for(auto e : edges){
         nodes[e[0] - 1].adj_nodes.push_back(e[1] - 1);
         nodes[e[1] - 1].adj_nodes.push_back(e[0] - 1);
     }
 }
 
 // DFS to calculate sum of tree whose root index is nodeIndex
 long DFS_Sum(vector<int> &c, vector<Node> &nodes, int nodeIndex){
     nodes[nodeIndex].sum = c[nodeIndex];
     nodes[nodeIndex].visited = true;
     
     for(auto i : nodes[nodeIndex].adj_nodes){
         if(!nodes[i].visited){
             nodes[nodeIndex].sum += DFS_Sum(c, nodes, i);
         }
     }

     cout << nodeIndex << ": " << nodes[nodeIndex].sum << endl;
     return nodes[nodeIndex].sum;
 }
 
 // We got all the sums here, time to solve the problem.
 long minNodeValue(vector<Node> &nodes, unordered_set<long> &previouslyPassedNodeSums, unordered_set<long> &currentPathNodeSums, long totalSum, int nodeIndex){
    // We need to find two equal sums (sumA & sumA), which are bigger than the rest (sumB = totalSum - 2 * sumA), the difference between sumA & sumB is the node we need to add to make 3 balanced trees.
    // So sumA must satisfy: 3 * sumA >= totalSum && 2 * sumA <=  totalSum. sumB must satisfy: 3 * sumB <= totalSum && (totalSum - sumB) % 2 == 0.
    // The added value to make balanced trees is: 3 * sumA - totalSum, or (totalSum - sumB) / 2 - sumB.
    // There are 6 scenarios:
    // 1. For previouslyPassedNodeSums:
    // 1.A. If current node sum is sumA, there must be a sibling node sum has the same value sumA. 
    // 1.B. If current node sum is sumA, there must be a sibling node sumB = totalSum - 2 * sumA.
    // 1.C. If current node sum is sumB, there must be a sibling node sumA = (totalSum - sumB) / 2.
    // 2. For currentPathNodeSums:
    // 2.A. If current node sum is sumA, there must be a parent node sum = 2 * sumA.
    // 2.B. If current node sum is sumA, there must be a parent node sum = totalSum - sumA.
    // 2.C. If current node sum is sumB, there must be a parent node sum = (totalSum + sumB) / 2.
    // Check out the image Balanced-Trees.png.

    long cw = LONG_MAX; // The final minimum added node value.

     nodes[nodeIndex].traversed = true;
    long sumA = nodes[nodeIndex].sum;
    long &sumB = sumA; // The concepts of sumA and sumB are asymmetric & imaginary, just to make it easier to understand.

    if(3 * sumA >= totalSum && 2 * sumA <=  totalSum){
        if(previouslyPassedNodeSums.find(sumA) != previouslyPassedNodeSums.end() || // 1.A
            previouslyPassedNodeSums.find(totalSum - 2 * sumA) != previouslyPassedNodeSums.end() // 1.B
        ){
            cw = min(cw, 3 * sumA - totalSum);
        }
        else if(currentPathNodeSums.find(2 * sumA) != currentPathNodeSums.end() || // 2.A
        currentPathNodeSums.find(totalSum - sumA) != currentPathNodeSums.end() // 2.B
        ){
            cw = min(cw, 3 * sumA - totalSum);
        }
    }
    if(3 * sumB <= totalSum && (totalSum - sumB) % 2 == 0){
        if((totalSum - sumB) % 2 == 0 && previouslyPassedNodeSums.find((totalSum - sumB) / 2) != previouslyPassedNodeSums.end()){ // 1.C
            cw = min(cw, (totalSum - sumB) / 2 - sumB);
        }
        
        else if((totalSum + sumB) % 2 == 0 && currentPathNodeSums.find((totalSum + sumB) / 2) != currentPathNodeSums.end()){ // 2.C
            cw = min(cw, (totalSum - sumB) / 2 - sumB);
        }
    }
    
    currentPathNodeSums.insert(sumA); // Finished current node, add to currentPathNodeSums to let the children trees calculate.
    for(auto i : nodes[nodeIndex].adj_nodes){
        if(!nodes[i].traversed){
            cw = min(cw, minNodeValue(nodes, previouslyPassedNodeSums, currentPathNodeSums, totalSum, i));
        }
    }

    previouslyPassedNodeSums.insert(sumA); // Passing over this node.
    currentPathNodeSums.erase(sumA); // Exiting current tree.
    return cw;
 }
 
 long balancedForest(vector<int> &c, vector<vector<int>> &edges) {
    // https://www.hackerrank.com/challenges/balanced-forest/forum/comments/255504
    // https://www.hackerrank.com/challenges/balanced-forest/forum/comments/557372
    vector<Node> nodes(c.size());
    
    // Make nodes.
    makeNodes(edges, nodes);
    
    // DFS traverse to calculate sums of all sub-trees.
    long totalSum = DFS_Sum(c, nodes, 0);
    
    // Solve the problem.
    unordered_set<long> previouslyPassedNodeSums; // All the node sums passed while traversing.
    unordered_set<long> currentPathNodeSums; // Current path sums traced back to root.
    long cw = minNodeValue(nodes, previouslyPassedNodeSums, currentPathNodeSums, totalSum, 0); // DFS traverse again to get the answer.
    return cw == LONG_MAX ? -1 : cw;
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

        long result = balancedForest(c, edges);

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
