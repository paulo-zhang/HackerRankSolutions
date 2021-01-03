/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.  

The Node struct is defined as follows:
	struct Node {
		int data;
		Node* left;
		Node* right;
	}
*/
    // https://en.wikipedia.org/wiki/Binary_search_tree
    bool checkBSTWithMaxMin(Node* root, int min, int max){
        if(root == NULL)return true;
        
        if(root->data < min || root->data > max)return false;
        
        return checkBSTWithMaxMin(root->left, min, root->data - 1) && checkBSTWithMaxMin(root->right, root->data + 1, max);
    }

	bool checkBST(Node* root) {
		return checkBSTWithMaxMin(root, 0, 10000);
	}