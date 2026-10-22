/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description:\\
\begin{minipage}{75mm}
Returns the shortest distance between point p and the line segment from point s to e.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-10mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentDistance}
\end{minipage}
 * Usage: 
 * 	P a, b(2,2), p(1,1);
 * 	bool onSegment = segDist(a,b,p) < 1e-10;
 * Status: tested
 */
#pragma once

#include "Point.h"

double segDist(P s, P e, P p) { // works for T = ll too
	if (s==e) return (p-s).dist();
	P a = p-s, b = e-s;
	double d = (double)b.dist2();
	double t = min(d, max(.0, (double)a.dot(b)));
	return hypot(a.x*d-b.x*t, a.y*d-b.y*t)/d;
}
