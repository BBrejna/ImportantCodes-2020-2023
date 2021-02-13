/// SCC zadanie 'Ścieżki Rowerowe' XXV OI e2 d1
#include <bits/stdc++.h>

#define pb push_back

using namespace std;

const int MAXN = 5e4+5, MAXM = 1e5+5;

int n, m, a, b;
vector<int> lS[MAXN], lSrev[MAXN], lScc[MAXN], postorder, topsort, beg;
bool vis[MAXN];
int cc[MAXN], it, stw[MAXN], ans[MAXN], ccsize[MAXN], vis2[MAXN];

void dfs(int v) {
  vis[v]=1;
  for (auto u : lS[v]) if (!vis[u]) dfs(u);
  postorder.pb(v);
}

void dfs2(int v, int w) {
  vis[v]=1, cc[v]=w, ccsize[w]++;
  for (auto u : lSrev[v]) if (!vis[u]) dfs2(u,w);
}

void dfs3(int v) {
  vis[v]=1;
  for (auto u : lS[v]) 
    if (cc[v]==cc[u]&&!vis[u]) {
      dfs3(u);
    } else if (cc[v]!=cc[u]&&vis2[cc[u]]!=cc[v]) {
      lScc[cc[v]].pb(cc[u]), stw[cc[u]]++, vis2[cc[u]]=cc[v];
    }
}

void dfs4(int v) {
  topsort.pb(v);
  for (auto u : lScc[v]) dfs4(u);
}

int main() {
  cin.tie(NULL),cout.tie(NULL),ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    cin >> a >> b;
    lS[a].pb(b), lSrev[b].pb(a);
  }
  /// Liczenie SCC
  for (int i = 1; i <= n; i++) if (!vis[i]) dfs(i);
  fill(vis,vis+MAXN,0);
  for (int i = postorder.size()-1; i >= 0; i--) {
    int v=postorder[i];
    if (!vis[v]) dfs2(v,++it);
  }
  /// cc[v]=w której spójnej składowej, ccsize[nr spójnej składowej]=wielkość spójnej składowej
  /// Niżej rozwiązanie zadania 
  fill(vis,vis+MAXN,0);
  for (int i = 1; i <= n; i++) if (!vis[i]) dfs3(i);
  for (int i = 1; i <= it; i++) if (!stw[i]) beg.pb(i);
  for (auto i : beg) dfs4(i);
  for (int i = topsort.size()-1; i >= 0; i--) {
    int v=topsort[i];
    ans[v]=ccsize[v];
    for (auto u : lScc[v]) ans[v]+=ans[u];
  }
  for (int i =1 ; i <= n; i++) {
    cout << ans[cc[i]]-1 << "\n";
  }
}