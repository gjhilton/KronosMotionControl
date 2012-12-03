// Easing Equations (c) 2003 Robert Penner, all rights reserved. Subject to the terms in http://www.robertpenner.com/easing_terms_of_use.html.
// C port by gjhilton 2012

#include "interpolation.h"
#include <math.h>

// INLINE

inline float _inlineCirc (float t, float b, float c, float d){
	if ((t/=d*0.5) < 1) return -c*0.5 * (sqrt(1 - t*t) - 1) + b;
	return c*0.5 * (sqrt(1 - (t-=2)*t) + 1) + b;
}
inline float _inlineCircIn (float t, float b, float c, float d){
	return -c * (sqrt(1 - (t/=d)*t) - 1) + b;
}
inline float _inlineCircOut (float t, float b, float c, float d){
	return c * sqrt(1 - (t=t/d-1)*t) + b;
}
inline float _inlineLinear (float t, float b, float c, float d){
	return c*t/d + b;
}
inline float _inlineQuad (float t, float b, float c, float d){
	if ((t/=d*0.5) < 1) return c*0.5*t*t + b;
	return -c*0.5 * ((--t)*(t-2) - 1) + b;
}
inline float _inlineQuadIn (float t, float b, float c, float d){
	return c*(t/=d)*t + b;
}
inline float _inlineQuadOut (float t, float b, float c, float d){
	return -c *(t/=d)*(t-2) + b;
}
inline float _inlineCubic (float t, float b, float c, float d){
	if ((t/=d*0.5) < 1) return c*0.5*t*t*t + b;
	return c*0.5*((t-=2)*t*t + 2) + b;
}
inline float _inlineCubicIn (float t, float b, float c, float d){
	return c*(t/=d)*t*t + b;
}
inline float _inlineCubicOut (float t, float b, float c, float d){
	return c*((t=t/d-1)*t*t + 1) + b;
}

// DIRECT API

float interpolateCirc (float t, float b, float c, float d){
	return _inlineCirc(t,b,c,d);
}
float interpolateCircIn (float t, float b, float c, float d){
	return _inlineCircIn(t,b,c,d);
}
float interpolateCircOut (float t, float b, float c, float d){
	return _inlineCircOut(t,b,c,d);
}
float interpolateLinear (float t, float b, float c, float d){
	return _inlineLinear(t,b,c,d);
}
float interpolateQuad (float t, float b, float c, float d){
	return _inlineQuad(t,b,c,d);
}
float interpolateQuadIn (float t, float b, float c, float d){
	return _inlineQuadIn(t,b,c,d);
}
float interpolateQuadOut (float t, float b, float c, float d){
	return _inlineQuadOut(t,b,c,d);
}
float interpolateCubic (float t, float b, float c, float d){
	return _inlineCubic(t,b,c,d);
}
float interpolateCubicIn (float t, float b, float c, float d){
	return _inlineCubicIn(t,b,c,d);
}
float interpolateCubicOut (float t, float b, float c, float d){
	return _inlineCubicOut(t,b,c,d);
}

// MULTIPLEXED API

float interpolate(float t, float b, float c, float d, Interpolation kind = LINEAR){
	switch (kind){
		case CIRCULAR:
			return _inlineCirc(t,b,c,d);
		case CIRCULAR_IN:
			return _inlineCircIn(t,b,c,d);
		case CIRCULAR_OUT:
			return _inlineCircOut(t,b,c,d);
		case LINEAR:
			return _inlineLinear(t,b,c,d);
		case QUAD:
			return _inlineQuad(t,b,c,d);
		case QUAD_IN:
			return _inlineQuadIn(t,b,c,d);
		case QUAD_OUT:
			return _inlineQuadOut(t,b,c,d);
		case CUBIC:
			return _inlineCubic(t,b,c,d);
		case CUBIC_IN:
			return _inlineCubicIn(t,b,c,d);
		case CUBIC_OUT:
			return _inlineCubicOut(t,b,c,d);
	}
	return 0; // can't happen
}

// CONVENIENCE TEMPLATE FOR ADDING NEW FUNCTIONS
/*
 
 // HEADER FILE
 
 float interpolateFUNC (float t, float b, float c, float d);
 float interpolateFUNCIn (float t, float b, float c, float d);
 float interpolateFUNCOut (float t, float b, float c, float d);
 
 // INLINE
 
 inline float _inlineFUNC (float t, float b, float c, float d){
 
 }
 inline float _inlineFUNCIn (float t, float b, float c, float d){
 
 }
 inline float _inlineFUNCOut (float t, float b, float c, float d){
 
 }
 
 // DIRECT API
 
 float interpolateFUNC (float t, float b, float c, float d){
 return _inlineFUNC(t,b,c,d);
 }
 float interpolateFUNCIn (float t, float b, float c, float d){
 return _inlineFUNCIn(t,b,c,d);
 }
 float interpolateFUNCOut (float t, float b, float c, float d){
 return _inlineFUNCOut(t,b,c,d);
 }
 
 // MULTIPLEXED API
 
 case FUNC:
 return _inlineFUNC(t,b,c,d);
 case FUNC_IN:
 return _inlineFUNCIn(t,b,c,d);
 case FUNC_OUT:
 return _inlineFUNCOut(t,b,c,d);
 
 */
