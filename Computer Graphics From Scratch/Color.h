#pragma once
#include "Vector.h"
#include "Utilities.h"

float RandomInRange(float min, float max);

class Color : public Vector4<float>
{
public:
	Color() = default;

	Color(int red, int green, int blue, int alpha = 255)
		: Vector4(red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f)
	{
	}

	Color(float red, float green, float blue, float alpha = 1.0f)
		: Vector4(red, green, blue, alpha)
	{}

	Color operator*(const float right) const
	{
		return {
			r * right,
			g * right,
			b * right,
			a * right
		};
	}

	Color operator*=(const float right) 
	{
		r *= right;
		g *= right;
		b *= right;
		a *= right;
		return *this;
	}

	Color operator+(const Color& right) const
	{
		return {r + right.r,
			g + right.g,
			b + right.b,
			a + right.a};
	}

	Color& operator+=(const Color& right)
	{
		r += right.r;
		g += right.g;
		b += right.b;
		a += right.a;
		return *this;
	}

	Color& operator-=(const Color& right)
	{
		r -= right.r;
		g -= right.g;
		b -= right.b;
		a -= right.a;
		return *this;
	}

	Color& operator*=(const Color& right)
	{
		r *= right.r;
		g *= right.g;
		b *= right.b;
		a *= right.a;
		return *this;
	}
	
	static Color Random(float min = 0.0f, float max = 1.0f)
	{
		return { RandomInRange(min, max), RandomInRange(min, max), RandomInRange(min, max) };
	}
};

inline Color operator*(float lhs, Color rhs)
{
	return rhs * lhs;
}

inline Color operator*(Color lhs, Color rhs)
{
	Color temp;
	temp.r = lhs.r * rhs.r;
	temp.g = lhs.g * rhs.g;
	temp.b = lhs.b * rhs.b;
	temp.a = lhs.a * rhs.a;

	return temp;
}