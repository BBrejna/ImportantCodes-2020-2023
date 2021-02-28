// Zadanie 'Pakowanie Plecaka' XVIII OI e2d1
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define pb push_back
#define st first
#define nd second

struct Treap{
    struct Node{
        Node* l=NULL;
        Node* r=NULL;
        ll val, rank, delta=0, size=1;
        Node(ll _val) : val(_val), rank(rand()) {}
        ~Node() {
            delete l;
            delete r;
        }
    };
    Node* root=NULL;
    vector<Node*> del;
    ~Treap() {
        for (auto i : del) delete i;
        delete root;
    }
    ll sz(Node* v) { return v==NULL?0:v->size; }
    void repair(Node* v) {
        if (v==NULL) return;
        v->size=sz(v->l)+sz(v->r)+1;
    }
    void push(Node* v) {
        if (v==NULL) return;
        if (v->delta>0) {
            v->val+=v->delta;
            if (v->l!=NULL) v->l->delta+=v->delta;
            if (v->r!=NULL) v->r->delta+=v->delta;
            v->delta=0;
        }
    }
    pair<Node*, Node*> split(Node* v, ll k) {
        push(v);
        if (v==NULL) return {NULL,NULL};
        if (v->val <= k) {
            auto p = split(v->r,k);
            v->r=p.st;
            repair(v);
            return {v,p.nd};
        } else {
            auto p = split(v->l,k);
            v->l=p.nd;
            repair(v);
            return {p.st,v};
        }
    }
    Node* merge(Node* l, Node* r) {
        push(l),push(r);
        if (l==NULL) return r;
        if (r==NULL) return l;
        if (l->rank > r->rank) {
            l->r = merge(l->r,r);
            repair(l);
            return l;
        } else {
            r->l = merge(l,r->l);
            repair(r);
            return r;
        }
    }
    void insert(ll k) {
        auto p = split(root, k);
        root = merge(new Node(k), p.nd);
        root = merge(p.st, root);
    }
    void erase(ll k) {
        auto p = split(root, k);
        auto l = split(p.st, k-1);
        root = merge(l.st,p.nd);
        del.pb(l.nd);
        l.nd=NULL;
    }
    void print(Node* v, vector<ll>& res) {
        if (v==NULL) return;
        push(v);
        print(v->l,res);
        res.pb(v->val);
        print(v->r,res);
    }
    void print() {
        vector<ll> v;
        print(root, v);
        for (size_t i = 0; i < v.size(); i++) cout << v[i] << " ";
        cout << "\n";
    }
    ll find_smaller(Node* v, ll val) {
        push(v);
        if (v==NULL) return -1;
        if (v->val >= val) return find_smaller(v->l,val);
        ll r = find_smaller(v->r,val);
        return r==-1?v->val:r;
    }
    ll find_smaller(ll val) { return find_smaller(root, val); }
    void add_val_to_greater_or_equal(ll beg, ll val) {
        auto p = split(root,beg-1);
        p.nd->delta+=val;
        merge(p.st,p.nd);
    }
	Node* find_kth(Node* v, ll k) {
        if (sz(v->l)+1 == k) return v;
        if (sz(v->l) >= k) return find_kth(v->l,k);
        return find_kth(v->r,k-(sz(v->l)+1));
    }
    ll find_kth(ll k) {
        if (k<1||k>sz(root)) return LLONG_MAX;
        return find_kth(root, k)->val; 
    }
    ll find_bound(Node* v, ll k, ll res=LLONG_MAX) {
        if (v==NULL) return LLONG_MAX;
        res = find_bound((v->val>k?v->l:v->r),k);
        if (v->val >= k) res=min(res,v->val);
        return res;
    }
    ll lower_bound(ll k) { return find_bound(root,k); }
    ll upper_bound(ll k) { return find_bound(root,k+1); }
    Node* find(Node*v, ll k) {
        if (v==NULL) return NULL;
        if (v->val==k) return v;
        auto akt = find((v->val>k?v->l:v->r),k);
        return akt;
    }
    Node* find(ll k) { return find(root,k); }
};

int n, a;
ll in[500005];

int32_t main() {
    Treap treap;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> in[i];
    treap.insert(0LL);
    for (int i = n-1; i >= 0; i--) {
        ll akt=treap.find_smaller(in[i]);
        treap.add_val_to_greater_or_equal(akt,in[i]);
        treap.insert(akt);
    } 
    treap.erase(0);
    treap.print();
}