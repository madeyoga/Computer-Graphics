#pragma once

class Vector
{
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
	Vector operator = (Vector &v);
	float operator ^ (Vector v);
	float length();
	Vector normalize();
	void set_value(float x, float y, float z);
	void set_x(float _x);
	void set_y(float _y);
	void set_z(float _z);
	void showVectorOnConsole();
	float dot_product(Vector _v);
	Vector cross_product(Vector _v);

	~Vector();
};

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
	float x = y * v.z - z * v.y;
	float y = z * v.x - x * v.z;
	float z = x * v.y - y * v.x;
	return Vector(x, y, z, 1);
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
	x = v.x;
	y = v.y;
	z = v.z;
	return Vector(v.x, v.y, v.z, 1);
}

float Vector::operator^(Vector v) {
	return Vector::dot_product(v);
}

float Vector::length() {
	return pow(pow(x, 2) + pow(y, 2) + pow(z, 2), 0.5);
}

Vector Vector::normalize() {
	float length = Vector::length();
	Vector temp;
	if (length != 0) {
		temp.x = x / length;
		temp.y = y / length;
		temp.z = z / length;
	}
	return temp;
}

float Vector::dot_product(Vector _v) {
	return (x * _v.x) + (y * _v.y) + (z * _v.z);
}

Vector Vector::cross_product(Vector _v) {
	return _v;
}

void Vector::set_value(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}

void Vector::set_x(float _x) {
	x = _x;
}

void Vector::set_y(float _y) {
	y = _y;
}

void Vector::set_z(float _z) {
	z = _z;
}

void Vector::showVectorOnConsole() {
	std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}

Vector::~Vector()
{
}
