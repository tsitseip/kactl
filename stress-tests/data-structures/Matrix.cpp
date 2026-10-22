#include "../utilities/template.h"

#include "../../content/data-structures/Matrix.h"

int main() {
	srand(1);
	rep(it,0,2000) {
		int n = rand() % 5 + 1, p = rand() % 30;
		Mat A(n, vector<ll>(n));
		for (auto& r : A) for (ll& x : r) x = rand() % 3 == 0 ? 0 : (ll)rand() * rand() % mod;
		Mat R(n, vector<ll>(n));
		rep(i,0,n) R[i][i] = 1;
		rep(k,0,p) { // naive
			Mat C(n, vector<ll>(n));
			rep(i,0,n) rep(j,0,n) rep(l,0,n) C[i][j] = (C[i][j] + R[i][l] * A[l][j]) % mod;
			R = C;
		}
		assert(pw(A, p) == R);
	}
	// Fibonacci + rectangular product
	Mat F = pw({{1,1},{1,0}}, 90);
	ll a = 0, b = 1;
	rep(i,0,90) { ll c = (a + b) % mod; a = b; b = c; }
	assert(F[0][1] == a);
	Mat v = Mat{{1,1},{1,0}} * Mat{{1},{0}};
	assert(v == (Mat{{1},{1}}));
	cout << "Tests passed!" << endl;
}
