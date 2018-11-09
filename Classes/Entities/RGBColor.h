#pragma once
class RGBColor {
public:
	float r = 0;
	float g = 0; 
	float b = 0;

	RGBColor (float _r = 255, float _g = 255, float _b = 255) {
		r = _r;
		g = _g;
		b = _b;
	}

	void set_rgb (float _r, float _g, float _b) {
		r = _r;
		g = _g;
		b = _b;
	}

	void set_r(float _r) {
		r = _r;
	}

	void set_g(float _g) {
		g = _g;
	}

	void set_b(float _b) {
		b = _b;
	}

	RGBColor plus (RGBColor __color) {
		RGBColor __result;
		__result.r = __color.r + r;
		__result.g = __color.g + g;
		__result.b = __color.b + b;
		return __result;
	}

	RGBColor multiplies (RGBColor __color) {
		RGBColor __result;
		__result.r = __color.r * r;
		__result.g = __color.g * g;
		__result.b = __color.b * b;
		return __result;
	}

	RGBColor set (RGBColor __color) {
		r = __color.r;
		g = __color.g;
		b = __color.b;
	}

};