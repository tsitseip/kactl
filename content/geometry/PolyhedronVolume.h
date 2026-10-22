/**
 * Author: Mattias de Zalenski
 * Date: 2002-11-04
 * Description: Magic formula for the volume of a polyhedron. Faces should point outwards.
 * Works directly on the output of hull3d.
 * Usage: double V = signedPolyVolume(pts, hull3d(pts));
 * Status: tested
 */
#pragma once

#include "3dHull.h"

double signedPolyVolume(const vector<P3>& p,
		const vector<F>& tri) {
	double v = 0;
	for (auto i : tri) v += p[i.a].cross(p[i.b]).dot(p[i.c]);
	return v / 6;
}
