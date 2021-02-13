/// UPD W PKT ZAPYTANIE NA PRZEDZIALE INDEXOWANE OD 1

#include <bits/stdc++.h>

using namespace std;
using ll=long long;

#define cint const int

ll T[1000005];
int n;

int magic(int x) {return x & -x;}

ll ask(int l, int r){
    l--;
    ll suma1 = 0;
    ll suma2 = 0;
    for(; r > 0; r -= magic(r)) suma1 += T[r];
    for(; l > 0; l -= magic(l)) suma2 += T[l];
    return (suma1 - suma2);
}

void upd(int pos, ll v){
    for(; pos <= n; pos += magic(pos)) T[pos] += v;
}