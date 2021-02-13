#include <bits/stdc++.h>
#define st first
#define nd second
#define ll long long
using namespace std;
using ull=unsigned long long;

vector<int> primes(int n){
  vector<bool> s(n + 1);
  for(ll i = 2; i * i <= n; i++)
    if(!s[i])
      for(ll j = i * i; j <= n; j += i)
        s[j] = true;
  vector<int> primes;
  for(int i = 2; i <= n; i++)
    if(!s[i])  primes.push_back(i);
  return primes;
}

ull modmul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}

ll pot(ll a, ll b){
  ll r = 1;
  for(; b; b >>= 1, a *= a)
    if(b & 1) r *= a;
  return r;
}

ull pot(ull a, ull b, ull mod){
  ull r = 1;
  for(; b; b >>= 1, a = modmul(a,a,mod))
    if(b & 1) r = modmul(r,a,mod);
  return r; 
}

pair<ll,ll> ext_gcd(ull a, ull b){
    if(b == 0)  return {1LL, 0LL};
    auto p = ext_gcd(b, a%b);
    return {p.second, p.first-(a/b)*p.second};
}

ull inv_gcd(ull a, ull m){
    auto p = ext_gcd(a,m);
    if(p.first < 0) p.first += m;
    return p.first;
}

ll inv_fastpow(ll x, ll mod) {
  return pot(x,mod-2,mod);
}

string discreteLogarithm(ll a, ll b, ll p, string ansF="") {
	if(__gcd(b,p) != 1 && b != 0)
		ansF = "NIE";
    else if (a%p == 0)
        if(b%p == 0)
			ansF = '1';
        else if(b%p == 1)
			ansF = '0';
        else            
			ansF = "NIE";
    else {
        unordered_map<int,int> values;
        ll n = (int)sqrt(p+.0)+1, newA = pot(a,n,p), ans = LLONG_MAX;
        for(int privP = 1, akt = newA; privP <= n; privP++) {
            if(!values.count(newA))    
                values[newA] = privP;
            newA=(akt*newA)%p;
        }
        for(int q = 0; q < n; q++) {
            ll akt = (pot(a,q,p)*b)%p;
            if(values.count(akt) > 0)    
                ans = min(ans, values[akt]*n-q);
        }
        if(pot(a,ans,p) != b%p || ans == LLONG_MAX) 
            ansF = "NIE";
		else 
            ansF = to_string(ans);
    }
    return ansF;
}

///Fast Factorization https://github.com/kth-competitive-programming/kactl
bool MillerRabinIsPrime(ull n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
        s = __builtin_ctzll(n-1), d = n >> s;
    for (ull a : A) {   
        ull p = pot(a%n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--)
            p = modmul(p, p, n);
        if (p != n-1 && i != s) return 0;
    }
    return 1;
}
ull pollard(ull n) {
	auto f = [n](ull x) { return modmul(x, x, n) + 1; };
	ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	while (t++ % 40 || __gcd(prd, n) == 1) {
		if (x == y) x = ++i, y = f(x);
		if ((q = modmul(prd, max(x,y) - min(x,y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return __gcd(prd, n);
}

vector<ull> factor(ull n) {
	if (n == 1) return {};
	if (MillerRabinIsPrime(n)) return {n};
	ull x = pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), r.begin(),r.end());
	return l;
}

int32_t main() {
    cin.tie(NULL),cout.tie(NULL),ios::sync_with_stdio(0);
    ull q, n, p;
    cin >> q;
    while (q--) {
      cin >> n >> p;
      cout << inv_gcd(n,p) << "\n";
    }
} 