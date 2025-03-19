#include <Common/Camera.h>
#include <Common/CustomNovice.h>

Camera::Camera() {
    SetCamera();
}

void Camera::SetTranslate(const Vector2 &translate) {
    translate_ = translate;
}

void Camera::SetScale(const Vector2 &scale) {
    scale_ = scale;
}

void Camera::SetRotate(float rotate) {
    rotate_ = rotate;
}

void Camera::SetOrtho(float left, float top, float right, float bottom) {
    orthoLeft_ = left;
    orthoTop_ = top;
    orthoRight_ = right;
    orthoBottom_ = bottom;
}

void Camera::SetViewport(float left, float top, float width, float height) {
    viewportLeft_ = left;
    viewportTop_ = top;
    viewportWidth_ = width;
    viewportHeight_ = height;
}

void Camera::SetCamera() {
    SetCamera(
        translate_, scale_, rotate_,
        orthoLeft_, orthoTop_, orthoRight_, orthoBottom_,
        viewportLeft_, viewportTop_, viewportWidth_, viewportHeight_
    );
}

void Camera::ResetCamera() {
    // 全変数を初期化
    translate_ = { 0.0f, 0.0f };
    scale_ = { 1.0f, 1.0f };
    rotate_ = 0.0f;
    orthoLeft_ = -(CustomNovice::WinWidth() / 2.0f);
    orthoTop_ = CustomNovice::WinHeight() / 2.0f;
    orthoRight_ = CustomNovice::WinWidth() / 2.0f;
    orthoBottom_ = -(CustomNovice::WinHeight() / 2.0f);
    viewportLeft_ = 0.0f;
    viewportTop_ = 0.0f;
    viewportWidth_ = CustomNovice::WinWidth();
    viewportHeight_ = CustomNovice::WinHeight();
    
    SetCamera();
}

void Camera::SetCamera(const Vector2 &translate, const Vector2 &scale, float rotate,
    float orthoLeft, float orthoTop, float orthoRight, float orthoBottom,
    float viewportLeft, float viewportTop, float viewportWidth, float viewportHeight) {

	// カメラのワ－ルドマトリックスの作成
	cameraWorldMatrix_ = MakeAffineMatrix(scale, rotate, translate);
	// カメラの処理のための作成
	wvpVpMatrix_ = RenderingPipeline(
		MakeTranslateMatrix({ 0.0f, 0.0f }),
		cameraWorldMatrix_,
		orthoLeft, orthoTop, orthoRight, orthoBottom, 
		viewportLeft, viewportTop, viewportWidth, viewportHeight
	);
}