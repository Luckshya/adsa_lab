#include <iostream>
#include<algorithm>
using namespace std;


struct Node{
    int val;
    Node* left;
    Node* right;
    int height;
    Node(int val): val(val), left(NULL), right(NULL), height(1) {};
};


int height(Node* n){
    return n ? n->height : 0;
}

int getBalance(Node* n){
    if(!n) return 0;
    return height(n->left) - height(n->right);
}

Node* rotateRight(Node* z){
    Node* y = z->left;
    Node* T = y->right;
   
    y->right = z;
    z->left = T;
   
    z->height = 1 + max(height(z->left),height(z->right));
    y->height = 1 + max(height(y->left),height(y->right));
    return y;
}

Node* rotateLeft(Node* z){
    Node* y = z->right;
    Node* T = y->left;
   
    y->left = z;
    z->right = T;
   
    z->height = 1 + max(height(z->left),height(z->right));
    y->height = 1 + max(height(y->left),height(y->right));
    return y;
}

Node* insert(Node* node, int key){
    Node* newNode = new Node(key);
    if(!node) return newNode;
    if(node->val > key)
        node->left = insert(node->left,key);
   
    else
        node->right = insert(node->right,key);
   
    node->height  = 1 + max(height(node->left),height(node->right));
   
    int balance = getBalance(node);
   
    if(balance > 1 ){
        if(key > node->left->val)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    else if(balance < -1){
        if(key < node->right->val)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
   
}

Node* succ(Node* root){
    if(!root->right) return NULL;
    Node* temp = root->right;
    while(temp->left) temp = temp->left;
    return temp;
}

Node* deleteNode(Node* root, int key){
    if(!root) return root;
    if(key < root->val)
        root->left = deleteNode(root->left,key);

    else if(key > root->val)
        root->right = deleteNode(root->right,key);
    
    else{
        Node* temp = root;
        if(!root->left){
            root = root->right;
            delete temp;
        }
        else if(!root->right){
            root = root->left;
            delete temp;
        }
        else{
            Node* temp =  succ(root);
            root->val = temp->val;
            root->right = deleteNode(root->right,temp->val);
        }
        
    }
    if(!root) return root;
    root->height = 1 + max(height(root->left),height(root->right));
    int balance = getBalance(root);
   
    if(balance > 1 ){
        if(key > root->left->val)
            root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    else if(balance < -1){
        if(key < root->right->val)
            root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

void preOrder(Node* root){
    if(root){
        cout << root->val << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    Node *root = NULL;
    root = insert(root, 10);
    preOrder(root);
    cout << "\n";
    root = insert(root, 20);
    preOrder(root);
    cout << "\n";
    root = insert(root, 30);
    preOrder(root);
    cout << "\n";
    root = insert(root, 40);
    preOrder(root);
    cout << "\n";
    root = insert(root, 50);
    preOrder(root);
    cout << "\n";
    root = insert(root, 25);
    preOrder(root);
    cout << "\n";
    root = deleteNode(root,40);
    preOrder(root);
    cout << "\n";
    root = deleteNode(root,30);
    preOrder(root);
    return 0;
}