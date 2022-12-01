#include <bits/stdc++.h>
using namespace std;

const int d = 256;

void search(string pat, string txt, int q)
{
    int M = pat.size();
    int N = txt.size();
    int i, j;
    int p = 0;
    int t = 0;
    int h = long(pow(d, M - 1)) % q;

    for (i = 0; i < M; i++)
    {
        p = (p * d + pat[i]) % q;
        t = (t * d + txt[i]) % q;
    }

    for (i = 0; i <= N - M; i++)
    {
        if (p == t)
        {
            for (j = 0; j < M; j++)
            {
                if (pat[j] != txt[i + j])
                    break;
            }
            if (j == M)
                cout << "Pattern at " << i << "\n";
        }

        if (i < N - M)
        {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;
            if (t < 0)
                t += q;
        }
    }
}

int main()
{
    string a;
    cout << "Enter a string: ";
    string b;
    cout << "Enter a pattern: ";
    int q = INT_MAX;

    search(b, a, q);
    return 0;
}