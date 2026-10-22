#include "../utilities/template.h"

#include "../../content/various/IntervalCover.h"

int main() {
	srand(109);
	vi ex = cover({0, 10}, {{0, 4}, {3, 10}, {2, 5}});
	assert(sz(ex) == 2);
	rep(it,0,5000) {
		int n = rand() % 8; vector<pdd> I;
		rep(i,0,n) { int a = rand() % 11, b = rand() % 11; if (a > b) swap(a, b); I.push_back({a, b}); }
		int L = rand() % 10, R = L + 1 + rand() % (10 - L);
		vi got = cover({L, R}, I);
		int best = -1; // brute force smallest subset covering [L, R)
		rep(S,0,1 << n) {
			vector<pdd> v; rep(i,0,n) if (S >> i & 1) v.push_back(I[i]);
			sort(all(v)); double cur = L;
			for (auto [a, b] : v) if (a <= cur) cur = max(cur, b);
			if (cur >= R && (best < 0 || __builtin_popcount(S) < best)) best = __builtin_popcount(S);
		}
		if (best < 0) { assert(got.empty()); continue; }
		assert(sz(got) == best);
		vector<pdd> v; for (int i : got) v.push_back(I[i]);
		sort(all(v)); double cur = L; for (auto [a, b] : v) if (a <= cur) cur = max(cur, b);
		assert(cur >= R);
	}
	cout << "Tests passed!" << endl;
}
