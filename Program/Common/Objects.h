#pragma once
#include "Structures.h"
#include "Camera.h"
#include "CommonFunctions.h"

enum ObjectType {
    OBJECT_NONE,
    OBJECT_RECT,
    OBJECT_TRIANGLE,
    OBJECT_ELLIPSE,
};

// オブジェクトの基底クラス
class Object {
protected:
    Vector2 localCenterPos_;
    Vector2 objectPos_;
    Vector2 scale_ = { 1.0f, 1.0f };
    float rotate_ = 0.0f;
    unsigned int color_ = WHITE;
    Matrix3x3 localMatrix_ = MakeTranslateMatrix({ 0.0f, 0.0f });
    FillMode fillMode_ = kFillModeSolid;
    ObjectType objectType_ = OBJECT_NONE;

public:
    void SetLocalCenterPos(const Vector2 &centerPos) { localCenterPos_ = centerPos; }
    void SetObjectPos(const Vector2 &objectPos) { objectPos_ = objectPos; }
    void SetScale(const Vector2 &scale) { scale_ = scale; }
    void SetRotate(float rotate) { rotate_ = rotate; }
    void SetColor(unsigned int color) { color_ = color; }
    void SetLocalMatrix(const Matrix3x3 &localMatrix) { localMatrix_ = localMatrix; }
    void SetFillMode(FillMode fillMode) { fillMode_ = fillMode; }
    
    Vector2 GetLocalCenterPos() { return localCenterPos_; }
    Vector2 GetObjectPos() { return objectPos_; }
    Vector2 GetScale() { return scale_; }
    float GetRotate() { return rotate_; }
    unsigned int GetColor() { return color_; }
    Matrix3x3 GetLocalMatrix() { return localMatrix_; }
    FillMode GetFillMode() { return fillMode_; }
    ObjectType GetObjectType() { return objectType_; }

    void MakeLocalMatrix() { localMatrix_ = MakeAffineMatrix(scale_, rotate_, localCenterPos_); }

    virtual void Draw() {}
    virtual void Draw(const Matrix3x3 &parentMatrix) { parentMatrix; }
    virtual void Draw(Camera &camera) { camera; }
};

// 矩形オブジェクトクラス
class RectObject : public Object {
private:
    float width_ = 128.0f;
    float height_ = 128.0f;

public:
    RectObject() { objectType_ = OBJECT_RECT; }

    void SetWidth(float width) { width_ = width; }
    void SetHeight(float height) { height_ = height; }

    float GetWidth() { return width_; }
    float GetHeight() { return height_; }

    void Draw() override;

    void Draw(Camera &camera) override;
};

// 三角形オブジェクトクラス
class TriangleObject : public Object {
private:
    Vector2 pos1_ = { 0.0f, 64.0f };
    Vector2 pos2_ = { 32.0f, -64.0f };
    Vector2 pos3_ = { -32.0f, -64.0f };

public:
    TriangleObject() { objectType_ = OBJECT_TRIANGLE; }

    void SetPos1(const Vector2 &pos1) { pos1_ = pos1; }
    void SetPos2(const Vector2 &pos2) { pos2_ = pos2; }
    void SetPos3(const Vector2 &pos3) { pos3_ = pos3; }

    Vector2 GetPos1() { return pos1_; }
    Vector2 GetPos2() { return pos2_; }
    Vector2 GetPos3() { return pos3_; }

    void Draw() override;
    void Draw(Camera &camera) override;
};

// 楕円オブジェクトクラス
class EllipseObject : public Object {
private:
    float radiusX_ = 64.0f;
    float radiusY_ = 64.0f;

public:
    EllipseObject() { objectType_ = OBJECT_ELLIPSE; }

    void SetRadiusX(float radiusX) { radiusX_ = radiusX; }
    void SetRadiusY(float radiusY) { radiusY_ = radiusY; }

    float GetRadiusX() { return radiusX_; }
    float GetRadiusY() { return radiusY_; }

    void Draw() override;
    void Draw(Camera &camera) override;
};