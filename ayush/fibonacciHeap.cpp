#include<iostream>
#include<cmath>
using namespace std;

struct FibNode{
    int key;
    int degree;
    bool mark;
    FibNode* child;
    FibNode* b;
    FibNode* f;
    FibNode* parent;
    FibNode(int val=0): key(val),degree(0),mark(false),
    child(NULL),b(NULL),f(NULL),parent(NULL) {}
};

class FibHeap{
    FibNode* min;
    int N;

    public:
        FibHeap(): min(NULL),N(0) {}
        FibHeap(FibNode* n): min(n),N(1) {
            n->b = n->f = n;
            n->parent = n->child = NULL;
        }

        bool isEmpty();
        int getMin();
        void insert(FibNode*);
        void merge(FibHeap*);
        // FibNode* searchNode(FibNode*, int);
        FibNode* extractMin();
        void decreaseKey(FibNode*, int);
        void deleteNode(FibNode*);
        // void display(); 
};

bool FibHeap::isEmpty(){
    return this->min == NULL;
}

void FibHeap::insert(FibNode* n){
    merge(new FibHeap(n));
}

void FibHeap::merge(FibHeap* h){
    this->N += h->N;
    if( h->isEmpty()) return;
    if(isEmpty()){
        min = h->min;
        return;
    }
    FibNode* f1 = min;
    FibNode* l1 = min->b;
    FibNode* f2 = h->min;
    FibNode* l2 = h->min->b;
    f1->b = l2;
    l1->f = f2;
    f2->b = l1;
    l2->f = f1;
    if(h->min->key < min->key)
        min = h->min;
}

int FibHeap::getMin(){
    return min->key;
}

FibNode* FibHeap::extractMin(){
    FibNode* ret = min;
    (this->N)--;
    if(ret->f == ret) min = NULL;
    else{
        FibNode* prev = ret->b;
        FibNode* next = ret->f;
        prev->f = next;
        next->b = prev;
        min = next;
    }
    if(ret->child){
        FibNode* firstChd = ret->child;
        FibNode* currChd = firstChd;
        do{
            currChd->parent = NULL;
            currChd = currChd -> f;
        }while(currChd != firstChd);
        
        if(isEmpty()){
            min = firstChd;
        }
        else{
            FibNode *f1 = this -> min;
            FibNode *l1 = this -> min -> b;
            FibNode *f2 = firstChd;
            FibNode *l2 = firstChd -> b;
            f1 -> b = l2;
            l1 -> f = f2;
            f2 -> b = l1;
            l2 -> f = f1;            
        }
    }
    if (min){
        int maxAuxSize = 5 * (((int)log2(this -> N + 1)) + 1);
        FibNode *aux[maxAuxSize + 1];
        for (int i=0;i<=maxAuxSize;i++) aux[i] = NULL;
        int maxDegree = 0;
        
        FibNode *curr = min;
        
        do{
            FibNode *next = curr->f;
            int deg = curr->degree;
            FibNode *P = curr;
            while (aux[deg]){
                FibNode *Q = aux[deg];
                aux[deg] = NULL;
                
                if (P->key > Q->key){
                    FibNode *tmp = P;
                    P = Q;
                    Q = tmp;
                }
                
                Q->parent = P;
                if (!P->child){
                    P->child = Q;
                    Q->b = Q->f = Q;
                }
                else{
                    FibNode *last = P->child->b;
                    last->f = Q;
                    Q->b = last;
                    P->child->b = Q;
                    Q->f = P->child;
                }
                
                deg++;
                P->degree = deg;
            }
            aux[deg] = P;
            if (deg > maxDegree) maxDegree = deg;
            curr = next;
        } while (curr != this->min);
        
        
        FibNode *previous = aux[maxDegree];
        this -> min = previous;
        for (int i=0;i<=maxDegree;i++){
            if (aux[i] != NULL){
                previous -> f = aux[i];
                aux[i] -> b = previous;
                if (aux[i] -> key < this -> min -> key) this -> min = aux[i];
                previous = aux[i];
            }
        }
        
    }
    return ret;
}

void FibHeap::decreaseKey(FibNode *n, int newKey)
{
    //Assuming newKey < n -> key
    n -> key = newKey;
    
    FibNode *curr = n;
    if (curr->parent){
        if (curr->key < curr->parent->key){
            FibNode *par = curr->parent;
            curr->mark = false;
            
            curr->parent = NULL;
            if (curr->f == curr) par->child = NULL;
            else{
                FibNode *prev = curr->b;
                FibNode *next = curr->f;
                prev->f = next;
                next->b = prev;
                if (par->child == curr) par->child = prev;
            }
            (par->degree)--;
            
            FibNode *last = min->b;
            last->f = curr;
            curr->b = last;
            min->b = curr;
            curr->f = min;
            
            if (curr->key < min->key) min = curr;
            
            while (par->parent && par->mark){
                curr = par;
                par = curr->parent;
                curr->mark = false;
                
                curr->parent = NULL;
                if (curr->f == curr) par->child = NULL;
                else{
                    FibNode *prev = curr->b;
                    FibNode *next = curr->f;
                    prev->f = next;
                    next->b = prev;
                    if (par->child == curr) par->child = prev;
                }
                par->degree = par->degree - 1;
                
                FibNode *last = this->min->b;
                last->f = curr;
                curr->b = last;
                min->b = curr;
                curr->f = min;
                
            }
            if (par->parent) par->mark = true;
        }
    }
    else if (n->key < min->key) min = n;
}

void FibHeap::deleteNode(FibNode* n){
    decreaseKey(n,INT_MIN);
    extractMin();
}

int main(){
    FibHeap *fh = new FibHeap();
    
    FibNode *x = new FibNode(11);
    FibNode *y = new FibNode(5);
    
    fh->insert(x);
    fh->insert(y);
    fh->insert(new FibNode(8));
    fh-> insert(new FibNode(3));
    fh->insert(new FibNode(4));
    
    fh->decreaseKey(x, 2);
    fh->deleteNode(y);
    
    while (!fh->isEmpty()){
        printf("%d ", fh->extractMin()->key);
    }
    printf("\n");
    return 0;
}