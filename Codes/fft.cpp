#include <bits/stdc++.h>

using namespace std;
using ld=long double;

#define infll ll(1e18)
#define inf int(1e9)
#define st first
#define nd second
#define MAXN int(5e4)
#define MAXV int(6e5+5)
#define pb push_back
#define K 16

struct C {
    ld r, i;
    C(ld _r = 0, ld _i = 0) : r(_r), i(_i) { }
    const inline C operator+ (const C &c) const { return C{r + c.r, i + c.i}; }
    const inline C operator- (const C &c) const { return C{r - c.r, i - c.i}; }
    const inline C operator* (const C &c) const { return C{r * c.r - i * c.i, r * c.i + i * c.r}; }
    const inline C operator/ (const ld &v) const { return C{r / v, i / v}; }
};
constexpr ld pi = acosl(-1);

void fft(vector<C> &a, bool inv=0) {
    int n=int(a.size());
    for (int i = 1, j=0; i<n; i++) {
        int bit=n/2;
        for(;j&bit;bit>>=1) j^=bit;
        j^=bit;
        if (j>i) swap(a[i],a[j]);
    }
    for (int dlg=2; dlg<=n; dlg*=2) {
        ld pot=(inv ? -2 : 2)*pi/dlg;
        C step(cos(pot),sin(pot));
        for (int i = 0; i < n; i+=dlg) {
            C akt(1);
            for (int j = 0; j < dlg/2; j++) {
                C l=a[i+j];
                C r=a[i+j+dlg/2]*akt;
                a[i+j]=(l+r);
                a[i+j+dlg/2]=(l-r);
                akt=akt*step;
            }
        }
    }
    if (inv) for (auto &i : a) i=i/ld(n);
}


int32_t main() {
    cin.tie(0),cout.tie(0),ios::sync_with_stdio(0);
    string a, b;
    cin >> a >> b;
    int n=int(max(a.size(),b.size()));
    int k=1;
    while ((1<<k)<n)k++;
    int sz=1<<(k+1);
    vector<C> liczba1(sz), liczba2(sz);
    for (int i = 0; i < int(a.size()); i++) liczba1[i].r=a[a.size()-1-i]-'0';
    for (int i = 0; i < int(b.size()); i++) liczba2[i].r=b[b.size()-1-i]-'0';
    fft(liczba1),fft(liczba2);
    for (int i = 0; i < sz; i++) liczba1[i]=liczba1[i]*liczba2[i];
    fft(liczba1,1);
    vector<int> ans;
    int carry=0;
    for (int i = 0; i < sz; i++) {
        int akt=int(liczba1[i].r+0.5)+carry;
        ans.pb(akt%10);
        carry=akt/10;
    }
    if (carry) ans.pb(carry);
    while (ans.size()>1&&ans.back()==0) ans.pop_back();
    for (int i = int(ans.size())-1; i>=0; i--) cout << ans[i];
    cout << "\n";
}