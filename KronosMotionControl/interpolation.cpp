#include "interpolation.h"

float interpolate(float t, float b, float c, float d, Interpolation kind = LINEAR){
	switch (kind){
		case LINEAR:
			return c*t/d + b;
		case QUAD_EASE:
			if ((t/=d*0.5) < 1) return c*0.5*t*t + b;
			return -c*0.5 * ((--t)*(t-2) - 1) + b;
		case QUAD_EASE_IN:
			return c*(t/=d)*t + b;
		case QUAD_EASE_OUT:
			return -c *(t/=d)*(t-2) + b;
	}
	return 0; // can't happen
}
