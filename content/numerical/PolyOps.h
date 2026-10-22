/**
 * Author: Claude (adapted from Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: https://cp-algorithms.com/algebra/polynomial.html
 * Description: Formal power series mod $x^n$ (mod = 998244353, from NTT):
 *  inverse ($a_0 \ne 0$), log ($a_0 = 1$), exp ($a_0 = 0$), sqrt
 *  ($a_0 = 1$; otherwise start $b$ with ModSqrt of $a_0$), and division
 *  with remainder ($a = bq + r$, $\deg r < \deg b$, b.back() $\ne 0$).
 *  For powers use $a^k = \exp(k \log a)$ when $a_0 = 1$.
 *  Typical use: counting with generating functions, e.g. sets of
 *  connected structures $= \exp(\cdot)$, sequences $= 1/(1 - \cdot)$.
 * Usage: vl b = polyInv(a, n); // a*b = 1 in the first n terms
 *  auto [q, r] = polyDiv(a, b);
 * Time: O(n \log n) each (exp has a large constant)
 * Status: stress-tested
 */
#pragma once

#include "NumberTheoreticTransform.h"

vl polyInv(const vl& a, int n) {
	vl b = {modpow(a[0], mod - 2)};
	for (int k = 1; k < n; k *= 2) { // b = b(2 - ab)
		vl c(a.begin(), a.begin() + min((int)a.size(), 2 * k));
		c = conv(c, conv(b, b)); c.resize(2 * k); b.resize(2 * k);
		for (int i = 0; i < 2 * k; i++)
			b[i] = (2 * b[i] - c[i] + mod) % mod;
	}
	b.resize(n); return b;
}
vl deriv(vl a) {
	for (int i = 1; i < a.size(); i++) a[i-1] = a[i] * i % mod;
	if (a.size()) a.pop_back();
	return a;
}
vl integ(vl a) {
	a.push_back(0);
	for (int i = (int)a.size() - 1; i; i--)
		a[i] = a[i-1] * modpow(i, mod - 2) % mod;
	a[0] = 0; return a;
}
vl polyLog(const vl& a, int n) {
	vl r = integ(conv(deriv(a), polyInv(a, n)));
	r.resize(n); return r;
}
vl polyExp(const vl& a, int n) { // b = b(1 - log b + a)
	vl b = {1};
	for (int k = 1; k < n; k *= 2) {
		vl c = polyLog(b, 2 * k);
		for (int i = 0; i < 2 * k; i++)
			c[i] = ((i < (int)a.size() ? a[i] : 0) - c[i] + mod) %
				mod;
		c[0] = (c[0] + 1) % mod;
		b = conv(b, c); b.resize(2 * k);
	}
	b.resize(n); return b;
}
vl polySqrt(const vl& a, int n) { // b = (b + a / b) / 2
	vl b = {1};
	for (int k = 1; k < n; k *= 2) {
		vl c(a.begin(), a.begin() + min((int)a.size(), 2 * k));
		c = conv(c, polyInv(b, 2 * k));
		c.resize(2 * k); b.resize(2 * k);
		for (int i = 0; i < 2 * k; i++)
			b[i] = (b[i] + c[i]) * ((mod + 1) / 2) % mod;
	}
	b.resize(n); return b;
}
pair<vl, vl> polyDiv(const vl& a, const vl& b) {
	int n = a.size(), m = b.size();
	if (n < m) return {{}, a};
	vl ra(a.rbegin(), a.rend()), rb(b.rbegin(), b.rend());
	ra.resize(n - m + 1);
	vl q = conv(ra, polyInv(rb, n - m + 1));
	q.resize(n - m + 1); reverse(q.begin(), q.end());
	vl r = conv(b, q); r.resize(m - 1);
	for (int i = 0; i < m - 1; i++)
		r[i] = (a[i] - r[i] + mod) % mod;
	return {q, r};
}
