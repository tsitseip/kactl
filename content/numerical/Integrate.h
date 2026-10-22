/**
 * Author: Simon Lindholm
 * Date: 2015-02-11
 * License: CC0
 * Source: Wikipedia
 * Description: Simple integration of a function over an interval using
 *  Simpson's rule. The error should be proportional to $h^4$, although in
 *  practice you will want to verify that the result is stable to desired
 *  precision when epsilon changes.
 * Usage: double I = quad(0, M_PI, [](double x) { return sin(x); }); // 2
 * Status: mostly untested
 */
#pragma once

double quad(double a, double b, function<double(double)> f,
		const int n = 1000) {
	double h = (b - a) / 2 / n, v = f(a) + f(b);
	for (int i = 1; i < n*2; i++)
		v += f(a + i*h) * (i&1 ? 4 : 2);
	return v * h / 3;
}
