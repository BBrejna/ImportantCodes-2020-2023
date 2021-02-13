/// Zadanie 'BerSU Ball' codeforces.com
#include <bits/stdc++.h>

#define pb push_back

using namespace std;

int m, n, tab[105], tab2[105], cnt;
bool used[105],used2[105];
vector<int> lS[505];
vector<pair<int,int>>v;
char c;
bool vis[505];
int matched[505];

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

int main() {
    cin.tie(NULL),cout.tie(NULL),ios::sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> tab[i];
    cin >> m;
    for (int i = 0; i < m; i++) cin >> tab2[i];
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        if (abs(tab[i]-tab2[j])<=1) lS[i].pb(j+n),lS[j+n].pb(i);
    }
    cout << turboMatching() << "\n";
}