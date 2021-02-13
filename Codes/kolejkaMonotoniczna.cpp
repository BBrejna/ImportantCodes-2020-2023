/// Minimum w okienku o długości k, push przyjmuje pare {wartość,pozycja}

#include <bits/stdc++.h>

using namespace std;
using ll=long long;
using pii=pair<int,int>;

#define cint const int

deque<pii> dq;
int k;

void push(pii New) {
    while (dq.size() && New.first < dq.front().first) dq.pop_front();
    while (dq.size() && New.second-k>=dq.back().second) dq.pop_back();
    dq.push_front(New);
}

int ask() {
    return dq.back().first;
}