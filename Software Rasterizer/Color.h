#pragma once
#include "Vector.h"
#include "Utilities.h"

class Color : public Vector4<float>
{
public:
	Color() = default;

	Color(const unsigned char red, const unsigned char green, const unsigned char blue, const unsigned char alpha = 255)
		: Vector4((float)red / 255.0f, (float)green / 255.0f, (float)blue / 255.0f, (float)alpha / 255.0f)
	{}

	Color(const float red, const float green, const float blue, const float alpha = 1.0f)
		: Vector4(red, green, blue, alpha)
	{}

	Color(const Vector4 input)
		: Vector4(input)
	{}
};