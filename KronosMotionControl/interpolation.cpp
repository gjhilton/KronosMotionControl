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
inline float _inlineQuart (float t, float b, float c, float d){
	if ((t/=d*0.5) < 1) return c*0.5*t*t*t*t + b;
	return -c*0.5 * ((t-=2)*t*t*t - 2) + b;
}
inline float _inlineQuartIn (float t, float b, float c, float d){
	return c*(t/=d)*t*t*t + b;
}
inline float _inlineQuartOut (float t, float b, float c, float d){
	return -c * ((t=t/d-1)*t*t*t - 1) + b;
}
inline float _inlineSine (float t, float b, float c, float d){
	return -c*0.5 * (cos(_PI*t/d) - 1) + b;
}
inline float _inlineSineIn (float t, float b, float c, float d){
	return -c * cos(t/d * _HALF_PI) + c + b;
}
inline float _inlineSineOut (float t, float b, float c, float d){
	return c * sin(t/d * _HALF_PI) + b;
}
inline float _inlineExpo (float t, float b, float c, float d){
	if (t==0) return b;
	if (t==d) return b+c;
	if ((t/=d*0.5) < 1) return c*0.5 * pow(2, 10 * (t - 1)) + b;
	return c*0.5 * (-pow(2, -10 * --t) + 2) + b;
}
inline float _inlineExpoIn (float t, float b, float c, float d){
	return (t==0) ? b : c * pow(2, 10 * (t/d - 1)) + b - c * 0.001;
}
inline float _inlineExpoOut (float t, float b, float c, float d){
	return (t==d) ? b+c : c * (-pow(2, -10 * t/d) + 1) + b;
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
float interpolateQuart (float t, float b, float c, float d){
	return _inlineQuart(t,b,c,d);
}
float interpolateQuartIn (float t, float b, float c, float d){
	return _inlineQuartIn(t,b,c,d);
}
float interpolateQuartOut (float t, float b, float c, float d){
	return _inlineQuartOut(t,b,c,d);
}
float interpolateSine (float t, float b, float c, float d){
	return _inlineSine(t,b,c,d);
}
float interpolateSineIn (float t, float b, float c, float d){
	return _inlineSineIn(t,b,c,d);
}
float interpolateSineOut (float t, float b, float c, float d){
	return _inlineSineOut(t,b,c,d);
}
float interpolateExpo (float t, float b, float c, float d){
	return _inlineExpo(t,b,c,d);
}
float interpolateExpoIn (float t, float b, float c, float d){
	return _inlineExpoIn(t,b,c,d);
}
float interpolateExpoOut (float t, float b, float c, float d){
	return _inlineExpoOut(t,b,c,d);
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
		case QUART:
			return _inlineQuart(t,b,c,d);
		case QUART_IN:
			return _inlineQuartIn(t,b,c,d);
		case QUART_OUT:
			return _inlineQuartOut(t,b,c,d);
		case SINE:
			return _inlineSine(t,b,c,d);
		case SINE_IN:
			return _inlineSineIn(t,b,c,d);
		case SINE_OUT:
			return _inlineSineOut(t,b,c,d);
		case EXPO:
			return _inlineExpo(t,b,c,d);
		case EXPO_IN:
			return _inlineExpoIn(t,b,c,d);
		case EXPO_OUT:
			return _inlineExpoOut(t,b,c,d);
	}
	return 0; // can't happen
}