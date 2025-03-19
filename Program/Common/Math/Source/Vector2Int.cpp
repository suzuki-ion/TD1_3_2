#include <Common/Math/Vector2Int.h>

Vector2Int Vector2Int::operator=(const Vector2Int &v) const {
    return { v.x, v.y };
}

Vector2Int Vector2Int::operator+(const Vector2Int &v) const {
    return { x + v.x, y + v.y };
}

Vector2Int Vector2Int::operator-(const Vector2Int &v) const {
    return { x - v.x, y - v.y };
}

Vector2Int Vector2Int::operator*(const Vector2Int &v) const {
    return { x * v.x, y * v.y };
}

Vector2Int Vector2Int::operator/(const Vector2Int &v) const {
    return { x / v.x, y / v.y };
}

Vector2Int Vector2Int::operator*(int num) const {
    return { x * num, y * num };
}

Vector2Int Vector2Int::operator/(int num) const {
    return { x / num, y / num };
}

Vector2Int Vector2Int::operator+=(const Vector2Int &v) {
    return { x += v.x, y += v.y };
}

Vector2Int Vector2Int::operator-=(const Vector2Int &v) {
    return { x -= v.x, y -= v.y };
}

Vector2Int Vector2Int::operator*=(const Vector2Int &v) {
    return { x *= v.x, y *= v.y };
}

Vector2Int Vector2Int::operator/=(const Vector2Int &v) {
    return { x /= v.x, y /= v.y };
}

bool Vector2Int::operator==(const Vector2Int &v) const {
    return (x == v.x) && (y == v.y);
}

bool Vector2Int::operator!=(const Vector2Int &v) const {
    return (x != v.x) || (y != v.y);
}

bool Vector2Int::operator<(const Vector2Int &v) const {
    return (x < v.x) && (y < v.y);
}

bool Vector2Int::operator>(const Vector2Int &v) const {
    return (x > v.x) && (y > v.y);
}

bool Vector2Int::operator<=(const Vector2Int &v) const {
    return (x <= v.x) && (y <= v.y);
}

bool Vector2Int::operator>=(const Vector2Int &v) const {
    return (x >= v.x) && (y >= v.y);
}