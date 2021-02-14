/// Centroid Decomposition - 'Ciel the Commander' codeforces

#include <bits/stdc++.h>

#define pb push_back

using namespace std; 

#define MAXN int(1e5)

int n, vis[MAXN+5],blocked[MAXN+5];
int ans[MAXN+5], a, b;
vector<int> lS[MAXN+5];
int stsize[MAXN+5];
int p[MAXN+5];
queue<int> q;

int dfs(int v, int subtreesize, int assignment) {
    vis[v]=1;
    int subtree=1, maxchild=0;
    for (auto u : lS[v]) {
        if (!vis[u] && !blocked[u]) {
            p[u]=v;
            int akt=dfs(u,subtreesize, assignment);
            if (akt==-1) return akt;
            subtree+=akt;
            maxchild=max(maxchild,akt);
            stsize[u]=akt;
        }
    }
    if (maxchild <= (subtreesize>>1) && subtreesize-subtree <= (subtreesize>>1)) {
        ans[v]=assignment;
        blocked[v]=1;
        stsize[p[v]]=subtreesize-subtree;
        q.push(v);
        return -1;
    }
    return subtree;
}

void decompose() {
    dfs(1,n,0);
    int prev=0;
    ans[prev]=-1;
    while (q.size()) {
        int akt=q.front();
        q.pop();
        if (ans[prev]!=ans[akt]) fill(vis,vis+n+1,0);
        prev=akt;
        for (auto u : lS[akt]) {
            if (!blocked[u] && !vis[u]) {
                dfs(u,stsize[u],ans[akt]+1);
            }
        }
    }
}

int32_t main() {
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        cin >> a >> b;
        lS[a].pb(b);
        lS[b].pb(a);
    }
    decompose();
    for (int i = 1; i <= n; i++) cout << char(ans[i]+'A') << " ";
    cout << "\n";
}
