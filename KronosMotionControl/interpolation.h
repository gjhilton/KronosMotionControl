// Easing Equations (c) 2003 Robert Penner, all rights reserved. Subject to the terms in http://www.robertpenner.com/easing_terms_of_use.html.
// C port by gjhilton 2012

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

#endif
