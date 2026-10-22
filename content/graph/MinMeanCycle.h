/**
 * Author: Claude (adapted from foreverbell's cheat sheet)
 * Date: 2026-10-18
 * License: CC0
 * Source: Karp 1978, https://github.com/foreverbell/acm-icpc-cheat-sheet
 * Description: Minimum mean weight of a directed cycle,
 *  $\min_C \frac{w(C)}{|C|}$ (Karp). Negative weights are fine. Returns
 *  1e18 if the graph is acyclic. For the maximum, negate all weights.
 *  Alternatively, binary search $\lambda$ + negative cycle check with
 *  weights $w - \lambda$ (works for ratio $\sum a / \sum b$ too).
 * Usage: double mu = minMeanCycle(n, eds); // eds: {a, b, w}, a -> b
 * Time: O(VE)
 * Status: stress-tested
 */
#pragma once

double minMeanCycle(int n, vector<array<ll, 3>>& eds) {
	const ll inf = LLONG_MAX / 4;
	vector<vector<ll>> d(n + 1, vector<ll>(n, inf));
	d[0].assign(n, 0); // walks of exactly k edges, any start
	for (int k = 0; k < n; k++)
		for (auto [a, b, w] : eds)
			if (d[k][a] < inf)
				d[k + 1][b] = min(d[k + 1][b], d[k][a] + w);
	double res = 1e18;
	for (int v = 0; v < n; v++) if (d[n][v] < inf) {
		double mx = -1e18;
		for (int k = 0; k < n; k++) if (d[k][v] < inf)
			mx = max(mx, double(d[n][v] - d[k][v]) / (n - k));
		res = min(res, mx);
	}
	return res;
}
