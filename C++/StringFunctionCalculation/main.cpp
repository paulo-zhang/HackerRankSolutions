#include <bits/stdc++.h>

using namespace std;

struct SuffixNode{
   SuffixNode *children[26];
   string suffix;
   int repeatCount;
   bool leaf;
   SuffixNode(){
       repeatCount = 0;
       leaf = true;
       memset(children, 0 , sizeof(SuffixNode*) * 26);
   }
};

// https://www.hackerearth.com/practice/notes/trie-suffix-tree-suffix-array/
// Put c into Trie.
// Mark maxVal.
void insertString(SuffixNode &root, string &t, int start, int &maxVal){
    int depth = 0;
    SuffixNode *p = &root;
    
    for(int i = start; i < t.size(); ++i){
        int index = t[i] - 'a';
        depth ++; // Actually a string lenth.
        
        SuffixNode *child = p->children[index];
        if(child == NULL){
            if(!p->leaf){
                p->children[index] = new SuffixNode();
                p->repeatCount ++;
                maxVal = max(maxVal, p->repeatCount * depth);
            }
            else{
                // This is a leaf.
                if(p->suffix.size() == 0){
                    p->suffix = t.substr(i, t.size() - i);
                    p->repeatCount ++;
                    maxVal = max(maxVal, p->repeatCount * depth);
                    maxVal = max(maxVal, (int)t.size());
                    break;
                }
                else {
                    // Break down the previous suffix.
                    p->repeatCount ++;
                    maxVal = max(maxVal, p->repeatCount * depth);

                    int ix = p->suffix[0] - 'a';
                    p->children[ix] = new SuffixNode();
                    p->children[ix]->repeatCount = 1;
                    p->children[ix]->suffix = p->suffix.erase(0);
                    p->suffix.clear();
                    p->leaf = false;
                    if(ix != index){
                        p->children[index] = new SuffixNode();
                        p->suffix = t.substr(i, t.size() - i);
                        p->repeatCount ++;
                        maxVal = max(maxVal, (int)t.size());
                        break;
                    }
                }
            }
        }
        
        p = p->children[index];
    }
}

int maxValue(string t) {
    int maxVal = 0;
    SuffixNode root;
    
    for(int i = 0; i < t.size(); ++i){
        insertString(root, t, i, maxVal);
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
