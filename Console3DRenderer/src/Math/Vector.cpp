#include "Vector.h"
#include <cmath>

vec4::vec4(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 1;
}

vec4 vec4::GetNormalized() const
{
	float mag = sqrtf(x * x + y * y + z * z);

	vec4 result(x, y, z);

	result.x /= mag;
	result.y /= mag;
	result.z /= mag;

	return result;
}

float vec4::operator*(const vec4& v)
{
	return x * v.x + y * v.y + z * v.z;
}