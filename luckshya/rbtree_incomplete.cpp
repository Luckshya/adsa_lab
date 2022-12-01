#include <bits/stdc++.h>

using namespace std;

struct RBNode {
	int data;
	
	RBNode *left;
	RBNode *right;
	RBNode *parent;
	
	char color;
	
	RBNode(int key) {
		data = key;
		
		left = NULL;
		right = NULL;
		parent = NULL;
		
		color = 'R';
	}
};

struct RBTree {
	RBNode *root;
	
	RBTree() {
		root = NULL;
	}
	
	void insert(RBNode *node, int key) {
		bool RRviolation = false;
		
		if(node == NULL) {
			return new RBNode(key);
		}
		else if(key < node->data) {
			node->left = insert(node->left, key);
			node->left->parent = node;
			
			if(node->left->color == 'R' && node->color == 'R') {
				RRviolation = true;
			}
		}
		else {
			node->right = insert(node->right, key);
			node->right->parent = node;
			
			if(node->right->color == 'R' && node->color == 'R') {
				RRviolation = true;
			}
		}
		
		if(RRviolation) {
			if(node->parent->right == node) {
				// uncle is left child of grandparent and UNCLE is RED
				if(node->parent->left == NULL || root->parent->left->color == 'R') {
					node->parent->left->color = 'B';
					node->color = 'B';
					
					if(node->parent != root) {
						node->parent->color = 'R';
					}
				}
				// UNCLE is BLACK
				else {
					
				}
			}
		}
	}
	
	void insert(int key) {
		if(!root) {
			root = new RBNode(key);
			root->color = 'B';
		} else {
			root = insert(root, key);
		}
	}
};

int main() {
	
	
	return 0;
}
