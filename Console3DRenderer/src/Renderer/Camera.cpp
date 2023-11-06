#include "Camera.h"
#include "../Math/Constants.h"
#include <cmath>

Camera::Camera()
{
	m_Screen = nullptr;
	m_Kx = 0.0f;
	m_Ky = 0.0f;
}

Camera::Camera(Screen* screen, float fov)
{
	m_Screen = screen;
	m_Kx = 1.0f / tan(fov / 2.0f * DEG_2_RAD) / screen->GetAspectRatio();
	m_Ky = 1.0f / tan(fov / 2.0f * DEG_2_RAD);
}

void Camera::WorldToScreen(const vec4& point, size_t& x, size_t& y) const
{
	float xp = m_Kx * point.x / point.z;
	float yp = m_Ky * point.y / point.z;

	x = (size_t)((xp + 1.0f) * 0.5f * (float)m_Screen->GetWidth());
	y = (size_t)((1.0f - yp) * 0.5f * (float)m_Screen->GetHeight());
}