/// Cykl i Ścieżka eulera w grafie skierowanym lub nieskierowany (zmienna DIRECTED)

#include <bits/stdc++.h>

using namespace std;
using ll=long long;

#define pb push_back
#define MAXN int(1e5)
#define MAXM int(2e5)
#define SUP cin.tie(0),cout.tie(0),ios::sync_with_stdio(0)

bool DIRECTED=0;
int n, m, a, b;
vector<pair<int,int>> lS[MAXN+5];
int ids[MAXN+5];
int stin[MAXN+5], stout[MAXN+5];
bool vis[MAXM+5];
vector<int> ans;

bool exist() {
    int iNp=0;
    if (DIRECTED) {
        for (int i = 1; i <= n; i++) if (stin[i]!=stout[i]) return 0;
        return 1;
    }
    for (int i = 1; i <= n; i++) iNp+=stin[i]&1;
    return (iNp==0);
}

void eulerCycle(int v) {
    for (;ids[v]<lS[v].size();ids[v]++){
        auto u=lS[v][ids[v]];
        if (!vis[u.second]) vis[u.second]=1,eulerCycle(u.first);
    }
    ans.pb(v);
}

int findbeg() {
    int iNp=0, id;
    if (DIRECTED) {
        bool was1, was2;
        was1=was2=0;
        for (int i = 1; i <= n; i++) {
            if (stin[i]-1==stout[i] && was1) return -1;
            if (stin[i]==stout[i]-1 && was2) return -1;
            if (stin[i]-1==stout[i]) was1=1;
            if (stin[i]==stout[i]-1) was2=1,id=i;
        }
        return id;
    }
    for (int i = 1; i <= n; i++) iNp+=stin[i]&1, id=stin[i]&1?i:id;
    return iNp==2?id:-1;
}

void eulerPath(int v) {
    for (;ids[v]<lS[v].size();ids[v]++){
        auto u=lS[v][ids[v]];
        if (!vis[u.second]) vis[u.second]=1,eulerPath(u.first);
    }
    ans.pb(v);
}

int main() {
    SUP;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a >> b;
        lS[a].pb({b,i}),stin[b]++,stout[a]++;
        if (!DIRECTED) lS[b].pb({a,i}),stin[a]++,stout[b]++;
    }
    /// Cycle
    {
        cout << "Cycle:\n";
        if (exist()) {
            eulerCycle(1);
            if (DIRECTED) reverse(ans.begin(),ans.end());
            cout << ans.size() << "\n";
            for (auto i : ans) cout << i << " ";
            cout << "\n";
        } else {
            cout << "-1\n";
        }
    }
    fill(ids+1,ids+n+1,0);
    fill(vis+1,vis+m+1,0);
    ans.clear();
    /// Path
    {
        cout << "PATH:\n";
        int beg=findbeg();
        if (beg!=-1) {
            eulerPath(beg);
            if (DIRECTED) reverse(ans.begin(),ans.end());
            cout << ans.size() << "\n";
            for (auto i : ans) cout << i << " ";
            cout << "\n";
        } else {
            cout << "-1\n";
        }
    }
}