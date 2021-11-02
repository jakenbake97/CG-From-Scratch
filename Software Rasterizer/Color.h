#pragma once
#include "Vector.h"
#include "Utilities.h"

class Color : public Vector4<unsigned char>
{
public:
	Color() = default;

	Color(const unsigned char red, const unsigned char green, const unsigned char blue, const unsigned char alpha = 255)
		: Vector4(red, green, blue, alpha)
	{}

};