#pragma once
#include <math.h>5

template <typename T>
class Vector2
{
public:
	Vector2() : x(static_cast<T>(0)), y(static_cast<T>(0))
	{
	}

	Vector2(T x, T y) : x(x), y(y)
	{
	}

	Vector2(const T& value) : x(value), y(value)
	{
	}

	T Length()
	{
		return sqrt(x * x + y * y);
	}

	T Dot(const Vector2<T>& v) const
	{
		return x * v.x + y * v.y;
	}

	Vector2<T>& Normalize()
	{
		T lengthSquared = Dot(*this);
		if (lengthSquared > 0)
		{
			T inverseLength = 1 / sqrt(lengthSquared);
			x *= inverseLength, y *= inverseLength;
		}

		return *this;
	}

	Vector2<T> operator+(const Vector2<T>& right) const
	{
		return Vector2<T>(x + right.x, y + right.y);
	}

	Vector2<T> operator-(const Vector2<T>& right) const
	{
		return Vector2<T>(x - right.x, y - right.y);
	}

	Vector2<T> operator-()
	{
		return Vector2<T>(-x, -y);
	}

	Vector2<T> operator*( const T& scalar) const
	{
		return Vector2<T>(x * scalar, y * scalar);
	}

	Vector2<T> operator/(const T& scalar) const
	{
		if (scalar == 0) return Vector2<T>(*this);
		
		return Vector2<T>(x / scalar, y / scalar);
	}

	Vector2<T>& operator+=(const Vector2<T>& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	}

	Vector2<T>& operator-=(const Vector2<T>& right)
	{
		x -= right.x;
		y -= right.y;
		return *this;
	}

	Vector2<T>& operator*=(const T& scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector2<T>& operator/=(const T& scalar)
	{
		if (scalar != 0)
		{
			x /= scalar;
			y /= scalar;
		}
		return *this;
	}

public:
	union
	{
		T x, u;
	};

	union
	{
		T y, v;
	};
};

template <typename T>
Vector2<T> operator*(const T& scalar, const Vector2<T>& rhs)
{
	return Vector2<T>(scalar * rhs.x, scalar * rhs.y);
}

typedef Vector2<int> Vec2Int;
typedef Vector2<float> Vec2;

template <typename T>
class Vector3
{
public:
	Vector3() : x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0))
	{
	}

	Vector3(T x, T y, T z) : x(x), y(y), z(z)
	{
	}

	Vector3(const T& value) : x(value), y(value), z(value)
	{
	}

	T Length()
	{
		return sqrt(x * x + y * y + z * z);
	}

	T Dot(const Vector3<T>& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	Vector3<T>& Normalize()
	{
		T lengthSquared = Dot(*this);
		if (lengthSquared > 0)
		{
			T inverseLength = 1 / sqrtf(lengthSquared);
			x *= inverseLength, y *= inverseLength, z *= inverseLength;
		}

		return *this;
	}

	Vector3<T> Cross(const Vector3<T>& v) const
	{
		return Vector3<T>(
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x
			);
	}

	Vector3<T> operator+(const Vector3<T>& right) const
	{
		return Vector3<T>(x + right.x, y + right.y, z + right.z);
	}

	Vector3<T> operator-(const Vector3<T>& right) const
	{
		return Vector3<T>(x - right.x, y - right.y, z - right.z);
	}

	Vector3<T> operator-() const
	{
		return Vector3<T>(-x, -y, -z);
	}

	Vector3<T> operator*(const T& scalar) const
	{
		return Vector3<T>(x * scalar, y * scalar, z * scalar);
	}

	Vector3<T> operator/(const T& scalar) const
	{
		if (scalar == 0) return Vector3<T>(*this);
		
		return Vector3<T>(x / scalar, y / scalar, z / scalar);
	}

	Vector3<T>& operator+=(const Vector3<T>& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	}

	Vector3<T>& operator-=(const Vector3<T>& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}

	Vector3<T>& operator*=(const T& scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	Vector3<T>& operator/=(const T& scalar)
	{
		if (scalar != 0)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
		}
		return *this;
	}

	float LengthSquared() const
	{
		return (x * x) + (y * y) + (z * z);
	}

	bool NearZero()
	{
		const float s = 1e-8;
		return fabsf(x) < s && fabsf(y) < s && fabsf(z) < s;
	}

public:
	union
	{
		T x, r;
	};

	union
	{
		T y, g;
	};

	union
	{
		T z, b;
	};
};

template <typename T>
Vector3<T> operator*(const T& scalar, const Vector3<T>& rhs)
{
	return Vector3<T>(scalar * rhs.x, scalar * rhs.y, scalar * rhs.z);
}

typedef Vector3<float> Vec3;
typedef Vector3<int> Vec3Int;

template <typename T>
class Vector4
{
public:
	Vector4() : x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)), w(static_cast<T>(0))
	{
	}

	Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w)
	{
	}

	Vector4(const T& value) : x(value), y(value), z(value), w(value)
	{
	}

	T Length()
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}

	T Dot(const Vector4<T>& v) const
	{
		return x * v.x + y * v.y + z * v.z + w * v.w;
	}

	Vector4<T>& Normalize()
	{
		T lengthSquared = Dot(*this);
		if (lengthSquared > 0)
		{
			T inverseLength = 1 / sqrt(lengthSquared);
			x *= inverseLength, y *= inverseLength, z *= inverseLength, w *= inverseLength;
		}

		return *this;
	}
	
	Vector4<T> operator+(const Vector4<T>& right) const
	{
		return Vector4<T>(x + right.x, y + right.y, z + right.z, w + right.w);
	}

	Vector4<T> operator-(const Vector4<T>& right) const
	{
		return Vector4<T>(x - right.x, y - right.y, z - right.z, w - right.w);
	}

	Vector4<T> operator-()
	{
		return Vector4<T>(-x, -y, -z, -w);
	}

	Vector4<T> operator*(const T& scalar) const
	{
		return Vector4<T>(x * scalar, y * scalar, z * scalar, w * scalar);
	}
	
	Vector4<T> operator/(const T& scalar) const
	{
		if (scalar == 0) return Vector4<T>(*this);
		
		return Vector4<T>(x / scalar, y / scalar, z / scalar, w / scalar);
	}

	Vector4<T>& operator+=(const Vector4<T>& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		w += right.w;
		return *this;
	}

	Vector4<T>& operator-=(const Vector4<T>& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		w -= right.w;
		return *this;
	}

	Vector4<T>& operator*=(const T& scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}

	Vector4<T>& operator/=(const T& scalar)
	{
		if (scalar != 0)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
			w /= scalar;
		}
		return *this;
	}

public:
	union
	{
		T x, r;
	};

	union
	{
		T y, g;
	};

	union
	{
		T z, b;
	};

	union
	{
		T w, a;
	};
};

template <typename T>
Vector4<T> operator*(const T& scalar, const Vector4<T>& rhs)
{
	return Vector4<T>(scalar * rhs.x, scalar * rhs.y, scalar * rhs.z, scalar * rhs.w);
}