/// PRZEDZIAŁ PRZEDZIAŁ DODAJ NA PRZEDZIALE SUMA NA PRZEDZIALE

#include <bits/stdc++.h>

using namespace std;
using ll=long long;

#define cint const int

ll T[1<<21], p[1<<21], shift=1<<20;

void lazy(cint& u, const ll& leafs) {
    T[u]+=p[u]*leafs;
    if (u>shift) {
        p[u<<1]+=p[u]>>1;
        p[u<<1|1]+=p[u]>>1;
    }
    p[u]=0;
}

void upd(cint& l, cint& r, const ll& val, cint& x=0, cint& y=shift-1, cint& u=1) {
    lazy(u,y-x+1);
    if (y < l || x > r) return;
    if (l <= x && y <= r) {
        p[u]+=val;
        lazy(u,y-x+1);
        return;
    }
    int m=(x+y)>>1;
    upd(l,r,val,x,m,u<<1),upd(l,r,val,m+1,y,u<<1|1);
    T[u]=T[u<<1]+T[u<<1|1];
}

ll ask(cint& l, cint& r, cint& x=0, cint& y=shift-1, cint& u=1) {
    lazy(u,y-x+1);
    if (y < l || x > r) return 0;
    if (l <= x && y <= r) return T[u];
    int m=(x+y)>>1;
    return ask(l,r,x,m,u<<1)+ask(l,r,m+1,y,u<<1|1);
}