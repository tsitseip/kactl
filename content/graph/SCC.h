/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Components are numbered in reverse topological order: an edge
 * $u \to v$ implies comp[u] $\ge$ comp[v] (a component only has edges
 * to components with lower index), so the condensation DAG can be
 * processed by iterating c = 0..ncomps-1.
 * Usage: scc(g); // g: vector<vector<int>> adjacency list
 *  comp[v] = component of v, comps[c] = vertices of c, ncomps
 * Time: O(E + V)
 * Status: Bruteforce-tested for N <= 5
 */
#pragma once

vector<int> val, comp, z;
vector<vector<int>> comps;
int Time, ncomps;
int dfs(int j, vector<vector<int>>& g) {
	int low = val[j] = ++Time, x; z.push_back(j);
	for (int e : g[j]) if (comp[e] < 0)
		low = min(low, val[e] ?: dfs(e, g));

	if (low == val[j]) {
		comps.emplace_back();
		do {
			x = z.back(); z.pop_back();
			comp[x] = ncomps;
			comps.back().push_back(x);
		} while (x != j);
		ncomps++;
	}
	return val[j] = low;
}
void scc(vector<vector<int>>& g) {
	int n = g.size();
	val.assign(n, 0); comp.assign(n, -1); comps.clear();
	Time = ncomps = 0;
	for (int i = 0; i < n; i++) if (comp[i] < 0) dfs(i, g);
}
