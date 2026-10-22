#include "../utilities/template.h"

#include "../../content/data-structures/XorBasis.h"

int main() {
	srand(9);
	rep(it,0,3000) {
		int bits = rand() % 8 + 1, n = rand() % 8;
		XorBasis B; vector<ll> a;
		rep(i,0,n) { ll x = rand() % (1 << bits); a.push_back(x); B.insert(x); }
		set<ll> all{0};
		for (ll x : a) { set<ll> nw = all; for (ll y : all) nw.insert(x ^ y); all = nw; }
		assert(sz(all) == (1 << B.rank));
		vector<ll> v(all.begin(), all.end());
		rep(k,0,sz(v)) assert(B.kth(k) == v[k]);
		rep(x,0,1 << bits) assert(B.contains(x) == (bool)all.count(x));
		ll q = rand() % (1 << bits), mx = 0;
		for (ll y : v) mx = max(mx, q ^ y);
		assert(B.maxXor(q) == mx);
	}
	XorBasis B; assert(B.insert(1LL << 62)); assert(!B.insert(1LL << 62)); assert(B.maxXor() == 1LL << 62);
	cout << "Tests passed!" << endl;
}
