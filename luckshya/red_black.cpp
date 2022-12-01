#include<bits/stdc++.h>
using namespace std;

enum Color = {red, black, double_black};

struct Node{
    int data;
    Node* left;
    Node* right;
    Color color;
    int height;
    Node(int d){
        data =d;
        left = NULL;
        right = NULL;
        color = red; 
    }
};

Node* ll_rotation(Node* root){
    Node* left_child = root->left;
    Node* left_child_left = left_child->left;
    Node* left_child_right = left_child->right;
    //ll rotation and changing swaping the color of root and left_child
    root->left = left_child_right;
    left_child->right = root;
    left_child->color = black;
    root->color = red;
    return left_child;
}

Node* rr_rotation(Node* root){
    Node* right_child = root->right;
    Node* right_child_left = right_child->left;
    Node* right_child_right = right_child->right;
    //rr rotation and changing swaping the color of root and right_child
    root->right = right_child_left;
    right_child->left = root;
    right_child->color = black;
    root->color = red;
    return right_child;
}

Node* lr_rotation(Node* root){
    Node* left_child = root->left;
    Node* left_child_left = left_child->left;
    Node* left_child_right = left_child->right;
    //lr swaping
    Node* lrl = left_child_right->left;
    left_child_right->left = left_child;
    left_child->right = lrl;
    root->left = left_child_right;

    return ll_rotation(root);
}

Node* rl_rotation(Node* root){
    Node* right_child = root->right;
    Node* right_child_left = right_child->left;
    Node* right_child_right = right_child->right;
    //lr swaping
    Node* rlr = right_child_left->right;
    right_child_left->right = right_child;
    right_child->left = rlr;
    root->right = right_child_left;

    return rr_rotation(root);
}

Node* insert(Node* root, int key){
    if(root == NULL){
        root = new Node(key);
        // root->color = black;
        // root->height = black;
        return root;
    }

    if(root->data > key){
        Node* left_child = insert(root->left,  key);
        root->left = left_child;
        Node* right_child = root->right;
        if(left_child->left == NULL && left_child->right == NULL) return root;

        if(left_child->color == black ) return root;

        int llc = left_child->left ? left_child->left->color : black;
        int lrc = left_child->right ? left_child->right->color : black;
        int rc = right_child ? right_child->color : black;

        if(llc == red){
            if(rc == red){
                left_child->color = black;
                right_child->color = black;
                root->color = red;
                return root;
            }else{
               return ll_rotation(root);
            }
        }else if(lrc == red){
            if(rc == red){
                left_child->color = black;
                right_child->color = black;
                root->color = red;
                return root;
            }else{
                return lr_rotation(root);
            }
        }
    }else{
        Node* right_child = insert(root->right,  key);
        root->right = right_child;
        Node* left_child = root->left;
        if(right_child->left == NULL && right_child->right == NULL) return root;

        if(right_child->color == black ) return root;

        int rlc = right_child->left ? right_child->left->color : black;
        int rrc = right_child->right ? right_child->right->color : black;
        int lc = left_child ? left_child->color : black;

        if(rrc == red){
            if(lc == red){
                left_child->color = black;
                right_child->color = black;
                root->color = red;
                return root;
            }else{
               return rr_rotation(root);
            }
        }else if(rlc == red){
            if(lc == red){
                left_child->color = black;
                right_child->color = black;
                root->color = red;
                return root;
            }else{
                return rl_rotation(root);
            }
        }
    }
    return root;
}

Node* deleteNode(Node* root, int key){
    if(root == NULL) return NULL;
    
}

void inorder(Node* root){
    if(root == NULL) return ;
    inorder(root->left);
    cout<<root->data<<"("<<root->color<<")"<<"   ";
    inorder(root->right);
}

void preorder(Node* root){
    if(root == NULL) return ;
    cout<<root->data<<"("<<root->color<<")"<<"   ";
    preorder(root->left);
    preorder(root->right);
}

int main(){
    // Node* root = NULL;
    Node* root = NULL;
    root = insert(root, 25);
    root->color = black;
   
    root = insert(root, 5);
    root->color = black;
    
    root = insert(root, 2);
    root->color = black;
    
    root = insert(root, 225);
    root->color = black;
    
    root = insert(root, 251);
    root->color = black;
    
    root = insert(root, 65);
    root->color = black;

    root = insert(root, 15);
    root->color = black;
    
    root = insert(root, 35);
    root->color = black;
   
    root = insert(root, 51);
    root->color = black;
    
    root = insert(root, 125);
    root->color = black;
    
    root = insert(root, 21);
    root->color = black;
    
    root = insert(root, 285);
    root->color = black;
    
    root = insert(root, 1525);
    root->color = black;
    cout<<"\n\n";
    preorder(root);
    cout<<"\n\n";
    inorder(root);

    return 0;
}