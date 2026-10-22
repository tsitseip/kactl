/**
 * Author: Claude (adapted from Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: https://cp-algorithms.com/geometry/convex_hull_trick.html
 * Description: Li Chao tree: add lines $y = kx + m$ and query the minimum
 *  at integer $x \in [lo, hi)$. addSeg adds a line that only exists for
 *  $x \in [a, b)$. For maximum, negate k, m and the answer.
 *  Simpler than LineContainer when queries are on a known integer range
 *  and needed for segments. Watch out for overflow in $kx + m$.
 * Usage: LiChao t(-1e9, 1e9+1); t.add({k, m}); ll y = t.query(x);
 * Time: O(\log C) per add/query, O(\log^2 C) per addSeg
 * Status: stress-tested
 */
#pragma once

struct Line {
	ll k, m;
	ll operator()(ll x) const { return k * x + m; }
};
struct LiChao {
	struct N { Line f; int c[2]{}; };
	vector<N> t; ll lo, hi;
	LiChao(ll lo, ll hi) : t(2, {{0, LLONG_MAX}}), lo(lo),
		hi(hi) {}
	void ins(Line g, int v, ll l, ll r) {
		for (;;) {
			ll m = l + (r - l) / 2;
			bool L = g(l) < t[v].f(l), M = g(m) < t[v].f(m);
			if (M) swap(t[v].f, g);
			if (r - l == 1) return;
			int d = L == M; // 0: left half, 1: right half
			(d ? l : r) = m;
			if (!t[v].c[d]) {
				t[v].c[d] = t.size(); t.push_back({g}); return;
			}
			v = t[v].c[d];
		}
	}
	void add(Line g) { ins(g, 1, lo, hi); }
	void seg(Line g, ll a, ll b, int v, ll l, ll r) {
		if (b <= l || r <= a) return;
		if (a <= l && r <= b) return ins(g, v, l, r);
		ll m = l + (r - l) / 2;
		for (int d = 0; d < 2; d++) {
			if (!t[v].c[d])
				t[v].c[d] = t.size(), t.push_back({{0, LLONG_MAX}});
			seg(g, a, b, t[v].c[d], d ? m : l, d ? r : m);
		}
	}
	void addSeg(Line g, ll a, ll b) { seg(g, a, b, 1, lo, hi); }
	ll query(ll x) {
		ll res = LLONG_MAX, l = lo, h = hi;
		for (int v = 1; v;) {
			res = min(res, t[v].f(x));
			ll m = l + (h - l) / 2;
			int d = x >= m;
			(d ? l : h) = m;
			v = t[v].c[d];
		}
		return res;
	}
};
