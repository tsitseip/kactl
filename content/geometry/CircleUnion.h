/**
 * Author: Claude (adapted from foreverbell's cheat sheet)
 * Date: 2026-10-18
 * License: CC0
 * Source: https://github.com/foreverbell/acm-icpc-cheat-sheet
 * Description: Area of the union of circles. For each circle, the arcs
 *  not covered by other circles form the boundary of the union; their
 *  area is summed with Green's theorem
 *  ($\frac12 \oint x\,dy - y\,dx$ over each arc). Duplicate circles are
 *  handled. Needs T = double.
 * Usage: double A = circleUnion(centers, radii);
 * Time: O(n^2 \log n)
 * Status: stress-tested
 */
#pragma once

#include "Point.h"

double circleUnion(vector<P>& c, vector<double>& r) {
	int n = c.size(); double res = 0, eps = 1e-9;
	auto arc = [&](int i, double a, double b) {
		return (r[i] * r[i] * (b - a) + r[i] * (c[i].x * (sin(b) -
			sin(a)) - c[i].y * (cos(b) - cos(a)))) / 2; };
	for (int i = 0; i < n; i++) {
		vector<pair<double, double>> cov; bool inside = 0;
		for (int j = 0; j < n; j++) if (j != i) {
			P d = c[j] - c[i]; double D = d.dist();
			if (D + r[i] < r[j] + eps && (r[i] < r[j] - eps || j<i))
				{ inside = 1; break; } // circle i is covered by j
			if (D + r[j] < r[i] + eps || D > r[i] + r[j] - eps)
				continue; // j inside i, or disjoint
			double a = d.angle(), w = acos(max(-1.0, min(1.0,
				(r[i]*r[i] + D*D - r[j]*r[j]) / (2*r[i]*D))));
			double lo = a - w, hi = a + w;
			if (lo < -M_PI) cov.push_back({lo + 2*M_PI, M_PI}),
				lo = -M_PI;
			if (hi > M_PI) cov.push_back({-M_PI, hi - 2*M_PI}),
				hi = M_PI;
			cov.push_back({lo, hi});
		}
		if (inside) continue;
		sort(cov.begin(), cov.end());
		double cur = -M_PI;
		for (auto [lo, hi] : cov) {
			if (lo > cur) res += arc(i, cur, lo);
			cur = max(cur, hi);
		}
		if (cur < M_PI) res += arc(i, cur, M_PI);
	}
	return res;
}
