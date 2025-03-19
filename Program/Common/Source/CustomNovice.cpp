#pragma once
#include <Novice.h>
#include <math.h>
#include <string>

#include <Common/CustomNovice.h>
#include <Common/CommonFunctions.h>
#include <Common/ScreenSizeGet.h>
#include <Common/Camera.h>

Vector2 CustomNovice::shiftPos_ = { 0.0f, 0.0f };
float CustomNovice::winWidth_ = 0.0f;
float CustomNovice::winHeight_ = 0.0f;
int CustomNovice::tmpTexture_ = -1;
bool CustomNovice::isFullScreen_ = false;

void CustomNovice::Initialize(const char *title, float width, float height, bool enableDebugLayer) {
	winWidth_ = width;
	winHeight_ = height;

	ScreenSize::Init(width, height);
	Novice::Initialize(title, ScreenSize::WinWidth(), ScreenSize::WinHeight(), enableDebugLayer);

	tmpTexture_ = Novice::LoadTexture("white1x1.png");
}

void CustomNovice::BeginFrame() {
    Novice::BeginFrame();
}

void CustomNovice::EndFrame() {
    ScreenSize::DrawBlank();
    Novice::EndFrame();
}

void CustomNovice::ChangeWindowMode() {
	if (isFullScreen_) {
		Novice::SetWindowMode(kWindowed);
		isFullScreen_ = false;
	} else {
		Novice::SetWindowMode(kFullscreen);
		isFullScreen_ = true;
	}
}

void CustomNovice::DrawBox(float x, float y, float w, float h, unsigned int color, float angle, FillMode fillMode) {
	Novice::DrawBox(
		static_cast<int>(x + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(y + ScreenSize::ShiftY() + shiftPos_.y),
		static_cast<int>(w),
		static_cast<int>(h),
		angle, color, fillMode
	);
}

void CustomNovice::DrawBox(Camera &camera, float x, float y, float w, float h, unsigned int color, float angle, FillMode fillMode) {
	static Vector2 leftTop;
	static float width;
	static float height;

    leftTop = Transform({ x, y }, camera.GetWVPVPMatrix());
    width = w / camera.GetScale().x;
    height = h / camera.GetScale().y;

	Novice::DrawBox(
		static_cast<int>(leftTop.x + ScreenSize::ShiftX()),
		static_cast<int>(leftTop.y + ScreenSize::ShiftY()),
		static_cast<int>(width),
		static_cast<int>(height),
		angle + camera.GetRotate(), color, fillMode
	);
}

void CustomNovice::DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, unsigned int color, FillMode fillMode) {
	Novice::DrawTriangle(
		static_cast<int>(x1 + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(y1 + ScreenSize::ShiftY() + shiftPos_.y),
		static_cast<int>(x2 + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(y2 + ScreenSize::ShiftY() + shiftPos_.y),
		static_cast<int>(x3 + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(y3 + ScreenSize::ShiftY() + shiftPos_.y),
		color, fillMode
	);
}

void CustomNovice::DrawTriangle(Camera &camera, float x1, float y1, float x2, float y2, float x3, float y3, unsigned int color, FillMode fillMode) {
	Vector2 pos1;
	Vector2 pos2;
	Vector2 pos3;

    pos1 = Transform({ x1, y1 }, camera.GetWVPVPMatrix());
    pos2 = Transform({ x2, y2 }, camera.GetWVPVPMatrix());
    pos3 = Transform({ x3, y3 }, camera.GetWVPVPMatrix());

	Novice::DrawTriangle(
		static_cast<int>(pos1.x + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(pos1.y + ScreenSize::ShiftY() + shiftPos_.y),
		static_cast<int>(pos2.x + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(pos2.y + ScreenSize::ShiftY() + shiftPos_.y),
		static_cast<int>(pos3.x + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(pos3.y + ScreenSize::ShiftY() + shiftPos_.y),
		color, fillMode
	);
}

void CustomNovice::DrawLine(float x1, float y1, float x2, float y2, unsigned int color) {
	Novice::DrawLine(
		static_cast<int>(x1 + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(y1 + ScreenSize::ShiftY() + shiftPos_.y),
		static_cast<int>(x2 + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(y2 + ScreenSize::ShiftY() + shiftPos_.y),
		color
	);
}

void CustomNovice::DrawLine(Camera &camera, float x1, float y1, float x2, float y2, unsigned int color) {
	static Vector2 pos1;
	static Vector2 pos2;

    pos1 = Transform({ x1, y1 }, camera.GetWVPVPMatrix());
    pos2 = Transform({ x2, y2 }, camera.GetWVPVPMatrix());

	Novice::DrawLine(
		static_cast<int>(pos1.x + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(pos1.y + ScreenSize::ShiftY() + shiftPos_.y),
		static_cast<int>(pos2.x + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(pos2.y + ScreenSize::ShiftY() + shiftPos_.y),
		color
	);
}

void CustomNovice::DrawEllipse(float x, float y, float radiusX, float radiusY, unsigned int color, float angle, FillMode fillMode) {
	Novice::DrawEllipse(
		static_cast<int>(x + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(y + ScreenSize::ShiftY() + shiftPos_.y),
		static_cast<int>(radiusX),
		static_cast<int>(radiusY),
		angle, color, fillMode
	);
}

void CustomNovice::DrawEllipse(Camera &camera, float x, float y, float radiusX, float radiusY, unsigned int color, float angle, FillMode fillMode) {
	Vector2 leftTop;
	Vector2 rightBottom;
	Vector2 center;
	leftTop = Transform({ x - radiusX, y + radiusY }, camera.GetWVPVPMatrix());
	rightBottom = Transform({ x + radiusX, y - radiusY }, camera.GetWVPVPMatrix());
	center.x = (leftTop.x + rightBottom.x) / 2.0f;
	center.y = (leftTop.y + rightBottom.y) / 2.0f;

	Novice::DrawEllipse(
		static_cast<int>(center.x + ScreenSize::ShiftX()),
		static_cast<int>(center.y + ScreenSize::ShiftY()),
		static_cast<int>((rightBottom.x - leftTop.x) / 2.0f),
		static_cast<int>((rightBottom.y - leftTop.y) / 2.0f),
		angle + camera.GetRotate(), color, fillMode
	);
}

void CustomNovice::DrawSprite(float x, float y, int textureHandle, unsigned int color, float scaleX, float scaleY, float angle) {
    if (textureHandle == -1) {
        textureHandle = tmpTexture_;
    }

	Novice::DrawSprite(
		static_cast<int>(x + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(y + ScreenSize::ShiftY() + shiftPos_.y),
		textureHandle, scaleX, scaleY, angle, color
	);
}

void CustomNovice::DrawSprite(Camera &camera, float x, float y, int textureHandle, unsigned int color) {
	static Vector2 pos;
	if (textureHandle == -1) {
		textureHandle = tmpTexture_;
	}
	pos = Transform({ x, y }, camera.GetWVPVPMatrix());

	Novice::DrawSprite(
		static_cast<int>(pos.x + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(pos.y + ScreenSize::ShiftY() + shiftPos_.y),
		textureHandle, camera.GetScale().x, camera.GetScale().y, camera.GetRotate(), color
	);
}

void CustomNovice::DrawSpriteRect(float destX, float destY, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color, float scaleX, float scaleY, float angle) {
	if (textureHandle == -1) {
		textureHandle = tmpTexture_;
	}

	Novice::DrawSpriteRect(
		static_cast<int>(destX + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(destY + ScreenSize::ShiftY() + shiftPos_.y),
		static_cast<int>(srcX),
		static_cast<int>(srcY),
		static_cast<int>(srcW),
		static_cast<int>(srcH),
		textureHandle, scaleX, scaleY, angle, color
	);
}

void CustomNovice::DrawSpriteRect(Camera &camera, float destX, float destY, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color, float scaleX, float scaleY) {
	static Vector2 pos;
	if (textureHandle == -1) {
		textureHandle = tmpTexture_;
	}

	pos = Transform({ destX, destY }, camera.GetWVPVPMatrix());

	Novice::DrawSpriteRect(
		static_cast<int>(pos.x + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(pos.y + ScreenSize::ShiftY() + shiftPos_.y),
		static_cast<int>(srcX),
		static_cast<int>(srcY),
		static_cast<int>(srcW),
		static_cast<int>(srcH),
		textureHandle, scaleX / camera.GetScale().x, scaleY / camera.GetScale().y, camera.GetRotate(), color
	);
}

void CustomNovice::DrawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color) {
	if (textureHandle == -1) {
		textureHandle = tmpTexture_;
	}

	Novice::DrawQuad(
		static_cast<int>(x1 + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(y1 + ScreenSize::ShiftY() + shiftPos_.y),
		static_cast<int>(x2 + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(y2 + ScreenSize::ShiftY() + shiftPos_.y),
		static_cast<int>(x3 + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(y3 + ScreenSize::ShiftY() + shiftPos_.y),
		static_cast<int>(x4 + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(y4 + ScreenSize::ShiftY() + shiftPos_.y),
		static_cast<int>(srcX),
		static_cast<int>(srcY),
		static_cast<int>(srcW),
		static_cast<int>(srcH),
		textureHandle, color
	);
}

void CustomNovice::DrawQuad(Camera &camera, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color) {
	static Vector2 pos1;
	static Vector2 pos2;
	static Vector2 pos3;
	static Vector2 pos4;
	if (textureHandle == -1) {
		textureHandle = tmpTexture_;
	}

	pos1 = Transform({ x1, y1 }, camera.GetWVPVPMatrix());
    pos2 = Transform({ x2, y2 }, camera.GetWVPVPMatrix());
    pos3 = Transform({ x3, y3 }, camera.GetWVPVPMatrix());
    pos4 = Transform({ x4, y4 }, camera.GetWVPVPMatrix());

	Novice::DrawQuad(
		static_cast<int>(pos1.x + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(pos1.y + ScreenSize::ShiftY() + shiftPos_.y),
		static_cast<int>(pos2.x + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(pos2.y + ScreenSize::ShiftY() + shiftPos_.y),
		static_cast<int>(pos3.x + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(pos3.y + ScreenSize::ShiftY() + shiftPos_.y),
		static_cast<int>(pos4.x + ScreenSize::ShiftX() + shiftPos_.x),
		static_cast<int>(pos4.y + ScreenSize::ShiftY() + shiftPos_.y),
		static_cast<int>(srcX),
		static_cast<int>(srcY),
		static_cast<int>(srcW),
		static_cast<int>(srcH),
		textureHandle, color
	);
}

void CustomNovice::DrawNum(float x, float y, int fontWidth, int fontHeight, int drawWidth, int drawHeight, int marginX, int fontGh, int drawNum, DrawMethod drawMethod, unsigned int color, int isShadow, float shadowX, float shadowY, int fontShadowGh, unsigned int shadowColor, int isZeroFill, int digit) {
	// 描画する値を分けて保存するための配列
	int *drawNums;
	// 実際に描画する座標
	int drawPosX = static_cast<int>(x);
	int drawPosY = static_cast<int>(y);
	// 描画時の拡大率
	float scaleX = static_cast<float>(drawWidth) / static_cast<float>(fontWidth);
	float scaleY = static_cast<float>(drawHeight) / static_cast<float>(fontHeight);

	// isZeroFill フラグが下がっていたら桁数を数える
	if (!isZeroFill) {
		digit = GetDigit(drawNum);
	}

	// 桁数分の配列を動的確保する
	drawNums = new int[digit];

	// 桁数分繰り返し
	for (int i = 0; i < digit; i++) {

		// drawNum から 10^(桁数 - i - 1) の値で割って保存
		drawNums[i] = drawNum / static_cast<int>(pow(10, digit - i - 1));

		// 保存した値を元の桁数に戻して drawNum から引く
		drawNum -= drawNums[i] * static_cast<int>(pow(10, digit - i - 1));
	}

	// 描画方法に応じて描画座標を計算
	switch (drawMethod) {
		case LEFT:
			drawPosX = static_cast<int>(x);
			break;

		case CENTER:
			drawPosX = static_cast<int>(x - ((static_cast<float>(fontWidth) * scaleX + static_cast<float>(marginX)) * (static_cast<float>(digit) / 2.0f)));
			break;

		case RIGHT:
			drawPosX = static_cast<int>(x - ((static_cast<float>(fontWidth) * scaleX + static_cast<float>(marginX)) * static_cast<float>(digit))) + marginX;
			break;

		default:
			drawPosX = static_cast<int>(x);
			break;
	}

	// 桁数分繰り返し
	for (int i = 0; i < digit; i++) {
		// isShadow フラグが立ってたら文字の影を描画
		if (isShadow) {
			Novice::DrawSpriteRect(
				drawPosX + static_cast<int>((static_cast<float>(fontWidth) * scaleX + static_cast<float>(marginX)) * static_cast<float>(i) + ScreenSize::ShiftX() + shadowX),
				drawPosY + static_cast<int>(shadowY + ScreenSize::ShiftY()),
				drawNums[i] * fontWidth,
				0,
				fontWidth,
				fontHeight,
				fontShadowGh,
				static_cast<float>(fontWidth) / static_cast<float>(fontWidth * 10) * scaleX,
				scaleY,
				0.0f,
				shadowColor
			);
		}
		Novice::DrawSpriteRect(
			drawPosX + static_cast<int>((static_cast<float>(fontWidth) * scaleX + static_cast<float>(marginX)) * static_cast<float>(i) + ScreenSize::ShiftX()),
			drawPosY + static_cast<int>(ScreenSize::ShiftY()),
			drawNums[i] * fontWidth,
			0,
			fontWidth,
			fontHeight,
			fontGh,
			static_cast<float>(fontWidth) / static_cast<float>(fontWidth * 10) * scaleX,
			scaleY,
			0.0f,
			color
		);
	}

	// 動的確保した配列を解放
	delete[] drawNums;
}

void CustomNovice::DrawFont(float x, float y, int fontWidth, int fontHeight, int drawWidth, int drawHeight, int marginX, int marginY, int fontGh, const char *str, DrawMethod drawMethod, unsigned int color, int isShadow, int shadowX, int shadowY, int fontShadowGh, unsigned int shadowColor) {
	// 実際の描画位置
	int drawPosX = static_cast<int>(x);
	int drawPosY = static_cast<int>(y);
	// 描画をずらすための変数
	int drawShiftX = 0;
	int drawShiftY = 0;
	// 描画時の拡大率
	float scaleX = static_cast<float>(drawWidth) / static_cast<float>(fontWidth);
	float scaleY = static_cast<float>(drawHeight) / static_cast<float>(fontHeight);
	// 文字数カウント用
	int charNum = 0;
	int charNumCode = 0;
	int charNumLine = 0;
	// 繰り返し用
	int i = 0;
	// 比較用文字列
	static const char test[9][128] = {
		"　、。・：；？！＾＿ー／～｜‘’”（）｛｝「」＋＝＜＞￥＄％＃＆",
		"＊＠０１２３４５６７８９ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲＳＴ",
		"ＵＶＷＸＹＺａｂｃｄｅｆｇｈｉｊｋｌｍｎｏｐｑｒｓｔｕｖｗｘｙｚ",
		"ぁあぃいぅうぇえぉおかがきぎくぐけげこごさざしじすずせぜそぞただ",
		"ちぢっつづてでとどなにぬねのはばぱひびぴふぶぷへべぺほぼぽまみむ",
		"めもゃやゅゆょよらりるれろゎわゐゑをんァアィイゥウェエォオカガキ",
		"ギクグケゲコゴサザシジスズセゼソゾタダチヂッツヅテデトドナニヌネ",
		"ノハバパヒビピフブプヘベペホボポマミムメモャヤュユョヨラリルレロ",
		"ヮワヰヱヲン．"
	};
	// 一致フラグ
	static int isStrMatch = false;

	// 文字数を数える
	for (i = 0; str[i] != '\0'; i++) {
		charNum++;
		// 別で改行コードをカウントする
		if (str[i] == '\n') {
			charNumCode++;
		}
	}

	// 繰り返し用変数をリセット
	i = 0;

	// 一行目の文字数を数える
	for (charNumLine = 0; str[charNumLine] != '\0' && str[charNumLine] != '\n'; charNumLine++);

	// 描画方法によって描画位置を変える
	switch (drawMethod) {
		case LEFT:
			drawPosX = static_cast<int>(x);
			break;

		case CENTER:
			drawPosX = static_cast<int>(x - ((static_cast<float>(fontWidth) * scaleX + static_cast<float>(marginX)) * (static_cast<float>(charNumLine / 3) / 2.0f)));
			break;

		case RIGHT:
			drawPosX = static_cast<int>(x - ((static_cast<float>(fontWidth) * scaleX + static_cast<float>(marginX)) * static_cast<float>(((charNumLine) / 3))));
			break;

		default:
			drawPosX = static_cast<int>(x);
			break;
	}

	while (i < charNum) {
		// 文字列の中に改行コードが入ってたらYをずらす
		if (str[i] == '\n') {
			drawShiftX = 0;
			drawShiftY++;
			i++;
			// 描画方法が CENTER または RIGHT ならXの描画位置を再計算
			if (drawMethod == CENTER || drawMethod == RIGHT) {
				// 行の文字数を数える
				for (charNumLine = 0; str[i + charNumLine] != '\0' && str[i + charNumLine] != '\n'; charNumLine++);
				// 描画方法によって描画位置を変える
				switch (drawMethod) {
					case CENTER:
						drawPosX = static_cast<int>(x - ((static_cast<float>(fontWidth) * scaleX + static_cast<float>(marginX)) * static_cast<float>(((charNumLine) / 3) / 2)));
						break;

					case RIGHT:
						drawPosX = static_cast<int>(x - ((static_cast<float>(fontWidth) * scaleX + static_cast<float>(marginX)) * static_cast<float>(((charNumLine) / 3))));
						break;
				}
			}

		} else {
			isStrMatch = false;
			for (int j = 0; j < 10 && !isStrMatch; j++) {
				for (int k = 0; k < 96 && !isStrMatch; k += 3) {
					// 比較用文字列の中に終端文字を見つけたら終了
					if (test[j][k] == '\0') {
						break;
					} else if ((str[i] << 16) + (str[i + 1] << 8) + str[i + 2] == (test[j][k] << 16) + (test[j][k + 1] << 8) + test[j][k + 2]) {
						// isShadow フラグが立っていて、かつ影用のテクスチャも設定されてたら文字の影を描画
						if (isShadow) {
							if (fontShadowGh != -1) {
								Novice::DrawSpriteRect(
									drawPosX + (static_cast<int>(static_cast<float>(fontWidth) * scaleX) + marginX) * drawShiftX + static_cast<int>(ScreenSize::ShiftX() + shadowX),
									drawPosY + (static_cast<int>(static_cast<float>(fontHeight) * scaleY) + marginY) * drawShiftY + static_cast<int>(ScreenSize::ShiftY() + shadowY),
									(k / 3) * fontWidth,
									j * (fontHeight * 2),
									fontWidth,
									(fontHeight * 2),
									fontShadowGh,
									static_cast<float>(fontWidth) / static_cast<float>(fontWidth * 32) * scaleX,
									static_cast<float>(fontHeight) / static_cast<float>(fontHeight * 9) * scaleY,
									0.0f,
									shadowColor
								);
							}
						}
						// 一致した文字を描画
						Novice::DrawSpriteRect(
							drawPosX + (static_cast<int>(static_cast<float>(fontWidth) * scaleX) + marginX) * drawShiftX + static_cast<int>(ScreenSize::ShiftX()),
							drawPosY + (static_cast<int>(static_cast<float>(fontHeight) * scaleY) + marginY) * drawShiftY + static_cast<int>(ScreenSize::ShiftY()),
							(k / 3) * fontWidth,
							j * (fontHeight * 2),
							fontWidth,
							(fontHeight * 2),
							fontGh,
							static_cast<float>(fontWidth) / static_cast<float>(fontWidth * 32) * scaleX,
							static_cast<float>(fontHeight) / static_cast<float>(fontHeight * 9) * scaleY,
							0.0f,
							color
						);
						// 一致フラグを立ててループ終了
						isStrMatch = true;
						break;
					}
				}
			}

			drawShiftX++;
			i += 3;
		}
	}
}
