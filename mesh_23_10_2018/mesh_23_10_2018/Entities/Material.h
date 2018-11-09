#pragma once
class Material {
public:
	RGBColor __color;
	float	 __ka;
	float	 __kd;
	float	 __ks;
	
	Material() {
		__ka = 0.0003;
		__kd = 0.4;
		__ks = 0.3;
	}

	void set_color(RGBColor color) {
		__color.set(color);
	}

	RGBColor get_ambient() {

	}

	RGBColor get_diffuse
	(
		Vector a, 
		Vector b, 
		Vector c, 
		Lightning l
	) 
	{

	}

	RGBColor get_specular
	(
		Vector a, 
		Vector b, 
		Vector c, 
		Lightning l, 
		Vector eye
	) 
	{

	}

	void load_bmp(const char *filename){
		
	}

};