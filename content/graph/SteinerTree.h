/**
 * Author: Claude (adapted from foreverbell's cheat sheet)
 * Date: 2026-10-18
 * License: CC0
 * Source: Dreyfus--Wagner, https://github.com/foreverbell/acm-icpc-cheat-sheet
 * Description: Minimum Steiner tree: cheapest connected subgraph
 *  containing all $k$ terminals of an undirected graph with
 *  non-negative weights. dp[mask][v] = cheapest tree spanning the
 *  terminals in mask plus vertex $v$: merge two submasks at $v$, then
 *  relax along edges with Dijkstra. Returns -1 if impossible.
 * Usage: ll c = steiner(adj, terms); // adj[v] = {(u, w)}
 * Time: O(3^k n + 2^k m \log m)
 * Status: stress-tested
 */
#pragma once

ll steiner(
	vector<vector<pair<int, int>>>& g, vector<int>& terms) {
	int n = g.size(), k = terms.size();
	const ll inf = LLONG_MAX / 4;
	if (!k) return 0;
	vector<vector<ll>> dp(1 << k, vector<ll>(n, inf));
	for (int i = 0; i < k; i++) dp[1 << i][terms[i]] = 0;
	for (int m = 1; m < 1 << k; m++) {
		vector<ll>& d = dp[m];
		for (int s = (m - 1) & m; s; s = (s - 1) & m)
			for (int v = 0; v < n; v++)
				d[v] = min(d[v], dp[s][v] + dp[m ^ s][v]);
		priority_queue<pair<ll, int>, vector<pair<ll, int>>,
			greater<>> pq;
		for (int v = 0; v < n; v++)
			if (d[v] < inf) pq.push({d[v], v});
		while (!pq.empty()) {
			auto [c, v] = pq.top(); pq.pop();
			if (c > d[v]) continue;
			for (auto [u, w] : g[v]) if (c + w < d[u])
				pq.push({d[u] = c + w, u});
		}
	}
	ll r = *min_element(dp.back().begin(), dp.back().end());
	return r < inf ? r : -1;
}
