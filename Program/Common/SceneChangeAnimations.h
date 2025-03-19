#pragma once
#include <Stage/StageManager.h>
#include "CustomNovice.h"
#include "Easings.h"

// シーン遷移のアニメーションの種類
enum SceneChangeAnimationType {
	// なにもシーン遷移のアニメーションをしない
	SCA_NONE,

	// 徐々に画面が暗くなるフェードイン
	SCA_FADE_IN_BLACKOUT,
	// 徐々に画面が出てくるフェードアウト
	SCA_FADE_OUT_BLACKOUT,
	
	// 右上から左下にかけて丸が順番に出てくるフェードイン
	SCA_FADE_IN_MANY_CIRCLES,
	// 右上から左下にかけて丸が順番に消えていくフェードアウト
	SCA_FADE_OUT_MANY_CIRCLES,

    // 四角形が回転しながら徐々に小さくなっていくフェードイン
    SCA_FADE_IN_ROTATE_RECT,
    // 四角形が回転しながら徐々に大きくなっていくフェードアウト
    SCA_FADE_OUT_ROTATE_RECT,

	// 四角形が回転しながら徐々に大きくなっていくフェードアウト(ステージタイトル付き用)
	SCA_FADE_OUT_ROTATE_RECT_AND_TITLE,
};

class SceneChange {
	// ステージ管理クラスへのポインタ
	static StageManager *stageManager_;

	static int animationCountMax_;
	static int animationWaitTimeBefore_;
	static int animationWaitTimeAfter_;
	static int animationCount_;
	static SceneChangeAnimationType sceneChangeAnimationType_;
	
	static bool isChanging_;
	static bool isChanged_;

    static void DrawFadeInBlackout();
    static void DrawFadeOutBlackout();
    static void DrawFadeInManyCircles();
    static void DrawFadeOutManyCircles();
    static void DrawFadeInRotateRect();
    static void DrawFadeOutRotateRect();
    static void DrawFadeOutRotateRectAndTitle();

public:
	// シーン遷移用の値の初期化用関数
	static void Reset();
	// シーン遷移開始用
	static void Start(
		SceneChangeAnimationType sceneChangeAnimationType,
		int animationCountMax = 60,
		int animationWaitTimeBefore = 30,
		int animationWaitTimeAfter = 30
	);

	static void SetStageManager(StageManager *stageManager);
	
	// シーン遷移中フラグ
    static bool IsChanging() { return isChanging_; }
	// シーン遷移完了フラグ
    static bool IsChanged() { return isChanged_; }
	
	static void Update();
    static void Draw();
};