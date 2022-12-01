#include <iostream>
#include<algorithm>
using namespace std;

enum color {RED, BLACK};

struct Node{
    int val;
    Node* parent;
    Node* left;
    Node* right;
    int color;//0 ->RED 1->BLACK
    Node(int val): val(val), parent(NULL),  left(NULL), right(NULL), color(RED) {};
};

class RBtree{
    Node* root;
    public:
        RBtree(): root(NULL) {}

        void rotateLeft(Node *);
        void rotateRight(Node *);
        Node* insertUtil(Node*, int);
        void insert(int);
        void insertFix(Node *);
        Node* successor(Node *);
        void deleteNode(int);
        void deleteFix(Node *);
        void disp();
        void display(Node* );
};

void RBtree::rotateLeft(Node* z){
    if(!z->right) return;
    
    Node *y = z->right;
    Node* T = y->left;
    
    z->right = T;
    if(T) T->parent = z;

    if(z->parent){
        y->parent = z->parent;
        if(z == z->parent->left)
            z->parent->left = y;
        else
            z->parent->right = y;
    }
    else root = y;

    y->left = z;
    z->parent = y;
    
}

void RBtree::rotateRight(Node* z){
    if(!z->left) return;
    Node* y = z->left;
    Node* T = y->right;

    z->left = T;
    if(T) T->parent = z;

    if(z->parent){
        y->parent = z->parent;
        if(z == z->parent->left)
            z->parent->left = y;
        else
            z->parent->right = y;
    }
    else root = y;
    
    y->right = z;
    z->parent = y;
}

void RBtree::insert(int key){
	Node *p, *q;
	Node *t = new Node(key);
	p = root;
	q = NULL;
	if (!root){
		root = t;
		t->parent = NULL;
	}
	else{
		while (p != NULL){
			q = p;
			if (p->val < t->val)
				p = p->right;
			else
				p = p->left;
		}
		t->parent = q;
		if (q->val < t->val)
			q->right = t;
		else
			q->left = t;
	}
	insertFix(t);
}
void RBtree::insertFix(Node *t){
	Node *u; //uncle
	if (root == t){
		t->color = BLACK;
		return;
	}
	while (t->parent != NULL && t->parent->color == RED){
		Node *g = t->parent->parent;
		if (g->left == t->parent){
			if (g->right != NULL){
				u = g->right;
				if (u->color == RED){
					t->parent->color = BLACK;
					u->color = BLACK;
					g->color = RED;
					t = g;
				}
			}
			else{
				if (t->parent->right == t){
					t = t->parent;
					rotateLeft(t);
				}
				t->parent->color = BLACK;
				g->color = RED;
				rotateRight(g);
			}
		}
		else{
			if (g->left != NULL){
				u = g->left;
				if (u->color == RED){
					t->parent->color = BLACK;
					u->color = BLACK;
					g->color = RED;
					t = g;
				}
			}
			else{
				if (t->parent->left == t){
					t = t->parent;
					rotateRight(t);
				}
				t->parent->color = BLACK;
				g->color = RED;
				rotateLeft(g);
			}
		}
		root->color = BLACK;
	}
}

void RBtree::deleteNode(int key)
{
	if (!root){
		cout << "\nEmpty Tree";
		return;
	}
	Node *p = root;
	Node *y = NULL;
	Node *q = NULL;
	bool found = 0;
	while (p != NULL && !found){
		if (p->val == key)
			found = true;
		if (!found)
		{
			if (p->val < key)
				p = p->right;
			else
				p = p->left;
		}
	}
	if (!found){
		cout << "\nElement not Found";
		return;
	}
	else{
		cout << "\nDeleted Element: " << p->val;
		cout << "\nColour: ";
		if (p->color == BLACK)
			cout << "Black";
		else
			cout << "Red";

		// if (p->parent != NULL)
		// 	cout << "\nParent: " << p->parent->val;
		// else
		// 	cout << "\nNo parent of the node.  ";
		// if (p->right != NULL)
		// 	cout << "\nRight Child: " << p->right->val;
		// else
		// 	cout << "\nNo right child of the node.  ";
		// if (p->left != NULL)
		// 	cout << "\nLeft Child: " << p->left->val;
		// else
		// 	cout << "\nNo left child of the node.  ";
		// cout << "\nNode Deleted.";
		if (p->left == NULL || p->right == NULL) y = p;
		else y = successor(p);
		
		if (y->left != NULL) q = y->left;
		else{
			if (y->right != NULL)
				q = y->right;
			else
				q = NULL;
		}
		if (q != NULL) q->parent = y->parent;
		if (y->parent == NULL) root = q;
		else{
			if (y == y->parent->left)
				y->parent->left = q;
			else
				y->parent->right = q;
		}
		if (y != p){
			p->color = y->color;
			p->val = y->val;
		}
		if (y->color == BLACK)
			deleteFix(q);
	}
}

void RBtree::deleteFix(Node *p){
	Node *s;
	while (p != root && p->color == BLACK){
		if (p->parent->left == p){
			s = p->parent->right;
			if (s->color == RED){
				s->color = BLACK;
				p->parent->color = RED;
				rotateLeft(p->parent);
				s = p->parent->right;
			}
			if (s->right->color == BLACK && s->left->color == BLACK){
				s->color = RED;
				p = p->parent;
			}
			else{
				if (s->right->color == BLACK){
					s->left->color = BLACK;
					s->color = RED;
					rotateRight(s);
					s = p->parent->right;
				}
				s->color = p->parent->color;
				p->parent->color = BLACK;
				s->right->color = BLACK;
				rotateLeft(p->parent);
				p = root;
			}
		}
		else{
			s = p->parent->left;
			if (s->color == RED){
				s->color = BLACK;
				p->parent->color = RED;
				rotateRight(p->parent);
				s = p->parent->left;
			}
			if (s->left->color == BLACK && s->right->color == BLACK){
				s->color = RED;
				p = p->parent;
			}
			else{
				if (s->left->color == BLACK){
					s->right->color = BLACK;
					s->color = RED;
					rotateLeft(s);
					s = p->parent->left;
				}
				s->color = p->parent->color;
				p->parent->color = BLACK;
				s->left->color = BLACK;
				rotateRight(p->parent);
				p = root;
			}
		}
		p->color = BLACK;
		root->color = BLACK;
	}
}


Node* RBtree::successor(Node *p){
	Node *y = NULL;
    if (p->left != NULL){
		y = p->left;
		while (y->right != NULL)
			y = y->right;
	}
	else{
		y = p->right;
		while (y->left != NULL)
			y = y->left;
	}
	return y;
}

void RBtree::disp(){
	display(root);
}

void RBtree::display(Node *p){
	if (root == NULL){
		cout << "\nEmpty Tree.";
		return;
	}
	if (p != NULL){
		cout << "\nNODE";
		cout << "\nKey: " << p->val;
		cout << "\nColor: ";
		if (p->color == BLACK)
			cout << "Black";
		else
			cout << "Red";
		if (p->parent != NULL)
			cout << "\n Parent: " << p->parent->val;
		if (p->left){
			cout << "\n\nLeft:\n";
			display(p->left);
		}
		if (p->right){
			cout << "\n\nRight:\n";
			display(p->right);
		}
	}
}

int main()
{
	int ch, y = 0;
    int key;
	RBtree obj;
	do{
		cout << "\n\t RED BLACK TREE ";
		cout << "\n 1. Insert";
		cout << "\n 2. Delete";
		cout << "\n 3. Display the tree";
		cout << "\n 4. Exit";
		cout << "\nChoice: ";
		cin >> ch;
		switch (ch){
		case 1:
            cout << "Enter key: ";
            cin >> key;
            obj.insert(key);
			cout << "\nNode Inserted.\n";
			break;
		case 2:
            cout << "Enter key: ";
            cin >> key;
            obj.deleteNode(key);
			break;
		case 3: obj.disp();
			break;
		case 4: y = 1;
			break;
		default: cout << "\nEnter a Valid Choice.";
		}
		cout << "\n";

	} while (y != 1);
	return 1;
}
