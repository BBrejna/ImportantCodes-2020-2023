/// Sparse Table Range Minimum Query
#include <bits/stdc++.h>

using namespace std;

#define cint const int
#define MAXN int(1e5)
#define K 16 ///int(log2(MAXN))

int n, q, a, b;
int Log[MAXN+5];
int st[MAXN][K+1];
int tab[MAXN+5];

void prepare() {
    Log[1] = 0;
    for (int i = 2; i <= MAXN; i++)
        Log[i] = Log[i/2] + 1;
}

void preprocess() {
    for (int i = 0; i < n; i++)
        st[i][0] = tab[i];

    for (int j = 1; j <= K; j++)
        for (int i = 0; i + (1 << j) <= n; i++)
            st[i][j] = min(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
}

int ask(int l, int r) {
    int j = Log[r - l + 1];
    return min(st[l][j], st[r - (1 << j) + 1][j]);
}

int main() {
    cin.tie(NULL),cout.tie(NULL),ios::sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> tab[i];
    prepare();
    preprocess();
    cin >> q;
    while (q--) {
        cin >> a >> b;
        cout << ask(a,b) << "\n"; 
    }
}