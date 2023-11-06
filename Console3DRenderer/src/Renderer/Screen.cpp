#include "Screen.h"
#include <iostream>
#include <cstdio>
#include <cstring>

Screen::Screen()
{
	m_Width = 0;
	m_Height = 0;
	m_OutputBuffer = nullptr;
	m_ZBuffer = nullptr;
}

Screen::Screen(size_t w, size_t h, float a)
{
	m_Width = w;
	m_Height = h;
	m_DefaultAspectRatio = a;

	m_OutputBuffer = new char[w * h];
	m_ZBuffer = new float[w * h];
}

void Screen::Clear()
{
	std::memset(m_OutputBuffer, ' ', GetOutputBufferBytesSize());
	std::memset(m_ZBuffer, 0, GetZBufferBytesSize());

	std::printf("\x1b[H");
}

void Screen::SetPixel(size_t x, size_t y, float zInv, char pixel)
{
	size_t index = GetWidth() * y + x;

	if (index < GetBuffersSize() && zInv > m_ZBuffer[index])
	{
		m_ZBuffer[index] = zInv;
		m_OutputBuffer[index] = pixel;
	}
}

void Screen::DrawBuffer()
{
	for (size_t y = 0; y < GetHeight(); y++)
	{
		for (size_t x = 0; x < GetWidth(); x++)
		{
			std::cout << m_OutputBuffer[y * GetWidth() + x];
		}

		std::cout << std::endl;
	}
}

void Screen::Release()
{
	delete[] m_OutputBuffer;
	delete[] m_ZBuffer;
}

float Screen::GetAspectRatio() const
{
	return (float)GetWidth() / (float)GetHeight() / m_DefaultAspectRatio;
}

size_t Screen::GetOutputBufferBytesSize() const
{
	return sizeof(*m_OutputBuffer) * GetBuffersSize();
}

size_t Screen::GetZBufferBytesSize() const
{
	return sizeof(*m_ZBuffer) * GetBuffersSize();
}

size_t Screen::GetBuffersSize() const
{
	return GetWidth() * GetHeight();
}

size_t Screen::GetWidth() const
{
	return m_Width;
}

size_t Screen::GetHeight() const
{
	return m_Height;
}