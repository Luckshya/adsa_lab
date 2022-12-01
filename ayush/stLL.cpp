#include<iostream>
using namespace std;
class Node{
    public:
    int val;
    Node* next;
    Node(){}
    Node(int val) : val(val), next(NULL){}
};

class stack{
    Node* head;
    bool isEmpty(){
        return !head;
    }
    
    public:
    stack() : head(NULL){}
    
    void push(int n){
        Node* newNode = new Node(n);
        newNode->next = head;
        head = newNode;
    }

    void pop(){
        if(isEmpty()){
            cout << "Empty";
            return;
        }
        Node* temp = head;
        cout << temp->val;
        head = temp->next;
        delete temp;
    }

    void top(){
        if(isEmpty()){
            cout << "Empty";
            return;
        }
        cout << head->val;
    }

};


int main(){
    int op = 1;
    int n;
    stack s;
    while(op != 4){
        cout << "1. Push\n2. Pop\n3. Top\n4. Quit\nEnter option: ";
        cin >> op;
        if(op == 1){
            cout << "Enter a no.: ";
            cin >> n;
            s.push(n); 
        }
        else if(op == 2){
            s.pop();
        }
        else if(op == 3){
            s.top();
        }
        else break;
        cout << "\n";
    }
    return 0;
}