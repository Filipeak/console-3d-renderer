#pragma once

#include <cstddef>

class Screen
{
public:
	Screen();
	Screen(size_t w, size_t h, float a);

	void Clear();
	void SetPixel(size_t x, size_t y, float zInv, char pixel);
	void DrawBuffer();
	void Release();

	float GetAspectRatio() const;
	size_t GetOutputBufferBytesSize() const;
	size_t GetZBufferBytesSize() const;
	size_t GetBuffersSize() const;
	size_t GetWidth() const;
	size_t GetHeight() const;

private:
	size_t m_Width;
	size_t m_Height;
	float m_DefaultAspectRatio;
	char* m_OutputBuffer;
	float* m_ZBuffer;
};