/**
 * Author: Claude (adapted from Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: https://cp-algorithms.com/string/suffix-automaton.html
 * Description: Suffix automaton: smallest DFA accepting all substrings
 *  of $s$ ($\le 2n$ states). Each state is a class of substrings with the
 *  same set of end positions; len = longest of them, link = suffix link
 *  (a tree). Substring $t$ occurs iff walking nx from 0 succeeds.
 *  \#distinct substrings $= \sum_{v>0}$ len[v] $-$ len[link[v]].
 *  After count(), occ[v] = \#occurrences of each string of state $v$.
 *  LCS of $s$, $t$: walk $t$, on a missing edge follow links (shrink
 *  the current length to len), track the max length.
 * Usage: SuffixAutomaton sa(s); sa.count(); int v = 0;
 *  for (char c : t) v = sa.st[v].nx[c]; // check sa.st[v].nx.count(c)!
 * Time: O(n \log \Sigma)
 * Status: stress-tested
 */
#pragma once

struct SuffixAutomaton {
	struct St {
		int len = 0, link = -1, occ = 0; map<char, int> nx;
	};
	vector<St> st{St()}; int last = 0;
	SuffixAutomaton(const string& s) { for (char c : s) add(c); }
	void add(char c) {
		int cur = st.size(), p = last;
		st.push_back({st[last].len + 1, 0, 1, {}});
		for (; p >= 0 && !st[p].nx.count(c); p = st[p].link)
			st[p].nx[c] = cur;
		if (p >= 0) {
			int q = st[p].nx[c];
			if (st[p].len + 1 == st[q].len) st[cur].link = q;
			else {
				int cl = st.size();
				st.push_back(st[q]);
				st[cl].len = st[p].len + 1, st[cl].occ = 0;
				for (; p >= 0 && st[p].nx[c] == q; p = st[p].link)
					st[p].nx[c] = cl;
				st[q].link = st[cur].link = cl;
			}
		}
		last = cur;
	}
	void count() { // occ = occurrences (call once)
		vector<int> ord(st.size());
		iota(ord.begin(), ord.end(), 0);
		sort(ord.begin(), ord.end(), [&](int a, int b) {
			return st[a].len > st[b].len; });
		for (int v : ord) if (v) st[st[v].link].occ += st[v].occ;
	}
	ll distinct() {
		ll r = 0;
		for (int v = 1; v < st.size(); v++)
			r += st[v].len - st[st[v].link].len;
		return r;
	}
};
