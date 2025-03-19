#pragma once
#include <windows.h>
#include "Structures.h"

class ScreenSize {
	// モニターの横幅
	static int monitorWidth_;
	// モニターの縦幅
	static int monitorHeight_;

	// ウィンドウの横幅(ウィンドウの初期化用。ゲーム用ではない。)
	static int winWidth_;
	// ウィンドウの縦幅(ウィンドウの初期化用。ゲーム用ではない。)
	static int winHeight_;

	// 描画ずらし用X座標
	static float shiftX_;
	// 描画ずらし用Y座標
	static float shiftY_;

public:
	// 画面外描画用
	static void DrawBlank();

	static void Init(const float kWinWidth, const float kWinHeight);

	static int WinWidth() { return winWidth_; };
	static int WinHeight() { return winHeight_; };

	static float ShiftX() { return shiftX_; };
	static float ShiftY() { return shiftY_; };
};