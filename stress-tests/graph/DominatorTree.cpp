#include "../utilities/template.h"

#include "../../content/graph/DominatorTree.h"

int main() {
	srand(19);
	rep(it,0,4000) {
		int n = rand() % 9 + 1, m = rand() % 20, r = rand() % n;
		vector<vi> g(n);
		rep(i,0,m) g[rand() % n].push_back(rand() % n);
		auto reach = [&](int ban) {
			vector<bool> vis(n); if (r == ban) return vis;
			vi st = {r}; vis[r] = 1;
			while (!st.empty()) { int v = st.back(); st.pop_back(); for (int u : g[v]) if (u != ban && !vis[u]) vis[u] = 1, st.push_back(u); }
			return vis;
		};
		auto base = reach(-1);
		vector<vector<bool>> dom(n, vector<bool>(n)); // dom[u][v]: u dominates v
		rep(u,0,n) { auto R = reach(u); rep(v,0,n) dom[u][v] = base[v] && (u == v || !R[v]); }
		vi idom = dominators(g, r);
		rep(v,0,n) {
			if (!base[v]) { assert(idom[v] == -1); continue; }
			if (v == r) { assert(idom[v] == r); continue; }
			// idom: strict dominator of v dominated by all other strict dominators
			int want = -1;
			rep(u,0,n) if (u != v && dom[u][v]) {
				bool ok = true;
				rep(w,0,n) if (w != v && dom[w][v] && !dom[w][u]) ok = false;
				if (ok) want = u;
			}
			assert(idom[v] == want);
		}
	}
	cout << "Tests passed!" << endl;
}
