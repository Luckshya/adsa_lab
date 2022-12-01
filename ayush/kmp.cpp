#include <iostream>
#include <vector>
using namespace std;


vector<int> computeLPS(string x){
    int n = x.length();
    vector<int> lps(n, 0);
    int len = 0;
    int i = 1;
    while (i < n){
        if (x[i] == x[len]){
            len++;
            lps[i] = len;
            i++;
        }
        else{
            if (len == 0){
                lps[i] = 0;
                i++;
            }
            else{
                len = lps[len - 1];
            }
        }
    }
    return lps;
}

void kmp(string txt, string pat){
    int n = txt.length();
    int m = pat.length();

    cout << pat << " is found at : ";

    if (m > n)
        return;

    vector<int> lps = computeLPS(pat);
    int i = 0, j = 0;

    while ((n - i) >= (m - j)){
        if (pat[j] == txt[i]){
            i++;
            j++;
            if (j == m){
                cout << i - m << " ";
                j = lps[j - 1];
            }
        }
        else{
            if (j == 0)
                i++;

            else
                j = lps[j - 1];
        }
    }
}
int main(){
    string txt = "";
    string pat = "";

    cout << "Enter text : ";
    cin >> txt;

    cout << "Enter pattern : ";
    cin >> pat;

    kmp(txt, pat);

    return 0;
}
