/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: tinyKACTL
 * Description: Returns twice the signed area of a polygon.
 *  Clockwise enumeration gives negative area. Exact with T = ll.
 * Usage: T a2 = polygonArea2(poly); // twice the area, ccw > 0
 * Status: Stress-tested and tested on kattis:polygonarea
 */
#pragma once

#include "Point.h"

T polygonArea2(vector<P>& v) {
	T a = v.back().cross(v[0]);
	for (int i = 0; i < (int)v.size() - 1; i++)
		a += v[i].cross(v[i + 1]);
	return a;
}
