#include "../utilities/template.h"

#include "../../content/graph/SteinerTree.h"

int main() {
	srand(29);
	rep(it,0,2000) {
		int n = rand() % 8 + 1, m = rand() % 16, k = rand() % min<int>(n, 5);
		vector<array<int, 3>> E;
		vector<vector<pii>> g(n);
		rep(i,0,m) { int a = rand() % n, b = rand() % n, w = rand() % 10; E.push_back({a, b, w}); g[a].push_back({b, w}); g[b].push_back({a, w}); }
		vi perm(n); iota(all(perm), 0); random_shuffle(all(perm));
		vi terms(perm.begin(), perm.begin() + k);
		ll best = -1;
		rep(S,0,1 << n) {
			bool ok = true; for (int t : terms) if (!(S >> t & 1)) ok = false;
			if (!ok || !S) continue;
			// MST of induced subgraph
			vi p(n); iota(all(p), 0);
			function<int(int)> f = [&](int x) { return p[x] == x ? x : p[x] = f(p[x]); };
			auto es = E; sort(all(es), [](auto& a, auto& b) { return a[2] < b[2]; });
			ll c = 0; int comps = __builtin_popcount(S);
			for (auto [a, b, w] : es) if ((S >> a & 1) && (S >> b & 1) && f(a) != f(b)) p[f(a)] = f(b), c += w, comps--;
			if (comps == 1 && (best < 0 || c < best)) best = c;
		}
		if (k == 0) best = 0;
		assert(steiner(g, terms) == best);
	}
	cout << "Tests passed!" << endl;
}
