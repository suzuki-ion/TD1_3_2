#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <fstream>
#include <Common/CommonFunctions.h>
#define M_PI (4.0f * atanf(1.0f))

template <typename Type>
void Swap(Type *a, Type *b) {
    Type tmp = *a;
    *a = *b;
    *b = tmp;
}

void Shuffle(int(*array)[], int max) {
    for (int i = 0; i < max; i++) {
        // i番目の値とランダムな位置の値を交換する
        Swap(&(*array)[i], &(*array)[rand() % max]);
    }
}

int CustomRangeRand(int min, int max) {
    return rand() % (max + 1 - min) + min;
}

float ConvertDeg2Rad(float degree) {
    return degree * M_PI / 180.0f;
}

float ConvertRad2Deg(float radian) {
    return radian * 180.0f / M_PI;
}

float Length(float x, float y) {
    return sqrtf(x * x + y * y);
}

Vector2 Normalize(float x, float y) {
    float length = Length(x, y);

    // length が 0 でなければ正規化した長さを返す
    if (length != 0.0f) {
        return {
            x / length,
            y / length
        };
    } else {
        // length が 0 なら 0 を返す
        return { 0.0f, 0.0f };
    }
}

float DotProduct(float x1, float y1, float x2, float y2) {
    return x1 * x2 + y1 * y2;
}

float CrossProduct(float x1, float y1, float x2, float y2) {
    return x1 * y2 - y1 * x2;
}

float Clamp(float t, float min, float max) {
    // tが指定された値を超えてたら指定された値で初期化
    if (t > max) {
        t = max;
    } else if (t < min) {
        t = min;
    }
    return t;
}

int IsCircle2CircleHit(float x1, float y1, float radius1, float x2, float y2, float radius2) {
    float x = x2 - x1;
    float y = y2 - y1;

    // 2つの円の半径の和よりも中心点間の距離のほうが短いならtrueを返す
    if (Length(x, y) <= radius1 + radius2) {
        return true;
    } else {
        // そうでなければfalseを返す
        return false;
    }
}

int IsRect2RectHit(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2) {
    if (x1 < x2 + width2 &&
        x2 < x1 + width1 &&
        y1 < y2 + height2 &&
        y2 < y1 + height1) {
        return true;
    } else {
        return false;
    }
}

int IsPos2CircleHit(float posX, float posY, float circleX, float circleY, float circleRadius) {
    float x = circleX - posX;
    float y = circleY - posY;

    // 円の半径よりも中心点間の距離のほうが短いならtrueを返す
    if (Length(x, y) <= circleRadius) {
        return true;
    } else {
        // そうでなければfalseを返す
        return false;
    }
}

int IsPos2RectHit(float posX, float posY, float rectX, float rectY, float rectWidth, float rectHeight) {
    if (posX < rectX + rectWidth &&
        rectX < posX &&
        posY < rectY + rectHeight &&
        rectY < posY) {
        return true;
    } else {
        return false;
    }
}

int IsCircle2RectHit(float circleX, float circleY, float radius, float rectX, float rectY, float width, float height) {
    int isHit = false;

    // 四角形の四辺に対して円の半径分だけ足したとき円が重なっていたら
    if ((circleX > rectX - radius) &&
        (circleX < rectX + width + radius) &&
        (circleY > rectY - radius) &&
        (circleY < rectY + height + radius)) {
        isHit = true;

        // 左
        if (circleX < rectX) {
            // 左上
            if (circleY < rectY) {
                if (!IsPos2CircleHit(circleX, circleY, rectX, rectY, radius)) {
                    isHit = false;
                }
            } else {
                // 左下
                if (circleY > rectY + height) {
                    if (!IsPos2CircleHit(circleX, circleY, rectX, rectY + height, radius)) {
                        isHit = false;
                    }
                }
            }
        } else {
            // 右
            if (circleX > rectX + width) {
                // 右上
                if (circleY < rectY) {
                    if (!IsPos2CircleHit(circleX, circleY, rectX + width, rectY, radius)) {
                        isHit = false;
                    }
                } else {
                    // 右下
                    if (circleY > rectY + height) {
                        if (!IsPos2CircleHit(circleX, circleY, rectX + width, rectY + height, radius)) {
                            isHit = false;
                        }
                    }
                }
            }
        }
    }

    return isHit;
}

int IsCircle2CapsuleHit(float circleX, float circleY, float circleRadius, float capsuleX1, float capsuleY1, float capsuleX2, float capsuleY2, float capsuleRadius) {
    Vector2 d = {
        circleX - capsuleX1,
        circleY - capsuleY1
    };
    Vector2 ba = {
        capsuleX2 - capsuleX1,
        capsuleY2 - capsuleY1
    };
    // baを正規化
    Vector2 e = Normalize(ba.x, ba.y);
    // tの値を求める
    float t = DotProduct(d.x, d.y, e.x, e.y) / Length(ba.x, ba.y);
    // tを0～1の範囲に収める
    t = Clamp(t, 0.0f, 1.0f);
    // 線形補完
    Vector2 f = {
        (1.0f - t) * capsuleX1 + t * capsuleX2,
        (1.0f - t) * capsuleY1 + t * capsuleY2
    };
    // 距離を求める
    float distance = Length(circleX - f.x, circleY - f.y);
    // 円とカプセルの半径の合計よりもc-fの長さが短ければ衝突
    if (distance < circleRadius + capsuleRadius) {
        // 衝突していたらtrueを返す
        return true;
    } else {
        // 衝突していなかったらfalseを返す
        return false;
    }
}

int IsOutsideAreaCircle(float circleX, float circleY, float radius, float areaX, float areaY, float areaWidth, float areaHeight) {
    if (circleX - radius < areaX ||
        circleY - radius < areaY ||
        circleX + radius > areaX + areaWidth ||
        circleY + radius > areaY + areaHeight) {
        return true;
    } else {
        return false;
    }
}

int IsOutsideAreaRect(float rectX, float rectY, float rectWidth, float rectHeight, float areaX, float areaY, float areaWidth, float areaHeight) {
    if (rectX < areaX ||
        rectY < areaY ||
        rectX + rectWidth > areaX + areaWidth ||
        rectY + rectHeight > areaY + areaHeight) {
        return true;
    } else {
        return false;
    }
}

Vector2 RotatePos(float rotateX, float rotateY, float originX, float originY, float theta) {
    return {
        originX + ((rotateX - originX) * cosf(theta) - (rotateY - originY) * sinf(theta)),
        originY + ((rotateY - originY) * cosf(theta) + (rotateX - originX) * sinf(theta)),
    };
}

float ConvertWCX(float posX, float worldOriginPosX) {
    return worldOriginPosX + posX;
}

float ConvertWCY(float posY, float worldOriginPosY) {
    return worldOriginPosY - posY;
}

float ConvertInt2Time(int nowT, int endT) {
    // 割る値が 0 なら強制的に 1.0f を返す
    if (endT == 0) {
        return 1.0f;
    } else {
        // 値が必ず 0.0f ～ 1.0f になるようにする
        return Clamp(static_cast<float>(nowT) / static_cast<float>(endT), 0.0f, 1.0f);
    }
}

float ConvertFloat2Time(float nowT, float endT) {
    // 割る値が 0.0f なら強制的に 1.0f を返す
    if (endT == 0.0f) {
        return 1.0f;
    } else {
        // 値が必ず 0.0f ～ 1.0f になるようにする
        return Clamp(static_cast<float>(nowT) / static_cast<float>(endT), 0.0f, 1.0f);
    }
}

int GetDigit(int num) {
    // 桁数
    int digit = 1;
    // 描画する値が1桁になるまで 10 で割り続ける
    for (digit = 1; num > 9; digit++) {
        num /= 10;
    }

    // 桁数を返す
    return digit;
}

Matrix3x3 MakeRotateMatrix(float theta) {
    // 回転行列
    Matrix3x3 rotateMatrix;

    rotateMatrix.m[0][0] = cosf(theta);
    rotateMatrix.m[0][1] = sinf(theta);
    rotateMatrix.m[1][0] = -sinf(theta);
    rotateMatrix.m[1][1] = cosf(theta);
    rotateMatrix.m[2][2] = 1.0f;

    return rotateMatrix;
}

Matrix3x3 MakeScaleMatrix(Vector2 scale) {
    Matrix3x3 scaleMatrix;

    scaleMatrix.m[0][0] = scale.x;
    scaleMatrix.m[1][1] = scale.y;
    scaleMatrix.m[2][2] = 1.0f;
    
    return scaleMatrix;
}

Matrix3x3 MakeTranslateMatrix(Vector2 translate) {
    // 平行移動行列
    Matrix3x3 translateMatrix;

    for (int i = 0; i < 3; i++) {
        translateMatrix.m[i][i] = 1.0f;
    }
    translateMatrix.m[2][0] = translate.x;
    translateMatrix.m[2][1] = translate.y;

    return translateMatrix;
}

Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate) {
    // アフィン行列
    Matrix3x3 affineMatrix;

    // 回転と拡縮をかける
    affineMatrix.m[0][0] = cosf(rotate) * scale.x;
    affineMatrix.m[0][1] = sinf(rotate) * scale.x;
    affineMatrix.m[1][0] = -sinf(rotate) * scale.y;
    affineMatrix.m[1][1] = cosf(rotate) * scale.y;

    // 平行移動
    affineMatrix.m[2][0] = translate.x;
    affineMatrix.m[2][1] = translate.y;

    // 最後の列を 0 0 1 になるようにする
    affineMatrix.m[0][2] = 0.0f;
    affineMatrix.m[1][2] = 0.0f;
    affineMatrix.m[2][2] = 1.0f;

    return affineMatrix;
}

Vector2 Transform(Vector2 vector, Matrix3x3 matrix) {
    // w=1 がデカルト座標系であるので (x, y, 1) のベクトルとして matrix との積を取る
    Vector2 result;

    result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
    result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
    float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];

    // ベクトルに対して基本的な操作を行う行列で w が 0 になることはありえない
    assert(w != 0.0f);

    // w=1 がデカルト座標系であるので、w 除算することで同次座標をデカルト座標系に戻す
    result.x /= w;
    result.y /= w;

    return result;
}

Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {
    // 行列の積の値保存用
    Matrix3x3 multiplyMatrix;

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            // 横と縦の積を求めて加算
            for (int i = 0; i < 3; i++) {
                multiplyMatrix.m[row][col] += matrix1.m[row][i] * matrix2.m[i][col];
            }
        }
    }

    // 行列の積の値を返す
    return multiplyMatrix;
}

Matrix3x3 Transpose(Matrix3x3 matrix) {
    // 転置行列
    Matrix3x3 transpose;

    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            transpose.m[row][column] = matrix.m[column][row];
        }
    }

    return transpose;
}

Matrix3x3 InverseMatrix(Matrix3x3 matrix) {
    Matrix3x3 result;

    float determinant = matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] + matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] + matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] - matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] - matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] - matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1];

    result.m[0][0] = (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]) / determinant;
    result.m[0][1] = (-1.0f * (matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1])) / determinant;
    result.m[0][2] = (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]) / determinant;

    result.m[1][0] = (-1.0f * (matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0])) / determinant;
    result.m[1][1] = (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]) / determinant;
    result.m[1][2] = (-1.0f * (matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0])) / determinant;

    result.m[2][0] = (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]) / determinant;
    result.m[2][1] = (-1.0f * (matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0])) / determinant;
    result.m[2][2] = (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]) / determinant;

    return result;
}

Matrix3x3 MakeOrthhogprahicsMatrix(float left, float top, float right, float bottom) {
    Matrix3x3 result;

    result.m[0][0] = 2.0f / (right - left);
    result.m[1][1] = 2.0f / (top - bottom);
    result.m[2][2] = 1.0f;

    result.m[2][0] = (left + right) / (left - right);
    result.m[2][1] = (top + bottom) / (bottom - top);

    return result;
}

Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height) {
    Matrix3x3 result;

    result.m[0][0] = width / 2.0f;
    result.m[1][1] = -(height / 2.0f);
    result.m[2][2] = 1.0f;

    result.m[2][0] = left + (width / 2.0f);
    result.m[2][1] = top + (height / 2.0f);

    return result;
}

Matrix3x3 RenderingPipeline(Matrix3x3 worldMatrix, Matrix3x3 cameraWorldMatrix, float orthoLeft, float orthoTop, float orthoRight, float orthoBottom, float viewportLeft, float viewportTop, float viewportWidth, float viewportHeight) {
    Matrix3x3 wvpVpMatrix;

    Matrix3x3 viewMatrix = InverseMatrix(cameraWorldMatrix);
    Matrix3x3 orthoMatrix = MakeOrthhogprahicsMatrix(orthoLeft, orthoTop, orthoRight, orthoBottom);
    Matrix3x3 viewportMatrix = MakeViewportMatrix(viewportLeft, viewportTop, viewportWidth, viewportHeight);

    wvpVpMatrix = Multiply(worldMatrix, viewMatrix);
    wvpVpMatrix = Multiply(wvpVpMatrix, orthoMatrix);
    wvpVpMatrix = Multiply(wvpVpMatrix, viewportMatrix);

    return wvpVpMatrix;
}

void MakeQuadPos(const Vector2 &pivot, Vector2 &leftTop, Vector2 &rightTop, Vector2 &leftBottom, Vector2 &rightBottom, float width, float height) {
    leftTop.x = -pivot.x;
    leftTop.y = pivot.y;

    rightTop.x = width - pivot.x;
    rightTop.y = pivot.y;

    leftBottom.x = -pivot.x;
    leftBottom.y = -height + pivot.y;

    rightBottom.x = width - pivot.x;
    rightBottom.y = -height + pivot.y;
}

bool IsPushedKeys(std::vector<int> keysID, char *keys) {
    for (const auto &key : keysID) {
        if (keys[key]) {
            return true;
        }
    }
    return false;
}

bool IsPrePushedKeys(std::vector<int> keysID, char *preKeys) {
    for (const auto &key : keysID) {
        if (preKeys[key]) {
            return true;
        }
    }
    return false;
}

bool IsReleaseKeys(std::vector<int> keysID, char *keys, char *preKeys) {
    for (const auto &key : keysID) {
        if (preKeys[key] && !keys[key]) {
            return true;
        }
    }
    return false;
}

bool IsTriggerKeys(std::vector<int> keysID, char *keys, char *preKeys) {
    for (const auto &key : keysID) {
        if (keys[key] && !preKeys[key]) {
            return true;
        }
    }
    return false;
}

bool IsFileExists(const std::string &fileName) {
    std::ifstream file(fileName);
    return file.good();
}

bool StringEndsWith(const std::string &str, const std::string &end) {
    if (str.length() < end.length()) {
        return false;
    }
    return str.substr(str.size() - end.size()) == end;
};