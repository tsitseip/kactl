#include "../utilities/template.h"

#include "../../content/graph/MinMeanCycle.h"

int main() {
	srand(23);
	rep(it,0,3000) {
		int n = rand() % 6 + 1, m = rand() % 12;
		vector<array<ll, 3>> eds;
		rep(i,0,m) eds.push_back({rand() % n, rand() % n, rand() % 21 - 10});
		double best = 1e18;
		// enumerate simple cycles through DFS (min mean is attained by a simple cycle)
		vector<bool> on(n);
		function<void(int, int, ll, int)> go = [&](int s, int v, ll w, int len) {
			for (auto [a, b, c] : eds) if (a == v) {
				if (b == s) best = min(best, double(w + c) / (len + 1));
				else if (b > s && !on[b]) { on[b] = 1; go(s, b, w + c, len + 1); on[b] = 0; }
			}
		};
		rep(s,0,n) { on[s] = 1; go(s, s, 0, 0); on[s] = 0; }
		double got = minMeanCycle(n, eds);
		assert(abs(got - best) < 1e-9 || (best > 1e17 && got > 1e17));
	}
	cout << "Tests passed!" << endl;
}
