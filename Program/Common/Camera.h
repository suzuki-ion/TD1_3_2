#pragma once
#include "Structures.h"
#include "CommonFunctions.h"
#include "CustomNovice.h"

class Camera {
public:
	Camera();

    void SetTranslate(const Vector2 &translate);
    void SetScale(const Vector2 &scale);
    void SetRotate(float rotate);
    void SetOrtho(float left, float top, float right, float bottom);
    void SetViewport(float left, float top, float width, float height);

	void SetCamera();
	void ResetCamera();
    void SetCamera(
		const Vector2 &translate, const Vector2 &scale, float rotate,
		float orthoLeft, float orthoTop, float orthoRight, float orthoBottom,
		float viewportLeft, float viewportTop, float viewportWidth, float viewportHeight
	);

    Vector2 GetTranslate() { return translate_; };
    Vector2 GetScale() { return scale_; };
    float GetRotate() { return rotate_; };
    Matrix3x3 GetCameraWorldMatrix() { return cameraWorldMatrix_; };
    Matrix3x3 GetWVPVPMatrix() { return wvpVpMatrix_; };
	Matrix3x3 GetInverseMatrix() { return InverseMatrix(wvpVpMatrix_); };

private:
	//カメラのワールドマトリックス
	Vector2 translate_;
	Vector2 scale_ = { 1.0f, 1.0f };
	float rotate_ = 0.0f;
	Matrix3x3 cameraWorldMatrix_;
	Matrix3x3 wvpVpMatrix_;

	//正規化用の変数　これが描画サイズ
	float orthoLeft_ = -(CustomNovice::WinWidth() / 2.0f);
	float orthoTop_ = CustomNovice::WinHeight() / 2.0f;
	float orthoRight_ = CustomNovice::WinWidth() / 2.0f;
	float orthoBottom_ = -(CustomNovice::WinHeight() / 2.0f);
	//映すスクリーンのサイズと位置
	float viewportLeft_ = 0.0f;
	float viewportTop_ = 0.0f;
	float viewportWidth_ = CustomNovice::WinWidth();
	float viewportHeight_ = CustomNovice::WinHeight();
};