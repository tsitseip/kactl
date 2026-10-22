/**
 * Author: Claude (adapted from Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: folklore
 * Description: Smallest primitive root $g$ modulo a prime $p$: the powers
 *  of $g$ hit every nonzero residue. $g$ is primitive iff
 *  $g^{(p-1)/q} \ne 1$ for every prime $q \mid p-1$. Needed e.g. for NTT
 *  with an unusual prime, or discrete $k$-th roots
 *  ($x^k = a$: write $x = g^y$, $a = g^{\log a}$, solve $ky \equiv \log a \pmod{p-1}$).
 *  Primitive roots mod $m$ exist iff $m = 1, 2, 4, p^k, 2p^k$.
 * Usage: ll g = primitiveRoot(998244353); // 3
 * Time: O(\sqrt p) for factoring $p-1$ (use Factor.h for big p)
 * Status: stress-tested
 */
#pragma once

#include "ModMulLL.h"

ll primitiveRoot(ll p) {
	vector<ll> f; ll x = p - 1;
	for (ll d = 2; d * d <= x; d++) if (x % d == 0) {
		f.push_back(d);
		while (x % d == 0) x /= d;
	}
	if (x > 1) f.push_back(x);
	for (ll g = 1;; g++) {
		bool ok = 1;
		for (ll q : f) ok &= modpow(g, (p - 1) / q, p) != 1;
		if (ok) return g;
	}
}
