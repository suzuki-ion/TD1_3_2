#include <Common/Math/Matrix3x3.h>

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