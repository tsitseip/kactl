#include "../utilities/template.h"
typedef ll T;
#define POINT_T

#include "../../content/geometry/ConvexHull.h"
#include "../../content/geometry/MinkowskiSum.h"

int main() {
	srand(43);
	rep(it,0,20000) {
		vector<P> A, B;
		int n = rand() % 8 + 1, m = rand() % 8 + 1;
		rep(i,0,n) A.push_back(P(rand() % 11 - 5, rand() % 11 - 5));
		rep(i,0,m) B.push_back(P(rand() % 11 - 5, rand() % 11 - 5));
		A = convexHull(A), B = convexHull(B);
		vector<P> all;
		for (P a : A) for (P b : B) all.push_back(a + b);
		auto want = convexHull(all), got = minkowski(A, B);
		int k = sz(got);
		rep(i,0,k) if (k > 2) assert(got[i].cross(got[(i+1)%k], got[(i+2)%k]) >= 0);
		auto g2 = convexHull(got);
		sort(all(want)); sort(all(g2));
		assert(want == g2);
	}
	cout << "Tests passed!" << endl;
}
