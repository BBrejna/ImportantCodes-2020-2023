#include <bits/stdc++.h>

using namespace std;

struct FastOutput {
    FastOutput& operator <<(char c) {
        putchar(c);
        return *this;
    }
    FastOutput& operator <<(const char* s) {
        for (int i=0;s[i]!='\0';i++) putchar(s[i]);
        return *this;
    }
    FastOutput& operator <<(string s) {
        for (auto i : s) putchar(i);
        return *this;
    }
    FastOutput& operator <<(long long res) {
        if (res==0) {
            putchar('0');
            return *this;
        }
        long long tab[20], it=-1;
        if (res<0) putchar('-'),res=abs(res);
        while (res) tab[++it]=res%10LL,res/=10LL;
        for (;it>=0;it--) putchar(char(tab[it]+'0'));
        return *this;
    }
    FastOutput& operator <<(int res) {
        if (res==0) {
            putchar('0');
            return *this;
        }
        int tab[10], it=-1;
        if (res<0) putchar('-'),res=abs(res);
        while (res) tab[++it]=res%10,res/=10;
        for (;it>=0;it--) putchar(char(tab[it]+'0'));
        return *this;
    }
    FastOutput& operator <<(unsigned long long res) {
        if (res==0) {
            putchar('0');
            return *this;
        }
        long long tab[20], it=-1;
        while (res) tab[++it]=res%10LL,res/=10LL;
        for (;it>=0;it--) putchar(char(tab[it]+'0'));
        return *this;
    }
    FastOutput& operator <<(unsigned int res) {
        if (res==0) {
            putchar('0');
            return *this;
        }
        int tab[10], it=-1;
        while (res) tab[++it]=res%10,res/=10;
        for (;it>=0;it--) putchar(char(tab[it]+'0'));
        return *this;
    }
    FastOutput& operator <<(long unsigned int res) {
        if (res==0) {
            putchar('0');
            return *this;
        }
        long int tab[10], it=-1;
        while (res) tab[++it]=res%10,res/=10;
        for (;it>=0;it--) putchar(char(tab[it]+'0'));
        return *this;
    }
} fast_output;
#define cout fast_output

struct FastInput {
    char get_first() {
        char c=char(getchar());
        while (c<33) c=char(getchar());
        return c;
    }
    FastInput& operator >>(char &c) {
        c=get_first();
        return *this;
    }
    FastInput& operator >>(string &s) {
        s="";
        char c=get_first();
        while (c>32) s+=c,c=char(getchar());
        return *this;
    }
    FastInput& operator >>(long long &res) {
        char c=get_first();
        long long mn=1;
        if (c==45) mn=-1,c=char(getchar()); 
        res=0;
        while (c>32) res*=10,res+=c-'0',c=char(getchar());
        res*=mn;
        return *this;
    }
    FastInput& operator >>(int &res) {
        char c=get_first();
        int mn=1;
        if (c==45) mn=-1,c=char(getchar()); 
        res=0;
        while (c>32) res*=10,res+=c-'0',c=char(getchar());
        res*=mn;
        return *this;
    }
    FastInput& operator >>(unsigned long long &res) {
        char c=get_first();
        res=0;
        while (c>32) res*=10,res+=c-'0',c=char(getchar());
        return *this;
    }
    FastInput& operator >>(unsigned int &res) {
        char c=get_first();
        res=0;
        while (c>32) res*=10,res+=c-'0',c=char(getchar());
        return *this;
    }
} fast_input;
#define cin fast_input

int32_t main() {
    vector<int> n(5);
    cout << n.size() << "\n";
    return 0;
}
