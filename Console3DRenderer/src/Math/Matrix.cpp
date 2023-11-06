#include "Matrix.h"
#include "Constants.h"
#include <cmath>

mat4x4 mat4x4::Translate(vec4 trans)
{
	return { {
		{1, 0, 0, trans.x},
		{0, 1, 0, trans.y},
		{0, 0, 1, trans.z},
		{0, 0, 0, 1},
	} };
}

mat4x4 mat4x4::Scale(vec4 scale)
{
	return { {
		{scale.x, 0, 0, 0},
		{0, scale.y, 0, 0},
		{0, 0, scale.z, 0},
		{0, 0, 0, 1},
	} };
}

mat4x4 mat4x4::RotX(float angle)
{
	angle *= DEG_2_RAD;

	return { {
		{1, 0, 0, 0},
		{0, cos(angle), -sin(angle), 0},
		{0, sin(angle), cos(angle), 0},
		{0, 0, 0, 1},
	} };
}

mat4x4 mat4x4::RotY(float angle)
{
	angle *= DEG_2_RAD;

	return { {
		{cos(angle), 0, -sin(angle), 0},
		{0, 1, 0, 0},
		{sin(angle), 0, cos(angle), 0},
		{0, 0, 0, 1},
	} };
}

mat4x4 mat4x4::RotZ(float angle)
{
	angle *= DEG_2_RAD;

	return { {
		{cos(angle), -sin(angle), 0, 0},
		{sin(angle), cos(angle), 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1},
	} };
}

vec4 mat4x4::operator*(const vec4& vec)
{
	vec4 v(0, 0, 0);

	v.x = vec.x * cells[0][0] + vec.y * cells[0][1] + vec.z * cells[0][2] + vec.w * cells[0][3];
	v.y = vec.x * cells[1][0] + vec.y * cells[1][1] + vec.z * cells[1][2] + vec.w * cells[1][3];
	v.z = vec.x * cells[2][0] + vec.y * cells[2][1] + vec.z * cells[2][2] + vec.w * cells[2][3];
	v.w = vec.x * cells[3][0] + vec.y * cells[3][1] + vec.z * cells[3][2] + vec.w * cells[3][3];

	return v;
}

mat4x4 mat4x4::operator*(const mat4x4& mat)
{
	mat4x4 m = {};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m.cells[i][j] = 0;

			for (int k = 0; k < 4; k++)
			{
				m.cells[i][j] += cells[i][k] * mat.cells[k][j];
			}
		}
	}

	return m;
}