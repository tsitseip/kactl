/**
 * Author: Claude (adapted from Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: Lengauer--Tarjan, https://tanujkhattar.wordpress.com/2016/01/11/dominator-tree-of-a-directed-graph/
 * Description: Dominator tree of a directed graph from root $r$:
 *  $u$ dominates $v$ if every path $r \to v$ passes through $u$.
 *  Returns idom[v] = immediate dominator (parent in the tree),
 *  idom[r] = r, -1 for vertices unreachable from $r$.
 *  Typical use: ``vertices whose removal disconnects $v$ from $r$'' =
 *  ancestors of $v$ in the dominator tree.
 * Usage: vector<int> idom = dominators(adj, root);
 * Time: O(E \log V)
 * Status: stress-tested
 */
#pragma once

vector<int> dominators(vector<vector<int>>& g, int root) {
	int n = g.size(), T = 0;
	vector<int> id(n, -1), rv(n), par(n), sd(n), dm(n), uf(n),
		lb(n);
	vector<vector<int>> rg(n), bk(n);
	auto dfs = [&](auto&& self, int v) -> void {
		rv[T] = v, id[v] = sd[T] = uf[T] = lb[T] = T, T++;
		for (int u : g[v]) {
			if (id[u] < 0) self(self, u), par[id[u]] = id[v];
			rg[id[u]].push_back(id[v]);
		}
	};
	dfs(dfs, root);
	auto find = [&](auto&& self, int u, int x) -> int {
		if (u == uf[u]) return x ? -1 : u;
		int v = self(self, uf[u], x + 1);
		if (v < 0) return u;
		if (sd[lb[uf[u]]] < sd[lb[u]]) lb[u] = lb[uf[u]];
		uf[u] = v;
		return x ? v : lb[u];
	};
	for (int i = T - 1; i >= 0; i--) {
		for (int j : rg[i]) sd[i] = min(sd[i], sd[find(find,j,0)]);
		if (i) bk[sd[i]].push_back(i);
		for (int j : bk[i]) {
			int v = find(find, j, 0);
			dm[j] = sd[v] == sd[j] ? sd[j] : v;
		}
		if (i) uf[i] = par[i];
	}
	vector<int> idom(n, -1);
	idom[root] = root;
	for (int i = 1; i < T; i++) {
		if (dm[i] != sd[i]) dm[i] = dm[dm[i]];
		idom[rv[i]] = rv[dm[i]];
	}
	return idom;
}
