#pragma once

struct vec4
{
	float x, y, z, w;

	vec4(float x, float y, float z);

	vec4 GetNormalized() const;

	float operator*(const vec4& v);
};