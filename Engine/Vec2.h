/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vec2.h
Author: Seulbin Seo
Creation date:  04/15/2022
-----------------------------------------------------------------*/
#pragma once
#include <cmath>
#include <limits>
namespace math
{
    [[nodiscard]] constexpr double abs(double d) noexcept { return (d < 0.0) ? -d : d; }
    [[nodiscard]] constexpr bool is_equal(double d1, double d2) noexcept
    {
        return abs(d1 - d2) <= std::numeric_limits<double>::epsilon() * abs(d1 + d2);
    }
    [[nodiscard]] constexpr bool is_equal(int i1, int i2) noexcept { return i1 == i2; }


    struct vec2
    {
        double x{ 0 };
        double y{ 0 };
        [[nodiscard]] constexpr vec2() noexcept = default;//vec2 a;
        [[nodiscard]] constexpr explicit vec2(double value) noexcept : vec2(value, value) {}//vec2 a(1.0)
        [[nodiscard]] constexpr  vec2(double x_, double y_) noexcept : x(x_), y(y_) {}//vec2 a(0.9,9.8)
        [[nodiscard]] constexpr vec2(int value) noexcept : vec2(static_cast<double>(value)) {}

        constexpr vec2& operator+=(const vec2& v) noexcept;
        constexpr vec2& operator-=(const vec2& v) noexcept;
        constexpr vec2& operator*=(const double v) noexcept;
        constexpr vec2& operator/=(const double v) noexcept;

        [[nodiscard]] constexpr double LengthSquared()const noexcept;
        [[nodiscard]] vec2 Normalize() const noexcept;
        [[nodiscard]] constexpr double Cross(const vec2& v) const noexcept;
    };

    [[nodiscard]] constexpr vec2 operator+(const vec2 v1, const vec2 v2) noexcept;
    [[nodiscard]] constexpr vec2 operator-(const vec2 v1, const vec2 v2) noexcept;
    [[nodiscard]] constexpr vec2 operator-(const vec2 v1) noexcept;
    [[nodiscard]] constexpr vec2 operator*(const vec2 v1, const vec2 v2) noexcept;
    [[nodiscard]] constexpr vec2 operator*(double v1, const vec2 v2) noexcept;
    [[nodiscard]] constexpr vec2 operator*(const vec2 v1, int iv2) noexcept;
    [[nodiscard]] constexpr vec2 operator/(const vec2 v1, double v2) noexcept;
    [[nodiscard]] constexpr bool operator==(const vec2 v1, const vec2 v2) noexcept;
    [[nodiscard]] constexpr bool operator!=(const vec2 v1, const vec2 v2) noexcept;

    struct ivec2
    {
        int x{ 0 };
        int y{ 0 };
        [[nodiscard]] constexpr ivec2() noexcept = default;
        [[nodiscard]] constexpr explicit ivec2(int value) noexcept : ivec2(value, value) {}
        [[nodiscard]] constexpr  ivec2(int x_i, int y_i) noexcept : x(x_i), y(y_i) {}

        constexpr ivec2& operator+=(const ivec2& iv) noexcept;
        constexpr ivec2& operator-=(const ivec2& iv) noexcept;
        constexpr ivec2& operator*=(const int iv) noexcept;
        constexpr ivec2& operator/=(const int iv) noexcept;

        [[nodiscard]] explicit constexpr operator vec2() { return vec2{ static_cast<double>(x),static_cast<double>(y) }; }
    };

    [[nodiscard]] constexpr ivec2 operator+(const ivec2 iv1, const ivec2 iv2) noexcept;
    [[nodiscard]] constexpr ivec2 operator-(const ivec2 iv1, const ivec2 iv2) noexcept;
    [[nodiscard]] constexpr ivec2 operator-(const ivec2 iv1) noexcept;
    [[nodiscard]] constexpr ivec2 operator*(const ivec2 iv1, const ivec2 iv2) noexcept;
    [[nodiscard]] constexpr ivec2 operator*(int iv1, const ivec2 iv2) noexcept;
    [[nodiscard]] constexpr bool operator==(const ivec2 iv1, const ivec2 iv2) noexcept;
    [[nodiscard]] constexpr bool operator!=(const ivec2 iv1, const ivec2 iv2) noexcept;
    [[nodiscard]] constexpr vec2 operator*(double v1, const ivec2 iv2) noexcept;
    [[nodiscard]] constexpr vec2 operator*(const ivec2 iv1, double v2) noexcept;
    [[nodiscard]] constexpr vec2 operator/(const ivec2 iv1, double v2) noexcept;
}

#include "Vec2.inl"