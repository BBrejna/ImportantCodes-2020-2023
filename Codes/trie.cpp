/// Czyste trie
#include <bits/stdc++.h>

#define SUP cin.tie(NULL);cout.tie(NULL);ios_base::sync_with_stdio(0)

using namespace std;

int trie[100005][26];
int cnt=1;
int czyKoniec[100005];
string s;
int n;
string zapytanie;
int q;

void dodaj(string a) {
	int wezel = 1;
	for (int j = 0; j < a.size(); j++) 
	{	
		czyKoniec[wezel]++;
		if (trie[wezel][a[j]-'a'] == 0) {
			trie[wezel][a[j]-'a'] = ++cnt;
			wezel = cnt;
		} else {
			wezel = trie[wezel][a[j]-'a'];
		}
	}
}

int odpowiedz(string a) {
	int wezel = 1;
	for (int j = 0; j < a.size(); j++) {
		if (trie[wezel][a[j]-'a'] != 0) {
			wezel = trie[wezel][a[j]-'a'];
		} else {
			return 0;
		}
	}
	return czyKoniec[wezel];
}

int main() {
	SUP;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> s;
		dodaj(s);
	}
	cin >> q;
	for (int i = 0; i < q; i++) {
		cin >> zapytanie;
		cout << odpowiedz(zapytanie);
	}
	return 0;
}
