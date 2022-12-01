#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;
using vii = vector<vector<int>>;

vi generateClause(int literals) {
	vi clause;
	
	for(int i = 1; i <= literals; ++i) {
		// take it or not take it
		int takeIt = rand() % 2;
		
		if(takeIt) {
			// complement it or not
			int complementIt = rand() % 2;
			clause.push_back(complementIt ? -i : i);
		}
	}
	
	if(clause.empty()) {
		int complementIt = rand() % 2;
		int val = rand() % literals;
		
		clause.push_back(complementIt ? -val : val);
	}
	
	return clause;
}

vii generateClauseSet(int literals) {
	int numSets = rand() % 5;
	numSets++;
	
	vii clauseSet;
	
	for(int i = 0; i < numSets; ++i) {
		clauseSet.push_back(generateClause(literals));	
	}
	
	return clauseSet;
}

vi generateLiteralValues(int literals) {
	vi literalValues;
	
	for(int i = 0; i < literals; ++i) {
		int value = rand() % 2;
		
		literalValues.push_back(value);
	}
	
	return literalValues;
}

bool evaluteSatisfiability(vi& literalValues, vii& clauseSet) {
	bool expVal = 1;
	
	for(int j = 0; j < clauseSet.size(); ++j) {
		auto clause = clauseSet[j];
		bool clauseVal = false;
		
		cout << "[(";
		
		for(int i = 0; i < clause.size(); ++i) {
			int literalVal = 0;
			
			int x = clause[i];
			
			if(x < 0) {
				cout << "!x" << -x << " = ";
				if(literalValues[-x-1] == 0) literalVal = 1;
			} else {
				cout << "x" << x << " = ";
				if(literalValues[x-1] == 1) literalVal = 1;
			}
			
			clauseVal = clauseVal | literalVal;
			cout << literalVal;
			
			if(i != clause.size() - 1) cout << " | ";
		}
		
		cout << ") = ";
		cout << clauseVal;
		cout << "]";
		
		if(j != clauseSet.size()-1) cout << " & \n";
		
		if(!clauseVal) {
			expVal = 0;
		}
	}
	
	cout << "\n";
	
	return expVal;
}

int main() {
	srand(time(0));
	
	int literals;
	cout << "Enter no. of literals: ";
	cin >> literals;
	
	int repeat;
	cout << "Repeat: ";
	cin >> repeat;
	
	while(repeat--) {
		vi literalValues = generateLiteralValues(literals);
		vii clauseSet = generateClauseSet(literals);

		int expVal = evaluteSatisfiability(literalValues, clauseSet);
		cout << (expVal ? "1" : "0") << "\n\n";
	}
	
	return 0;
}
