#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

struct TrieNode{
    TrieNode *left = nullptr;
    TrieNode *right = nullptr;
    int data = 0;
};

void insert(TrieNode &head, int a){
    uint mask = 0x80000000; // 10000000 00000000 00000000 00000000
    TrieNode *p = &head;

    for(int i = 0;i < 32; ++i){
        if(mask & a){ // go right.
            if(p->right == nullptr){
                p->right = new TrieNode();
            }
            
            p = p->right;
        }
        else{ // go left.
            if(p->left == nullptr){
                p->left = new TrieNode();
            }

            p = p->left;
        }

        mask = mask >> 1;
    }

    p->data = a; // Leaf.
}

int search(const TrieNode &head, int q){
    uint mask = 0x80000000; // 10000000 00000000 00000000 00000000
    const TrieNode *p = &head;

    // cout << ~q << ": " << bitset<32>(q) << "\n";

    for(int i = 0;i < 32; ++i){
        // cout << "mask: " << bitset<32>(mask) << "\n";
        if(mask & q){ // Try go right.
            if(p->right == nullptr){
                p = p->left; // not perfect, still try to find the best.
            }
            else{
                p = p->right;
            }
        }
        else{ // Try go left.
            if(p->left == nullptr){
                p = p->right; // // not perfect, still try to find the best.
            }
            else{
                p = p->left;
            }
        }

        mask = mask >> 1;
    }

    // cout << p->data << ": " << bitset<32>(p->data) << "\n\n";
    return p->data; // Leaf, the best number.
}

// Complete the maxXor function below.
// https://www.geeksforgeeks.org/trie-insert-and-search/
// https://www.programiz.com/dsa/huffman-coding
vector<int> maxXor(vector<int> arr, vector<int> queries) {
    // solve here
    vector<int> result(queries.size(), 0);
    TrieNode head;
    for(int a : arr){
        insert(head, a);
    }

    for( int i = 0; i < queries.size(); ++ i){
        int n = search(head, ~queries[i]);
        result[i] = n ^ queries[i];
    }
    
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    int m;
    cin >> m;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> queries(m);

    for (int i = 0; i < m; i++) {
        int queries_item;
        cin >> queries_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        queries[i] = queries_item;
    }

    vector<int> result = maxXor(arr, queries);

    for (int i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
