/**
 * Author: Claude (adapted from Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: https://cp-algorithms.com/geometry/planar.html
 * Description: Faces of a planar straight-line graph (edges only meet
 *  at endpoints, no duplicate points, no multi-edges). adj[v] lists the
 *  neighbours of $v$ (each edge in both lists). Returns the boundary
 *  walk of every face as a vertex list. Bounded faces are ccw (positive
 *  polygonArea2); each connected component also yields one walk with
 *  area $\le 0$: its outer boundary. A connected graph has
 *  $E - V + 2$ walks (Euler).
 * Usage: vector<vector<int>> f = planarFaces(pts, adj);
 * Time: O(E \log E)
 * Status: stress-tested
 */
#pragma once

#include "Point.h"

vector<vector<int>> planarFaces(
	const vector<P>& pts, vector<vector<int>> adj) {
	int n = pts.size();
	auto half = [](P p) { return p.y < 0 || (!p.y && p.x < 0); };
	map<pair<int, int>, int> id;
	for (int v = 0; v < n; v++) {
		sort(adj[v].begin(), adj[v].end(), [&](int a, int b) {
			P p = pts[a] - pts[v], q = pts[b] - pts[v];
			if (half(p) != half(q)) return half(p) < half(q);
			return p.cross(q) > 0; });
		for (int i = 0; i < adj[v].size(); i++)
			id[{v, adj[v][i]}] = i;
	}
	vector<vector<int>> used(n), faces;
	for (int v = 0; v < n; v++)
		used[v].assign((int)adj[v].size(), 0);
	for (int s = 0; s < n; s++)
		for (int i = 0; i < adj[s].size(); i++)
			if (!used[s][i]) {
				vector<int> f;
				for (int v = s, e = i; !used[v][e];) {
					used[v][e] = 1;
					f.push_back(v);
					int u = adj[v][e], j = id[{u, v}];
					v = u, e = (j + 1) % (int)adj[u].size();
				}
				reverse(f.begin(), f.end());
				faces.push_back(f);
			}
	return faces;
}
