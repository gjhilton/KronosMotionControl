// Easing Equations (c) 2003 Robert Penner, all rights reserved. Subject to the terms in http://www.robertpenner.com/easing_terms_of_use.html.
// C port by gjhilton 2012

#include <math.h>

#ifndef interpolation_h
#define interpolation_h

#define _PI 3.14159265358979
#define _HALF_PI 1.5707963267949

enum Interpolation {
	CIRCULAR,
	CIRCULAR_IN,
	CIRCULAR_OUT,
	CUBIC,
	CUBIC_IN,
	CUBIC_OUT,
	EXPO,
	EXPO_IN,
	EXPO_OUT,
	LINEAR,
	QUAD,
	QUAD_IN,
	QUAD_OUT,
	QUART,
	QUART_IN,
	QUART_OUT,
	SINE,
	SINE_IN,
	SINE_OUT
};

/*
 
 t - the current time, between 0 and duration inclusive
 b - the initial value of the animation property
 c - the total change in the animation property
 d - the duration of the motion
 
*/

float interpolate(float t, float b, float c, float d, Interpolation kind);

float interpolateCirc (float t, float b, float c, float d);
float interpolateCircIn (float t, float b, float c, float d);
float interpolateCircOut (float t, float b, float c, float d);

float interpolateLinear (float t, float b, float c, float d);

float interpolateQuad (float t, float b, float c, float d);
float interpolateQuadIn (float t, float b, float c, float d);
float interpolateQuadOut (float t, float b, float c, float d);

float interpolateCubic (float t, float b, float c, float d);
float interpolateCubicIn (float t, float b, float c, float d);
float interpolateCubicOut (float t, float b, float c, float d);

float interpolateQuart (float t, float b, float c, float d);
float interpolateQuartIn (float t, float b, float c, float d);
float interpolateQuartOut (float t, float b, float c, float d);

float interpolateSine (float t, float b, float c, float d);
float interpolateSineIn (float t, float b, float c, float d);
float interpolateSineOut (float t, float b, float c, float d);

float interpolateExpo (float t, float b, float c, float d);
float interpolateExpoIn (float t, float b, float c, float d);
float interpolateExpoOut (float t, float b, float c, float d);

// INLINE IMPLEMENTATION

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


#endif
