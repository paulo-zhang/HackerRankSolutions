#include <bits/stdc++.h>

using namespace std;

// https://www.hackerearth.com/practice/notes/disjoint-set-union-union-find/
struct Node{
    int parent = 0; // parent node id, 0 means itself.
    int size = 1; // Size of the tree, only valid if this node is the root.
};

int getRoot(unordered_map<int, Node> &parents, int node){
    int i = node;
    while(parents[i].parent != i && parents[i].parent != 0){
        int temp = parents[i].parent;
        parents[i].parent = parents[parents[i].parent].parent; // Compress path while traversing to reduce the tree depth.
        i = temp;
    }
    
    if(parents[i].parent == 0) {
        parents[i].parent = i; // Set the root correctly to itself.
    }
    
    return i;
}

void setUnion(unordered_map<int, Node> &parents, int n1, int n2){
    int root1 = getRoot(parents, n1);
    int root2 = getRoot(parents, n2);
    if(root1 == root2)return;
    
    // add to bigger tree to reduce depth.
    if(parents[root1].size > parents[root2].size){ 
        parents[root2].parent = root1;
        parents[root1].size += parents[root2].size;
    }
    else {
        parents[root1].parent = root2;
        parents[root2].size += parents[root1].size;
    }
}

// Complete the maxCircle function below.
vector<int> maxCircle(vector<vector<int>> queries) {
    vector<int> result(queries.size(), 0);
    int index = 0;
    unordered_map<int, Node> parents; // Use unordered_map instead of array to possibly reduce the memory needed.
    
    for(auto q : queries){
        setUnion(parents, q[0], q[1]);
        int root1 = getRoot(parents, q[0]);
        int root2 = getRoot(parents, q[1]);
        result[index] = max(index == 0 ? 1 : result[index - 1], max(parents[root1].size, parents[root2].size));
        index ++;
    }
    
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> queries(q);
    for (int i = 0; i < q; i++) {
        queries[i].resize(2);

        for (int j = 0; j < 2; j++) {
            cin >> queries[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<int> ans = maxCircle(queries);

    for (int i = 0; i < ans.size(); i++) {
        fout << ans[i];

        if (i != ans.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
