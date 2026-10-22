#include "../utilities/template.h"
typedef ll T;
#define POINT_T

#include "../../content/geometry/FastDelaunay.h"
#include "../../content/geometry/PolygonArea.h"
#include "../../content/geometry/PlanarFaces.h"

int main() {
	srand(53);
	rep(it,0,3000) {
		int n = rand() % 25 + 1;
		set<P> S; while (sz(S) < n) S.insert(P(rand() % 30, rand() % 30));
		vector<P> pts(all(S));
		auto tri = triangulate(pts);
		map<P, int> id; rep(i,0,n) id[pts[i]] = i;
		set<pii> E;
		set<vi> tris;
		for (int i = 0; i < sz(tri); i += 3) {
			vi t = {id[tri[i]], id[tri[i+1]], id[tri[i+2]]};
			rep(k,0,3) { int a = t[k], b = t[(k+1)%3]; E.insert({min(a,b), max(a,b)}); }
			rotate(t.begin(), min_element(all(t)), t.end()); tris.insert(t);
		}
		bool del = it % 2;
		vector<pii> edges;
		for (auto e : E) if (!del || rand() % 3) edges.push_back(e);
		if (!del && n >= 2 && E.empty()) rep(i,0,n-1) edges.push_back({i, i+1}); // collinear: path
		vector<vi> adj(n);
		for (auto [a, b] : edges) adj[a].push_back(b), adj[b].push_back(a);
		auto faces = planarFaces(pts, adj);
		// every directed edge exactly once
		int tot = 0; for (auto& f : faces) tot += sz(f);
		assert(tot == 2 * sz(edges));
		// components among non-isolated vertices
		vi p(n); iota(all(p), 0);
		function<int(int)> fd = [&](int x) { return p[x] == x ? x : p[x] = fd(p[x]); };
		for (auto [a, b] : edges) p[fd(a)] = fd(b);
		int V = 0, C = 0; rep(v,0,n) if (sz(adj[v])) { V++; if (fd(v) == v) C++; }
		assert(sz(faces) == sz(edges) - V + 2 * C);
		int outer = 0;
		set<vi> got;
		for (auto& f : faces) {
			vector<P> poly; for (int v : f) poly.push_back(pts[v]);
			if (polygonArea2(poly) <= 0) outer++;
			else if (sz(f) == 3) { vi t = f; rotate(t.begin(), min_element(all(t)), t.end()); got.insert(t); }
		}
		assert(outer == C);
		if (!del && !tris.empty()) assert(got == tris);
	}
	cout << "Tests passed!" << endl;
}
