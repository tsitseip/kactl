/**
 * Author: Ulf Lundstrom
 * Date: 2009-08-03
 * License: CC0
 * Source: My head
 * Description: Matrix product and power modulo mod, e.g. for linear
 *  recurrences: if $v_{i+1} = A v_i$ then $v_n = A^n v_0$ (a vector is an
 *  $n \times 1$ matrix). For doubles change ll to double and drop \% mod.
 * Usage: Mat A = {{1,1},{1,0}}; Mat B = pw(A, n); // B[0][1] = Fib(n)
 * Time: O(N^3 \log p)
 * Status: stress-tested
 */
#pragma once

const ll mod = 1e9 + 7;
typedef vector<vector<ll>> Mat;
Mat operator*(const Mat& a, const Mat& b) {
	int n = a.size(), k = b.size(), m = b[0].size();
	Mat c(n, vector<ll>(m));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < k; j++)
			if (a[i][j])
				for (int l = 0; l < m; l++)
					c[i][l] = (c[i][l] + a[i][j] * b[j][l]) % mod;
	return c;
}
Mat pw(Mat a, ll p) {
	Mat r((int)a.size(), vector<ll>(a.size()));
	for (int i = 0; i < a.size(); i++) r[i][i] = 1;
	for (; p; p /= 2, a = a * a)
		if (p & 1) r = r * a;
	return r;
}
