#include "../utilities/template.h"

#include "../../content/numerical/Integrate.h"
#include "../../content/numerical/GoldenSectionSearch.h"

int main() {
	assert(abs(quad(0, M_PI, [](double x) { return sin(x); }) - 2) < 1e-9);
	double c = 3; // capture works
	assert(abs(quad(0, 1, [&](double x) { return c * x * x; }) - 1) < 1e-9);
	double xm = gss(-1000, 1000, [&](double x) { return 4 + x + .3 * x * x; });
	assert(abs(xm - (-1 / 0.6)) < 1e-5);
	cout << "Tests passed!" << endl;
}
