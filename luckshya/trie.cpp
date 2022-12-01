#include <bits/stdc++.h>

using namespace std;

struct TrieNode {
	unordered_map<int, TrieNode*> childs;
	bool isEnd;
	
	TrieNode() {
		isEnd = false;
	}
};

struct Trie {
	TrieNode *root;
	
	Trie() {
		root = new TrieNode();	
	}
	
	void insert(string key) {
		TrieNode *curr = root;
		
		for(char c: key) {
			if(curr->childs.find(c) == curr->childs.end()) {
				curr->childs[c] = new TrieNode();
			}
			
			curr = curr->childs[c];
		}
		
		curr->isEnd = true;
	}
	
	bool search(string key) {
		TrieNode *curr = root;
		
		for(char c: key) {
			if(curr->childs.find(c) == curr->childs.end()) {
				return false;
			}
			
			curr = curr->childs[c];
		}
		
		return curr->isEnd;
	}
};

int main() {
	Trie trie;
	
	string keys[] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
                     
	for(string s: keys) {
		cout << "Inserting '" << s << "' in trie\n";
		trie.insert(s);
	}
	
	
	cout << "\n";
	
	string toFind[] = {"the", "these", "their", "thaw"};
	
	for(string s: toFind) {
		bool found = trie.search(s);
		
		if(found) cout << s << " - found in trie\n";
		else cout << s << " - not found in trie\n";
	}
	
	return 0;
}
