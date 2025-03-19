#include <Common/Math/Matrix3x3.h>

Matrix3x3::Matrix3x3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22) {
    m[0][0] = m00;
    m[0][1] = m01;
    m[0][2] = m02;
    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;
    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;
}

Matrix3x3::Matrix3x3(float matrix[9]) {
    for (int i = 0; i < 9; i++) {
        m[i / 3][i % 3] = matrix[i];
    }
}

Matrix3x3::Matrix3x3(float matrix[3][3]) {
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            m[row][column] = matrix[row][column];
        }
    }
}

Matrix3x3::Matrix3x3(const Matrix3x3 &matrix) {
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            m[row][column] = matrix.m[row][column];
        }
    }
}

Matrix3x3 Matrix3x3::operator=(const Matrix3x3 &matrix) const {
    Matrix3x3 result;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            result.m[row][column] = matrix.m[row][column];
        }
    }
    return result;
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3 &matrix) const {
    Matrix3x3 result;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            result.m[row][column] = m[row][column] + matrix.m[row][column];
        }
    }
    return result;
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3 &matrix) const {
    Matrix3x3 result;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            result.m[row][column] = m[row][column] - matrix.m[row][column];
        }
    }
    return result;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3 &matrix) const {
    Matrix3x3 result;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            for (int i = 0; i < 3; i++) {
                result.m[row][column] += m[row][i] * matrix.m[i][column];
            }
        }
    }
    return result;
}

Matrix3x3 Matrix3x3::operator/(const Matrix3x3 &matrix) const {
    Matrix3x3 result;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            result.m[row][column] = m[row][column] / matrix.m[row][column];
        }
    }
    return result;
}

Matrix3x3 Matrix3x3::operator*(float f) const {
    Matrix3x3 result;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            result.m[row][column] = m[row][column] * f;
        }
    }
    return result;
}

Matrix3x3 Matrix3x3::operator/(float f) const {
    Matrix3x3 result;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            result.m[row][column] = m[row][column] / f;
        }
    }
    return result;
}

Matrix3x3 Matrix3x3::operator+=(const Matrix3x3 &matrix) {
    Matrix3x3 result;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            result.m[row][column] = m[row][column] + matrix.m[row][column];
        }
    }
    return result;
}

Matrix3x3 Matrix3x3::operator-=(const Matrix3x3 &matrix) {
    Matrix3x3 result;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            result.m[row][column] = m[row][column] - matrix.m[row][column];
        }
    }
    return result;
}

Matrix3x3 Matrix3x3::operator*=(const Matrix3x3 &matrix) {
    Matrix3x3 result;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            for (int i = 0; i < 3; i++) {
                result.m[row][column] = m[row][i] * matrix.m[i][column];
            }
        }
    }
    return result;
}

Matrix3x3 Matrix3x3::operator/=(const Matrix3x3 &matrix) {
    Matrix3x3 result;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            result.m[row][column] = m[row][column] / matrix.m[row][column];
        }
    }
    return result;
}

bool Matrix3x3::operator==(const Matrix3x3 &matrix) const {
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            if (m[row][column] != matrix.m[row][column]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix3x3::operator!=(const Matrix3x3 &matrix) const {
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            if (m[row][column] == matrix.m[row][column]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix3x3::operator<(const Matrix3x3 &matrix) const {
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            if (m[row][column] >= matrix.m[row][column]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix3x3::operator>(const Matrix3x3 &matrix) const {
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            if (m[row][column] <= matrix.m[row][column]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix3x3::operator<=(const Matrix3x3 &matrix) const {
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            if (m[row][column] > matrix.m[row][column]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix3x3::operator>=(const Matrix3x3 &matrix) const {
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            if (m[row][column] < matrix.m[row][column]) {
                return false;
            }
        }
    }
    return true;
}