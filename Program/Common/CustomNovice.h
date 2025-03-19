#pragma once
#include <Novice.h>
#include "Structures.h"

class Camera;

// フォントの描画方法
enum DrawMethod {
	LEFT,
	CENTER,
	RIGHT
};

class CustomNovice {
    static Vector2 shiftPos_;
	static float winWidth_;
	static float winHeight_;
    static int tmpTexture_;
    static bool isFullScreen_;
    static WindowMode windowMode_;

public:
	static void Initialize(const char *title, float width = 1280, float height = 720, bool enableDebugLayer = true);

    static void BeginFrame();
    static void EndFrame();

    static void ChangeWindowMode();
    static void SetShiftPos(const Vector2 &shiftPos) { shiftPos_ = shiftPos; };
    static void SetWindowMode(WindowMode windowMode) { windowMode_ = windowMode; };
    static Vector2 GetShiftPos() { return shiftPos_; };
    static WindowMode GetWindowMode() { return windowMode_; };
	static float WinWidth() { return winWidth_; };
	static float WinHeight() { return winHeight_; };

	/// <summary>
	/// float型の値で四角形を描画する
	/// </summary>
	/// <param name="x">描画する四角形の左上座標 X</param>
	/// <param name="y">描画する四角形の左上座標 Y</param>
	/// <param name="w">描画する四角形の横幅</param>
	/// <param name="h">描画する四角形の縦幅</param>
	/// <param name="color">描画する四角形の色</param>
	/// <param name="angle">描画する四角形の回転角</param>
	/// <param name="fillMode">塗りつぶしモード</param>
	static void DrawBox(float x, float y, float w, float h, unsigned int color = WHITE, float angle = 0.0f, FillMode fillMode = kFillModeSolid);

	/// <summary>
	/// カメラを使用して四角形を描画する
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="x">描画する四角形の左上座標 X</param>
	/// <param name="y">描画する四角形の左上座標 Y</param>
	/// <param name="w">描画する四角形の横幅</param>
	/// <param name="h">描画する四角形の縦幅</param>
	/// <param name="color">描画する四角形の色</param>
	/// <param name="fillMode">塗りつぶしモード</param>
	static void DrawBox(Camera &camera, float x, float y, float w, float h, unsigned int color = WHITE, float angle = 0.0f, FillMode fillMode = kFillModeSolid);

	/// <summary>
	/// float型の値で三角形を描画する
	/// </summary>
	/// <param name="x1">描画する三角形の頂点1 X</param>
	/// <param name="y1">描画する三角形の頂点1 Y</param>
	/// <param name="x2">描画する三角形の頂点2 X</param>
	/// <param name="y2">描画する三角形の頂点2 Y</param>
	/// <param name="x3">描画する三角形の頂点3 X</param>
	/// <param name="y3">描画する三角形の頂点3 Y</param>
	/// <param name="color">描画する三角形の色</param>
	/// <param name="fillMode">塗りつぶしモード</param>
	static void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, unsigned int color = WHITE, FillMode fillMode = kFillModeSolid);

	/// <summary>
	/// カメラを使用して三角形を描画する
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="x1">描画する三角形の頂点1 X</param>
	/// <param name="y1">描画する三角形の頂点1 Y</param>
	/// <param name="x2">描画する三角形の頂点2 X</param>
	/// <param name="y2">描画する三角形の頂点2 Y</param>
	/// <param name="x3">描画する三角形の頂点3 X</param>
	/// <param name="y3">描画する三角形の頂点3 Y</param>
	/// <param name="color">描画する三角形の色</param>
	/// <param name="fillMode">塗りつぶしモード</param>
	static void DrawTriangle(Camera &camera, float x1, float y1, float x2, float y2, float x3, float y3, unsigned int color = WHITE, FillMode fillMode = kFillModeSolid);

	/// <summary>
	/// float型の値で線を描画する
	/// </summary>
	/// <param name="x1">描画する線の始点座標 X</param>
	/// <param name="y1">描画する線の始点座標 Y</param>
	/// <param name="x2">描画する線の終点座標 X</param>
	/// <param name="y2">描画する線の終点座標 Y</param>
	/// <param name="color">描画する線の色</param>
	static void DrawLine(float x1, float y1, float x2, float y2, unsigned int color = WHITE);

	/// <summary>
	/// カメラを使用して線を描画する
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="x1">描画する線の始点座標 X</param>
	/// <param name="y1">描画する線の始点座標 Y</param>
	/// <param name="x2">描画する線の終点座標 X</param>
	/// <param name="y2">描画する線の終点座標 Y</param>
	/// <param name="color">描画する線の色</param>
	static void DrawLine(Camera &camera, float x1, float y1, float x2, float y2, unsigned int color = WHITE);

	/// <summary>
	/// float型の値で楕円を描画する
	/// </summary>
	/// <param name="x">楕円の中心座標 X</param>
	/// <param name="y">楕円の中心座標 Y</param>
	/// <param name="radiusX">楕円の半径 X</param>
	/// <param name="radiusY">楕円の半径 Y</param>
	/// <param name="color">楕円の色</param>
	/// <param name="angle">楕円の回転角(rad)</param>
	/// <param name="fillMode">塗りつぶしモード</param>
	static void DrawEllipse(float x, float y, float radiusX, float radiusY, unsigned int color = WHITE, float angle = 0.0f, FillMode fillMode = kFillModeSolid);

	/// <summary>
	/// カメラを使用して楕円を描画する
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="x">楕円の中心座標 X</param>
	/// <param name="y">楕円の中心座標 Y</param>
	/// <param name="radiusX">楕円の半径 X</param>
	/// <param name="radiusY">楕円の半径 Y</param>
	/// <param name="color">楕円の色</param>
	/// <param name="fillMode">塗りつぶしモード</param>
	static void DrawEllipse(Camera &camera, float x, float y, float radiusX, float radiusY, unsigned int color = WHITE, float angle = 0.0f, FillMode fillMode = kFillModeSolid);

	/// <summary>
	/// float型の値でスプライトを描画する
	/// </summary>
	/// <param name="x">描画するスプライトの左上座標 X</param>
	/// <param name="y">描画するスプライトの左上座標 Y</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="color">描画するスプライトの色</param>
	/// <param name="scale">描画するスプライトの倍率 X</param>
	/// <param name="scale">描画するスプライトの倍率 Y</param>
	/// <param name="angle">描画するスプライトの回転角</param>
	static void DrawSprite(float x, float y, int textureHandle, unsigned int color = WHITE, float scaleX = 1.0f, float scaleY = 1.0f, float angle = 0.0f);

	/// <summary>
	/// カメラを使用してスプライトを描画する
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="x">描画するスプライトの左上座標 X</param>
	/// <param name="y">描画するスプライトの左上座標 Y</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="color">描画するスプライトの色</param>
	/// <param name="scale">描画するスプライトの倍率 X</param>
	/// <param name="scale">描画するスプライトの倍率 Y</param>
	/// <param name="angle">描画するスプライトの回転角</param>
	static void DrawSprite(Camera &camera, float x, float y, int textureHandle, unsigned int color = WHITE);

	/// <summary>
	/// float型の値でスプライトの指定矩形部分のみを描画を描画する
	/// </summary>
	/// <param name="destX">描画するスプライトの左上座標 X</param>
	/// <param name="destY">描画するスプライトの左上座標 Y</param>
	/// <param name="srcX">画像上の描画したい範囲左上座標 X</param>
	/// <param name="srcY">画像上の描画したい範囲左上座標 Y</param>
	/// <param name="srcW">画像上の描画したい範囲横幅</param>
	/// <param name="srcH">画像上の描画したい範囲縦幅</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="color">描画するスプライトの色</param>
	/// <param name="scale">描画するスプライトの倍率 X</param>
	/// <param name="scale">描画するスプライトの倍率 Y</param>
	/// <param name="angle">描画するスプライトの回転角</param>
	static void DrawSpriteRect(float destX, float destY, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color = WHITE, float scaleX = 1.0f, float scaleY = 1.0f, float angle = 0.0f);

	/// <summary>
	/// カメラを使用してスプライトの指定矩形部分のみを描画を描画する
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="destX">描画するスプライトの左上座標 X</param>
	/// <param name="destY">描画するスプライトの左上座標 Y</param>
	/// <param name="srcX">画像上の描画したい範囲左上座標 X</param>
	/// <param name="srcY">画像上の描画したい範囲左上座標 Y</param>
	/// <param name="srcW">画像上の描画したい範囲横幅</param>
	/// <param name="srcH">画像上の描画したい範囲縦幅</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="color">描画するスプライトの色</param>
	/// <param name="scale">描画するスプライトの倍率 X</param>
	/// <param name="scale">描画するスプライトの倍率 Y</param>
	/// <param name="angle">描画するスプライトの回転角</param>
	static void DrawSpriteRect(Camera &camera, float destX, float destY, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color = WHITE, float scaleX = 1.0f, float scaleY = 1.0f);

	/// <summary>
	/// float型の値で四角形描画
	/// </summary>
	/// <param name="x1">描画する四角形の左上座標 X</param>
	/// <param name="y1">描画する四角形の左上座標 Y</param>
	/// <param name="x2">描画する四角形の右上座標 X</param>
	/// <param name="y2">描画する四角形の右上座標 Y</param>
	/// <param name="x3">描画する四角形の左下座標 X</param>
	/// <param name="y3">描画する四角形の左下座標 Y</param>
	/// <param name="x4">描画する四角形の右下座標 X</param>
	/// <param name="y4">描画する四角形の右下座標 Y</param>
	/// <param name="srcX">画像上の描画したい範囲左上座標 X</param>
	/// <param name="srcY">画像上の描画したい範囲左上座標 Y</param>
	/// <param name="srcW">画像上の描画したい範囲横幅</param>
	/// <param name="srcH">画像上の描画したい範囲縦幅</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="color">描画するスプライトの色</param>
	static void DrawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color = WHITE);

	/// <summary>
	/// カメラを使用して四角形描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	/// <param name="x1">描画する四角形の左上座標 X</param>
	/// <param name="y1">描画する四角形の左上座標 Y</param>
	/// <param name="x2">描画する四角形の右上座標 X</param>
	/// <param name="y2">描画する四角形の右上座標 Y</param>
	/// <param name="x3">描画する四角形の左下座標 X</param>
	/// <param name="y3">描画する四角形の左下座標 Y</param>
	/// <param name="x4">描画する四角形の右下座標 X</param>
	/// <param name="y4">描画する四角形の右下座標 Y</param>
	/// <param name="srcX">画像上の描画したい範囲左上座標 X</param>
	/// <param name="srcY">画像上の描画したい範囲左上座標 Y</param>
	/// <param name="srcW">画像上の描画したい範囲横幅</param>
	/// <param name="srcH">画像上の描画したい範囲縦幅</param>
	/// <param name="textureHandle">テクスチャのハンドル</param>
	/// <param name="color">描画するスプライトの色</param>
	static void DrawQuad(Camera &camera, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color = WHITE);

	/// <summary>
	/// 数字の描画用関数
	/// </summary>
	/// <param name="x">描画座標 X</param>
	/// <param name="y">描画座標 Y</param>
	/// <param name="fontWidth">フォント画像の横幅</param>
	/// <param name="fontHeight">フォント画像の縦幅</param>
	/// <param name="drawWidth">描画時の横幅</param>
	/// <param name="drawHeight">描画時の縦幅</param>
	/// <param name="fontGh">フォント画像のグラフハンドル</param>
	/// <param name="drawNum">描画する数字</param>
	/// <param name="drawMethod">描画位置 (LEFT:左寄せ CENTER:中央寄せ RIGHT:右寄せ)</param>
	/// <param name="color">文字の色</param>
	/// <param name="isShadow">文字の影の有無</param>
	/// <param name="shadowX">影の相対座標 X</param>
	/// <param name="shadowY">影の相対座標 Y</param>
	/// <param name="fontShadowGh">影用のフォント画像のグラフハンドル</param>
	/// <param name="shadowColor">影の色</param>
	/// <param name="isZeroFill">ゼロで埋めるかの有無</param>
	/// <param name="digit">桁数 (isZeroFill を true にしてたら設定必須)</param>
	static void DrawNum(float x, float y, int fontWidth, int fontHeight, int drawWidth, int drawHeight, int marginX, int fontGh, int drawNum, DrawMethod drawMethod = LEFT, unsigned int color = WHITE, int isShadow = false, float shadowX = 4, float shadowY = 4, int fontShadowGh = -1, unsigned int shadowColor = 0xBFBFBFFF, int isZeroFill = false, int digit = 1);

	/// <summary>
	/// 文字列の描画用関数
	/// </summary>
	/// <param name="x">描画座標 X</param>
	/// <param name="y">描画座標 Y</param>
	/// <param name="fontWidth">フォント画像の横幅</param>
	/// <param name="fontHeight">フォント画像の縦幅</param>
	/// <param name="drawWidth">描画時の横幅</param>
	/// <param name="drawHeight">描画時の縦幅</param>
	/// <param name="fontGh">フォント画像のグラフハンドル</param>
	/// <param name="str">描画する文字列</param>
	/// <param name="drawMethod">描画位置 (LEFT:左寄せ CENTER:中央寄せ RIGHT:右寄せ)</param>
	/// <param name="color">文字の色</param>
	/// <param name="isShadow">文字の影の有無</param>
	/// <param name="shadowX">影の相対座標 X</param>
	/// <param name="shadowY">影の相対座標 Y</param>
	/// <param name="fontShadowGh">影用のフォント画像のグラフハンドル</param>
	/// <param name="shadowColor">影の色</param>
	static void DrawFont(float x, float y, int fontWidth, int fontHeight, int drawWidth, int drawHeight, int marginX, int marginY, int fontGh, const char *str, DrawMethod drawMethod = LEFT, unsigned int color = WHITE, int isShadow = false, int shadowX = 4, int shadowY = 4, int fontShadowGh = -1, unsigned int shadowColor = 0xBFBFBFFF);
};