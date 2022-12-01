// Write a program for AVL tree to implement following operation.
	// a. Insertion
		// Test program for all cases, LL, LR, RL, RR rotation
	// b. Deletion
		// Test program for all cases, R0, R1, R-1, L0, L1, L-1
	// c. Display
	
#include <bits/stdc++.h>

using namespace std;

struct Node {
	int key;
	Node *left;
	Node *right;
	
	int height;	
	
	Node(int key) {
		height = 1;
		this->key = key;
		
		left = NULL;
		right = NULL;
	}
};

class AVLTree {
	public:
	Node *root;
	
	AVLTree() {
	 	root = NULL;
	}
	
	int getHeight(Node *root) {
		if(root == NULL) return 0;
		
		return root->height;
	}
	
	int getBalance(Node *root) {
		if (root == NULL) return 0;
		return getHeight(root->left) - getHeight(root->right); 
	}
	
	void fixHeight(Node *root) {
		root->height = 1 + max(getHeight(root->left), getHeight(root->right));
	}
	
	Node* leftRotate(Node *root) {
		Node *right = root->right;
		Node *rightLeft = right->left;
		
		right->left = root;
		root->right = rightLeft;
		
		fixHeight(root);
		fixHeight(right);
		
		return right;
	}
	
	Node* rightRotate(Node *root) {
		Node *left = root->left;
		Node *leftRight = left->right;
		
		left->right = root;
		root->left = leftRight;
		
		fixHeight(root);
		fixHeight(left);
		
		return left;
	}
	
	void insert(int key) {
		root = insert(root, key);
	}
	
	Node* insert(Node *root, int key) {
		if(root == NULL) return new Node(key);
	
		if(key < root->key) {
			root->left = insert(root->left, key);
		} else if(key > root->key) {
			root->right = insert(root->right, key);
		} else {
			return root;
		}
		
		fixHeight(root);
		
		int balance = getBalance(root);
		
		// lH > rH
		// LL
		if(balance > 1 && getBalance(root->left) >= 0) {
			return rightRotate(root);
		}
		// lH > rH
		// LR
		else if(balance > 1 && getBalance(root->left) < 0) {
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
		// rH > lH
		// RL
		else if(balance < -1 && getBalance(root->right) <= 0) {
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
		// rH > lH
		// RR
		else if(balance < -1 && getBalance(root->right) > 0) {
			return leftRotate(root);
		}
		
		// do nothing
		return root;
	}
	
	Node * minValueNode(Node* node) {
		Node* current = node;
		
    	/* loop down to find the leftmost leaf */
    	while (current->left != NULL) 
        	current = current->left;
        	
    	return current; 
	}
	
	Node* deleteNode(Node* root, int key) {
		if (root == NULL) return root;
    	if (key < root->key) root->left = deleteNode(root->left, key); 
  		else if(key > root->key) root->right = deleteNode(root->right, key); 
	    else { 
	        if((root->left == NULL) || (root->right == NULL)) {
				Node *temp = root->left ? root->left : root->right; 
	  
	            if (temp == NULL) { 
	            	temp = root; 
	                root = NULL; 
	            } 
	            else *root = *temp;
	            
	            free(temp); 
	        } 
	        else
	        { 
	            Node* temp = minValueNode(root->right); 
	            root->key = temp->key;
	            root->right = deleteNode(root->right, temp->key); 
	        } 
	    } 
  
	    if (root == NULL) return root; 
	  	fixHeight(root);
	  
	    int balance = getBalance(root);
		
		// lH > rH
		// LL
		if(balance > 1 && getBalance(root->left) >= 0) {
			return rightRotate(root);
		}
		// lH > rH
		// LR
		else if(balance > 1 && getBalance(root->left) < 0) {
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
		// rH > lH
		// RL
		else if(balance < -1 && getBalance(root->right) <= 0) {
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
		// rH > lH
		// RR
		else if(balance < -1 && getBalance(root->right) > 0) {
			return leftRotate(root);
		}
		
		// do nothing
		return root;
	}
	
	void display() {
		if(root == NULL) {
			cout << "Tree is empty\n";
			return;
		}
		
		preOrder(root);
		
		cout << "\n";
	}
	
	void preOrder(Node *root) {
		if(root == NULL) return;
		
		cout << root->key << " ";
		
		preOrder(root->left);
		preOrder(root->right);
	}	
};

int main() {
	AVLTree tree;
	int op;
	
	while(1) {
		cout << "0. Insert\n";
		cout << "1. Delete\n";
		cout << "2. Display\n";
		cout << "3. Insert multiple in preorder\n";
		
		cout << "Enter operation: ";
		cin >> op;
		
		bool invalid = false;
		
		switch(op) {
			case 0: {
				cout << "Enter number: ";
				int x; cin >> x;
				
				tree.insert(x);
				tree.display();
				break;
			}
			case 1: {
				cout << "Enter number: ";
				int x; cin >> x;
				
				//tree.remove(x);
				tree.display();
				break;
			}
			case 2: {
				tree.display();
				break;
			}
			case 3: {
				cout << "Enter number: ";
				int n; cin >> n;
				
				while(n--) {
					int x; cin >> x;
					tree.insert(x);
				}
				
				tree.display();
				break;
			}
			default: {
				invalid = true;
				break;
			}
		}
		
		if(invalid) break;
		
		cout << "\n";
	}
	
	return 0;
}
