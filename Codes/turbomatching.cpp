#include <bits/stdc++.h>

#define pb push_back
#define inf int(1e9)
#define MAXV int(5e2)

using namespace std;

int m, n, e, a, b;
vector<int> lS[MAXV+5];
bool vis[MAXV+5];
int matched[MAXV+5];

bool match(int v) {
    vis[v]=1;
    for (auto u : lS[v]) {
        if (matched[u]==-1 || (!vis[matched[u]] && match(matched[u]))) {
            matched[v]=u, matched[u]=v;
            return 1;
        }
    }
    return 0;
}

int turboMatching() {
    int ans=0, akt=1;
    fill(matched,matched+n+m,-1);
    while (akt) {
        akt=0;
        fill(vis,vis+n,0);
        for (int i = 0; i < n+m; i++) {
            if (matched[i]==-1&&!vis[i]&&match(i)) akt++;
        }
        ans+=akt;
    }
    return ans;
}

vector<int> findVertexCover() {
    queue<int> q;
    for (int i = 0; i < n+m; i++) if (matched[i]==-1) q.push(i);
    vector<int> d(n+m,inf);
    while (q.size()) {
        int v=q.front(); q.pop();
        for (auto i : lS[v]) {
            if (d[i]!=inf || i==matched[v]) continue;
            q.push(matched[i]), d[i]=d[v]+1, d[matched[i]]=d[i]+1;
        }
    }
    vector<int> res;
    for (int i = 0; i < n; i++)
        if ((d[i]!=inf && d[i]&1) || (matched[i]!=-1 && d[i]==inf && d[matched[i]]==inf))
            res.pb(i);
    return res;
}

int main() {
    cin.tie(0),cout.tie(0),ios::sync_with_stdio(0);
    cin >> n >> m >> e;
    while (e--) {
        cin >> a >> b;
        a--,b--;
        lS[a].pb(b),lS[b].pb(a);
    }
    cout << turboMatching() << "\n";
    auto res=findVertexCover();
    for (auto i : res) cout << i << " ";
    cout << "\n";
}