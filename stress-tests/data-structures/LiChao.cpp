#include "../utilities/template.h"

#include "../../content/data-structures/LiChao.h"

int main() {
	srand(5);
	rep(it,0,3000) {
		ll lo = rand() % 41 - 20, hi = lo + rand() % 40 + 1;
		LiChao t(lo, hi);
		vector<ll> best(hi - lo, LLONG_MAX);
		rep(op,0,40) {
			int ty = rand() % 3;
			if (ty < 2) {
				Line g{rand() % 21 - 10, rand() % 201 - 100};
				ll a = lo, b = hi;
				if (ty == 1) {
					a = lo + rand() % (hi - lo); b = lo + rand() % (hi - lo + 1);
					if (a > b) swap(a, b);
					t.addSeg(g, a, b);
				} else t.add(g);
				for (ll x = a; x < b; x++) best[x - lo] = min(best[x - lo], g(x));
			} else {
				ll x = lo + rand() % (hi - lo);
				assert(t.query(x) == best[x - lo]);
			}
		}
		for (ll x = lo; x < hi; x++) assert(t.query(x) == best[x - lo]);
	}
	// big range, max via negation
	LiChao t(-1e9, 1e9 + 1);
	vector<Line> ls;
	rep(i,0,2000) { Line g{rand() % 2001 - 1000, rand() % 2000001 - 1000000}; ls.push_back(g); t.add({-g.k, -g.m}); }
	rep(i,0,2000) {
		ll x = (ll)rand() % 2000000001 - 1000000000, mx = LLONG_MIN;
		for (auto& g : ls) mx = max(mx, g(x));
		assert(-t.query(x) == mx);
	}
	assert(sz(t.t) <= 2000 + 2);
	cout << "Tests passed!" << endl;
}
