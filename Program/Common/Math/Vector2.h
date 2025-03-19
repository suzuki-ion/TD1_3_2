#pragma once

/// @brief 二次元ベクトル構造体
struct Vector2 final {
    Vector2() = default;
    Vector2(float x, float y) : x(x), y(y) {}
    Vector2(const Vector2 &v) : x(v.x), y(v.y) {}
    Vector2 operator=(const Vector2 &v) const;
    Vector2 operator+(const Vector2 &v) const;
    Vector2 operator-(const Vector2 &v) const;
    Vector2 operator*(const Vector2 &v) const;
    Vector2 operator/(const Vector2 &v) const;
    Vector2 operator*(float f) const;
    Vector2 operator/(float f) const;
    Vector2 operator+=(const Vector2 &v);
    Vector2 operator-=(const Vector2 &v);
    Vector2 operator*=(const Vector2 &v);
    Vector2 operator/=(const Vector2 &v);
    bool operator==(const Vector2 &v) const;
    bool operator!=(const Vector2 &v) const;
    bool operator<(const Vector2 &v) const;
    bool operator>(const Vector2 &v) const;
    bool operator<=(const Vector2 &v) const;
    bool operator>=(const Vector2 &v) const;

    static Vector2 InitialValue() {
        static Vector2 vector;
        return vector;
    }

    // X座標
    float x = 0.0f;
    // Y座標
    float y = 0.0f;
};