/**
 * Author: Claude (adapted from Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: folklore (Gauss--Jordan)
 * Description: Solves $Ax = b$ modulo a prime (entries in $[0, \text{mod})$).
 *  Returns the rank, or -1 if there is no solution; $x$ gets one solution
 *  with free variables 0. The number of solutions is $\text{mod}^{m - \text{rank}}$.
 *  Destroys $A$ and $b$. For mod 2 use SolveLinearBinary.
 * Usage: vector<vector<ll>> A(n, vector<ll>(m)); vector<ll> b(n), x(m);
 *  int r = solveLinearMod(A, b, x);
 * Time: O(n^2 m)
 * Status: stress-tested
 */
#pragma once

#include "../number-theory/ModPow.h"

int solveLinearMod(vector<vector<ll>>& A, vector<ll>& b,
		vector<ll>& x) {
	int n = A.size(), m = x.size(), r = 0;
	vector<int> where(m, -1);
	for (int c = 0; c < m; c++) {
		if (r == n) break;
		int p = r;
		while (p < n && !A[p][c]) p++;
		if (p == n) continue;
		swap(A[p], A[r]), swap(b[p], b[r]), where[c] = r;
		ll iv = modpow(A[r][c], mod - 2);
		for (int j = c; j < m; j++) A[r][j] = A[r][j] * iv % mod;
		b[r] = b[r] * iv % mod;
		for (int i = 0; i < n; i++) if (i != r && A[i][c]) {
			ll f = A[i][c];
			for (int j = c; j < m; j++)
				A[i][j] = (A[i][j] - f * A[r][j] % mod + mod) % mod;
			b[i] = (b[i] - f * b[r] % mod + mod) % mod;
		}
		r++;
	}
	for (int i = r; i < n; i++) if (b[i]) return -1;
	x.assign(m, 0);
	for (int c = 0; c < m; c++)
		if (where[c] >= 0) x[c] = b[where[c]];
	return r;
}
