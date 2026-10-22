/**
 * Author: Claude (adapted from Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: folklore (segment tree over time + DSU with rollback)
 * Description: Offline dynamic connectivity. Time is $0..Q-1$; each
 *  edge is alive during a time interval $[l, r)$ (from its insertion to
 *  its deletion). Computes for every time the number of components;
 *  put other queries (e.g. uf.find(a) == uf.find(b)) at the leaf.
 *  Build intervals with map<pair<int, int>,int> start time; end = Q if never removed.
 * Usage: DynCon d(n, Q); d.addEdge(a, b, l, r); d.solve(); d.ans[t]
 * Time: O(Q \log Q \log n)
 * Status: stress-tested
 */
#pragma once

#include "../data-structures/UnionFindRollback.h"

struct DynCon {
	int Q, comps;
	vector<vector<pair<int, int>>> seg;
	RollbackUF uf;
	vector<int> ans;
	DynCon(int n, int Q) : Q(Q), comps(n), seg(2 * Q), uf(n),
		ans(Q) {}
	void addEdge(int a, int b, int l, int r) {
		for (l += Q, r += Q; l < r; l /= 2, r /= 2) {
			if (l & 1) seg[l++].push_back({a, b});
			if (r & 1) seg[--r].push_back({a, b});
		}
	}
	void dfs(int v) {
		int t = uf.time(), c = comps;
		for (auto [a, b] : seg[v]) comps -= uf.join(a, b);
		if (v >= Q) ans[v - Q] = comps; // answer queries at v-Q
		else dfs(2 * v), dfs(2 * v + 1);
		uf.rollback(t); comps = c;
	}
	void solve() { if (Q) dfs(1); }
};
