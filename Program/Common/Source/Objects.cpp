#include <Common/CustomNovice.h>
#include <Common/CommonFunctions.h>
#include <Common/Objects.h>

void RectObject::Draw() {
    static Vector2 drawPos;
    drawPos.x = objectPos_.x - width_ / 2.0f;
    drawPos.y = objectPos_.y + height_ / 2.0f;
	MakeLocalMatrix();
    drawPos = Transform(drawPos, localMatrix_);
	CustomNovice::DrawBox(
		drawPos.x,
		drawPos.y,
		width_ * scale_.x,
		height_ * scale_.y,
		color_,
		-rotate_,
		fillMode_
	);
}

void RectObject::Draw(Camera &camera) {
	static Vector2 drawPos;
    drawPos.x = objectPos_.x - width_ / 2.0f;
    drawPos.y = objectPos_.y + height_ / 2.0f;
    MakeLocalMatrix();
    drawPos = Transform(drawPos, localMatrix_ * camera.GetWVPVPMatrix());
	CustomNovice::DrawBox(
		drawPos.x,
		drawPos.y,
		width_ * scale_.x / camera.GetScale().x,
		height_ * scale_.y / camera.GetScale().y,
		color_,
        -rotate_ + camera.GetRotate(),
		fillMode_
	);
}

void TriangleObject::Draw() {
	MakeLocalMatrix();
	Vector2 drawPos1 = Transform(pos1_, localMatrix_);
	Vector2 drawPos2 = Transform(pos2_, localMatrix_);
	Vector2 drawPos3 = Transform(pos3_, localMatrix_);
    CustomNovice::DrawTriangle(
        drawPos1.x,
        drawPos1.y,
		drawPos2.x,
        drawPos2.y,
        drawPos3.x,
        drawPos3.y,
        color_,
        fillMode_
    );
}

void TriangleObject::Draw(Camera &camera) {
    MakeLocalMatrix();
	Vector2 drawPos1 = Transform(objectPos_ + pos1_, localMatrix_);
	Vector2 drawPos2 = Transform(objectPos_ + pos2_, localMatrix_);
	Vector2 drawPos3 = Transform(objectPos_ + pos3_, localMatrix_);
	CustomNovice::DrawTriangle(
        camera,
		drawPos1.x,
		drawPos1.y,
		drawPos2.x,
		drawPos2.y,
		drawPos3.x,
		drawPos3.y,
		color_,
		fillMode_
	);
}

void EllipseObject::Draw() {
    static Vector2 drawPos;
	MakeLocalMatrix();
    drawPos = Transform(objectPos_, localMatrix_);
    CustomNovice::DrawEllipse(
        drawPos.x,
        drawPos.y,
        radiusX_ * scale_.x,
        radiusY_ * scale_.y,
        color_,
        -rotate_,
        fillMode_
    );
}

void EllipseObject::Draw(Camera &camera) {
    static Vector2 drawPos;
    MakeLocalMatrix();
	drawPos = Transform(objectPos_, localMatrix_);
    CustomNovice::DrawEllipse(
        camera,
        drawPos.x,
        drawPos.y,
        radiusX_ * scale_.x / camera.GetScale().x,
        radiusY_ * scale_.y / camera.GetScale().y,
        color_,
        -rotate_,
        fillMode_
    );
}
