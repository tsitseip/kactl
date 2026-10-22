/**
 * Author: Simon Lindholm
 * Date: 2021-01-09
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/Stoer%E2%80%93Wagner_algorithm
 * Description: Find a global minimum cut in an undirected graph, as represented by an adjacency matrix.
 * Usage: auto [w, side] = globalMinCut(mat); // mat: weights
 * Time: O(V^3)
 * Status: Stress-tested together with GomoryHu
 */
#pragma once

pair<int, vector<int>> globalMinCut(vector<vector<int>> mat) {
	pair<int, vector<int>> best = {INT_MAX, {}};
	int n = mat.size();
	vector<vector<int>> co(n);
	for (int i = 0; i < n; i++) co[i] = {i};
	for (int ph = 1; ph < n; ph++) {
		vector<int> w = mat[0];
		size_t s = 0, t = 0;
		// O(V^2) -> O(E log V) with prio. queue
		for (int it = 0; it < n - ph; it++) {
			w[t] = INT_MIN;
			s = t, t = max_element(w.begin(), w.end()) - w.begin();
			for (int i = 0; i < n; i++) w[i] += mat[t][i];
		}
		best = min(best, {w[t] - mat[t][t], co[t]});
		co[s].insert(co[s].end(), co[t].begin(), co[t].end());
		for (int i = 0; i < n; i++) mat[s][i] += mat[t][i];
		for (int i = 0; i < n; i++) mat[i][s] = mat[s][i];
		mat[0][t] = INT_MIN;
	}
	return best;
}
