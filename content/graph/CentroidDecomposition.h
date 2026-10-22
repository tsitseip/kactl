/**
 * Author: Claude (adapted from Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: folklore
 * Description: Centroid decomposition of a tree. Repeatedly removes a
 *  centroid (all remaining parts have $\le$ half the size). par[c] =
 *  parent of $c$ in the centroid tree (-1 for the root); it has depth
 *  $O(\log n)$ and the path $u$--$v$ passes through their centroid-tree
 *  LCA. Typical use: at the marked line, DFS from $c$ over vertices with
 *  !rem[] to handle all paths through $c$ (e.g. count paths of length K).
 * Usage: Centroid cd(adj); // cd.par[v]
 * Time: O(n \log n) plus the work at each centroid times O(\log n)
 * Status: stress-tested
 */
#pragma once

struct Centroid {
	vector<vector<int>> adj; vector<int> par, siz, rem;
	Centroid(vector<vector<int>> g) :
			adj(g), par((int)g.size(), -1), siz(g.size()),
			rem(g.size()) {
		if (g.size()) build(0, -1);
	}
	int dfsSz(int v, int p) {
		siz[v] = 1;
		for (int u : adj[v]) if (u != p && !rem[u])
			siz[v] += dfsSz(u, v);
		return siz[v];
	}
	void build(int v, int p) {
		int n = dfsSz(v, -1), c = v, prev = -1;
		for (bool moved = 1; moved;) {
			moved = 0;
			for (int u : adj[c])
				if (u != prev && !rem[u] && 2 * siz[u] > n) {
					prev = c, c = u, moved = 1; break;
				}
		}
		par[c] = p; rem[c] = 1;
		// process all paths through c here
		for (int u : adj[c]) if (!rem[u]) build(u, c);
	}
};
