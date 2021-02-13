#include <bits/stdc++.h>
 
#define pb push_back
 
using namespace std;
 
struct edge{
    int dest, id;
};
int NA_KRAWEDZIACH=0;

/// NA KRAWĘDZIACH:
// int n, a, b, c;
// vector<edge> lS[10005];
// int head[10005];
// int parent[10005];
// int depth[10005];
// int Tree[1<<15];
// int pre[10005], it;
// int recalc[10005];
// int shift;

/// NA WIERZCHOŁKACH:
vector<edge> lS[100005];
int head[100005];
int parent[100005];
int depth[100005];
int pre[100005];
int Tree[1<<18];
int shift;
int n, a, b, it;
char c;
int recalc[100005];

void upd(int v, int val) {
    v+=shift;
    Tree[v]+=val; /// DODAWANIE ZAMIAST USTAWIANIA
    while (v>>=1) Tree[v]=max(Tree[v<<1],Tree[v<<1|1]);
}

int ask(int l, int r, int x=0, int y=shift-1, int v=1) {
    if (y < l || x > r) return 0;
    if (l <= x && y <= r) return Tree[v];
    int m = (x+y)/2;
    return max(ask(l,r,x,m,v<<1),ask(l,r,m+1,y,v<<1|1));
}

int dfs(int v) {
    if (!NA_KRAWEDZIACH) recalc[v]=v;
    int bestSize=0, mySize=1;
    for (auto& i : lS[v]) {
        if (i.dest!=parent[v]) {
            if (NA_KRAWEDZIACH) recalc[i.id]=i.dest;
            parent[i.dest]=v;
            depth[i.dest]=depth[v]+1;
            int aktSize=dfs(i.dest);
            if (aktSize>bestSize) {
                swap(lS[v][0],i),bestSize=aktSize;
            }
            mySize+=aktSize;
        }
    }
    return mySize;
}

void decomposition(int v, int h) {
    head[v]=h, pre[v]=it++;
    if (lS[v].size()==1 && v!=0) return;
    decomposition(lS[v][0].dest,h);
    for (auto i : lS[v]) {
        if (i.dest!=parent[v] && i.dest!=lS[v][0].dest) {
            decomposition(i.dest,i.dest);
        }
    }
}
 
int hld(int a, int b) {
    int res=0;
    for(;head[a]!=head[b];b=parent[head[b]]) {
        if (depth[head[a]]>depth[head[b]]) 
            swap(a,b);
        res=max(res,ask(pre[head[b]],pre[b]));
    }
    if (depth[a] > depth[b]) swap(a,b);
    res = max(res,ask(pre[a]+NA_KRAWEDZIACH,pre[b]));
    return res;
}

int lca(int a, int b) {
    for (;head[a]!=head[b];b=parent[head[b]])
        if (depth[head[a]]>depth[head[b]])
            swap(a,b);
    return depth[a]>depth[b]?b:a;
}

/// NA KRAWĘDZIACH:
// void solve() {
//     fill(Tree,Tree+2*shift,0);
//     it=0;
//     for (int i = 0; i <= n; i++) lS[i].clear();
//     cin >> n;
//     int x=1;
//     while ((1<<x)<=n)x++;
//     shift = (1<<x);
//     vector<int> ToUpdate;
//     for (int i = 0; i < n-1; i++) {
//         cin >> a >> b >> c;
//         a--,b--;
//         lS[a].pb({b,i}),lS[b].pb({a,i});
//         ToUpdate.pb(c);
//     }
//     dfs(0);
//     decomposition(0,0);
//     for (int i = 0; i < n-1; i++) {
//         upd(pre[recalc[i]],ToUpdate[i]);
//     }
//     string query;
//     while(1) {
//         cin >> query;
//         if (query=="DONE") break;
//         cin >> a >> b;
//         if (query=="QUERY") cout << hld(a-1,b-1) << "\n";
//         else {
//             upd(pre[recalc[a-1]],b);
//         }
//     }
//     cout << "\n";
// }
 
// int main(){
//     cin.tie(NULL),cout.tie(NULL),ios::sync_with_stdio(0);
//     int iloscBugowWKodzie=1;
//     cin >> iloscBugowWKodzie;
//     while (iloscBugowWKodzie--) solve();
// } 

/// NA WIERZCHOŁKACH:
int main() {
    cin.tie(NULL),cout.tie(NULL),ios::sync_with_stdio(0);
    cin >> n;
    int k=1;
    while ((1<<k)<=n)k++;
    shift=(1<<k);
    for (int i = 0; i < n-1; i++) {
        cin >> a >> b;
        a--,b--;
        lS[a].pb({b,i}),lS[b].pb({a,i}); 
    }
    dfs(0);
    decomposition(0,0);
    cin >> n;
    while (n--) {
        cin >> c >> a >> b;
        if (c=='I') upd(pre[recalc[a-1]],b);
        else cout << hld(a-1,b-1) << "\n";
    }
}