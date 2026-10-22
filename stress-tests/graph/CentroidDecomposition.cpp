#include "../utilities/template.h"
#include "../utilities/genTree.h"

#include "../../content/graph/CentroidDecomposition.h"

int main() {
	srand(17);
	rep(it,0,2000) {
		int n = rand() % 40 + 2; // genRandomTree needs n >= 2
		vector<vi> adj(n);
		auto ed = genRandomTree(n);
		for (auto [a, b] : ed) adj[a].push_back(b), adj[b].push_back(a);
		Centroid cd(adj);
		auto& par = cd.par;
		int roots = 0, maxDep = 0;
		vector<vi> ch(n);
		rep(v,0,n) { if (par[v] < 0) roots++; else ch[par[v]].push_back(v); }
		assert(roots == 1);
		// subtree of c in centroid tree must be a connected piece of the tree,
		// and each child piece has size <= half
		vi sub(n);
		function<int(int, int, vi&)> collect = [&](int c, int d, vi& out) {
			maxDep = max(maxDep, d); out.push_back(c);
			int s = 1; for (int u : ch[c]) s += collect(u, d + 1, out);
			return sub[c] = s;
		};
		vi tmp; rep(v,0,n) if (par[v] < 0) collect(v, 0, tmp);
		assert(sz(tmp) == n);
		assert((1 << maxDep) <= n);
		rep(c,0,n) {
			vi piece; vector<bool> in(n);
			function<void(int)> col = [&](int v) { piece.push_back(v); for (int u : ch[v]) col(u); };
			col(c); for (int v : piece) in[v] = 1;
			// connected?
			vector<bool> vis(n); vi st = {c}; vis[c] = 1; int cnt = 0;
			while (!st.empty()) { int v = st.back(); st.pop_back(); cnt++; for (int u : adj[v]) if (in[u] && !vis[u]) vis[u] = 1, st.push_back(u); }
			assert(cnt == sz(piece));
			for (int u : ch[c]) assert(2 * sub[u] <= sz(piece));
		}
	}
	{ Centroid one(vector<vi>(1)); assert(one.par[0] == -1); }
	cout << "Tests passed!" << endl;
}
