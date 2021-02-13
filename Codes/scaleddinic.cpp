/// Skalowany algorytm Dinica - zadanie 'Konflikt' solve sparingi oraz flowy do matchingu zadanie 'BerSU Ball' codeforces
 
#include <bits/stdc++.h>
 
using namespace std;
using ll=long long;
 
#define pb push_back
#define MAXN int(2e2)
#define MAXM int(200*199/2)
 
struct edge{
    int v, u, flow, capasity;
};
 
vector<int> lS[MAXN+5];
vector<edge> edges;
int s, t;
vector<int> ids;
 
void addEdge(int v, int u, int capasity) {
    lS[v].pb(edges.size());
    edges.pb({v,u,0,capasity});
    lS[u].pb(edges.size());
    edges.pb({u,v,0,0});
}
 
vector<int> d;
queue<int> q;
bool bfs(int limit) {
    d=vector<int>(MAXN+5,-1);
    d[s]=0;
    q.push(s);
    while (q.size()) {
        int v=q.front(); q.pop();
        for (auto i : lS[v]) {
            auto e = edges[i];
            if (d[e.u]==-1 && e.capasity-e.flow>=limit) {
                d[e.u]=d[v]+1;
                q.push(e.u);
            }
        }
    }
    return d[t]!=-1;
}
 
bool dfs(int v, int limit) {
    if (v==t) return 1;
    for (;ids[v]<lS[v].size();ids[v]++) {
        auto it = lS[v][ids[v]];
        auto e = edges[it];
        if (d[v]+1==d[e.u] && e.capasity-e.flow >= limit && dfs(e.u,limit)) {
            edges[it^0].flow+=limit;
            edges[it^1].flow-=limit;
            return 1;
        }
    }
    return 0;
}
 
ll flow() {
    ll res=0;
    for (int lim = 1<<30; bfs(lim) || (lim>>=1);) {
        ids=vector<int>(MAXN+5,0);
        while (dfs(s,lim)) res+=lim;
    }
    return res;
}
 
/// BerSU Ball:
int tab[105],tab2[105],n,m;
int32_t main() {
    cin.tie(NULL),cout.tie(NULL),ios::sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> tab[i];
    cin >> m;
    for (int i = 1; i <= m; i++) cin >> tab2[i];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
        if (abs(tab[i]-tab2[j])<=1) addEdge(i,j+n,1);
    }
    for (int i = 1; i <= n; i++) addEdge(0,i,1);
    for (int j = 1; j <= m; j++) addEdge(j+n,n+m+1,1);
    s=0,t=n+m+1;
    cout << flow() << "\n";
}

/// Konflikt:
// ll n, m, a, b;
// int32_t main() {
//     cin.tie(NULL),cout.tie(NULL),ios::sync_with_stdio(0);
//     cin >> n >> m;
//     for (int i = 0; i < m; i++) {
//         cin >> a >> b;
//         addEdge(a,b,1);
//         addEdge(b,a,1);
//     }
//     s=1,t=2;
//     cout << m-flow() << "\n";
// }