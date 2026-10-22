#include "../utilities/template.h"

#include "../../content/graph/GeneralMatching.h"

int main() {
	srand(31);
	rep(it,0,20000) {
		int n = rand() % 13 + 1, m = rand() % 30;
		vector<vi> g(n); set<pii> E;
		rep(i,0,m) { int a = rand() % n, b = rand() % n; if (a == b) continue; g[a].push_back(b); g[b].push_back(a); E.insert({a, b}); E.insert({b, a}); }
		vi dp(1 << n, 0); // max matching on vertex subset
		rep(S,1,1 << n) {
			int v = __builtin_ctz(S); dp[S] = dp[S ^ (1 << v)];
			for (int u : g[v]) if (u != v && (S >> u & 1)) dp[S] = max(dp[S], 1 + dp[S ^ (1 << v) ^ (1 << u)]);
		}
		vi mt; int k = generalMatching(g, mt);
		assert(k == dp[(1 << n) - 1]);
		int cnt = 0;
		rep(v,0,n) if (mt[v] >= 0) { assert(mt[mt[v]] == v); assert(E.count({v, mt[v]})); cnt++; }
		assert(cnt == 2 * k);
	}
	cout << "Tests passed!" << endl;
}
