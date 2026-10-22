/**
 * Author: Claude (adapted from Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: Edmonds' blossom algorithm, https://cp-algorithms.com/graph/Edmonds_Blossom.html
 * Description: Maximum matching in a general (non-bipartite)
 *  undirected graph. Returns the size; mt[v] = partner of $v$ or -1.
 *  For bipartite graphs prefer HopcroftKarp.
 * Usage: vector<int> mt; int k = generalMatching(adj, mt);
 * Time: O(V^3)
 * Status: stress-tested
 */
#pragma once

int generalMatching(vector<vector<int>>& g, vector<int>& mt) {
	int n = g.size(), res = 0;
	vector<int> p(n), base(n), q(n);
	vector<bool> used(n), bl(n);
	mt.assign(n, -1);
	auto lca = [&](int a, int b) -> int {
		vector<bool> seen(n);
		for (;;) {
			a = base[a]; seen[a] = 1;
			if (mt[a] < 0) break;
			a = p[mt[a]];
		}
		for (;; b = p[mt[b]]) if (seen[b = base[b]]) return b;
	};
	auto mark = [&](int v, int b, int x) {
		while (base[v] != b) {
			bl[base[v]] = bl[base[mt[v]]] = 1;
			p[v] = x; x = mt[v]; v = p[x];
		}
	};
	auto path = [&](int root) -> int {
		fill(used.begin(), used.end(), 0);
		fill(p.begin(), p.end(), -1);
		iota(base.begin(), base.end(), 0);
		int qh = 0, qt = 0;
		used[root] = 1;
		q[qt++] = root;
		while (qh < qt) {
			int v = q[qh++];
			for (int to : g[v]) {
				if (base[v] == base[to] || mt[v] == to) continue;
				if (to == root || (mt[to] >= 0 && p[mt[to]] >= 0)) {
					int b = lca(v, to);
					fill(bl.begin(), bl.end(), 0);
					mark(v, b, to);
					mark(to, b, v);
					for (int i = 0; i < n; i++)
						if (bl[base[i]]) {
							base[i] = b;
							if (!used[i]) used[i] = 1, q[qt++] = i;
						}
				} else if (p[to] < 0) {
					p[to] = v;
					if (mt[to] < 0) return to;
					used[mt[to]] = 1;
					q[qt++] = mt[to];
				}
			}
		}
		return -1;
	};
	for (int i = 0; i < n; i++) if (mt[i] < 0) {
		int v = path(i);
		if (v < 0) continue;
		res++;
		while (v >= 0) {
			int pv = p[v], nv = mt[pv];
			mt[v] = pv, mt[pv] = v, v = nv;
		}
	}
	return res;
}
