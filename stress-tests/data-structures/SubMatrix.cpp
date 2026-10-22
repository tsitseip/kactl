#include "../utilities/template.h"

#include "../../content/data-structures/SubMatrix.h"

int main() {
	srand(103);
	rep(it,0,200) {
		int R = rand() % 8 + 1, C = rand() % 8 + 1;
		vector<vi> v(R, vi(C)); for (auto& r : v) for (int& x : r) x = rand() % 2001 - 1000;
		SubMatrix m(v);
		rep(u,0,R+1) rep(d,u,R+1) rep(l,0,C+1) rep(r,l,C+1) {
			ll s = 0; rep(i,u,d) rep(j,l,r) s += v[i][j];
			assert(m.sum(u, l, d, r) == s);
		}
	}
	cout << "Tests passed!" << endl;
}
