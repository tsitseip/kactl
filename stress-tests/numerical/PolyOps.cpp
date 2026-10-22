#include "../utilities/template.h"

#include "../../content/numerical/PolyOps.h"

vl naiveMul(const vl& a, const vl& b, int n) {
	vl c(n); rep(i,0,min(n, sz(a))) rep(j,0,min(n - i, sz(b))) c[i+j] = (c[i+j] + a[i] * b[j]) % mod;
	return c;
}
int main() {
	srand(89);
	rep(it,0,400) {
		int n = rand() % 70 + 1, len = rand() % 80 + 1;
		vl a(len); for (ll& x : a) x = (ll)rand() * rand() % mod;
		if (!a[0]) a[0] = 1;
		// inverse
		vl b = polyInv(a, n), c = naiveMul(a, b, n);
		rep(i,0,n) assert(c[i] == (i == 0));
		// log/exp with a[0] = 1 / 0
		vl a1 = a; a1[0] = 1;
		vl L = polyLog(a1, n), E = polyExp(L, n);
		rep(i,0,min(n, sz(a1))) assert(E[i] == a1[i]);
		rep(i,sz(a1),n) assert(E[i] == 0);
		// derivative check of log: (log a)' * a = a'
		vl lhs = naiveMul(deriv(L), a1, n - 1), da = deriv(a1); da.resize(max<int>(0, n - 1));
		assert(lhs == da);
		// sqrt
		vl S = polySqrt(a1, n), S2 = naiveMul(S, S, n);
		rep(i,0,n) assert(S2[i] == (i < sz(a1) ? a1[i] : 0));
		// division
		int m = rand() % 40 + 1; vl d(m); for (ll& x : d) x = rand() % mod; if (!d.back()) d.back() = 1;
		auto [q, r] = polyDiv(a, d);
		assert(sz(r) == min(sz(a), m - 1) || sz(a) < m);
		vl back = naiveMul(d, q, sz(a)); rep(i,0,sz(r)) back[i] = (back[i] + r[i]) % mod;
		if (sz(a) >= m) assert(back == a); else assert(r == a && q.empty());
	}
	cout << "Tests passed!" << endl;
}
