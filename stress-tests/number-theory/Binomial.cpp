#include "../utilities/template.h"

#define MOD_SET
const ll mod = 7;
#define LIM_SET
const int LIM = 7;
#include "../../content/combinatorial/Binomial.h"

int main() {
	initFact();
	vector<vector<ll>> pas(60, vector<ll>(60));
	rep(n,0,60) { pas[n][0] = 1; rep(k,1,n+1) pas[n][k] = (pas[n-1][k-1] + pas[n-1][k]) % mod; }
	rep(n,0,60) rep(k,-2,62) {
		ll want = k < 0 || k > n ? 0 : pas[n][k];
		assert(lucas(n, max<int>(k, 0)) == (k < 0 ? lucas(n, 0) : want));
		if (n < mod) assert(C(n, k) == want);
	}
	cout << "Tests passed!" << endl;
}
