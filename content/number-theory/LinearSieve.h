/**
 * Author: Claude (adapted from Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: https://cp-algorithms.com/algebra/prime-sieve-linear.html
 * Description: Linear sieve: lp[i] = smallest prime factor, pr = all
 *  primes, plus Euler's phi and M\"obius mu, for all $i <$ LIM.
 *  Factorize $x <$ LIM in $O(\log x)$: while ($x > 1$) $p$ = lp[$x$], $x$ /= $p$.
 *  Any multiplicative $f$ works the same way: split on whether $p$ = lp[i].
 * Usage: sieve(); // then lp, pr, phi, mu
 * Time: O(LIM)
 * Status: stress-tested
 */
#pragma once

const int LIM = 1e6; // ~12 bytes per number
int lp[LIM], phi[LIM], mu[LIM];
vector<int> pr;
void sieve() {
	phi[1] = mu[1] = 1;
	for (int i = 2; i < LIM; i++) {
		if (!lp[i])
			lp[i] = i, pr.push_back(i), phi[i] = i - 1, mu[i] = -1;
		for (int p : pr) {
			if (p > lp[i] || (ll)i * p >= LIM) break;
			lp[i * p] = p;
			phi[i * p] = phi[i] * (p == lp[i] ? p : p - 1);
			mu[i * p] = p == lp[i] ? 0 : -mu[i];
		}
	}
}
