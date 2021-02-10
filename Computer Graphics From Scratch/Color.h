#pragma once
#include "Vector.h"

class Color
{
public:
	Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
		: r(red), g(green), b(blue), a(alpha)
	{
	}

	Color& operator+(const Color& right)
	{
		*this += right;
		return *this;
	}

	Color& operator-(const Color& right)
	{
		*this -= right;
		return *this;
	}

	Color& operator*(const Color& right)
	{
		*this *= right;
		return *this;
	}

	Color& operator/(const Color& right)
	{
		*this /= right;
		return *this;
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

	Color& operator/=(const Color& right)
	{
		if (right.r != 0 && right.g != 0 && right.b != 0 && right.a != 0)
		{
			r = Clamp(r / right.r);
			g = Clamp(g /right.g);
			b = Clamp(b /right.b);
			a = Clamp(a /right.a);
		}
		return *this;
	}

	template <typename T>
	Color& operator*=(T value)
	{
		r = Clamp(r * value);
		g = Clamp(g * value);
		b = Clamp(b * value);
		a = Clamp(a * value);
		return *this;
	}

	template <typename T>
	Color& operator/=(T value)
	{
		if (value != static_cast<T>(0))
		{
			r = Clamp(r / value);
			g = Clamp(g / value);
			b = Clamp(b / value);
			a = Clamp(a / value);
		}
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
public:
	unsigned char r, g, b, a;
};
