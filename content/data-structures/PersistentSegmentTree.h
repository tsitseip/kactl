/**
 * Author: Claude (adapted from Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: folklore
 * Description: Persistent segment tree on positions $[0, n)$ with point
 *  add and range sum. Every add returns a new root; old roots stay valid.
 *  Node 0 is the empty tree. Classic use, $k$-th smallest of $a[l..r)$:
 *  insert compressed values in array order, then walk the difference
 *  of versions $r$ and $l$ (kth). Same idea: count of values in
 *  $[lo, hi)$ inside $a[l..r)$ = query(root[r]) - query(root[l]).
 * Usage: PST t(n); vector<int> root = {0};
 *  for (int x : a) root.push_back(t.add(root.back(), x, 1));
 *  int v = t.kth(root[l], root[r], k); // k is 0-based
 * Time: O(\log n) per operation
 * Memory: O(\log n) new nodes per add
 * Status: stress-tested
 */
#pragma once

struct PST {
	int n; vector<int> L{0}, R{0}; vector<ll> S{0};
	PST(int n) : n(n) {}
	int upd(int v, int p, ll x, int l, int r) {
		int u = S.size();
		L.push_back(L[v]), R.push_back(R[v]);
		S.push_back(S[v] + x);
		if (r - l > 1) {
			int m = (l + r) / 2, c;
			if (p < m) c = upd(L[v], p, x, l, m), L[u] = c;
			else c = upd(R[v], p, x, m, r), R[u] = c;
		}
		return u;
	}
	int add(int rt, int p, ll x) { return upd(rt, p, x, 0, n); }
	ll sum(int v, int a, int b, int l, int r) {
		if (!v || b <= l || r <= a) return 0;
		if (a <= l && r <= b) return S[v];
		int m = (l + r) / 2;
		return sum(L[v], a, b, l, m) + sum(R[v], a, b, m, r);
	}
	ll query(int rt, int a, int b) { return sum(rt,a,b,0,n); }
	int kth(int v, int u, ll k) { // in version u minus version v
		int l = 0, r = n;
		while (r - l > 1) {
			int m = (l + r) / 2; ll c = S[L[u]] - S[L[v]];
			if (k < c) v = L[v], u = L[u], r = m;
			else k -= c, v = R[v], u = R[u], l = m;
		}
		return l;
	}
};
