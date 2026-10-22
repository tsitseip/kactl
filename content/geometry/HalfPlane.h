/**
 * Author: Claude (adapted from cp-algorithms and Bohdan's library)
 * Date: 2026-10-18
 * License: CC0
 * Source: https://cp-algorithms.com/geometry/halfplane-intersection.html
 * Description: Intersection of half-planes; each is a directed line
 *  $s \to e$ and keeps its left side. Returns the vertices of the convex
 *  result in ccw order, or empty if the intersection is empty or
 *  degenerate (zero area). If it may be unbounded, add the four sides of
 *  a big bounding box. Needs T = double.
 * Usage: vector<array<P,2>> h = {{P(0,0), P(1,0)}, ...};
 *  vector<P> poly = halfPlanes(h);
 * Time: O(n \log n)
 * Status: stress-tested
 */
#pragma once

#include "Point.h"

typedef array<P, 2> HP;
vector<P> halfPlanes(vector<HP> h) {
	const double eps = 1e-9;
	auto dir = [](const HP& a) { return a[1] - a[0]; };
	auto out = [&](const HP& a, P p) { // p strictly right of a
		return dir(a).cross(p - a[0]) < -eps; };
	auto inter = [&](const HP& a, const HP& b) {
		P d = dir(a), e = dir(b);
		return a[0] + d * ((b[0] - a[0]).cross(e) / d.cross(e)); };
	sort(h.begin(), h.end(), [&](const HP& a, const HP& b) {
		return dir(a).angle() < dir(b).angle(); });
	deque<HP> q;
	for (HP& l : h) {
		while ((int)q.size() > 1 &&
			out(l, inter(q.back(), q[(int)q.size() - 2])))
			q.pop_back();
		while ((int)q.size() > 1 && out(l, inter(q[0], q[1])))
			q.pop_front();
		if ((int)q.size() &&
			abs(dir(l).cross(dir(q.back()))) < eps) {
			if (dir(l).dot(dir(q.back())) < 0) return {};
			if (out(l, q.back()[0])) q.pop_back();
			else continue;
		}
		q.push_back(l);
	}
	while ((int)q.size() > 2 &&
		out(q[0], inter(q.back(), q[(int)q.size() - 2])))
		q.pop_back();
	while ((int)q.size() > 2 && out(q.back(), inter(q[0], q[1])))
		q.pop_front();
	if ((int)q.size() < 3) return {};
	vector<P> res; double A = 0;
	for (int i = 0; i < q.size(); i++)
		res.push_back(inter(q[i], q[(i + 1) % (int)q.size()]));
	for (int i = 0; i < res.size(); i++)
		A += res[i].cross(res[(i + 1) % (int)res.size()]);
	if (A < eps) return {}; // empty sets can collapse to a point
	return res;
}
