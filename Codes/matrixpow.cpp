/// Potęgowanie macierzy zadanie 'Ciąg Fibonacciego' solve.edu.pl
#include <iostream>
#include <vector>

using namespace std;

#define mod (long long) (1e9+7)
#define SUP cin.tie(NULL);cout.tie(NULL);ios_base::sync_with_stdio(0)
#define matrix vector<vector<long long>>



matrix pomnoz(matrix A, matrix B) {
    matrix C(A.size(), vector<long long> (A.size(), 0));
    int wielkosc = A.size();
    for (int i = 0; i < wielkosc; i++) {
        for (int j = 0; j < wielkosc; j++) {
            for (int k = 0; k < wielkosc; k++) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
            }
        }
    }
    return C;
}

matrix pow(matrix A, long long wykladnik) {
    matrix wynik(A.size(), vector<long long> (A.size(), 0));
    for (int i = 0; i < A.size(); i++) {
        wynik[i][i] = 1;
    }
    while (wykladnik > 0) {
        if (wykladnik%2 == 1) {
            wynik = pomnoz(wynik, A);
            wykladnik--;
        } else {
            A = pomnoz(A,A);
            wykladnik /= 2;
        }
    }
    return wynik;
}


int main() {
    SUP;
    matrix wejscie;
    int n;
    cin >> n;
    wejscie.resize(2);
    for (int i = 0; i < 2; i++) {
        wejscie[i].resize(2);
    }
    wejscie[0][1] = 1;
    wejscie[1][0] = 1;
    wejscie[0][0] = 1;
    wejscie[1][1] = 0;
    wejscie = pow(wejscie, n+2);
    cout << wejscie[0][0]-1;
    return 0;
}