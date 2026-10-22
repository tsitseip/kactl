#include "../utilities/template.h"

#include "../../content/data-structures/PersistentXorTrie.h"

int main() {
	srand(11);
	rep(it,0,300) {
		int n = rand() % 40 + 1; vi a(n);
		for (int& x : a) x = rand() % 2 ? rand() % 64 : rand() & ((1 << 30) - 1);
		XorTrie t; for (int x : a) t.add(x);
		rep(q,0,200) {
			int l = rand() % n, r = l + 1 + rand() % (n - l), x = rand() & ((1 << 30) - 1);
			int mx = 0; rep(i,l,r) mx = max(mx, a[i] ^ x);
			assert(t.maxXor(l, r, x) == mx);
		}
	}
	cout << "Tests passed!" << endl;
}
