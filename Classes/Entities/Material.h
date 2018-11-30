#pragma once
class Material {
public:
	RGBColor __color;
	float	 __ka; // ambient
	float	 __kd; // diffuse
	float	 __ks; // specular
	
	Material() {
		__ka = 0.0003;
		__kd = 0.4;
		__ks = 0.3;
	}

	void set_color(RGBColor color) {
		__color.set(color);
	}

	RGBColor get_ambient() {
		return __color.multiplies(__ka);
	}

	RGBColor get_diffuse
	(
		Vector a, 
		Vector b, 
		Vector c, 
		Lightning l
	) 
	{
		float n;
		Vector N;
		N = (a - b) * (c - b);
		Vector L = l.__position - b; // ^ dot, * cross
		/*N.normalize();
		L.normalize();*/
		// n = N ^(dot) L;
		n = N.normalize().dot_product(L.normalize());
		return (__color.multiplies(__kd)).multiplies(abs(n));
	}

	RGBColor get_specular
	(
		Vector a, 
		Vector b, 
		Vector c, 
		Lightning L, 
		Vector eye
	) 
	{
		Vector v1 = a - b, v2 = c - b, l, n;
		l = (b - L.__position).normalize(); // LIGHT POST // b - l / l - b //
		n = (v1.cross_product(v2)).normalize();

		float pl = abs(n.dot_product(l)); // ^ dot, * cross

		Vector r = (n * (2 * pl)) - l; // * bukan cross, kali
		// Vector l di dot kan vector mata, dapat cos, return __color * cos 
		return __color.multiplies( abs(r.dot_product((eye - b).normalize())) * __ks);
	}

	void load_bmp(const char *filename){
		
	}

};