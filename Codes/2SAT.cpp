#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define infll ll(1e18)
#define inf int(1e9)
#define st first
#define nd second
#define MAXN int(1.5e5+5)
#define MAXV int(3e5+5)
#define pb push_back

vector<int> syf[MAXN];
map<pair<int,int>,int> m;
int n, k, it;
int in[MAXN];

struct SAT{
    vector<bool> val;
    vector<vector<int>> lS;
    vector<int> s;
    int n,c;
    SAT(){}
    SAT(int _n) : n(_n) {
        val = vector<bool>(2*n);
        lS = vector<vector<int>>(2*n);
        s = vector<int> (2*n);
    }

    void add_clause(int x, bool valx, int y, bool valy) {
        int v1=x*2+valx, v2=y*2+valy;
        lS[v1^1].pb(v2),lS[v2^1].pb(v1);
    }

    bool dfs(int v) {
        if (val[v^1]) return 0;
        if (val[v]) return 1;
        val[v]=1,s[c++]=v;
        for (auto u : lS[v]) if (!dfs(u)) return 0;
        return 1;
    }

    bool satisfy(){
        vector<int> ord;
        for(int i = 0; i < n; ++i) ord.push_back(i*2);
        random_shuffle(ord.begin(), ord.end());
        for(auto i : ord) if(!val[i] && !val[i+1]) {
            c=0;
            if(!dfs(i)) {
                while(c) val[s[--c]] = 0;
                if(!dfs(i+1)) return 0;
            }
        }
        return 1;
    }
};

void clear() {
    m.clear(); 
    for (int i = 0; i <= n; i++) syf[i].clear();
}

void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> in[i];
    SAT sat(MAXV);
    sat.add_clause(0,1,0,1);
    sat.add_clause(n-2,1,n-2,1);
    for (int i = 0; i < n-2; i++) sat.add_clause(i,1,i+1,1);
    for (int i = 0; i < n-1; i++) m[{in[i],in[i+1]}]=i;
    for (int i = 0; i < n-1; i++) syf[m[{in[i],in[i+1]}]].pb(i);
    it=n-1;
    for (auto walek : m) {
        bool beg=1;
        for (auto id : syf[walek.second]) {
            sat.add_clause(id,0,it,1);
            if (!beg) {
                sat.add_clause(it-1,0,it,1);
                sat.add_clause(it-1,0,id,0);
            }
            beg=0,it++;
        }
    }
    cout << (sat.satisfy()?"TAK":"NIE") << "\n";
    clear();
}

int32_t main() {
    cin.tie(NULL),cout.tie(NULL),ios::sync_with_stdio(0);
    int t=1;
    cin >> t;
    while (t--) solve();
}