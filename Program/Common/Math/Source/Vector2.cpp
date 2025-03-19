#include <Common/Math/Vector2.h>

Vector2 Vector2::operator=(const Vector2 &v) const {
    return { v.x, v.y };
}

Vector2 Vector2::operator+(const Vector2 &v) const {
    return { x + v.x, y + v.y };
}

Vector2 Vector2::operator-(const Vector2 &v) const {
    return { x - v.x, y - v.y };
}

Vector2 Vector2::operator*(const Vector2 &v) const {
    return { x * v.x, y * v.y };
}

Vector2 Vector2::operator/(const Vector2 &v) const {
    return { x / v.x, y / v.y };
}

Vector2 Vector2::operator*(float f) const {
    return { x * f, y * f };
}

Vector2 Vector2::operator/(float f) const {
    return { x / f, y / f };
}

Vector2 Vector2::operator+=(const Vector2 &v) {
    return { x += v.x, y += v.y };
}

Vector2 Vector2::operator-=(const Vector2 &v) {
    return { x -= v.x, y -= v.y };
}

Vector2 Vector2::operator*=(const Vector2 &v) {
    return { x *= v.x, y *= v.y };
}

Vector2 Vector2::operator/=(const Vector2 &v) {
    return { x /= v.x, y /= v.y };
}

bool Vector2::operator==(const Vector2 &v) const {
    return (x == v.x) && (y == v.y);
}

bool Vector2::operator!=(const Vector2 &v) const {
    return (x != v.x) || (y != v.y);
}

bool Vector2::operator<(const Vector2 &v) const {
    return (x < v.x) && (y < v.y);
}

bool Vector2::operator>(const Vector2 &v) const {
    return (x > v.x) && (y > v.y);
}

bool Vector2::operator<=(const Vector2 &v) const {
    return (x <= v.x) && (y <= v.y);
}

bool Vector2::operator>=(const Vector2 &v) const {
    return (x >= v.x) && (y >= v.y);
}