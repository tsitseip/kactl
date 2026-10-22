#include "../utilities/template.h"

#include "../../content/strings/SuffixAutomaton.h"

int main() {
	srand(59);
	rep(it,0,3000) {
		int n = rand() % 15, k = rand() % 3 + 1;
		string s; rep(i,0,n) s += char('a' + rand() % k);
		SuffixAutomaton sa(s);
		set<string> subs;
		rep(i,0,n) rep(j,i+1,n+1) subs.insert(s.substr(i, j - i));
		assert(sa.distinct() == sz(subs));
		assert(sz(sa.st) <= max<int>(1, 2 * n));
		sa.count();
		rep(q,0,20) {
			int len = rand() % 5 + 1; string t; rep(i,0,len) t += char('a' + rand() % k);
			int occ = 0; rep(i,0,n-len+1) occ += s.substr(i, len) == t;
			int v = 0; bool ok = true;
			for (char c : t) { if (!sa.st[v].nx.count(c)) { ok = false; break; } v = sa.st[v].nx[c]; }
			assert(ok == (occ > 0));
			if (ok) assert(sa.st[v].occ == occ);
		}
	}
	cout << "Tests passed!" << endl;
}
