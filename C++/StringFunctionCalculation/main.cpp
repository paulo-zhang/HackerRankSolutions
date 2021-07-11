#include <bits/stdc++.h>

using namespace std;

struct TrieNode{
   TrieNode *children[26];
   int reachCount;
   TrieNode(){
       reachCount = 0;
       memset(children, 0 , sizeof(TrieNode*) * 26);
   }
};

// https://www.hackerearth.com/practice/notes/trie-suffix-tree-suffix-array/
// Put c into Trie.
// Mark maxVal.
void insertChar(TrieNode &root, string &t, int start, int &maxVal){
    int depth = 0;
    TrieNode *p = &root;
    
    for(int i = start; i < t.size(); ++i){
        int index = t[i] - 'a';
        depth ++; // Actually a string lenth.
        
        TrieNode *child = p->children[index];
        if(child == NULL){
            child = new TrieNode();
            p->children[index] = child;
        }
        
        p = p->children[index];
        p->reachCount ++;
        
        maxVal = max(maxVal, p->reachCount * depth);
    }
}

int maxValue(string t) {
    int maxVal = 0;
    TrieNode root;
    
    for(int i = 0; i < t.size(); ++i){
        insertChar(root, t, i, maxVal);
    }
    
    return maxVal;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t;
    getline(cin, t);

    int result = maxValue(t);

    fout << result << "\n";

    fout.close();

    return 0;
}
