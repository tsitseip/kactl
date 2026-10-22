/**
 * Author: Claude (adapted from cp-algorithms and Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: https://cp-algorithms.com/geometry/minkowski.html
 * Description: Minkowski sum $\{a + b : a \in A, b \in B\}$ of two convex
 *  polygons given in ccw order (e.g. from convexHull). The result is ccw
 *  and may contain collinear points. Uses: distance between convex
 *  polygons = distance from origin to $A + (-B)$; collision of a moving
 *  convex shape with an obstacle.
 * Usage: vector<P> s = minkowski(convexHull(a), convexHull(b));
 * Time: O(n + m)
 * Status: stress-tested
 */
#pragma once

#include "Point.h"

vector<P> minkowski(vector<P> a, vector<P> b) {
	auto fix = [](vector<P>& v) { // start at lowest point, pad
		auto low = [](P p, P q) {
			return tie(p.y, p.x) < tie(q.y, q.x); };
		rotate(v.begin(), min_element(v.begin(), v.end(), low),
			v.end());
		v.push_back(v[0]); v.push_back(v[1]);
	};
	fix(a); fix(b);
	vector<P> res;
	for (int i = 0, j = 0;
		i < (int)a.size() - 2 || j < (int)b.size() - 2;) {
		res.push_back(a[i] + b[j]);
		auto c = (a[i+1] - a[i]).cross(b[j+1] - b[j]);
		if (c >= 0 && i < (int)a.size() - 2) i++;
		if (c <= 0 && j < (int)b.size() - 2) j++;
	}
	return res;
}
