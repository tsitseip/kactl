/**
 * Author: Claude (adapted from Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: https://arxiv.org/abs/1506.04862 (eertree)
 * Description: Palindromic tree (eertree) of a lowercase string: one
 *  node per distinct palindromic substring (nodes 2.., so \#distinct =
 *  (int)t.size()$-2$). Node 0 = imaginary root (len $-1$), 1 = empty string.
 *  link = longest proper palindromic suffix. After add(c), last = node
 *  of the longest palindrome ending at the new character. After count(),
 *  occ = \#occurrences of the node's palindrome in the whole string.
 * Usage: Eertree e; for (char c : s) e.add(c); e.count();
 * Time: O(n)
 * Status: stress-tested
 */
#pragma once

struct Eertree {
	struct N { int len, link, occ = 0; array<int, 26> nx{}; };
	vector<N> t{{-1, 0}, {0, 0}}; string s; int last = 1;
	int get(int v) { // longest pal. suffix of v, extendable
		int i = (int)s.size() - 1;
		while (i - t[v].len < 1 || s[i - t[v].len - 1] != s[i])
			v = t[v].link;
		return v;
	}
	void add(char ch) {
		s += ch;
		int c = ch - 'a', v = get(last);
		if (!t[v].nx[c]) {
			int w = t[get(t[v].link)].nx[c];
			t.push_back({t[v].len + 2, w ? w : 1});
			t[v].nx[c] = (int)t.size() - 1;
		}
		last = t[v].nx[c]; t[last].occ++;
	}
	void count() { // call once, after all add()
		for (int v = (int)t.size() - 1; v > 1; v--)
			t[t[v].link].occ += t[v].occ;
	}
};
