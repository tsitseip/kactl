/**
 * Author: Claude (adapted from Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: https://cp-algorithms.com/algebra/polynomial.html
 * Description: Evaluates a polynomial at many points, and interpolates
 *  the polynomial of degree $< n$ through $n$ points with distinct $x$,
 *  mod 998244353. Uses the product tree of $(X - x_i)$ (node $v$ has
 *  children $2v$, $2v+1$; leaves $n..2n-1$).
 * Usage: vl y = multiEval(a, xs); vl p = interpolate(xs, ys);
 * Time: O(n \log^2 n)
 * Status: stress-tested
 */
#pragma once

#include "PolyOps.h"

struct SubProd {
	int n; vector<vl> t;
	SubProd(const vl& x) : n(x.size()), t(2 * n) {
		for (int i = 0; i < n; i++)
			t[n + i] = {(mod - x[i]) % mod, 1};
		for (int i = n-1; i > 0; i--) t[i] = conv(t[2*i],t[2*i+1]);
	}
	void eval(int v, vl a, vl& res) {
		a = polyDiv(a, t[v]).second;
		if (v >= n) {
			res[v - n] = (int)a.size() ? a[0] : 0;
			return;
		}
		eval(2 * v, a, res), eval(2 * v + 1, a, res);
	}
};
vl multiEval(const vl& a, const vl& x) {
	vl res(x.size());
	if (x.size()) SubProd(x).eval(1, a, res);
	return res;
}
vl interpolate(const vl& x, const vl& y) {
	int n = x.size();
	if (!n) return {};
	SubProd s(x); vl w(n);
	s.eval(1, deriv(s.t[1]), w);
	vector<vl> u(2 * n);
	for (int i = 0; i < n; i++)
		u[n + i] = {y[i] * modpow(w[i], mod - 2) % mod};
	for (int i = n - 1; i > 0; i--) {
		vl a = conv(u[2*i], s.t[2*i+1]);
		vl b = conv(u[2*i+1], s.t[2*i]);
		a.resize(max((int)a.size(), (int)b.size()));
		for (int j = 0; j < b.size(); j++)
			a[j] = (a[j] + b[j]) % mod;
		u[i] = a;
	}
	u[1].resize(n); return u[1];
}
