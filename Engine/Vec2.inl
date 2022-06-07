#include "Vec2.h"
/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vec2.inl
Author: Seulbin Seo
Creation date: 6/02/2022
-----------------------------------------------------------------*/

namespace math
{
	/////////////////vec2
	constexpr vec2& vec2::operator+=(const vec2& v) noexcept
	{
		(*this).x = (*this).x + v.x;
		(*this).y = (*this).y + v.y;
		return *this;
	}

	constexpr vec2& vec2::operator-=(const vec2& v) noexcept
	{
		this->x = this->x - v.x;
		this->y = this->y - v.y;
		return *this;
	}

	constexpr vec2& vec2::operator*=(const double v) noexcept
	{
		this->x = this->x * v;
		this->y = this->y * v;
		return *this;
	}

	constexpr vec2& vec2::operator/=(const double v) noexcept
	{
		this->x = this->x / v;
		this->y = this->y / v;
		return *this;
	}

	[[nodiscard]] constexpr double vec2::LengthSquared() const noexcept
	{
		return this->x * this->x + this->y * this->y;
	}

	[[nodiscard]] inline vec2 vec2::Normalize() const noexcept
	{
		double length = sqrt(LengthSquared());
		return *this / length;
	}

	[[nodiscard]] inline constexpr double vec2::Cross(const vec2& v) const noexcept
	{
		return this->x * v.y - this->y * v.x;
	}

	[[nodiscard]] constexpr vec2 operator+(const vec2 v1, const vec2 v2) noexcept
	{
		return vec2(v1.x + v2.x, v1.y + v2.y);
	}

	[[nodiscard]] constexpr vec2 operator-(const vec2 v1, const vec2 v2) noexcept
	{
		return vec2(v1.x - v2.x, v1.y - v2.y);
	}

	[[nodiscard]] constexpr vec2 operator-(const vec2 v1) noexcept
	{
		return vec2(-v1.x, -v1.y);
	}

	[[nodiscard]] constexpr vec2 operator*(double v1, const vec2 v2) noexcept
	{
		return vec2(v1 * v2.x, v1 * v2.y);
	}

	[[nodiscard]] constexpr vec2 operator*(const vec2 v1, double v2) noexcept
	{
		return vec2(v1.x * v2, v1.y * v2);
	}

	[[nodiscard]] constexpr vec2 operator/(const vec2 v1, double v2) noexcept
	{
		return vec2(v1.x / v2, v1.y / v2);
	}


	[[nodiscard]] constexpr bool operator==(const vec2 v1, const vec2 v2) noexcept
	{
		return (is_equal(v1.x, v2.x) == is_equal(v1.y, v2.y));
	}

	[[nodiscard]] constexpr bool operator!=(const vec2 v1, const vec2 v2) noexcept
	{
		return (!is_equal(v1.x, v2.x) || !is_equal(v1.y, v2.y));
	}

	/////////////////ivec2

	constexpr ivec2& ivec2::operator+=(const ivec2& v) noexcept
	{
		this->x = this->x + v.x;
		this->y = this->y + v.y;
		return *this;
	}

	inline constexpr ivec2& ivec2::operator-=(const ivec2& v) noexcept
	{
		this->x = this->x - v.x;
		this->y = this->y - v.y;
		return *this;
	}

	inline constexpr ivec2& ivec2::operator*=(const int v) noexcept
	{
		this->x = this->x * v;
		this->y = this->y * v;
		return *this;
	}

	inline constexpr ivec2& ivec2::operator/=(const int v) noexcept
	{
		this->x = this->x / v;
		this->y = this->y / v;
		return *this;
	}

	[[nodiscard]] constexpr ivec2 operator+(const ivec2 iv1, const ivec2 iv2) noexcept
	{
		return ivec2(iv1.x + iv2.x, iv1.y + iv2.y);
	}

	[[nodiscard]] constexpr ivec2 operator-(const ivec2 iv1, const ivec2 iv2) noexcept
	{
		return ivec2(iv1.x - iv2.x, iv1.y - iv2.y);
	}

	[[nodiscard]] constexpr ivec2 operator-(const ivec2 iv1) noexcept
	{
		return ivec2(-iv1.x, -iv1.y);
	}

	[[nodiscard]] constexpr ivec2 operator*(int iv1, const ivec2 iv2) noexcept
	{
		return ivec2(iv1 * iv2.x, iv1 * iv2.y);
	}

	[[nodiscard]] constexpr ivec2 operator*(const ivec2 iv1, int iv2) noexcept
	{
		return ivec2(iv1.x * iv2, iv1.y * iv2);
	}

	[[nodiscard]] constexpr ivec2 operator/(const ivec2 iv1, int iv2) noexcept
	{
		return ivec2(iv1.x / iv2, iv1.y / iv2);
	}

	[[nodiscard]] constexpr bool operator==(const ivec2 iv1, const ivec2 iv2) noexcept
	{
		return (is_equal(iv1.x, iv2.x) == is_equal(iv1.y, iv2.y));
	}

	[[nodiscard]] constexpr bool operator!=(const ivec2 iv1, const ivec2 iv2) noexcept
	{
		return (!is_equal(iv1.x, iv2.x) || !is_equal(iv1.y, iv2.y));
	}

	[[nodiscard]] constexpr vec2 operator*(double v1, const ivec2 iv2) noexcept
	{
		return vec2(v1 * iv2.x, v1 * iv2.y);
	}

	[[nodiscard]] constexpr vec2 operator*(const ivec2 iv1, double v2) noexcept
	{
		return vec2(iv1.x * v2, iv1.y * v2);
	}

	[[nodiscard]] constexpr vec2 operator/(const ivec2 iv1, double v2) noexcept
	{
		return vec2(iv1.x / v2, iv1.y / v2);
	}
}