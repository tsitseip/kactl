#include "../utilities/template.h"

#include "../../content/numerical/IntegrateAdaptive.h"

int main() {
	double sphereVolume = quad(-1, 1, [](double x) {
		return quad(-1, 1, [&](double y) {
			return quad(-1, 1, [&](double z) {
				return x*x + y*y + z*z < 1; });});});
	assert(abs(sphereVolume - 4 * M_PI / 3) < 1e-2);
	assert(abs(quad(0, 1, [](double x) { return exp(x); }) - (M_E - 1)) < 1e-9);
	cout << "Tests passed!" << endl;
}
