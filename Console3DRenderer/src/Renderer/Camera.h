#pragma once

#include "Screen.h"
#include "../Math/Vector.h"

#include <cstddef>

class Camera
{
public:
	Camera();
	Camera(Screen* screen, float fov);

	void WorldToScreen(const vec4& point, size_t& x, size_t& y) const;

private:
	Screen* m_Screen;
	float m_Kx;
	float m_Ky;
};