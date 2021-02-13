/// Zadanie 'Ile różnych? Hard' solve.edu.pl
#include <bits/stdc++.h>

#define pii pair<int,int>
#define MAX 50005
#define MAXZ 100005

using namespace std;

const int D = 285;
pii zapytania[MAXZ];
int kolejnosc[MAXZ];
int n, q;
int wejscie[MAX];
unordered_map<int,int> M;
int l, r;
int wynik[MAXZ];

bool cmp(int a, int b) {
    int a1 = zapytania[a].first/D;
    int b1 = zapytania[b].first/D;
    if (a1 < b1) return 1;
    if (a1 == b1) return zapytania[a].second > zapytania[b].second;
    return 0;
}

void wyczysc() {
    M.clear();
}

inline void scanIO(int *a) {
    register char tmp = 0;
    while (tmp < 33) tmp=getchar();
    (*a) = 0;
    while(tmp>32) {
        (*a)=(*a)*10+tmp-48;
        tmp=getchar();
    }
}

inline void printIO(int a) {
    if (a == 0) {
        putchar('0');
        return;
    }
    char tab[10];
    int tmp = 0;
    while (a > 0) {
        tab[tmp++] = (a%10)+48;
        a /= 10;
    }
    while (tmp--) {
        putchar(tab[tmp]);
    }
    putchar('\n');
}


int main()
{
    {
        scanIO(&n);
        for (int i = 1; i <= n; i++) {
            scanIO(&wejscie[i]);
        }
        scanIO(&q);
        for (int i = 0; i < q; i++) {
            scanIO(&zapytania[i].first);
            scanIO(&zapytania[i].second);
            kolejnosc[i] = i;
        }

    }
    {
        sort(kolejnosc, kolejnosc+q, cmp);
        int wD = 0;
        for (int i = 0; i < q; i++) {
            int a = zapytania[kolejnosc[i]].first;
            int b = zapytania[kolejnosc[i]].second;
            if (a >= wD*D) {
                wD++;
                if (wD != 0) wyczysc();
                l = a;
                r = b;
                for (int j = a; j <= b; j++) {
                    M[wejscie[j]]++;
                }
                wynik[kolejnosc[i]] = M.size();
                continue;
            }
            while (l > a) {
                l--;
                M[wejscie[l]]++;
            }
            while (r < b) {
                r++;
                M[wejscie[r]]++;
            }
            while (l < a) {
                M[wejscie[l]]--;
                if (M[wejscie[l]] == 0) M.erase(wejscie[l]);
                l++;
            }
            while (r > b) {
                M[wejscie[r]]--;
                if (M[wejscie[r]] == 0) M.erase(wejscie[r]);
                r--;
            }
            wynik[kolejnosc[i]] = M.size();
        }
        for (int i = 0; i < q; i++) {
            printIO(wynik[i]);
        }
    }
    return 0;
}
