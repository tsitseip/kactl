#include "../utilities/template.h"

#define MOD_SET
const ll mod = 5;
#include "../../content/numerical/SolveLinearMod.h"

int main() {
	srand(83);
	rep(it,0,20000) {
		int n = rand() % 4 + 1, m = rand() % 4 + 1;
		vector<vector<ll>> A(n, vector<ll>(m)); vector<ll> b(n), x(m);
		for (auto& r : A) for (ll& v : r) v = rand() % mod;
		for (ll& v : b) v = rand() % mod;
		auto A0 = A; auto b0 = b;
		int cnt = 0, total = 1; rep(i,0,m) total *= mod;
		rep(code,0,total) { // brute force all x
			vector<ll> y(m); int c = code; rep(i,0,m) y[i] = c % mod, c /= mod;
			bool ok = true; rep(i,0,n) { ll s = 0; rep(j,0,m) s += A0[i][j] * y[j]; if (s % mod != b0[i]) ok = false; }
			cnt += ok;
		}
		int r = solveLinearMod(A, b, x);
		if (!cnt) { assert(r == -1); continue; }
		ll pw = 1; rep(i,0,m-r) pw *= mod;
		assert(r >= 0 && pw == cnt);
		rep(i,0,n) { ll s = 0; rep(j,0,m) s += A0[i][j] * x[j]; assert(s % mod == b0[i]); }
	}
	cout << "Tests passed!" << endl;
}
