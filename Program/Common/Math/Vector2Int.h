#pragma once

/// @brief int型の二次元ベクトル構造体
struct Vector2Int final {
    Vector2Int() = default;
    Vector2Int(int x, int y) : x(x), y(y) {}
    Vector2Int(const Vector2Int &v) : x(v.x), y(v.y) {}
    Vector2Int operator=(const Vector2Int &v) const;
    Vector2Int operator+(const Vector2Int &v) const;
    Vector2Int operator-(const Vector2Int &v) const;
    Vector2Int operator*(const Vector2Int &v) const;
    Vector2Int operator/(const Vector2Int &v) const;
    Vector2Int operator*(int num) const;
    Vector2Int operator/(int num) const;
    Vector2Int operator+=(const Vector2Int &v);
    Vector2Int operator-=(const Vector2Int &v);
    Vector2Int operator*=(const Vector2Int &v);
    Vector2Int operator/=(const Vector2Int &v);
    bool operator==(const Vector2Int &v) const;
    bool operator!=(const Vector2Int &v) const;
    bool operator<(const Vector2Int &v) const;
    bool operator>(const Vector2Int &v) const;
    bool operator<=(const Vector2Int &v) const;
    bool operator>=(const Vector2Int &v) const;

    static Vector2Int InitialValue() {
        static Vector2Int vector;
        return vector;
    }

    // X座標
    int x = 0;
    // Y座標
    int y = 0;
};