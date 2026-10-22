#include "../utilities/template.h"

#include "../../content/combinatorial/Binomial.h"

int main() {
	initFact();
	vector<vector<ll>> pas(1001, vector<ll>(1001));
	rep(n,0,1001) { pas[n][0] = 1; rep(k,1,n+1) pas[n][k] = (pas[n-1][k-1] + pas[n-1][k]) % mod; }
	rep(n,0,1001) rep(k,-1,n+2) assert(C(n, k) == (k < 0 || k > n ? 0 : pas[n][k]));
	assert(C(LIM-1, 1) == LIM-1);
	cout << "Tests passed!" << endl;
}
