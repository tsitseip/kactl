#include "../utilities/template.h"

#include "../../content/data-structures/OrderStatisticTree.h"

int main() {
	example();
	srand(101);
	Tree t; set<int> s;
	rep(it,0,20000) {
		int x = rand() % 1000;
		if (rand() % 3) t.insert(x), s.insert(x); else t.erase(x), s.erase(x);
		int q = rand() % 1000;
		assert((int)t.order_of_key(q) == (int)distance(s.begin(), s.lower_bound(q)));
		if (!s.empty()) { int k = rand() % sz(s); assert(*t.find_by_order(k) == *next(s.begin(), k)); }
	}
	cout << "Tests passed!" << endl;
}
