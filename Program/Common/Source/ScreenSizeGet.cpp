#include <Common/ScreenSizeGet.h>
#include <Novice.h>

int ScreenSize::monitorWidth_ = 0;
int ScreenSize::monitorHeight_ = 0;
int ScreenSize::winWidth_ = 0;
int ScreenSize::winHeight_ = 0;
float ScreenSize::shiftX_ = 0.0f;
float ScreenSize::shiftY_ = 0.0f;

void ScreenSize::Init(const float kWinWidth, const float kWinHeight) {
	monitorWidth_ = GetSystemMetrics(SM_CXSCREEN);
	monitorHeight_ = GetSystemMetrics(SM_CYSCREEN);

	winWidth_ = static_cast<int>(kWinWidth);
	winHeight_ = static_cast<int>(kWinHeight);

	// ゲーム画面の大きさとモニターの解像度の大きさが何倍差か求める
	float scaleX = kWinWidth / static_cast<float>(monitorWidth_);
	float scaleY = kWinHeight / static_cast<float>(monitorHeight_);

	// 縦と横どっちが倍率高いかを比較して小さいほうを大きいほうと同じ倍率にして返す
	if (scaleX > scaleY) {
		winHeight_ = static_cast<int>(static_cast<float>(monitorHeight_) * scaleX);
	} else if (scaleY > scaleX) {
		winWidth_ = static_cast<int>(static_cast<float>(monitorWidth_) * scaleY);
	}

	// ゲーム画面の大きさとウィンドウの大きさの差からどれだけ描画をずらすか計算
	shiftX_ = (static_cast<float>(winWidth_) - kWinWidth) / 2.0f;
	shiftY_ = (static_cast<float>(winHeight_) - kWinHeight) / 2.0f;
}

void ScreenSize::DrawBlank() {
	//--------- 上下の空白 ---------//
	Novice::DrawBox(
		0,
		0,
		winWidth_,
		static_cast<int>(shiftY_),
		0.0f,
		BLACK,
		kFillModeSolid
	);
	Novice::DrawBox(
		0,
		winHeight_,
		winWidth_,
		-static_cast<int>(shiftY_),
		0.0f,
		BLACK,
		kFillModeSolid
	);

	//--------- 左右の空白 ---------//
	Novice::DrawBox(
		0,
		0,
		static_cast<int>(shiftX_),
		winHeight_,
		0.0f,
		BLACK,
		kFillModeSolid
	);
	Novice::DrawBox(
		winWidth_,
		0,
		-static_cast<int>(shiftX_),
		winHeight_,
		0.0f,
		BLACK,
		kFillModeSolid
	);
}