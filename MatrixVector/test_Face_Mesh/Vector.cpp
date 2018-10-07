#include "Vector.h"

Vector::Vector()
{
}

Vector::Vector(float _x, float _y, float _z, float w)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector Vector::operator+(Vector v) 
{
	return Vector(x + v.x, y + v.y, z + v.z, v.w /*, w + v.w*/);
}

Vector Vector::operator-(Vector v)
{
	return Vector(x - v.x, y - v.y, z - v.z, v.w /*, w - v.w*/);
}

Vector Vector::operator*(Vector v)
{
	return Vector(x * v.x, y * v.y, z * v.z, v.w /*, w * v.w*/);
}

Vector Vector::operator*(int val)
{
	return Vector(x * val, y * val, z * val, 1 /*, w * v.w*/);
}

Vector Vector::operator/(Vector v)
{
	return Vector(x / v.x, y / v.y, z / v.z, v.w /*, w / v.w*/);
}

Vector Vector::operator=(Vector &v) 
{
	return Vector(v.x, v.y, v.z, v.w);
}

Vector::~Vector()
{
}
