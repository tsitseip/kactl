/**
 * Author: Claude (adapted from Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/SMAWK_algorithm
 * Description: Row minima of an implicit $n \times m$ totally monotone
 *  matrix (e.g. Monge: $f(i,j) + f(i',j') \le f(i,j') + f(i',j)$ for
 *  $i<i'$, $j<j'$). Returns for every row the column of its leftmost
 *  minimum; these are non-decreasing. Use for DP transitions
 *  $dp[i] = \min_j (\dots)$ with Monge cost when D\&C opt is too slow.
 * Usage: vector<int> c = smawk(n, m, [\&](int i, int j) { return A[i][j]; });
 * Time: O(n + m) evaluations of f
 * Status: stress-tested
 */
#pragma once

typedef function<ll(int, int)> F;
void rec(const vector<int>& rows, const vector<int>& cols,
	F& f, vector<int>& ans) {
	if (rows.empty()) return;
	vector<int> st, odd;
	for (int c : cols) { // REDUCE to at most |rows| columns
		while ((int)st.size() &&
			f(rows[(int)st.size() - 1], st.back()) >
				f(rows[(int)st.size() - 1], c))
			st.pop_back();
		if ((int)st.size() < (int)rows.size()) st.push_back(c);
	}
	for (int i = 1; i < (int)rows.size(); i += 2)
		odd.push_back(rows[i]);
	rec(odd, st, f, ans);
	for (int i = 0, k = 0; i < (int)rows.size();
		i += 2) { // INTERPOLATE
		int hi = i + 1 < (int)rows.size() ? ans[rows[i + 1]]
																			: st.back();
		ll best = f(rows[i], st[k]); ans[rows[i]] = st[k];
		while (st[k] != hi) {
			ll v = f(rows[i], st[++k]);
			if (v < best) best = v, ans[rows[i]] = st[k];
		}
	}
}
vector<int> smawk(int n, int m, F f) {
	vector<int> rows(n), cols(m), ans(n);
	iota(rows.begin(), rows.end(), 0);
	iota(cols.begin(), cols.end(), 0);
	rec(rows, cols, f, ans);
	return ans;
}
