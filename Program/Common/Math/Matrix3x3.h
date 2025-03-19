#pragma once

/// @brief 3x3行列
struct Matrix3x3 final {
    Matrix3x3() = default;
    Matrix3x3(float matrix[3][3]);
    Matrix3x3(const Matrix3x3 &matrix);
    Matrix3x3 operator=(const Matrix3x3 &matrix) const;
    Matrix3x3 operator+(const Matrix3x3 &matrix) const;
    Matrix3x3 operator-(const Matrix3x3 &matrix) const;
    Matrix3x3 operator*(const Matrix3x3 &matrix) const;
    Matrix3x3 operator/(const Matrix3x3 &matrix) const;
    Matrix3x3 operator*(float f) const;
    Matrix3x3 operator/(float f) const;
    Matrix3x3 operator+=(const Matrix3x3 &matrix);
    Matrix3x3 operator-=(const Matrix3x3 &matrix);
    Matrix3x3 operator*=(const Matrix3x3 &matrix);
    Matrix3x3 operator/=(const Matrix3x3 &matrix);
    bool operator==(const Matrix3x3 &matrix) const;
    bool operator!=(const Matrix3x3 &matrix) const;
    bool operator<(const Matrix3x3 &matrix) const;
    bool operator>(const Matrix3x3 &matrix) const;
    bool operator<=(const Matrix3x3 &matrix) const;
    bool operator>=(const Matrix3x3 &matrix) const;

    static Matrix3x3 InitialValue() {
        static Matrix3x3 matrix;
        return matrix;
    }
    static Matrix3x3 Identity() {
        static Matrix3x3 matrix = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        };
        return matrix;
    }

    float m[3][3] = {
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f }
    };
};