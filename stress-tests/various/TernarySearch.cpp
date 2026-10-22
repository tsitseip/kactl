#include "../utilities/template.h"

#include "../../content/various/TernarySearch.h"

int main() {
	srand(107);
	rep(it,0,20000) {
		int n = rand() % 30 + 1, peak = rand() % n;
		vector<ll> a(n); a[peak] = 1000;
		for (int i = peak - 1; i >= 0; i--) a[i] = a[i+1] - 1 - rand() % 5; // strictly increasing up to peak
		for (int i = peak + 1; i < n; i++) a[i] = a[i-1] - rand() % 3;  // non-increasing after
		int got = ternSearch(0, n - 1, [&](int i) { return a[i]; });
		int want = max_element(all(a)) - a.begin();
		assert(got == want);
	}
	cout << "Tests passed!" << endl;
}
