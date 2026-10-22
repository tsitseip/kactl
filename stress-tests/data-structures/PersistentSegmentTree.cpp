#include "../utilities/template.h"

#include "../../content/data-structures/PersistentSegmentTree.h"

int main() {
	srand(7);
	rep(it,0,500) {
		int n = rand() % 30 + 1, N = rand() % 30;
		vi a(N); for (int& x : a) x = rand() % n;
		PST t(n); vi root = {0};
		for (int x : a) root.push_back(t.add(root.back(), x, 1));
		rep(l,0,N+1) rep(r,l,N+1) {
			vi b(a.begin() + l, a.begin() + r); sort(all(b));
			rep(k,0,r-l) assert(t.kth(root[l], root[r], k) == b[k]);
			int lo = rand() % n, hi = rand() % (n + 1);
			int c = 0; rep(i,l,r) c += lo <= a[i] && a[i] < hi;
			assert(t.query(root[r], lo, hi) - t.query(root[l], lo, hi) == (lo < hi ? c : 0));
		}
		// versions with arbitrary point adds, branching history
		vector<vector<ll>> val = {vector<ll>(n)}; vi rt = {0};
		rep(op,0,50) {
			int v = rand() % sz(rt), p = rand() % n; ll x = rand() % 21 - 10;
			rt.push_back(t.add(rt[v], p, x));
			val.push_back(val[v]); val.back()[p] += x;
			int w = rand() % sz(rt), lo = rand() % n, hi = lo + rand() % (n - lo + 1);
			ll s = 0; rep(i,lo,hi) s += val[w][i];
			assert(t.query(rt[w], lo, hi) == s);
		}
	}
	cout << "Tests passed!" << endl;
}
