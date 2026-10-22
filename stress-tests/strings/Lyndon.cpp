#include "../utilities/template.h"

#include "../../content/strings/Lyndon.h"

bool lyndon(const string& w) { rep(i,1,sz(w)) if (w.substr(i) <= w) return false; return !w.empty(); }

int main() {
	srand(67);
	rep(it,0,20000) {
		int n = rand() % 15, k = rand() % 3 + 1;
		string s; rep(i,0,n) s += char('a' + rand() % k);
		vi st = duval(s); st.push_back(n);
		if (n == 0) { assert(sz(st) == 1); continue; }
		assert(st[0] == 0);
		string prev;
		rep(i,0,sz(st)-1) {
			string w = s.substr(st[i], st[i+1] - st[i]);
			assert(lyndon(w));
			if (i) assert(prev >= w);
			prev = w;
		}
		// min rotation via duval(s+s)
		string ss = s + s; vi f = duval(ss); int r = 0; for (int x : f) if (x < n) r = x;
		string best = s; rep(i,0,n) best = min(best, ss.substr(i, n));
		assert(ss.substr(r, n) == best);
	}
	cout << "Tests passed!" << endl;
}
