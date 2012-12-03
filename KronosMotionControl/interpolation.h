// Easing Equations (c) 2003 Robert Penner, all rights reserved. Subject to the terms in http://www.robertpenner.com/easing_terms_of_use.html.
// C port by gjhilton 2012

#ifndef interpolation_h
#define interpolation_h

enum Interpolation {
	LINEAR,
	QUAD_EASE,
	QUAD_EASE_IN,
	QUAD_EASE_OUT
};

/*
 
 t - the current time, between 0 and duration inclusive
 b - the initial value of the animation property
 c - the total change in the animation property
 d - the duration of the motion
 
*/

float interpolate(float t, float b, float c, float d, Interpolation kind);

#endif
