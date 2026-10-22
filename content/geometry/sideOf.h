/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description: Returns where $p$ is as seen from $s$ towards $e$. 1/0/-1 $\Leftrightarrow$ left/on line/right.
 * If the optional argument $eps$ is given 0 is returned if $p$ is within distance $eps$ from the line.
 * It uses products in intermediate steps so watch out for overflow if using int or long long.
 * Usage:
 * 	bool left = sideOf(p1,p2,q)==1;
 * Status: tested
 */
#pragma once

#include "Point.h"

int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

int sideOf(P s, P e, P p, double eps) {
	auto a = (e-s).cross(p-s);
	double l = (e-s).dist()*eps;
	return (a > l) - (a < -l);
}
