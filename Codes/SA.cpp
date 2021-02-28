#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define pb push_back;

vector<int> sa,old,akt;
int n, len=1;
string s;

bool cmp(int a, int b) {
    if (old[a]!=old[b]) return old[a]<old[b];
    if (a+len>=n || b+len >=n) return a>b;
    return old[a+len]<old[b+len];
}

void SA() {
    sa=old=akt=vector<int>(n);
    for (int i = 0; i < n; i++) sa[i]=i,old[i]=s[i]-'a';
    do {
        sort(sa.begin(),sa.end(),cmp);
        akt[sa[0]]=0;
        for (int i = 1; i < n; i++) akt[sa[i]]=akt[sa[i-1]]+cmp(sa[i-1],sa[i]);
        old.swap(akt);
        len<<=1;
    } while (old[sa[n-1]]<n-1);
}

ll BASE=31;
ll pot[200005];
ll Hash[200005];
ll here=1;

ll get_hash(int l, int r) { return Hash[l]-Hash[r+1]*pot[r-l+1]; }

ll lcp(int a, int b) {
    if (s[a]!=s[b]) return 0;
    int l=0, r=n-max(a,b);
    while (r-l>1) {
        int m=(l+r)/2;
        if (get_hash(a,a+m)==get_hash(b,b+m)) l=m;
        else r=m;
    }
    return l+1;
}

int32_t main() {
    cin.tie(NULL),cout.tie(NULL),ios::sync_with_stdio(0);
    cin >> s;
    n=int(s.size());
    SA();
    for (int i = 0; i < n; i++) pot[i]=here,here*=BASE;
    for (int i = n-1; i >= 0; i--) Hash[i]=Hash[i+1]*BASE+s[i]-'a'+1;
    ll res=n-sa[0];
    for (int i = 1; i < n; i++) res+=n-sa[i]-lcp(sa[i-1],sa[i]);
    cout << res << "\n";
}