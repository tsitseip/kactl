#include "../utilities/template.h"

#include "../../content/various/SMAWK.h"

int main() {
	srand(79);
	rep(it,0,5000) {
		int n = rand() % 30 + 1, m = rand() % 30 + 1;
		// Monge: (x_i - y_j)^2 with sorted x, y, plus row/col offsets, or convex g(j - i)
		vector<ll> x(n), y(m), u(n), v(m);
		for (ll& t : x) t = rand() % 50; for (ll& t : y) t = rand() % 50;
		sort(all(x)); sort(all(y));
		for (ll& t : u) t = rand() % 100; for (ll& t : v) t = rand() % 100;
		int ty = rand() % 2;
		auto f = [&](int i, int j) -> ll {
			if (ty) return (x[i] - y[j]) * (x[i] - y[j]) + u[i] + v[j];
			ll d = j - i; return d * d * (x[0] % 5 + 1) + v[j] + u[i];
		};
		int evals = 0;
		vi c = smawk(n, m, [&](int i, int j) { evals++; return f(i, j); });
		rep(i,0,n) {
			int best = 0; rep(j,0,m) if (f(i, j) < f(i, best)) best = j;
			assert(c[i] == best);
		}
		assert(evals <= 20 * (n + m));
	}
	cout << "Tests passed!" << endl;
}
