#pragma once
class RGBColor {
public:
	float *white() {
		float white[3] = { 255, 255, 255 };
		return white;
	}
	float *red() {
		float red[3] = { 255, 0, 0 };
		return red;
	}
	float *green() {
		float green[3] = { 0, 255, 0 };
		return green;
	}
	float *blue() {
		float blue[3] = { 0, 0, 255 };
		return blue;
	}
	float *orange() {
		float orange[3] = { 255, 128, 0 };
		return orange;
	}
};