#include "../utilities/template.h"

#include "../../content/number-theory/LinearSieve.h"

int main() {
	sieve();
	int cnt = 0;
	rep(n,1,LIM) {
		int x = n, ph = n, m = 1, sp = n == 1 ? 0 : -1;
		for (int d = 2; (ll)d * d <= x; d++) if (x % d == 0) {
			if (sp < 0) sp = d;
			int e = 0; while (x % d == 0) x /= d, e++;
			ph = ph / d * (d - 1); m = e > 1 ? 0 : -m;
		}
		if (x > 1) { if (sp < 0) sp = x; ph = ph / x * (x - 1); m = -m; }
		if (n > 1) assert(lp[n] == sp);
		assert(phi[n] == ph && mu[n] == m);
		if (n > 1 && lp[n] == n) cnt++;
		if (n > 20000 && n < LIM - 20000) n += 97; // spot check the middle
	}
	assert(sz(pr) == 78498);
	cout << "Tests passed!" << endl;
}
