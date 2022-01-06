#include <stack>
#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(int d)
    {
        data = d;
        left = NULL;
        right = NULL;
    }
};

class Solution
{
public:
    Node *insert(Node *root, int data)
    {
        if (root == NULL)
        {
            return new Node(data);
        }
        else
        {
            Node *cur;
            if (data <= root->data)
            {
                cur = insert(root->left, data);
                root->left = cur;
            }
            else
            {
                cur = insert(root->right, data);
                root->right = cur;
            }

            return root;
        }
    }

    /*The tree node has data, left child and right child
    class Node {
        int data;
        Node* left;
        Node* right;
    };

    */

    /* Written by @RubenzZzZ */
    // Node* lca(Node* root, int v1, int v2) {
    //     //Decide if you have to call rekursively
    //     //Samller than both
    //     if (root->data < v1 && root->data < v2) {
    //         return lca(root->right, v1, v2);
    //     }
    //     //Bigger than both
    //     if (root->data > v1 && root->data > v2) {
    //         return lca(root->left, v1, v2);
    //     }

    //    //Else solution already found
    //    return root;
    //}
    /* End by @RubenzZzZ */

    Node *lca(Node *root, int v1, int v2)
    {
        // Write your code here.
        vector<bool> ancestors(26, false);
        getAncestors(root, v1, ancestors);

        Node *lca = nullptr;
        getLca(root, ancestors, v2, &lca);
        return lca;
    }

    bool getLca(Node *node, vector<bool> &ancestors, int v2, Node **lca)
    {
        if (node == nullptr)
            return false;
        if (v2 == node->data)
        {
            if (ancestors[node->data])
            {
                *lca = node;
            }

            return true;
        }

        if (getLca(node->left, ancestors, v2, lca))
        {
            if (ancestors[node->data] && *lca == nullptr)
            {
                *lca = node;
            }

            return true;
        }

        if (getLca(node->right, ancestors, v2, lca))
        {
            if (ancestors[node->data] && *lca == nullptr)
            {
                *lca = node;
            }

            return true;
        }

        return false;
    }

    bool getAncestors(Node *node, int v1, vector<bool> &ancestors)
    {
        if (node == nullptr)
            return false;
        if (v1 == node->data)
        {
            ancestors[node->data] = true;
            return true;
        }

        if (getAncestors(node->left, v1, ancestors))
        {
            ancestors[node->data] = true;
            return true;
        }

        if (getAncestors(node->right, v1, ancestors))
        {
            ancestors[node->data] = true;
            return true;
        }

        return false;
    }

}; // End of Solution

int main()
{

    Solution myTree;
    Node *root = NULL;

    int t;
    int data;

    std::cin >> t;

    while (t-- > 0)
    {
        std::cin >> data;
        root = myTree.insert(root, data);
    }

    int v1, v2;
    std::cin >> v1 >> v2;

    Node *ans = myTree.lca(root, v1, v2);

    std::cout << ans->data;

    return 0;
}
