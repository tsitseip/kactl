#include "../utilities/template.h"

#include "../../content/numerical/MultipointEval.h"

int main() {
	srand(97);
	rep(it,0,300) {
		int n = rand() % 60, k = rand() % 60 + 1;
		vl a(k); for (ll& x : a) x = (ll)rand() * rand() % mod;
		set<ll> used; vl xs;
		while (sz(xs) < n) { ll x = rand() % 2 ? rand() % 100 : (ll)rand() * rand() % mod; if (used.insert(x).second) xs.push_back(x); }
		vl y = multiEval(a, xs);
		rep(i,0,n) { ll v = 0; for (int j = k; j--;) v = (v * xs[i] + a[j]) % mod; assert(y[i] == v); }
		vl ys(n); for (ll& v : ys) v = rand() % mod;
		vl p = interpolate(xs, ys);
		assert(sz(p) == n);
		vl back = multiEval(p, xs);
		assert(back == ys);
	}
	cout << "Tests passed!" << endl;
}
