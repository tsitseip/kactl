#include "../utilities/template.h"

#include "../../content/geometry/CircleUnion.h"

// numeric: integrate length of union of vertical chords
double numeric(vector<P>& c, vector<double>& r) {
	int n = sz(c);
	vector<double> xs;
	rep(i,0,n) xs.push_back(c[i].x - r[i]), xs.push_back(c[i].x + r[i]);
	rep(i,0,n) rep(j,0,i) { // x of circle intersection points
		P d = c[j] - c[i]; double D = d.dist();
		if (D < 1e-12 || D > r[i] + r[j] || D < abs(r[i] - r[j])) continue;
		double a = (r[i]*r[i] - r[j]*r[j] + D*D) / (2*D), h = sqrt(max(0.0, r[i]*r[i] - a*a));
		P m = c[i] + d * (a / D), off = d.perp() * (h / D);
		xs.push_back((m + off).x); xs.push_back((m - off).x);
	}
	sort(all(xs));
	auto f = [&](double x) {
		vector<pair<double, double>> iv;
		rep(i,0,n) { double dx = x - c[i].x; if (abs(dx) < r[i]) { double h = sqrt(r[i]*r[i] - dx*dx); iv.push_back({c[i].y - h, c[i].y + h}); } }
		sort(all(iv)); double len = 0, cur = -1e18;
		for (auto [a, b] : iv) { if (b > cur) len += b - max(a, cur), cur = b; }
		return len;
	};
	double tot = 0;
	rep(k,0,sz(xs)-1) {
		double a = xs[k], b = xs[k+1]; if (b - a < 1e-12) continue;
		// substitution x = a + (b-a)(1-cos t)/2 removes sqrt endpoint singularities
		int N = 400; double s = 0;
		rep(i,0,N+1) {
			double t = M_PI * i / N, w = (i == 0 || i == N) ? 1 : (i & 1 ? 4 : 2);
			double x = a + (b - a) * (1 - cos(t)) / 2, dx = (b - a) * sin(t) / 2;
			s += w * f(x) * dx;
		}
		tot += s * (M_PI / N) / 3;
	}
	return tot;
}

int main() {
	srand(47);
	rep(it,0,3000) {
		int n = rand() % 6 + 1;
		vector<P> c; vector<double> r;
		rep(i,0,n) {
			if (i && rand() % 5 == 0) { int j = rand() % i; c.push_back(c[j]); r.push_back(rand() % 2 ? r[j] : rand() % 5 + 1); continue; }
			c.push_back(P(rand() % 11 - 5, rand() % 11 - 5)); r.push_back(rand() % 5 + 1);
		}
		double a = circleUnion(c, r), b = numeric(c, r);
		if (abs(a - b) > 1e-6 * max(1.0, b)) {
			cerr << a << " vs " << b << endl;
			rep(i,0,n) cerr << c[i] << " " << r[i] << endl;
			abort();
		}
	}
	cout << "Tests passed!" << endl;
}
