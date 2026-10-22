#include "../utilities/template.h"

#include "../../content/various/SlopeTrick.h"

const int K = 200; // brute force domain [-K, K]
int main() {
	srand(13);
	rep(it,0,3000) {
		SlopeTrick s; vector<ll> f(2*K+1, 0);
		auto at = [&](ll x) -> ll& { return f[x + K]; };
		int ops = rand() % 12;
		rep(o,0,ops) {
			int ty = rand() % 6; ll a = rand() % 21 - 10;
			if (ty == 0) { s.addXA(a); for (ll x = -K; x <= K; x++) at(x) += max(0LL, x - a); }
			if (ty == 1) { s.addAX(a); for (ll x = -K; x <= K; x++) at(x) += max(0LL, a - x); }
			if (ty == 2) { s.addAbs(a); for (ll x = -K; x <= K; x++) at(x) += abs(x - a); }
			if (ty == 3) { s.prefMin(); for (ll x = -K+1; x <= K; x++) at(x) = min(at(x), at(x-1)); }
			if (ty == 4) { s.sufMin(); for (ll x = K-1; x >= -K; x--) at(x) = min(at(x), at(x+1)); }
			if (ty == 5) {
				ll lo = rand() % 7 - 3, hi = lo + rand() % 4;
				s.shift(lo, hi);
				vector<ll> g(2*K+1, LLONG_MAX / 4);
				for (ll x = -K; x <= K; x++) for (ll y = x - hi; y <= x - lo; y++)
					if (-K <= y && y <= K) g[x + K] = min(g[x + K], at(y));
				f = g;
			}
		}
		// compare min and argmin interval on the central part of the domain
		ll mn = LLONG_MAX; for (ll x = -K/2; x <= K/2; x++) mn = min(mn, at(x));
		assert(mn == s.mn);
		ll l = max(s.topL(), (ll)-K/2), r = min(s.topR(), (ll)K/2);
		for (ll x = -K/2; x <= K/2; x++) assert((at(x) == mn) == (l <= x && x <= r));
	}
	// classic: min cost to make a non-decreasing
	rep(it,0,500) {
		int n = rand() % 7 + 1; vi a(n); for (int& x : a) x = rand() % 10;
		SlopeTrick s; for (int x : a) s.addAbs(x), s.prefMin();
		vector<ll> dp(10, 0); // dp over last value
		for (int x : a) { vector<ll> nd(10); ll best = LLONG_MAX; rep(v,0,10) best = min(best, dp[v]), nd[v] = best + abs(x - v); dp = nd; }
		assert(*min_element(all(dp)) == s.mn);
	}
	cout << "Tests passed!" << endl;
}
