/**
 * Author: Claude (adapted from Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: Hyyrö, bit-parallel LCS
 * Description: Length of the longest common subsequence of $a$ and $b$,
 *  using bit-parallel rows ($D$ = row of the DP in difference form):
 *  $X = M_c \mid D$, $D = X \,\&\, \lnot(X - ((D \ll 1) \mid 1))$ with
 *  multi-word subtraction.
 * Usage: int L = lcs(a, b);
 * Time: O(|a| |b| / 64)
 * Status: stress-tested
 */
#pragma once

typedef unsigned long long ull;
int lcs(const string& a, const string& b) {
	int W = (int)b.size() / 64 + 1, res = 0;
	vector<vector<ull>> M(256, vector<ull>(W));
	for (int i = 0; i < b.size(); i++)
		M[(unsigned char)b[i]][i / 64] |= 1ULL << i % 64;
	vector<ull> D(W);
	for (unsigned char c : a) {
		ull sh = 1, br = 0; // carry of the shift, borrow
		for (int i = 0; i < W; i++) {
			ull x = M[c][i] | D[i], y = D[i] << 1 | sh, z = x-y-br;
			sh = D[i] >> 63;
			br = x < y || (x == y && br);
			D[i] = x & ~z;
		}
	}
	for (ull d : D) res += __builtin_popcountll(d);
	return res;
}
