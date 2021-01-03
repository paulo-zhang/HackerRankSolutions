#include <stack>
#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int d) {
        data = d;
        left = NULL;
        right = NULL;
    }
};

class Solution {
public:
    Node* insert(Node* root, int data) {
        if (root == NULL) {
            return new Node(data);
        }
        else {
            Node* cur;
            if (data <= root->data) {
                cur = insert(root->left, data);
                root->left = cur;
            }
            else {
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
    //Node* lca(Node* root, int v1, int v2) {
    //    //Decide if you have to call rekursively
    //    //Samller than both
    //    if (root->data < v1 && root->data < v2) {
    //        return lca(root->right, v1, v2);
    //    }
    //    //Bigger than both
    //    if (root->data > v1 && root->data > v2) {
    //        return lca(root->left, v1, v2);
    //    }

    //    //Else solution already found
    //    return root;
    //}
    /* End by @RubenzZzZ */

    Node* lca(Node* root, int v1, int v2) {
        // Write your code here.
        stack<Node*> ancestorStack;
        traverseTree(root, v1, v2, ancestorStack);
        if (v1 == 0 && v2 == 0 && ancestorStack.size() > 0) {
            // found it;
            return ancestorStack.top();
        }

        return NULL;
    }

    bool traverseTree(Node* node, int& v1, int& v2, stack<Node*>& ancestorStack)
    {
        bool pushed = false;

        if (v1 != 0 && v2 != 0) {// Both not found
            ancestorStack.push(node);
            pushed = true;
        }

        if (node->data == v1) { // found one
            v1 = 0;// mark another
        }
        if (node->data == v2) { // found another
            v2 = 0;// mark another
        }

        if (v1 == 0 && v2 == 0) { // Both found
            return false; // Don't pop, the last one is correct answer.
        }

        // Go down to the children.
        if (node->left != NULL) {
            bool ret = traverseTree(node->left, v1, v2, ancestorStack);
            if (ret && (v1 != 0 || v2 != 0)) {
                ancestorStack.pop();
            }
        }

        if (node->right != NULL) {
            bool ret = traverseTree(node->right, v1, v2, ancestorStack);
            if (ret && (v1 != 0 || v2 != 0)) {
                ancestorStack.pop();
            }
        }

        return pushed;
    }

}; //End of Solution

int main() {

    Solution myTree;
    Node* root = NULL;

    int t;
    int data;

    std::cin >> t;

    while (t-- > 0) {
        std::cin >> data;
        root = myTree.insert(root, data);
    }

    int v1, v2;
    std::cin >> v1 >> v2;

    Node* ans = myTree.lca(root, v1, v2);

    std::cout << ans->data;

    return 0;
}
