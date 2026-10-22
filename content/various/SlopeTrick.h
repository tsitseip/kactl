/**
 * Author: Claude (adapted from Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: https://codeforces.com/blog/entry/77298
 * Description: Maintains a convex piecewise linear function $f$
 *  (initially 0) as two heaps of breakpoints. mn = $\min f$, minimum
 *  attained on [topL(), topR()]. Operations: $f \mathrel{+}= \max(0, x-a)$,
 *  $\max(0, a-x)$, $|x-a|$; prefMin: $f(x) := \min_{y \le x} f(y)$;
 *  sufMin: $\min_{y \ge x}$; shift(a,b): $f(x) := \min_{x-b \le y \le x-a} f(y)$
 *  ($a \le b$; shift(a,a) translates $f$ right by a).
 *  Classic use: min $\sum |a_i - b_i|$ with $b$ non-decreasing:
 *  for each $a_i$: addAbs($a_i$), prefMin(); answer mn.
 * Usage: SlopeTrick s; for (ll a : v) s.addAbs(a), s.prefMin();
 *  ll best = s.mn; // min of f; argmin in [topL(), topR()]
 * Time: O(\log n) per operation
 * Status: stress-tested
 */
#pragma once

struct SlopeTrick {
	priority_queue<ll> L;
	priority_queue<ll, vector<ll>, greater<ll>> R;
	ll addL = 0, addR = 0, mn = 0, inf = LLONG_MAX / 4;
	ll topL() { return L.empty() ? -inf : L.top() + addL; }
	ll topR() { return R.empty() ? inf : R.top() + addR; }
	void pushL(ll x) { L.push(x - addL); }
	void pushR(ll x) { R.push(x - addR); }
	void addXA(ll a) { // f += max(0, x - a)
		mn += max(0LL, topL() - a);
		pushL(a); pushR(topL()); L.pop();
	}
	void addAX(ll a) { // f += max(0, a - x)
		mn += max(0LL, a - topR());
		pushR(a); pushL(topR()); R.pop();
	}
	void addAbs(ll a) { addXA(a), addAX(a); }
	void prefMin() { R = {}; }
	void sufMin() { L = {}; }
	void shift(ll a, ll b) { addL += a, addR += b; }
};
