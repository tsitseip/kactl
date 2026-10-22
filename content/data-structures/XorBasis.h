/**
 * Author: Claude (adapted from Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: folklore
 * Description: Linear basis of non-negative 63-bit integers under XOR
 *  (vector space over $\mathbb F_2$). rank = basis size; the set of all
 *  subset xors has $2^{rank}$ distinct values. kth(k) gives the $k$-th
 *  smallest of them (0-based, $k < 2^{rank}$, 0 included).
 * Usage: XorBasis b; for (ll x : a) b.insert(x); ll best = b.maxXor();
 * Time: O(\log C) per insert/query, O(\log^2 C) for kth
 * Status: stress-tested
 */
#pragma once

struct XorBasis {
	ll b[63] = {}; int rank = 0;
	bool insert(ll x) { // false if x was already representable
		for (int i = 62; i >= 0; i--) if (x >> i & 1) {
			if (!b[i]) return b[i] = x, ++rank;
			x ^= b[i];
		}
		return false;
	}
	bool contains(ll x) {
		for (int i = 62; i >= 0; i--) if (x >> i & 1) x ^= b[i];
		return !x;
	}
	ll maxXor(ll x = 0) { // max of x ^ (some subset xor)
		for (int i = 62; i >= 0; i--) x = max(x, x ^ b[i]);
		return x;
	}
	ll kth(ll k) {
		vector<ll> v;
		for (int i = 0; i < 63; i++) if (b[i]) {
			ll x = b[i];
			for (int j = i; j--;) if (x >> j & 1) x ^= b[j];
			v.push_back(x);
		}
		ll r = 0;
		for (int i = 0; i < v.size(); i++)
			if (k >> i & 1) r ^= v[i];
		return r;
	}
};
