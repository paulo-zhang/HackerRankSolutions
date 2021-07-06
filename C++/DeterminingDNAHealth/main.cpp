#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

struct NodeValue
{
   size_t index;
   int health; 
};

struct TrieNode
{
    TrieNode *children[26];
    vector<NodeValue> healths;
    
    TrieNode()
    {
        //memset(children, 0, 26 * sizeof(TrieNode*));
        for(int i = 0;i < 26;i ++)
        {
            children[i] = NULL;
        }
    }
};

// https://www.geeksforgeeks.org/trie-insert-and-search/
void buildTrie(TrieNode &root, string words, size_t index, int health)
{
    TrieNode *p = &root;
    for(size_t i = 0;i < words.size(); ++i)
    {
        int charIndex = words[i] - 'a';
        if(p->children[charIndex] == NULL)
        {
            p->children[charIndex] = new TrieNode();
        }
        
        p = p->children[charIndex];
    }
    
    // Word ended.
    p->healths.push_back(NodeValue{.index = index, .health = health});
}

long getHealth(TrieNode &root, string s, int start, int end)
{
    long result = 0;
    for(size_t i = 0; i < s.size(); ++i)
    {
        size_t j = i;
        TrieNode *p = root.children[s[j] - 'a'];
        while(p != NULL)
        {
            for(const auto &h : p->healths)
            {
                if(h.index >= start && h.index <= end)
                {
                    result += h.health;
                    // cout << s.substr(i, j - i + 1) << ": " << h.health << ",";
                }
            }
            
            p = p->children[s[++j] - 'a'];
        }
    }
    // cout << "result:" << result << endl;
    return result;
}

int main()
{
    ifstream fin("input02.txt");
    string n_temp;
    getline(fin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string genes_temp_temp;
    getline(fin, genes_temp_temp);

    vector<string> genes_temp = split(rtrim(genes_temp_temp));

    vector<string> genes(n);

    for (int i = 0; i < n; i++) {
        string genes_item = genes_temp[i];

        genes[i] = genes_item;
    }

    string health_temp_temp;
    getline(fin, health_temp_temp);

    vector<string> health_temp = split(rtrim(health_temp_temp));

    vector<int> health(n);
    TrieNode root;

    for (int i = 0; i < n; i++) {
        int health_item = stoi(health_temp[i]);

        // health[i] = health_item;
        buildTrie(root, genes[i], i, health_item);
    }

    string s_temp;
    getline(fin, s_temp);

    int s = stoi(ltrim(rtrim(s_temp)));
    
    long maxHealth = LONG_MIN, minHealth = LONG_MAX;
    for (int s_itr = 0; s_itr < s; s_itr++) {
        string first_multiple_input_temp;
        getline(fin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int first = stoi(first_multiple_input[0]);

        int last = stoi(first_multiple_input[1]);

        string d = first_multiple_input[2];
        
        long health = getHealth(root, d, first, last);
        
        maxHealth = max(maxHealth, health);
        minHealth = min(minHealth, health);
    }
    
    cout << minHealth << " " << maxHealth;

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
