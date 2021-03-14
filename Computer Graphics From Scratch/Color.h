#pragma once
#include "Vector.h"

class Color : public Vector4<unsigned char>
{
public:
	Color(unsigned char red, unsigned char green, unsigned char blue)
		: Vector4(red, green, blue, 255)
	{
	}

	Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
		: Vector4(red, green, blue, alpha)
	{
	}

	Color operator*(const float right) const
	{
		return {
			Clamp(r * right),
			Clamp(g * right),
			Clamp(b * right),
			255
		};
	}

	Color operator+(const Color& right) const
	{
		return {Clamp(r + right.r), Clamp(g + right.g), Clamp(b + right.b), Clamp(a + right.a)};
	}

	Color& operator+=(const Color& right)
	{
		r = Clamp(r + right.r);
		g = Clamp(g + right.g);
		b = Clamp(b + right.b);
		a = Clamp(a + right.a);
		return *this;
	}

	Color& operator-=(const Color& right)
	{
		r = Clamp(r - right.r);
		g = Clamp(g - right.g);
		b = Clamp(b - right.b);
		a = Clamp(a - right.a);
		return *this;
	}

	Color& operator*=(const Color& right)
	{
		r = Clamp(r * right.r);
		g = Clamp(g * right.g);
		b = Clamp(b * right.b);
		a = Clamp(a * right.a);
		return *this;
	}

private:
	static unsigned char Clamp(const int value)
	{
		if (value < 0)
		{
			return 0;
		}
		if (value > 255)
		{
			return 255;
		}
		return static_cast<unsigned char>(value);
	}

	static unsigned char Clamp(const float value)
	{
		if (value < 0.0f)
		{
			return 0;
		}
		if (value > 255.0f)
		{
			return 255;
		}
		return static_cast<unsigned char>(value);
	}
};
