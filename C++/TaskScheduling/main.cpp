#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Rational: Find the number of the free time units freeCount from the deadline backward.
 * If the time units are not used, marke them as used.
 * The max overshoot lastMax = lastMax + m - freeCount.
 */

// Naive solution that passed 9/10 test cases, except for one timeout.
/*uint lastMax = 0;
int start = 0;
vector<bool> freeUnits(100001, true);// All free units
int taskScheduling(int d, int m) {
    int freeCount = 0; // the number of free time units before deadline.
    int i = d - 1;
    for(; i >= start && freeCount < m; --i){
        if(freeUnits[i]){
            freeCount ++;
            freeUnits[i] = false; // Always occupy the largest possible time unit.
        }
    }
    
    if(i < start){
        start = d; // All previus time units are marked.
    }
    // cout << "d: " << d << ", m: " << m << ", free: " << freeCount << ", last: " << lastMax << "\n";
    lastMax += m - freeCount;
    return lastMax;
}*/

/*************/
bool initialized = false;
set<int> freeUnits; // All free units
int lastOverShoot = 0;

int taskScheduling1(int d, int m)
{
    if (!initialized)
    {
        for (int i = 1; i < 100001; i++)
        {
            freeUnits.insert(i);
        }

        initialized = true;
    }

    auto last = freeUnits.upper_bound(d);
    auto first = last;

    while (first != freeUnits.begin() && m > 0)
    {
        first--;
        m--;
    }

    freeUnits.erase(first, last);
    lastOverShoot += m; // over_shoot = last_over_shoot + m(current over shoot);
    return lastOverShoot;
}

// Segment tree with array: https://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range/
// Lazy propagation segment tree: https://www.geeksforgeeks.org/lazy-propagation-in-segment-tree/
struct TreeNode{
    TreeNode(int _size){
        free = _size;
        size = _size;
        if(size > 1){
            int leftSize = _size / 2;
            int rightSize = _size - leftSize;
            left = new TreeNode(leftSize);
            right = new TreeNode(rightSize);
        }
    }

    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    int free; // free time units that can be used to run task.
    int size; // tree size.
};

class SegmentTree{
    private:
    TreeNode* root;
    int maxOvershoot = 0; // The last max over shoot after scheduling the task.
    // Destory the tree, release memory.
    void DestoryTree(TreeNode* node){
        if(node == nullptr) return;

        if(node->left != nullptr){
            DestoryTree(node->left);
        }

        if(node->right != nullptr){
            DestoryTree(node->right);
        }

        delete node;
    }

    // Dynamically allocate tree to represent every time unit (leaves).
    // The number of leaves will be 2^root(log(dealine))
    TreeNode* GetTreeRoot(int deadline){
        while(deadline > root->size){
            auto left = root;
            root = new TreeNode(1);
            root->left = left; // Make the old root a left child.
            root->right = new TreeNode(left->size); // Create the same sized right tree.
            root->size = left->size * 2; // Double the tree size.
            root->free = left->free + root->right->free; // Keep track of the free units on the left side.
        }

        return root;
    }
    public:
    SegmentTree(){
        root = new TreeNode(1);
    }

    ~SegmentTree(){
        DestoryTree(root);
    }
    
    // Execute the task on node, and return the free units (not overshoot time units) used for this task.
    int GetFreeUnits(TreeNode* node, int deadline, int duration){
        if(node->free == 0 || deadline <= 0 || duration <= 0){
            return 0; // No task to execute before deadline.
        }

        if((deadline >= node->size && node->free <= duration) || // The deadline covers current node & all free units (otherwise we need to allocate the right most units) can be consumed.
            (node->left == nullptr && node->right == nullptr) // We reached to a leave, don't need to go deeper.
        ){
            int free = node->free;
            node->free = 0;
            return free;
        }

        int freeUnits = 0;
        if(node->left->size < deadline){
            // Left node is not enough, use the right most free units for rest duration. Allocate from deadline backward.
            freeUnits = GetFreeUnits(node->right, deadline - node->left->size, duration); // Deadline needs to readjust to suit new node.
        }
        // Use the left nodes, we can only allocate duration - freeUnits units.
        freeUnits += GetFreeUnits(node->left, deadline, duration - freeUnits);

        node->free -= freeUnits;
        return freeUnits;
    }

    // Schedule task, return the max overshoot.
    int ScheduleTask(int deadline, int duration){
        TreeNode* root = GetTreeRoot(deadline);// Allocate tree nodes and return root.
        int free = GetFreeUnits(root, deadline, duration);
        // Rational: if we execute the task from deadline backward, current max overshoot = last max overshoot + duration - free units.
        maxOvershoot += duration - free; 
        return maxOvershoot;
    }
};

SegmentTree tree;
int taskScheduling(int d, int m) {
    return tree.ScheduleTask(d, m);
}

int main()
{
    ofstream fout("output.txt");
    ifstream fin("input00.txt");

    string t_temp;
    getline(fin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string first_multiple_input_temp;
        getline(fin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int d = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        int result = taskScheduling(d, m);

        fout << result << "\n";
    }

    fout.close();
    fin.close();

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
