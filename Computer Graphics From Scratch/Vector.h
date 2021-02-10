#pragma once
template <typename T>
class Vector2
{
public:
	Vector2()
		: x(static_cast<T>(0)), y(static_cast<T>(0))
	{
	}

	Vector2(T x, T y)
		: x(x), y(y)
	{
		
	}

	Vector2& operator+(const Vector2<T>& right) const
	{
		Vector2<T> temp(*this);
		temp += right;
		return temp;
	}

	Vector2& operator-(const Vector2<T>& right) const
	{
		Vector2<T> temp(*this);
		temp -= right;
		return temp;
	}

	Vector2& operator*(const Vector2<T>& right) const
	{
		Vector2<T> temp(*this);
		temp *= right;
		return temp;
	}

	Vector2& operator/(const Vector2<T>& right) const
	{
		Vector2<T> temp(*this);
		temp /= right;
		return temp;
	}

	Vector2& operator+=(const Vector2<T>& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	}

	Vector2& operator-=(const Vector2<T>& right)
	{
		x -= right.x;
		y -= right.y;
		return *this;
	}

	Vector2& operator*=(const Vector2<T>& right)
	{
		x *= right.x;
		y *= right.y;
		return *this;
	}

	Vector2& operator/=(const Vector2<T>& right)
	{
		if (right.x != 0 && right.y != 0)
		{
			x /= right.x;
			y /= right.y;
		}
		return *this;
	}

public:
	T x, y;
};
typedef Vector2<int> Vec2Int;
typedef Vector2<float> Vec2;

template <typename T>
class Vector3
{
public:
	Vector3()
		: x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0))
	{
	}

	Vector3(T x, T y, T z)
		: x(x), y(y), z(z)
	{
	}

	Vector3& operator+(const Vector3<T>& right) const
	{
		Vector3<T> temp(*this);
		temp += right;
		return temp;
	}

	Vector3& operator-(const Vector3<T>& right) const
	{
		Vector3<T> temp(*this);
		temp -= right;
		return temp;
	}

	Vector3& operator*(const Vector3<T>& right) const
	{
		Vector3<T> temp(*this);
		temp *= right;
		return temp;
	}

	Vector3& operator/(const Vector3<T>& right) const
	{
		Vector3<T> temp(*this);
		temp /= right;
		return temp;
	}

	Vector3& operator+=(const Vector3<T>& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	}

	Vector3& operator-=(const Vector3<T>& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}

	Vector3& operator*=(const Vector3<T>& right)
	{
		x *= right.x;
		y *= right.y;
		z *= right.z;
		return *this;
	}

	Vector3& operator/=(const Vector3<T>& right)
	{
		if (right.x != 0 && right.y != 0)
		{
			x /= right.x;
			y /= right.y;
			z /= right.z;
		}
		return *this;
	}

public:
	T x, y, z;
};
typedef Vector3<float> Vec3;
typedef Vector3<int> Vec3Int;

template <typename T>
class Vector4
{
public:
	Vector4()
		: x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0))
	{
	}

	Vector4(T x, T y)
		: x(x), y(y)
	{
		
	}

	Vector4& operator+(const Vector4<T>& right) const
	{
		Vector4<T> temp(*this);
		temp += right;
		return temp;
	}

	Vector4& operator-(const Vector4<T>& right) const
	{
		Vector4<T> temp(*this);
		temp -= right;
		return temp;
	}

	Vector4& operator*(const Vector4<T>& right) const
	{
		Vector4<T> temp(*this);
		temp *= right;
		return temp;
	}

	Vector4& operator/(const Vector4<T>& right) const
	{
		Vector4<T> temp(*this);
		temp /= right;
		return temp;
	}

	Vector4& operator+=(const Vector4<T>& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		w += right.w;
		return *this;
	}

	Vector4& operator-=(const Vector4<T>& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		w -= right.w;
		return *this;
	}

	Vector4& operator*=(const Vector4<T>& right)
	{
		x *= right.x;
		y *= right.y;
		z *= right.z;
		w *= right.w;
		return *this;
	}

	Vector4& operator/=(const Vector4<T>& right)
	{
		if (right.x != 0 && right.y != 0 && right.z != 0 && right.w != 0)
		{
			x /= right.x;
			y /= right.y;
			z /= right.z;
			w /= right.w;
		}
		return *this;
	}

public:
	T x, y, z, w;
};