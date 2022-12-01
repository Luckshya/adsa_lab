#include<iostream>
#include<vector>
using namespace std;

#include <bits/stdc++.h>
using namespace std;
  
const int ALPHABET = 26;
  
struct Node{
    struct Node *next[ALPHABET];
    bool isEndOfWord;
    Node(){
        isEndOfWord = false;
        for(int i=0;i<ALPHABET;i++) next[i] = NULL;
    }
};

class Trie{
    
    public:
    Node* root;
    Trie(){
        root = new Node();
    }
    void insert(string );
    bool search(string);
    bool isEmpty(Node*);
    Node* remove(Node*, string, int);
    void display(Node*, char str[], int);
};

void Trie::insert(string key){
    struct Node *pCrawl = root;
    for (int i = 0; i < key.length(); i++){
        int index = key[i] - 'a';
        if (!pCrawl->next[index])
            pCrawl->next[index] = new Node();  
        pCrawl = pCrawl->next[index];
    }

    pCrawl->isEndOfWord = true;
}
  

bool Trie::search(string key){
    struct Node *pCrawl = root;
    for (int i = 0; i < key.length(); i++){
        int index = key[i] - 'a';
        if (!pCrawl->next[index])
            return false;
        pCrawl = pCrawl->next[index];
    }
    return pCrawl->isEndOfWord;
}

bool Trie::isEmpty(Node* curr){
    for (int i = 0; i < ALPHABET; i++)
        if (curr->next[i])
            return false;
    return true;
}
 
Node* Trie::remove(Node* curr, string key, int depth = 0){
    if (!curr)
        return NULL;

    if (depth == key.size()) {

        if (curr->isEndOfWord)
            curr->isEndOfWord = false;

        if (isEmpty(curr)) {
            delete curr;
            curr = NULL;
        }
        return curr;
    }

    int index = key[depth] - 'a';
    curr->next[index] = remove(curr->next[index], key, depth + 1);
 
    if (isEmpty(curr) && curr->isEndOfWord == false) {
        delete (curr);
        curr = NULL;
    }
    return curr;
}

void Trie::display(struct Node* curr, char str[], int depth)
{
    if (curr->isEndOfWord) {
        str[depth] = '\0';
        cout << str << "\n";
    }
    for (int i = 0; i < ALPHABET; i++) {
        if (curr->next[i]) {
            str[depth] = i+'a';
            display(curr->next[i], str, depth+1);
        }
    }
}


int main(){
    Trie t = Trie();
    vector<string> v = {"the", "a", "there",
                    "answer", "any", "by",
                     "bye", "their"};
    for(string i: v){
        t.insert(i);
    }
    char str[20];
    t.remove(t.root,"bye");
    t.display(t.root,str, 0);
    return 0;
}