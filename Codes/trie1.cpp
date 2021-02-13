/// Zadanie 'Słownik T9' solve.edu.pl
#include <bits/stdc++.h>

#define SUP cin.tie(NULL);cout.tie(NULL);ios_base::sync_with_stdio(0)
#define MAX (int)1e6+5

using namespace std;

int cnt = 1;
int trie[MAX][10];
int czyKoniec[MAX];
string slowa[250005];
int it;
int n, q;
string input;
int konce[MAX];

int jakaGalaz(char literka) {
    literka -= 'a';
    if (literka < 3) return 2;
    if (literka < 6) return 3;
    if (literka < 9) return 4;
    if (literka < 12) return 5;
    if (literka < 15) return 6;
    if (literka < 19) return 7;
    if (literka < 22) return 8;
    return 9;
}

void dodaj(string s) {
    int wezel = 1;
    konce[wezel] = it;
    czyKoniec[wezel]++;
    for (int i = 0; i < s.size(); i++) {
        int cyfra = jakaGalaz(s[i]);
        if (trie[wezel][cyfra] == 0) {
            wezel = trie[wezel][cyfra] = ++cnt;
            konce[wezel] = it;
            czyKoniec[wezel]++;
        } else {
            wezel = trie[wezel][cyfra];
            konce[wezel] = it;
            czyKoniec[wezel]++;
        }
    }
}

void pytanie(string s) {
    int wezel = 1;
    for (int i = 0; i < s.size(); i++) {
        int cyfra = s[i]-'1'+1;
        if (cyfra != 1) {
            if (trie[wezel][cyfra] == 0) {
                cout << "NIE\n";
                return;
            } else {
                wezel = trie[wezel][cyfra];
            }
        }
    }
    if (czyKoniec[wezel] == 1) {
        cout << slowa[konce[wezel]] << "\n";
    } else {
        cout << czyKoniec[wezel] << "\n";
    }
}

int main() {
    SUP;
    cin >> n >> q;
    for (; it < n; it++) {
        cin >> input;
        slowa[it] = input;
        dodaj(input);
    }
    for (int i = 0; i < q; i++) {
        cin >> input;
        pytanie(input);
    }
    return 0;
}
