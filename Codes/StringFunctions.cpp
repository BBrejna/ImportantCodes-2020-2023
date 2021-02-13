#include <bits/stdc++.h>
#define st first
#define nd second
#define ll long long
using namespace std;
using ull=unsigned long long;

void ManacherOdd(string s, vector<int>& res) {
    res.resize(s.size());
    for (int i = 0, l = 0, r = -1; i < s.size(); i++) {
        int k = (i > r) ? 1 : min(res[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < s.size() && s[i - k] == s[i + k]) k++;
        res[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
}

void ManacherEven(string s, vector<int>& res) {
    res.resize(s.size());
    for (int i = 0, l = 0, r = -1; i < s.size(); i++) {
        int k = (i > r) ? 0 : min(res[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < s.size() && s[i - k - 1] == s[i + k]) k++;
        res[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k ;
        }
    }
}

void Zfunction(string s, vector<int>& Z) {
    Z.resize(s.size());
    for (int i = 1, l = 0, r = 0; i < s.size(); ++i) {
        if (i <= r) Z[i] = min(r - i + 1, Z[i - l]);
        while (i + Z[i] < s.size() && s[Z[i]] == s[i + Z[i]]) Z[i]++;
        if (i + Z[i] - 1 > r) l = i, r = i + Z[i] - 1;
    }
}

int PrefixoSufix(string a, string b, vector<int>& pi) { ///długość sufixu b będąca słowem a, tablica pi jak w zwykłym KMP
    string s=a+'#'+b;
    pi.resize(s.size());
    pi[0] = 0;
    int i, d;
    for(i = 1, d = 0; i<s.size();i++){
        while(d>0&&s[i]!=s[d]) d=pi[d-1];
        if(s[i]==s[d]) d++;
        pi[i]=d;
    }
    return d;
}

int32_t main() {
    cin.tie(NULL),cout.tie(NULL),ios::sync_with_stdio(0);
    string s;
    cin >> s;
    vector<int> res;
    ManacherOdd(s,res);
    for (auto i : res) cout << i << " ";
    cout << "\n";
    ManacherEven(s,res);
    for (auto i : res) cout << i << " ";
    cout << "\n";
}