#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// bignum template by Bartosz Brejna based on https://gist.github.com/ar-pa/957297fb3f88996ead11 published in alpha version on https://github.com/olaf-ideas/templatka/blob/master/bb.cpp
const int base = 1000000000, baseDigits = 9;
struct bignum {
    vector<int> a;
    int sign;
    bignum() : sign(1) {}
	bignum(long long b) { *this = b; }
	bignum(const string &s) { read(s); }
    int size() {
        if (a.empty()) return 0;
        int ans = ((int)a.size()-1)*baseDigits;
        int ac = a.back();
        while (ac) ans++,ac/=10;
        return ans;
    }
    bool isZero() const { return a.empty() || (a.size() == 1 && !a[0]); }
	void operator=(const bignum &b) { sign = b.sign, a = b.a; }
    void operator=(long long b) {
        sign = 1;
        a.clear();
        if (b < 0) sign = -1, b = -b;
        for(;b > 0; b = b/base) a.push_back((int)(b%base));
    }
    bool operator<(const long long &b) const { return *this < bignum(b); }
    bool operator<(const bignum &b) const {
        if (sign != b.sign) return sign < b.sign;
        if (a.size() != b.a.size()) return a.size()*sign < b.a.size()*b.sign;
        for (int i = (int)a.size()-1; i >= 0; i--)
            if (a[i] != b.a[i])
                return a[i]*sign < b.a[i]*b.sign;
        return 0;
    }
    bool operator>(const bignum &b) const { return b < *this; }
    bool operator<=(const bignum &b) const { return !(b < *this); }
    bool operator>=(const bignum &b) const { return !(*this < b); }
    bool operator==(const bignum &b) const { return !(*this < b) && !(b < *this); }
    bool operator!=(const bignum &b) const { return *this < b || b < *this; }
    bignum operator/(const long long &v) { return *this/bignum(v); }
    bignum abs() const {
        bignum res = *this;
        res.sign *= res.sign;
        return res;
    }
    bignum operator+(const bignum &b) const {
        if (sign == b.sign) {
            bignum res = b;
            for (int i = 0, carry = 0; i < (int) max(a.size(),b.a.size()) || carry; i++) {
                if (i==(int)res.a.size()) res.a.push_back(0);
                res.a[i]+=carry+(i < (int) a.size() ? a[i] : 0);
                carry = res.a[i] >= base;
                if (carry) res.a[i] -= base;
            }
            return res;
        }
        return *this - (-b);
    }
    bignum operator-(const bignum &b) const {
        if (sign == b.sign) {
            if (abs() >= b.abs()) {
                bignum res = *this;
                for (int i = 0, carry = 0; i < (int)b.a.size() || carry; i++) {
                    res.a[i] -= carry+ (i < (int) b.a.size() ? b.a[i] : 0);
                    carry = res.a[i]<0;
                    if (carry) res.a[i]+=base;
                }
                res.trim();
                return res;
            }
            return -(b-*this);
        }
        return *this + (-b);
    }
    bignum operator-() const {
        bignum res = *this;
        res.sign = -sign;
        return res;
    }
    void operator+=(const bignum &v) { *this = *this + v; }
	void operator-=(const bignum &v) { *this = *this - v; }
	void operator*=(const bignum &v) { *this = *this * v; }
	void operator/=(const bignum &v) { *this = *this / v; }
    void operator+=(const long long &v) {
        bignum tmp; tmp.a.push_back((int)v);
        return *this += tmp;
    }
    void trim() {
        while (!a.empty() && !a.back()) a.pop_back();
        if (a.empty()) sign = 1;
    }
    static vector<int> convertBase(const vector<int> &a, int old_digits, int new_digits) {
		vector<long long> p(max(old_digits, new_digits) + 1);
		p[0] = 1;
		for (int i = 1; i < (int) p.size(); i++) p[i] = p[i - 1] * 10;
		vector<int> res;
		long long cur = 0;
		int cur_digits = 0;
		for (int i = 0; i < (int) a.size(); i++) {
			cur += a[i] * p[cur_digits];
			cur_digits += old_digits;
			while (cur_digits >= new_digits) {
				res.push_back(int(cur % p[new_digits]));
				cur /= p[new_digits];
				cur_digits -= new_digits;
			}
		}
		res.push_back((int) cur);
		while (!res.empty() && !res.back()) res.pop_back();
		return res;
	}
    static vector<long long> karatsubaMultiply(const vector<long long> &a, const vector<long long> &b) {
		int n = (int)a.size();
		vector<long long> res(n + n);
		if (n <= 32) {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					res[i + j] += a[i] * b[j];
			return res;
		}
		int k = n >> 1;
		vector<long long> a1(a.begin(), a.begin() + k);
		vector<long long> a2(a.begin() + k, a.end());
		vector<long long> b1(b.begin(), b.begin() + k);
		vector<long long> b2(b.begin() + k, b.end());
		vector<long long> a1b1 = karatsubaMultiply(a1, b1);
		vector<long long> a2b2 = karatsubaMultiply(a2, b2);
		for (int i = 0; i < k; i++) a2[i] += a1[i];
		for (int i = 0; i < k; i++) b2[i] += b1[i];
		vector<long long> r = karatsubaMultiply(a2, b2);
		for (int i = 0; i < (int) a1b1.size(); i++) r[i] -= a1b1[i];
		for (int i = 0; i < (int) a2b2.size(); i++) r[i] -= a2b2[i];
		for (int i = 0; i < (int) r.size(); i++) res[i + k] += r[i];
		for (int i = 0; i < (int) a1b1.size(); i++) res[i] += a1b1[i];
		for (int i = 0; i < (int) a2b2.size(); i++) res[i + n] += a2b2[i];
		return res;
	}
    bignum operator*(const bignum &v) const {
		int privBaseDigits=4, privBase=10000;
		vector<int> a6 = convertBase(this->a, baseDigits, privBaseDigits);
		vector<int> b6 = convertBase(v.a, baseDigits, privBaseDigits);
		vector<long long> a(a6.begin(), a6.end());
		vector<long long> b(b6.begin(), b6.end());
		while (a.size() < b.size()) a.push_back(0);
		while (b.size() < a.size()) b.push_back(0);
		while (a.size() & (a.size() - 1)) a.push_back(0), b.push_back(0);
		vector<long long> c = karatsubaMultiply(a, b);
		bignum res;
		res.sign = sign * v.sign;
		for (int i = 0, carry = 0; i < (int) c.size(); i++) {
			long long cur = c[i] + carry;
			res.a.push_back((int) (cur % privBase));
			carry = (int) (cur / privBase);
		}
		res.a = convertBase(res.a, privBaseDigits, baseDigits);
		res.trim();
		return res;
	}
    void operator*=(int v) {
		if (v < 0)
			sign = -sign, v = -v;
		for (int i = 0, carry = 0; i < (int) a.size() || carry; ++i) {
			if (i == (int) a.size())
				a.push_back(0);
			long long cur = a[i] * (long long) v + carry;
			carry = (int) (cur / base);
			a[i] = (int) (cur % base);
		}
		trim();
	}
	void operator*=(long long v) {
		if (v < 0)
			sign = -sign, v = -v;
		if(v > base){
			*this = *this * (v / base) * base + *this * (v % base);
			return;
		}
		for (int i = 0, carry = 0; i < (int) a.size() || carry; ++i) {
			if (i == (int) a.size())
				a.push_back(0);
			long long cur = a[i] * (long long) v + carry;
			carry = (int) (cur / base);
			a[i] = (int) (cur % base);
		}
		trim();
	}
	bignum operator*(long long v) const { return *this * bignum(v); }  
	void read(const string &s) {
		sign = 1;
		a.clear();
		int pos = 0;
		while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {
			if (s[pos] == '-')
				sign = -sign;
			pos++;
		}
		for (int i = (int)s.size() - 1; i >= pos; i -= baseDigits) {
			int x = 0;
			for (int j = max(pos, i - baseDigits + 1); j <= i; j++)
				x = x * 10 + s[j] - '0';
			a.push_back(x);
		}
		trim();
	}
	friend istream& operator>>(istream &stream, bignum &v) {
		string s;
		stream >> s;
		v.read(s);
		return stream;
	}
	friend ostream& operator<<(ostream &stream, const bignum &v) {
		if (v.sign == -1) stream << '-';
		stream << (v.a.empty() ? 0 : v.a.back());
		for (int i = (int) v.a.size() - 2; i >= 0; --i) stream << setw(baseDigits) << setfill('0') << v.a[i];
		return stream;
	}
	bignum gcd(const bignum &c, const bignum &b) const { return b.isZero() ? c : gcd(b,c%b); }
	bignum lcm(const bignum &c, const bignum &b) const { return c/gcd(c,b)*b; }
	bignum divmod(const bignum &a1, const bignum &b1) const {
		int norm = base / (b1.a.back() + 1);
		bignum a = a1.abs() * norm;
		bignum b = b1.abs() * norm;
		bignum q, r;
		q.a.resize(a.a.size());
		for (int i = (int)a.a.size() - 1; i >= 0; i--) {
			r *= base;
			r += a.a[i];
			int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
			int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
			int d = (int)(((long long) base * s1 + s2) / (long long)b.a.back());
			r -= b * d;
			while (r < 0)
				r += b, --d;
			q.a[i] = d;
		}
		q.sign = a1.sign * b1.sign;
		r.sign = a1.sign;
		q.trim();
		r.trim();
		return q;
	}
	bignum operator/(const bignum &v) const { return divmod(*this, v); }
	bignum operator%(const bignum &v) const { return *this-(*this/v)*v; }
	friend bignum pow(bignum &b, long long pot, long long MOD) {
		bignum r = 1;
		for (b=b%bignum(MOD); pot; pot>>=1, b = (b*b)%MOD)
			if (pot&1) r = (r*b)%bignum(MOD);
		return r;
	}
	friend bignum pow(bignum &b, long long pot) {
		bignum r = 1;
		for (; pot; pot >>= 1, b*=b)
			if (pot&1) r*=b;
		return r;
	}
};
bignum gcd(const bignum c, const bignum b) { return b.isZero() ? c : gcd(b,c%b); }
bignum lcm(const bignum &c, const bignum &b) { return c/gcd(c,b)*b; }
bignum abs(bignum b) { return b.sign *= b.sign, b; }

int main() {
	bignum a, b;
	cin >>a >> b;
	cout << a+b << " " << a-b << " " << a*b << " " << a/b << "\n";
	cout << abs(a) << " " << gcd(a,b) << " " << lcm(a,b) << " " << pow(a,10) << " " << pow(a,10,4) << "\n";
    return 0;
}