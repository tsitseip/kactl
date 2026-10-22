#include "../utilities/template.h"

#include "../../content/strings/BitsetLCS.h"

int slow(const string& a, const string& b) {
	vector<vi> d(sz(a)+1, vi(sz(b)+1));
	rep(i,0,sz(a)) rep(j,0,sz(b)) d[i+1][j+1] = a[i] == b[j] ? d[i][j] + 1 : max(d[i][j+1], d[i+1][j]);
	return d[sz(a)][sz(b)];
}
int main() {
	srand(71);
	rep(it,0,4000) {
		int n = rand() % 200, m = rand() % (it % 10 ? 70 : 300), k = rand() % 4 + 1;
		string a, b; rep(i,0,n) a += char('a' + rand() % k); rep(i,0,m) b += char('a' + rand() % k);
		assert(lcs(a, b) == slow(a, b));
	}
	string a(2000, 'x'), b(1999, 'x'); assert(lcs(a, b) == 1999);
	cout << "Tests passed!" << endl;
}
