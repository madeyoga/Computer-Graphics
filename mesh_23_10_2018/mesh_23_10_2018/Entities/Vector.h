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
	Vector operator = (Vector &v);
	void set_value(float x, float y, float z);
	void showVectorOnConsole();

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

void Vector::set_value(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}

void Vector::showVectorOnConsole() {
	std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}

//Matrix Vector::to_matrix(Matrix _m) {
//	Matrix __matrix_v(4, 1);
//	__matrix_v.matrix[0][0] = x;
//	__matrix_v.matrix[1][0] = x;
//	__matrix_v.matrix[2][0] = x;
//	__matrix_v.matrix[3][0] = 1;
//	return __matrix_v;
//}

Vector::~Vector()
{
}
