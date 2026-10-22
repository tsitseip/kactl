/**
 * Author: Simon Lindholm
 * Date: 2016-03-22
 * License: CC0
 * Source: hacKIT, NWERC 2015
 * Description: A set (not multiset!) with support for finding the n'th
 * element, and finding the index of an element.
 * To get a map, change \texttt{null\_type} to the value type.
 * For a multiset, store pairs (value, unique id).
 * Usage: Tree t; t.insert(x); t.order_of_key(x); // count < x
 *  *t.find_by_order(k); // k-th smallest, 0-based
 * Time: O(\log N)
 */
#pragma once

#include <bits/extc++.h> /** keep-include */ // above #define int

using namespace __gnu_pbds;

// key type int; for pairs/ll replace both ints
typedef tree<int, null_type, less<int>, rb_tree_tag,
		tree_order_statistics_node_update> Tree;

void example() {
	Tree t, t2; t.insert(8);
	auto it = t.insert(10).first;
	assert(it == t.lower_bound(9));
	assert(t.order_of_key(10) == 1);
	assert(t.order_of_key(11) == 2);
	assert(*t.find_by_order(0) == 8);
	t.join(t2); // assuming T < T2 or T > T2, merge t2 into t
}
