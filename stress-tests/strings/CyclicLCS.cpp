#include "../utilities/template.h"

#include "../../content/strings/CyclicLCS.h"

int slow(const string& a, const string& b) {
	vector<vi> d(sz(a)+1, vi(sz(b)+1));
	rep(i,0,sz(a)) rep(j,0,sz(b)) d[i+1][j+1] = a[i] == b[j] ? d[i][j] + 1 : max(d[i][j+1], d[i+1][j]);
	return d[sz(a)][sz(b)];
}
int main() {
	srand(73);
	rep(it,0,20000) {
		int n = rand() % 10 + 1, m = rand() % 10, k = rand() % 3 + 1;
		string a, b; rep(i,0,n) a += char('a' + rand() % k); rep(i,0,m) b += char('a' + rand() % k);
		int best = 0; rep(r,0,n) best = max(best, slow(a.substr(r) + a.substr(0, r), b));
		assert(cyclicLCS(a, b) == best);
	}
	cout << "Tests passed!" << endl;
}
