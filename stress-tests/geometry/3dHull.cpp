#include "../utilities/template.h"

#include "../../content/geometry/Point3D.h"
#include "../../content/geometry/PolyhedronVolume.h"

int main() {
	mt19937 rng(113);
	uniform_real_distribution<double> U(-1, 1);
	rep(it,0,200) {
		int n = 4 + it % 60;
		vector<P3> pts;
		rep(i,0,n) { P3 p(U(rng), U(rng), U(rng)); pts.push_back(p.unit() * (0.5 + 0.5 * (U(rng) + 1) / 2)); }
		auto fs = hull3d(pts);
		double V = signedPolyVolume(pts, fs);
		assert(V > 0 && V < 4 * M_PI / 3);
		for (auto& f : fs) rep(i,0,n) assert(f.q.dot(pts[i] - pts[f.a]) < 1e-9); // outward normals
		// Euler: triangulated sphere has F = 2V' - 4
		set<int> verts; for (auto& f : fs) verts.insert(f.a), verts.insert(f.b), verts.insert(f.c);
		assert(sz(fs) == 2 * sz(verts) - 4);
	}
	// unit cube corners perturbed: volume ~ 1
	vector<P3> cube; rep(m,0,8) cube.push_back(P3(m & 1, m >> 1 & 1, m >> 2 & 1) + P3(U(rng), U(rng), U(rng)) * 1e-7);
	assert(abs(signedPolyVolume(cube, hull3d(cube)) - 1) < 1e-5);
	cout << "Tests passed!" << endl;
}
