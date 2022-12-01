#include<iostream>
using namespace std;

int stack[10000];
int top = -1;

bool isEmpty(){
    return top == -1;
}
void push(int n){
    stack[++top] = n;
}

void pop(){
    if(top == -1) cout << "Empty";
    else {
        cout << stack[top--];
    }
}

int main(){
    int op = 1;
    int n;
    while(op != 4){
        cout << "1. Push\n2. Pop\n3. Top\n4. Quit\nEnter option: ";
        cin >> op;
        if(op == 1){
            cout << "Enter a no.: ";
            cin >> n;
            push(n); 
        }
        else if(op == 2){
            pop();
        }
        else if(op == 3){
            if(!isEmpty()) cout << stack[top];
            else cout << "Empty";
        }
        else break;
        cout << "\n";

    }
    return 0;
}