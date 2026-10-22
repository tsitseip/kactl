/**
 * Author: Claude (adapted from Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: folklore
 * Description: $\binom{n}{k} \bmod p$ for $n <$ LIM with precomputed
 *  factorials, $p$ prime $\ge$ LIM. For huge $n$ and small prime $p$
 *  (set LIM $= p$) use lucas: $\binom{n}{k} \equiv \prod \binom{n_i}{k_i}$ over
 *  base-$p$ digits.
 * Usage: initFact(); ll c = C(n, k);
 * Time: O(LIM) precomputation, O(1) per query
 * Status: stress-tested
 */
#pragma once

#include "../number-theory/ModPow.h"

#ifndef LIM_SET /// exclude-line
const int LIM = 1e6 + 5; // > max n (for lucas: LIM = mod)
#endif /// exclude-line
ll fact[LIM], ifact[LIM];
void initFact() {
	fact[0] = 1;
	for (int i = 1; i < LIM; i++) fact[i] = fact[i-1] * i % mod;
	ifact[LIM-1] = modpow(fact[LIM-1], mod - 2);
	for (int i = LIM-1; i; i--) ifact[i-1] = ifact[i] * i % mod;
}
ll C(ll n, ll k) {
	if (k < 0 || k > n) return 0;
	return fact[n] * ifact[k] % mod * ifact[n-k] % mod;
}
ll lucas(ll n, ll k) { // needs mod < LIM
	ll r = 1;
	for (; n || k; n /= mod, k /= mod)
		r = r * C(n % mod, k % mod) % mod;
	return r;
}
