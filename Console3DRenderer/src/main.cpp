#include <iostream>
#include <cmath>

#include "Renderer/Screen.h"
#include "Renderer/Camera.h"
#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Math/Constants.h"

static constexpr char SHADOW_DATA[] = ".,-~:;=!*#$@";

static constexpr float CONSOLE_DEFAULT_ASPECT_RATIO = 2.5f;
static constexpr size_t WIDTH = 70;
static constexpr size_t HEIGHT = 20;

static constexpr float PHI_STEP = 0.02f;
static constexpr float THETA_STEP = 0.02f;
static constexpr float R_OUTER = 3.0f;
static constexpr float R_INNER = 1.5f;

static constexpr float FOV = 100.0f;
static constexpr float VIEWER_DISTANCE = 6.0f;
static constexpr float ROT_SPEED = 5.0f;

static const vec4 LIGHT_LOCATION = vec4(0, 1, -1);

int main()
{
	Screen screen(WIDTH, HEIGHT, CONSOLE_DEFAULT_ASPECT_RATIO);
	Camera cam(&screen, FOV);

	vec4 lightNorm = LIGHT_LOCATION.GetNormalized();
	float rot = 0.0f;

	while (true)
	{
		screen.Clear();

		rot += ROT_SPEED;

		for (float theta = 0; theta < 2 * PI; theta += THETA_STEP)
		{
			for (float phi = 0; phi < 2 * PI; phi += PHI_STEP)
			{
				mat4x4 rotMat = mat4x4::RotX(rot);
				mat4x4 transMat = mat4x4::Translate(vec4(0, 0, VIEWER_DISTANCE));

				vec4 point = vec4((R_OUTER + R_INNER * cos(theta)) * cos(phi), R_INNER * sin(theta), -(R_OUTER + R_INNER * cos(theta)) * sin(phi));
				vec4 normal = vec4(cos(theta) * cos(phi), sin(theta), -sin(phi) * cos(theta));

				point = transMat * rotMat * point;
				normal = rotMat * normal;
				
				float L = normal * lightNorm;

				if (L > 0.0f)
				{
					size_t luminanceIndex = (size_t)(L * (strlen(SHADOW_DATA) - 1));
					size_t x, y;

					cam.WorldToScreen(point, x, y);
					screen.SetPixel(x, y, 1.0f / point.z, SHADOW_DATA[luminanceIndex]);
				}
			}
		}

		screen.DrawBuffer();
	}

	screen.Release();

	return 0;
}