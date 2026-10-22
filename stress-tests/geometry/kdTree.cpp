#include "../utilities/template.h"
typedef ll T;
#define POINT_T

#include "../../content/geometry/kdTree.h"

int main() {
	srand(127);
	rep(it,0,300) {
		int n = rand() % 200 + 1;
		vector<P> pts; rep(i,0,n) pts.push_back(P(rand() % 1000, rand() % 1000));
		KDTree kd(pts);
		rep(q,0,50) {
			P p(rand() % 1200 - 100, rand() % 1200 - 100);
			ll best = LLONG_MAX; for (P x : pts) best = min(best, (x - p).dist2());
			assert(kd.nearest(p).first == best);
		}
	}
	cout << "Tests passed!" << endl;
}
