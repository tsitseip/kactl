/**
 * Author: Claude (adapted from Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: folklore
 * Description: Persistent binary trie over $B$-bit numbers. Version $i$
 *  holds $a[0..i)$. maxXor(l, r, x) = $\max_{l \le j < r} x \oplus a[j]$
 *  (requires $l < r$). Without persistence, a plain trie (one version)
 *  answers ``max xor with any inserted value''.
 * Usage: XorTrie t; for (int v : a) t.add(v); int m = t.maxXor(l, r, x);
 * Time: O(B) per operation
 * Memory: O(N B)
 * Status: stress-tested
 */
#pragma once

struct XorTrie {
	static const int B = 30;
	vector<array<int, 2>> nx{{0, 0}};
	vector<int> cnt{0}, root{0};
	int clone(int v) {
		nx.push_back(nx[v]); cnt.push_back(cnt[v] + 1);
		return (int)cnt.size() - 1;
	}
	void add(int x) {
		int v = root.back(), u = clone(v);
		root.push_back(u);
		for (int b = B; b--;) {
			int c = x >> b & 1, w = clone(nx[v][c]);
			nx[u][c] = w; u = w; v = nx[v][c];
		}
	}
	int maxXor(int l, int r, int x) {
		int u = root[r], v = root[l], res = 0;
		for (int b = B; b--;) {
			int c = !(x >> b & 1);
			if (cnt[nx[u][c]] > cnt[nx[v][c]]) res |= 1 << b;
			else c ^= 1;
			u = nx[u][c], v = nx[v][c];
		}
		return res;
	}
};
