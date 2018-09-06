#pragma once

class Vector
{
private:
	
public:

	float x, y, z;
	const float w = 1;

	Vector();
	Vector(float _x, float _y, float _z, float w);
	
	Vector operator + (Vector v);
	Vector operator - (Vector v);
	Vector operator * (Vector v);
	Vector operator * (int val) ;
	Vector operator / (Vector v);

	~Vector();



};

