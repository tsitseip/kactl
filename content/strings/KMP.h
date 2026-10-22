/**
 * Author: Johan Sannemo
 * Date: 2016-12-15
 * License: CC0
 * Description: pi[x] computes the length of the longest prefix of s that ends at x,
 * other than s[0...x] itself (abacaba -> 0010123).
 * Can be used to find all occurrences of a string.
 * Usage: vector<int> p = pi(s); vector<int> at = match(text, pat); // start positions
 * Time: O(n)
 * Status: Tested on kattis:stringmatching
 */
#pragma once

vector<int> pi(const string& s) {
	vector<int> p(s.size());
	for (int i = 1; i < s.size(); i++) {
		int g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}

vector<int> match(const string& s, const string& pat) {
	vector<int> p = pi(pat + '\0' + s), res;
	for (int i = (int)p.size()-(int)s.size(); i < p.size(); i++)
		if (p[i] == pat.size())
			res.push_back(i - 2 * (int)pat.size());
	return res;
}
