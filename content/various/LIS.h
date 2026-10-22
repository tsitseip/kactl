/**
 * Author: Johan Sannemo
 * License: CC0
 * Description: Compute indices for the longest increasing subsequence.
 * Usage: vector<int> idx = lis(a); // a[idx[0]] < a[idx[1]] < ...
 * Time: $O(N \log N)$
 * Status: Tested on kattis:longincsubseq, stress-tested
 */
#pragma once

vector<int> lis(const vector<int>& S) { // ll: change int here
	if (S.empty()) return {};
	vector<int> prev(S.size());
	typedef pair<int, int> p; // and the first int here
	vector<p> res;
	for (int i = 0; i < S.size(); i++) {
		// change 0 -> i for longest non-decreasing subsequence
		auto it = lower_bound(res.begin(), res.end(), p{S[i], 0});
		if (it == res.end()) res.emplace_back(), it = res.end()-1;
		*it = {S[i], i};
		prev[i] = it == res.begin() ? 0 : (it-1)->second;
	}
	int L = res.size(), cur = res.back().second;
	vector<int> ans(L);
	while (L--) ans[L] = cur, cur = prev[cur];
	return ans;
}
