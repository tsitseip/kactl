/**
 * Author: Simon Lindholm
 * Date: 2017-05-11
 * License: CC0
 * Source: folklore
 * Description: Computes sums a[i,j] for all i<I, j<J, and increases single elements a[i,j].
 *  Requires that the elements to be updated are known in advance (call fakeUpdate() before init()).
 * Usage: FT2 f(X); for each future update: f.fakeUpdate(x, y);
 *  f.init(); f.update(x, y, d); f.query(x, y); // i<x, j<y
 * Time: $O(\log^2 N)$. (Use persistent segment trees for $O(\log N)$.)
 * Status: stress-tested
 */
#pragma once

#include "FenwickTree.h"

struct FT2 {
	vector<vector<int>> ys; vector<FT> ft;
	FT2(int limx) : ys(limx) {}
	void fakeUpdate(int x, int y) {
		for (; x < (int)ys.size(); x |= x + 1) ys[x].push_back(y);
	}
	void init() {
		for (vector<int>& v : ys)
			sort(v.begin(), v.end()), ft.emplace_back(v.size());
	}
	int ind(int x, int y) {
		return (int)(lower_bound(ys[x].begin(), ys[x].end(), y) -
			ys[x].begin());
	}
	void update(int x, int y, ll dif) {
		for (; x < (int)ys.size(); x |= x + 1)
			ft[x].update(ind(x, y), dif);
	}
	ll query(int x, int y) {
		ll sum = 0;
		for (; x; x &= x - 1)
			sum += ft[x-1].query(ind(x-1, y));
		return sum;
	}
};
