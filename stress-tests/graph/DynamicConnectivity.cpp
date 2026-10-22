#include "../utilities/template.h"

#include "../../content/graph/DynamicConnectivity.h"

int main() {
	srand(37);
	rep(it,0,3000) {
		int n = rand() % 8 + 1, Q = rand() % 30;
		DynCon d(n, Q);
		vector<array<int, 4>> E;
		map<pii, int> open; vector<set<pii>> alive(Q);
		set<pii> cur;
		rep(t,0,Q) {
			int a = rand() % n, b = rand() % n; if (a > b) swap(a, b);
			if (cur.count({a, b})) { cur.erase({a, b}); d.addEdge(a, b, open[{a, b}], t); }
			else if (rand() % 3) { cur.insert({a, b}); open[{a, b}] = t; }
			alive[t] = cur;
		}
		for (auto e : cur) d.addEdge(e.first, e.second, open[e], Q);
		d.solve();
		rep(t,0,Q) {
			vi p(n); iota(all(p), 0);
			function<int(int)> f = [&](int x) { return p[x] == x ? x : p[x] = f(p[x]); };
			int c = n; for (auto [a, b] : alive[t]) if (f(a) != f(b)) p[f(a)] = f(b), c--;
			assert(d.ans[t] == c);
		}
	}
	cout << "Tests passed!" << endl;
}
