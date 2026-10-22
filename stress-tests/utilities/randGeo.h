#pragma once

#include "../../content/geometry/Point.h"

P randIntPt(int lim) {
	return P(rand()%(lim*2) - lim, rand()%(lim*2)-lim);
}
