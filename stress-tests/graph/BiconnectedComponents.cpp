#include "../utilities/template.h"

#include "../../content/graph/BiconnectedComponents.h"

int n, m;
vector<pii> E;
int ncc(int skipV, int skipE) { // connected components, ignoring a vertex/edge
	vi p(n); iota(all(p), 0);
	function<int(int)> f = [&](int x) { return p[x] == x ? x : p[x] = f(p[x]); };
	rep(i,0,m) if (i != skipE) {
		auto [a, b] = E[i];
		if (a == skipV || b == skipV) continue;
		p[f(a)] = f(b);
	}
	int c = 0;
	rep(i,0,n) if (i != skipV && f(i) == i) c++;
	return c;
}

int main() {
	srand(3);
	rep(it,0,30000) {
		n = rand() % 7 + 1; m = rand() % 9;
		E.clear();
		rep(i,0,m) E.push_back({rand() % n, rand() % n});
		ed.assign(n, {});
		rep(i,0,m) {
			auto [a, b] = E[i];
			ed[a].emplace_back(b, i);
			ed[b].emplace_back(a, i);
		}
		bicomps(m);
		int base = ncc(-1, -1);
		// bridges
		rep(e,0,m) {
			bool br = E[e].first != E[e].second && ncc(-1, e) > base;
			assert(br == (bool)isBridge[e]);
		}
		// articulation points: removing v increases #components among the rest
		rep(v,0,n) {
			bool alone = true; // isolated after removing loops?
			rep(i,0,m) if ((E[i].first == v) != (E[i].second == v)) alone = false;
			int after = ncc(v, -1);
			bool cut = after > base - (alone ? 1 : 0);
			assert(cut == (bool)isCut[v]);
		}
		// components: edges partitioned by "lie on a common simple cycle"
		vi which(m, -1);
		rep(c,0,sz(comps)) for (int e : comps[c]) { assert(which[e] == -1); which[e] = c; }
		vi uf(m); iota(all(uf), 0);
		function<int(int)> f = [&](int x) { return uf[x] == x ? x : uf[x] = f(uf[x]); };
		// enumerate simple cycles (length >= 2, no self-loops) by DFS over edges
		vi path, onv(n);
		function<void(int,int,int)> go = [&](int s, int v, int lastE) {
			for (auto [y, e] : ed[v]) if (e != lastE && E[e].first != E[e].second) {
				if (y == s && !path.empty()) {
					for (int x : path) uf[f(x)] = f(e);
				} else if (!onv[y] && y > s) {
					onv[y] = 1; path.push_back(e);
					go(s, y, e);
					onv[y] = 0; path.pop_back();
				}
			}
		};
		rep(s,0,n) { onv[s] = 1; go(s, s, -1); onv[s] = 0; }
		rep(e,0,m) {
			bool loop = E[e].first == E[e].second;
			if (loop || isBridge[e]) { assert(which[e] == -1); continue; }
			assert(which[e] != -1);
			rep(g,0,m) if (which[g] != -1)
				assert((which[e] == which[g]) == (f(e) == f(g)));
		}
	}
	cout << "Tests passed!" << endl;
}
