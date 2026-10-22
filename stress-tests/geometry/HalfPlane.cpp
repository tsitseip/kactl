#include "../utilities/template.h"

#include "../../content/geometry/HalfPlane.h"
#include "../../content/geometry/PolygonCut.h"
#include "../../content/geometry/PolygonArea.h"

int main() {
	srand(41);
	int nonempty = 0;
	rep(it,0,30000) {
		const double B = 20;
		vector<HP> h = {{P(-B,-B), P(B,-B)}, {P(B,-B), P(B,B)}, {P(B,B), P(-B,B)}, {P(-B,B), P(-B,-B)}};
		int n = rand() % 8;
		rep(i,0,n) {
			P s(rand() % 21 - 10, rand() % 21 - 10), d(rand() % 11 - 5, rand() % 11 - 5);
			if (d == P()) d = P(1, 0);
			h.push_back({s, s + d});
			if (rand() % 4 == 0) h.push_back({s + d.perp() * (rand() % 3 - 1), s + d.perp() * (rand() % 3 - 1) + d * 2}); // parallel
		}
		shuffle(all(h), mt19937(it));
		vector<P> poly = {P(-B,-B), P(B,-B), P(B,B), P(-B,B)};
		for (auto& l : h) poly = polygonCut(poly, l[1], l[0]); // keep left of l
		double want = sz(poly) >= 3 ? polygonArea2(poly) / 2 : 0;
		auto res = halfPlanes(h);
		double got = sz(res) >= 3 ? polygonArea2(res) / 2 : 0;
		if (abs(want - got) > 1e-6) {
			cerr << want << " " << got << endl;
			for (auto& l : h) cerr << l[0] << "->" << l[1] << endl;
			abort();
		}
		if (got > 1e-9) nonempty++;
		// result convex & ccw, and inside all half-planes
		rep(i,0,sz(res)) {
			assert(res[i].cross(res[(i+1)%sz(res)], res[(i+2)%sz(res)]) > -1e-6);
			for (auto& l : h) assert((l[1]-l[0]).cross(res[i]-l[0]) > -1e-6);
		}
	}
	assert(nonempty > 1000);
	cout << "Tests passed!" << endl;
}
