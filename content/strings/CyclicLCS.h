/**
 * Author: Claude (adapted from foreverbell's cheat sheet)
 * Date: 2026-10-18
 * License: CC0
 * Source: Nguyen, ``Solving cyclic LCS in quadratic time''; https://github.com/foreverbell/acm-icpc-cheat-sheet
 * Description: Longest common subsequence of $b$ and any rotation of $a$.
 *  Builds the LCS DP of $a+a$ vs $b$ once (pa = which neighbour each cell
 *  came from) and, for each rotation, re-roots the path tree instead of
 *  recomputing.
 * Usage: int L = cyclicLCS(a, b);
 * Time: O(|a| |b|)
 * Status: stress-tested
 */
#pragma once

int cyclicLCS(string a, const string& b) {
	int m = a.size(), n = b.size(), ans = 0;
	a += a;
	vector<vector<int>> dp(2 * m + 1, vector<int>(n + 1)),
		pa = dp; // 1 left 2 diag 3 up
	for (int i = 0; i < 2 * m + 1; i++)
		for (int j = 0; j < n + 1; j++)
			if (i || j) {
				int& d = dp[i][j] = -1;
				if (j && dp[i][j - 1] > d)
					d = dp[i][j - 1], pa[i][j] = 1;
				if (i && j && a[i - 1] == b[j - 1] &&
					dp[i - 1][j - 1] + 1 > d)
					d = dp[i - 1][j - 1] + 1, pa[i][j] = 2;
				if (i && dp[i - 1][j] > d)
					d = dp[i - 1][j], pa[i][j] = 3;
			}
	auto trace = [&](int sx, int ex) { // #diagonals on path
		int l = 0, x = ex, y = n;
		while (x != sx || y) {
			int p = pa[x][y];
			if (p != 3) y--;
			if (p != 1) x--;
			l += p == 2;
		}
		return l;
	};
	ans = trace(0, m);
	for (int r = 1; r < m;
		r++) { // re-root: remove row r from the path tree
		int i = r, j = 1;
		while (j <= n && pa[i][j] != 2) j++;
		if (j <= n) {
			pa[i][j] = 1;
			while (i < 2*m && j < n) {
				if (pa[i+1][j] == 3) pa[++i][j] = 1;
				else if (pa[i+1][j+1] == 2) pa[++i][++j] = 1;
				else j++;
			}
			while (i < 2*m && pa[i+1][j] == 3) pa[++i][j] = 1;
		}
		ans = max(ans, trace(r, m + r));
	}
	return ans;
}
