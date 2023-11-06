#pragma once

#include "Vector.h"

struct mat4x4
{
	float cells[4][4];

	static mat4x4 Translate(vec4 trans);
	static mat4x4 Scale(vec4 scale);
	static mat4x4 RotX(float angle);
	static mat4x4 RotY(float angle);
	static mat4x4 RotZ(float angle);

	vec4 operator*(const vec4& vec);
	mat4x4 operator*(const mat4x4& mat);
};