#include <bits/stdc++.h>

using namespace std;

struct C {
	double r, i;
	
	C operator* (const C &other) const {
		return C{r * other.r - i * other.i,
				 r * other.i + i * other.r};
	}
	C operator- (const C &other) const {
		return C{r - other.r, i - other.i};
	}
	void operator+= (const C &other) {
		r += other.r, i += other.i;
	}
	void operator/= (const int &n) {
		r /= n; i /= n;
	}
};

constexpr double PI = acos(-1);

constexpr int L = 17; /// Druga najmniejsza potęga dwójki większa niż max długość

int rev[1 << L]; /// max n
void fft(C a[], int n, bool invert) {
	for(int i = 0; i < n; i++)
		if(i < rev[i])	swap(a[i], a[rev[i]]);
	
	static C wlen_pw[1 << L]; /// max n
	for(int len = 2; len <= n; len <<= 1) {
		double ang = 2 * PI / len * (invert ? -1 : +1);
		int len2 = len >> 1;
		
		C wlen{cos(ang), sin(ang)};
		wlen_pw[0] = C{1, 0};
		for(int i = 1; i < len2; i++)
			wlen_pw[i] = wlen_pw[i - 1] * wlen;
		
		for(int i = 0; i < n; i += len) {
			C t, *pu = a + i, *pv = a + i + len2, *pu_end = a + i + len2, *pw = wlen_pw;
			for(; pu != pu_end; pu++, pv++, pw++) {
				t = *pv * *pw;
				*pv = *pu - t;
				*pu += t;
			}
		}
	}
	
	if(invert)
		for(int i = 0; i < n; i++)
			a[i] /= n;
}

void fft_init(int n) {
	const int log_n = __lg(n);
	for(int i = 0; i < n; i++) {
		rev[i] = 0;
		for(int j = 0; j < log_n; j++)
			if(i & (1 << j))
				rev[i] |= 1 << (log_n - 1 - j);
	}
}

void mult(vector<int>& a, vector<int>&b, vector<int>& res) {
    int n=1;
    while (n<max(a.size(),b.size())) n<<=1;
    n<<=1;
    fft_init(n);

    static C fa[1<<L],fb[1<<L];
    for (int i = 0; i < a.size(); i++) fa[i]={a[i],0};
    for (int i = 0; i < b.size(); i++) fb[i]={b[i],0};
    
    fft(fa,n,0),fft(fb,n,0);
    for (int i = 0; i < n; i++) {
        fa[i]=fa[i]*fb[i];
    }
    fft(fa,n,1);
    res.resize(n);
    for (int i = 0; i < n; i++) {
        res[i]=int(fa[i].r+0.5);
    }
}

int main() {
    string a, b;
    cin >> a >> b;
    vector<int> v1,v2,res;
    for (int i = a.size()-1; i>=0; i--) v1.push_back(a[i]-'0');
    for (int i = b.size()-1; i>=0; i--) v2.push_back(b[i]-'0');

    mult(v1,v2,res);
    int carry=0;
    for (int i = 0; i < res.size()-1; i++) {
        res[i]+=carry;
        carry=res[i]/10;
        res[i]%=10;
    }
    while (res.size()>1 && res.back()==0) res.pop_back();
    reverse(res.begin(),res.end());
    for (auto i : res) cout << i;
    cout << "\n";
}