/**
 * Author: Lucian Bicsi
 * Date: 2015-06-25
 * License: GNU Free Documentation License 1.2
 * Source: csacademy
 * Description: Transform to a basis with fast convolutions of the form
 * $\displaystyle c[z] = \sum\nolimits_{z = x \oplus y} a[x] \cdot b[y]$,
 * where $\oplus$ is one of AND, OR, XOR. The size of $a$ must be a power of two.
 * Keep only the line(s) marked with your operation.
 * Usage: vector<int> c = conv(a, b); // sz power of 2; AND (or OR/XOR)
 * Time: O(N \log N)
 * Status: stress-tested
 */
#pragma once

void FST(vector<int>& a, bool inv) {
	for (int n = a.size(), s = 1; s < n; s *= 2)
		for (int i = 0; i < n; i++) if (!(i & s)) {
			int &u = a[i], &v = a[i + s], x = u, y = v;
			if (inv) u = y - x, v = x; else u = y, v = x + y; // AND
			// if (inv) u = y, v = x - y; else u = x + y, v = x; // OR /// include-line
			// u = x + y, v = x - y; // XOR /// include-line
		}
	// if (inv) for (int& x : a) x /= (int)a.size(); // XOR only /// include-line
}
vector<int> conv(vector<int> a, vector<int> b) {
	FST(a, 0); FST(b, 0);
	for (int i = 0; i < a.size(); i++) a[i] *= b[i];
	FST(a, 1); return a;
}
