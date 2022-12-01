#include<iostream>
#include<list>
using namespace std;

struct BinTreeNode{
    int key;
    int degree;
    BinTreeNode* child;
    BinTreeNode* sibling;
    BinTreeNode* parent;
    BinTreeNode(int val=0): key(val),degree(0),child(NULL),sibling(NULL),parent(NULL) {}
};

class BinHeap{
    BinTreeNode* min;
    BinTreeNode* roots;
    void joinTree(BinTreeNode*, BinTreeNode*);
    BinTreeNode* mergeRoots(BinHeap*);
    void displayUtil(BinTreeNode*);
    public:
        BinHeap(): roots(NULL), min(NULL) {}
        BinHeap(BinTreeNode* root): roots(root), min(root) {}
        bool isEmpty();
        int getMin();
        void insert(int);
        void merge(BinHeap*);
        BinTreeNode* searchNode(BinTreeNode*, int);
        BinTreeNode* extractMin();
        void decreaseKey(int, int);
        void deleteNode(int);
        void display();
};

void BinHeap::joinTree(BinTreeNode* x, BinTreeNode* y){
    x->parent = y;
    x->sibling = y->child;
    y->child = x;
    (y->degree)++;
}

BinTreeNode* BinHeap::mergeRoots(BinHeap* b){
    BinTreeNode* ret = new BinTreeNode();
    BinTreeNode* end = ret;
    BinTreeNode* L = this->roots;
    BinTreeNode* R = b->roots;
    if(!L) return R;
    if(!R) return L;

    while( L != NULL || R != NULL){
        if(L==NULL){
            end->sibling = R;
            end = end->sibling;
            R = R->sibling;
        }
        else if(R == NULL){
            end->sibling = L;
            end = end->sibling;
            L = L->sibling;
        }
        else{
            if (L->degree < R->degree){
                end->sibling = L;
                end = end->sibling;
                L = L->sibling;
            }
            else{
                end->sibling = R;
                end = end->sibling;
                R = R->sibling;
            }
        }
    }
    return ret->sibling;
}


bool BinHeap::isEmpty(){
    return roots == NULL;
}

int BinHeap::getMin(){
    return min->key;
}

void BinHeap::insert(int key){
    BinTreeNode* newNode = new BinTreeNode(key);
    merge(new BinHeap(newNode));
}

void BinHeap::merge(BinHeap* b){
    BinHeap* H = new BinHeap();
    H->roots = mergeRoots(b);
    if(!H->roots){
        roots = NULL;
        min = NULL;
        return;
    }
    BinTreeNode* prev = NULL;
    BinTreeNode* curr = H->roots;
    BinTreeNode* next = curr->sibling;
    while(next != NULL){
        if(curr->degree != next->degree ||
            (next->sibling != NULL && next->sibling->degree == curr->degree)){
                prev = curr;
                curr = next;
        }
        else if(curr->key <= next->key){
            curr->sibling = next->sibling;
            joinTree(next,curr);
        }
        else{
            if(!prev) H->roots = next;
            else prev->sibling = next;
            joinTree(curr,next);
            curr = next;
        }
        next = curr->sibling;
    }
    roots = H->roots;
    min = roots;
    curr = roots;
    while(curr != NULL){
        if(curr->key < min->key) min = curr;
        curr = curr->sibling;
    }
}

BinTreeNode* BinHeap::searchNode(BinTreeNode* n, int key){
    while(n){
        if(n->key == key) return n;
        else if(n->key < key){
            BinTreeNode* temp = searchNode(n->child,key);
            if(temp) return temp;
        }
        n = n->sibling;
    }
    return NULL;
}

BinTreeNode* BinHeap::extractMin(){
    BinTreeNode* minNode = min;
    BinTreeNode* prev = NULL;
    BinTreeNode* curr = roots;
    while(curr != minNode){
        prev = curr;
        curr = curr->sibling;
    }
    if(!prev) roots = curr->sibling;
    else prev->sibling = curr->sibling;

    BinTreeNode* revChild = NULL;
    curr = minNode->child;
    while(curr){
        BinTreeNode* next = curr->sibling;
        curr->sibling = revChild;
        revChild = curr;
        curr = next;
    }

    BinHeap* H = new BinHeap();
    H->roots = revChild;
    merge(H);
    return minNode;
}

void BinHeap::decreaseKey(int oldKey, int newKey){
    BinTreeNode* x = searchNode(roots,oldKey);
    if(!x) {
        cout << "\nKey not found";
        return;
    }

    x->key = newKey;
    BinTreeNode* y = x;
    BinTreeNode* z = y->parent;
    while(z && y->key < z->key){
        swap(y->key,z->key);
        y = z;
        z = y->parent;
    }
    if(y->key < min->key) min = y;
}

void BinHeap::deleteNode(int key){
    decreaseKey(key,INT_MIN);
    extractMin();
}

void BinHeap::displayUtil(BinTreeNode* temp){
    while(temp){
        cout << temp->key << " ";
        displayUtil(temp->child);
        temp = temp->sibling;
    }
}

void BinHeap::display(){
    BinTreeNode* temp = roots;
    while(temp){
        cout<< temp->key << "->";
        displayUtil(temp->child);
        cout << "\n";
        temp = temp->sibling;
    }
    cout << "\n";
}

int main(){
    BinHeap* h = new BinHeap();
    
    h->insert(30);
    h->insert(21);
    h->insert(57);
    h->insert(10);
    h->insert(4);
    h->insert(12);
    h->insert(36);
    h->display();
    h->decreaseKey(57,3);
    h->display();
    cout << h->getMin() << "\n";
    h->extractMin();
    h->display();
    h->deleteNode(30);
    h->display();
    return 0;
}