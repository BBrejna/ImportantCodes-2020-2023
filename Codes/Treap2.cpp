// Zadanie 'Odwracane sortowanie' solve.edu.pl
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define pb push_back
#define st first
#define nd second

struct Treap{
    struct node {
        node* l=NULL;
        node* r=NULL;
        node* p=NULL;
        ll key, val, rank, size=1;
        pair<ll,node*> min;
        bool rev=0;
        node(ll _key=0, ll _val=0) : key(_key), val(_val), rank(rand()), min(_val,this) {}
        ~node(){
            delete l;
            delete r;
        }
    };
    vector<node*> del;
    ll eps=1;
    node* root=NULL;
    ~Treap() {
        for (auto i : del) delete i;
        delete root;
    }
    ll sz(node* v) { return v==NULL ? 0LL : v->size; }
    void repair(node* v) { 
        if (v==NULL) return;
        v->size = sz(v->l)+sz(v->r)+1, v->min={v->val,v}; 
        if (v->p != NULL && v->p->l != v && v->p->r != v) v->p=NULL;
        if (v->l!=NULL) v->l->p=v, v->min=min(v->min,v->l->min); 
        if (v->r!=NULL) v->r->p=v, v->min=min(v->min,v->r->min);
    }
    void push(node* v) {
        if (v==NULL) return;
        if (v->rev) {
            swap(v->l,v->r);
            if (v->l!=NULL) v->l->rev^=1;
            if (v->r!=NULL) v->r->rev^=1;
        }
        v->rev=0;
    }

    pair<node*,node*> split(node* v, ll k) {
        push(v);
        if (v==NULL) return {NULL,NULL};
        if (sz(v->l) < k) {
            auto akt=split(v->r,k-(sz(v->l)+1));
            v->r=akt.st;
            repair(v);
            return {v,akt.nd};
        } else {
            auto akt=split(v->l,k);
            v->l=akt.nd;
            repair(v);
            return {akt.st,v};
        }
    }
    node* merge(node* l, node* r) {
        push(l),push(r);
        if (l==NULL) return r;
        if (r==NULL) return l;
        if (l->rank > r->rank) {
            l->r=merge(l->r,r);
            repair(l);
            return l;
        } else {
            r->l=merge(l,r->l);
            repair(r);
            return r;
        }
    }
    void insert(ll pos, ll k) {
        auto p=split(root,pos);
        root=merge(new node(pos,k),p.nd);
        root=merge(p.st,root);
    }
    void erase(ll k) {
        auto p=split(root,k);
        root=p.nd;
        del.pb(p.st);
        p.st=NULL;
    }
    void print(node* v, vector<pair<ll,ll>>& res) {
        if (v==NULL) return;
        print(v->l,res);
        res.pb({v->key,v->min.st});
        print(v->r,res);
    }
    void print() {
        vector<pair<ll,ll>> res;
        print(root,res);
        cout << "PRINTING:\n";
        for (auto i : res) cout << i.first << "->" << i.second << "\n";
    }
    void repair_path(node* v) {
        if (v==NULL) return;
        repair(v);
        repair_path(v->p);
        push(v);
    }
    ll get_index(node* v) {
        push(v);
        if (v->p==NULL) return sz(v->l);
        if (v->p->r == v) return get_index(v->p)+sz(v->l)+1;
        else return get_index(v->p)-sz(v->r)-1;
    }
    void reverse_range(ll length) {
        auto p=split(root,length);
        p.st->rev^=1;
        root=merge(p.st,p.nd);
    }
    ll handle(ll res=0) {
        node* mini=root->min.nd;
        repair_path(mini);
        res=get_index(mini)+1;
        reverse_range(res);
        erase(1);
        return res;
    }
};


int32_t main() {
    Treap treap;
    int n, a;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a;
        treap.insert(i,a);
    }
    for (int i = 0; i < n; i++) cout << treap.handle()+i << " ";
    cout << "\n";
}
