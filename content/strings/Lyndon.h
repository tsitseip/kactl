/**
 * Author: Claude (adapted from Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: https://cp-algorithms.com/string/lyndon_factorization.html
 * Description: Duval's algorithm: factors $s = w_1 w_2 \dots w_k$ into Lyndon
 *  words with $w_1 \ge w_2 \ge \dots \ge w_k$ (a Lyndon word is strictly
 *  smaller than each of its proper suffixes). Returns the start index
 *  of every factor. The minimal rotation of $s$ starts at the last
 *  factor start $< n$ of duval(s+s) (or use MinRotation).
 * Usage: vector<int> st = duval(s); // factor i = s[st[i] .. st[i+1])
 * Time: O(n)
 * Status: stress-tested
 */
#pragma once

vector<int> duval(const string& s) {
	int n = s.size(), i = 0; vector<int> res;
	while (i < n) {
		int j = i + 1, k = i;
		for (; j < n && s[k] <= s[j]; j++)
			k = s[k] < s[j] ? i : k + 1;
		for (; i <= k; i += j - k) res.push_back(i);
	}
	return res;
}
