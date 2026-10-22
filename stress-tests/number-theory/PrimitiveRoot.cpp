#include "../utilities/template.h"

#include "../../content/number-theory/PrimitiveRoot.h"

int main() {
	rep(p,2,3000) {
		bool prime = true; for (int d = 2; d * d <= p; d++) if (p % d == 0) prime = false;
		if (!prime) continue;
		ll g = primitiveRoot(p);
		// brute: smallest g whose order is p-1
		ll want = -1;
		for (ll h = 1; h < p && want < 0; h++) {
			ll x = 1; int ord = 0;
			do { x = x * h % p; ord++; } while (x != 1);
			if (ord == p - 1) want = h;
		}
		assert(g == want);
	}
	assert(primitiveRoot(998244353) == 3);
	assert(primitiveRoot(1000000007) == 5);
	cout << "Tests passed!" << endl;
}
