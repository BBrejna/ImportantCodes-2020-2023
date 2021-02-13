/// Random test generator taken from https://github.com/Kacperfis/OI/blob/master/testing/generatorka.cpp

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define size(x) (int)x.size()

long long int rand(long long int a, long long int b){
	return a + rand() % (b - a + 1);
}

struct generatorka{
	//NUMBERS
	~generatorka() { cout << "\n"; }
	void number_gen(long long n, long long maxliczba) { ///ile liczb, maxliczba
		cout << n << "\n";
		set<long long int> used;
		for(long long int i = 0; i < n; i++){
			long long int x;
			do{
				x = rand(1, maxliczba); //zakres liczby
			}while(used.count(x));
			cout << x << " ";
			used.insert(x);
		}
	}
	//PERMUTATIONS
	void perm_gen(long long n){ /// długość permutacji
		vector<long long int> perm;
		for(long long int i = 1; i <= n; i++) perm.pb(i); //permutacja liczb od 1 do n
		random_shuffle(perm.begin(), perm.end());
		cout << n << "\n";
		for(auto it : perm) cout << it << " ";
	}
	///STRINGS
	void string_gen(long long n, const long long len){ /// ile stringów, długość stringa
		while(n--){
			string tmp_s;
			static const char alphanum[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz"; //alfabet

			tmp_s.reserve(len);
			for (long long int i = 0; i < len; ++i) 
				tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
			
			cout << tmp_s << "\n";
		}
	}
	//MATRIX
	void matrix_gen(long long n, long long m, long long maxliczba){ //matrix [n*m]
		cout << n << " " << m << "\n";
		for(long long int i = 1; i <= n; i++){
			for(long long int j = 1; j <= m; j++){
				cout << rand(1, maxliczba) << " "; //zakres liczb
			}
			cout << "\n";
		}
	}
	//TREES
	void random_tree(long long n){
		cout << n << "\n";
		vector<pair<long long int, long long int> > edges;
		for(long long int i = 2; i <= n; i++){
			edges.emplace_back(rand(1, i-1), i);
		}
		vector<long long int> perm(n+1);
		for(long long int i = 1; i <= n; i++){
			perm[i] = i;
		}
		random_shuffle(perm.begin()+1, perm.end());
		random_shuffle(edges.begin(), edges.end());
		for(auto it : edges){
			if(rand() % 2) swap(it.first, it.second);
			cout << it.first << " " << it.second << "\n";
		}
	}
	void star_tree(long long n){ /// ilość wierzchołków
		cout << n << "\n";
		for(long long int i = 2; i <= n; i++){
			cout << 1 << " " << i << "\n";
		}
	}
	void path_tree(long long n){ /// ilość wierzchołków
		cout << n << "\n";
		for(long long int i = 2; i <= n; i++){
			cout << i - 1 << " " << i << "\n";
		}
	}
	void binary_tree(long long n){ /// ilość wierzchołków
		cout << n << "\n";
		for(long long int i = 2; i <= n; i++){
			cout << i / 2 << " " << i << "\n";
		}
	}
	void caterpillar_tree(long long n){ /// ilość wierzchołków
		cout << n << "\n";
		long long int m = n / 2;
		long long int licznik = n / 2;
		for(long long int i = 2; i <= m; i++){
			cout << i - 1 << " " << i << "\n";
		}
		long long int idx = m;
		while(licznik){
			long long int x = rand(1, m);
			long long int ilosc = min(licznik, rand(1, 3));
			licznik = max(0LL, licznik - ilosc);
			for(long long int i = 1; i <= ilosc; i++){
				cout << x << " " << ++idx << "\n";
			}
		}
	}
	//GRAPHS
	vector<pair<long long int, long long int> > rand_graph_tree(int n){
		vector<pair<long long int, long long int> > edges;
		for(long long int i = 1; i < n; i++) {
			edges.pb(mp(rand(0, i - 1), i));
		}
		return edges;
	}
	void graph_gen(long long n, long long m){ /// ilość wierzchołków i krawędzi
		cout << n << " " << m << "\n";
		
		vector<pair<long long int, long long int> > graph;
		set<pair<long long int, long long int> > edges;
		long long int licznik = 0;
		while(licznik < n && m > 0) {
			long long int current = rand(1, min(m + 1, n - licznik));
			vector<pair<long long int, long long int> > tree = rand_graph_tree(current);
			for(auto &it : tree){
				edges.insert(mp(it.first + licznik, it.second + licznik));
			}
			licznik += size(tree) + 1;
			m -= size(tree);
		}
		while(m > 0) {
			long long int u, v;
			do{
				u = rand(0, n - 2);
				v = rand(u + 1, n - 1);
			} while(edges.count(mp(u, v)));
			edges.insert(mp(u, v));
			m--;
		}
		for(auto it : edges){
			cout << it.first + 1 << " " << it.second + 1 << "\n";
		}
	}
};

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);                  												       

	srand(atoi(argv[1]));
	generatorka().number_gen(2,10);
	return 0;
}