/// HASH SŁOWA (prepare) NA DRZEWIE(ask i upd) I NA LINII (makeHash, getHash)

#include <bits/stdc++.h>

using namespace std;
using ll=long long;

#define cint const int

#define dlg int(1e5)
ll BASE=31;
ll MOD=1e9+696969;
ll pot[dlg+5];
ll Hash[dlg+5];
ll T[1<<21], leafs[1<<21], shift=1<<20;

void upd(int u, char v) {
	u+=shift;
	T[u]=v-'a'+1;
	leafs[u]=1;
	for (int i=2; u/=2; i<<=1) leafs[u] = i,T[u]=(T[2*u]+T[2*u+1]*pot[leafs[2*u+1]])%MOD;
}

ll ask(int l, int r, int x=0, int y=shift-1, int u=1) {
	if (x > r || y < l) return 0;
	if (l <= x && y <= r) return T[u]*pot[x-l];
	int m = (x+y)/2;
	return (ask(l,r,x,m,2*u)+ask(l,r,m+1,y,2*u+1))%MOD;
}

void prepare() {
    ll akt=1;
    for (int i = 0; i <= dlg; i++) pot[i]=akt, akt=(akt*BASE)%MOD;
}

ll getHash(int l, int r) {
    return (Hash[l]-((Hash[r+1]*pot[r-l+1])%MOD+MOD)%MOD+MOD)%MOD;
}

void makeHash(string s) {
    for (int i = s.size()-1; i >= 0; i--) 
        Hash[i]=(Hash[i+1]*BASE+(s[i]-'a'+1))%MOD;
}