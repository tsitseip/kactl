#include "../utilities/template.h"

#include "../../content/strings/PalindromicTree.h"

int main() {
	srand(61);
	rep(it,0,3000) {
		int n = rand() % 20, k = rand() % 3 + 1;
		string s; rep(i,0,n) s += char('a' + rand() % k);
		Eertree e; vi lastLen;
		for (char c : s) e.add(c), lastLen.push_back(e.t[e.last].len);
		e.count();
		map<string, int> occ;
		rep(i,0,n) rep(j,i+1,n+1) { string t = s.substr(i, j - i); if (t == string(t.rbegin(), t.rend())) occ[t]++; }
		assert(sz(e.t) - 2 == sz(occ));
		// longest palindrome ending at each position
		rep(i,0,n) { int best = 0; rep(j,0,i+1) { string t = s.substr(j, i - j + 1); if (t == string(t.rbegin(), t.rend())) { best = i - j + 1; break; } } assert(lastLen[i] == best); }
		// occurrence counts: reconstruct each node's palindrome via its first end position
		vi endPos(sz(e.t), -1);
		{ Eertree f; rep(i,0,n) { f.add(s[i]); if (endPos[f.last] < 0) endPos[f.last] = i; } }
		rep(v,2,sz(e.t)) { int L = e.t[v].len, i = endPos[v]; string t = s.substr(i - L + 1, L); assert(occ[t] == e.t[v].occ); }
	}
	cout << "Tests passed!" << endl;
}
