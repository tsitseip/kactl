/**
 * Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time.
 * Usage:
 *  RMQ rmq(values); // values is a vector<int>
 *  rmq.query(inclusive, exclusive);
 * Time: $O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
#pragma once

struct RMQ { // for ll / max: change vector<int>, int and min
	vector<vector<int>> jmp;
	RMQ(const vector<int>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= V.size(); pw *= 2, ++k) {
			jmp.emplace_back((int)V.size() - pw * 2 + 1);
			for (int j = 0; j < jmp[k].size(); j++)
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	int query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};
