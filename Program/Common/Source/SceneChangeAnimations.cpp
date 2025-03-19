#include <Common/SceneChangeAnimations.h>
#include <Common/CommonFunctions.h>
#include <Common/CustomNovice.h>
#include <Common/Easings.h>

StageManager *SceneChange::stageManager_ = nullptr;
int SceneChange::animationCountMax_ = 0;
int SceneChange::animationWaitTimeBefore_;
int SceneChange::animationWaitTimeAfter_;
int SceneChange::animationCount_;
SceneChangeAnimationType SceneChange::sceneChangeAnimationType_ = SCA_NONE;
bool SceneChange::isChanging_ = false;
bool SceneChange::isChanged_ = false;

void SceneChange::DrawFadeInBlackout() {
    // 徐々に画面が暗くなるフェードイン
    CustomNovice::DrawBox(
        0.0f,
        0.0f,
        CustomNovice::WinWidth(),
        CustomNovice::WinHeight(),
        0x000000FF - static_cast<unsigned int>(255.0f - 255.0f * ConvertInt2Time(animationCount_ - animationWaitTimeBefore_, animationCountMax_))
    );
}

void SceneChange::DrawFadeOutBlackout() {
    // 徐々に画面が出てくるフェードアウト
    CustomNovice::DrawBox(
        0.0f,
        0.0f,
        CustomNovice::WinWidth(),
        CustomNovice::WinHeight(),
        0x000000FF - static_cast<unsigned int>(255.0f * ConvertInt2Time(animationCount_ - animationWaitTimeBefore_, animationCountMax_))
    );
}

void SceneChange::DrawFadeInManyCircles() {
    static AnimCircle circle[5][9];

	if (animationCount_ == 0) {
		for (int y = 0; y < 5; y++) {
			for (int x = 8; x >= 0; x--) {
				circle[y][x].pos.x = 240.0f * static_cast<float>(x);
				circle[y][x].pos.y = 240.0f * static_cast<float>(y) + 60.0f;
				circle[y][x].radius = 360.0f;
				circle[y][x].startCount = (animationCountMax_ / (5 + 9) / 2) * (y + (8 - x));
				circle[y][x].endCount = circle[y][x].startCount + (animationCountMax_ / (5 + 9) / 2 * 3);
			}
		}
        animationCount_++;
	}

    // 右上から左下にかけて丸が順番に出てくるフェードイン
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 9; x++) {
            CustomNovice::DrawEllipse(
                circle[y][x].pos.x,
                circle[y][x].pos.y,
                Ease::Auto((animationCount_ - animationWaitTimeBefore_ - circle[y][x].startCount), circle[y][x].endCount, 0.0f, circle[y][x].radius, EASE_IN_SINE),
                Ease::Auto((animationCount_ - animationWaitTimeBefore_ - circle[y][x].startCount), circle[y][x].endCount, 0.0f, circle[y][x].radius, EASE_IN_SINE),
                BLACK
            );
        }
    }
}

void SceneChange::DrawFadeOutManyCircles() {
	static AnimCircle circle[5][9];

	if (animationCount_ == 0) {
		for (int y = 0; y < 5; y++) {
			for (int x = 8; x >= 0; x--) {
				circle[y][x].pos.x = 240.0f * static_cast<float>(x);
				circle[y][x].pos.y = 240.0f * static_cast<float>(y) + 60.0f;
				circle[y][x].radius = 360.0f;
				circle[y][x].startCount = (animationCountMax_ / (5 + 9) / 2) * (y + (8 - x));
				circle[y][x].endCount = circle[y][x].startCount + (animationCountMax_ / (5 + 9) / 2 * 3);
			}
		}
	}

    // 右上から左下にかけて丸が順番に消えていくフェードアウト
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 9; x++) {
            CustomNovice::DrawEllipse(
                circle[y][x].pos.x,
                circle[y][x].pos.y,
                Ease::Auto((animationCount_ - animationWaitTimeBefore_ - circle[y][x].startCount), circle[y][x].endCount, circle[y][x].radius, 0.0f, EASE_OUT_SINE),
                Ease::Auto((animationCount_ - animationWaitTimeBefore_ - circle[y][x].startCount), circle[y][x].endCount, circle[y][x].radius, 0.0f, EASE_OUT_SINE),
                BLACK
            );
        }
    }
}

void SceneChange::DrawFadeInRotateRect() {
    static Matrix3x3 rotateMatrix;
    static Vector2 rectCenterPos[4] = {
        { 1920.0f, 0.0f },
        { -1920.0f, 0.0f },
        { 0.0f, 1920.0f },
        { 0.0f, -1920.0f }
    };
    static Vector2 rectDrawPos[4];
    static Vector2 leftTop;
    static Vector2 rightTop;
    static Vector2 leftBottom;
    static Vector2 rightBottom;

    rotateMatrix = MakeAffineMatrix(
        { 1.0f, 1.0f },
        ConvertDeg2Rad(
            Ease::Auto(
                animationCount_ - animationWaitTimeBefore_,
                animationCountMax_,
                0.0f,
                360.0f,
                EASE_OUT_QUINT
            )
        ),
        { CustomNovice::WinWidth() / 2.0f, CustomNovice::WinHeight() / 2.0f }
    );

    for (int i = 0; i < 4; i++) {
        rectDrawPos[i] = {
            Ease::Auto(
                animationCount_ - animationWaitTimeBefore_,
                animationCountMax_,
                rectCenterPos[i].x,
                rectCenterPos[i].x / 2.0f,
                EASE_OUT_QUINT
            ),
            Ease::Auto(
                animationCount_ - animationWaitTimeBefore_,
                animationCountMax_,
                rectCenterPos[i].y,
                rectCenterPos[i].y / 2.0f,
                EASE_OUT_QUINT
            )
        };

        leftTop = Transform({ rectDrawPos[i].x - 960.0f, rectDrawPos[i].y + 960.0f }, rotateMatrix);
        rightTop = Transform({ rectDrawPos[i].x + 960.0f, rectDrawPos[i].y + 960.0f }, rotateMatrix);
        leftBottom = Transform({ rectDrawPos[i].x - 960.0f, rectDrawPos[i].y - 960.0f }, rotateMatrix);
        rightBottom = Transform({ rectDrawPos[i].x + 960.0f, rectDrawPos[i].y - 960.0f }, rotateMatrix);
        
        CustomNovice::DrawQuad(
            leftTop.x,
            leftTop.y,
            rightTop.x,
            rightTop.y,
            leftBottom.x,
            leftBottom.y,
            rightBottom.x,
            rightBottom.y,
            0, 0, 1, 1,
            -1,
            BLACK
        );
    }
}

void SceneChange::DrawFadeOutRotateRect() {
    static Matrix3x3 rotateMatrix;
    static Vector2 rectCenterPos[4] = {
        { 960.0f, 0.0f },
        { -960.0f, 0.0f },
        { 0.0f, 960.0f },
        { 0.0f, -960.0f }
    };
    static Vector2 rectDrawPos[4];
    static Vector2 leftTop;
    static Vector2 rightTop;
    static Vector2 leftBottom;
    static Vector2 rightBottom;

    rotateMatrix = MakeAffineMatrix(
        { 1.0f, 1.0f },
        ConvertDeg2Rad(
            Ease::Auto(
                animationCount_ - animationWaitTimeBefore_,
                animationCountMax_,
                0.0f,
                360.0f,
                EASE_OUT_QUINT
            )
        ),
        { CustomNovice::WinWidth() / 2.0f, CustomNovice::WinHeight() / 2.0f }
    );

    for (int i = 0; i < 4; i++) {
        rectDrawPos[i] = {
            Ease::Auto(
                animationCount_ - animationWaitTimeBefore_,
                animationCountMax_,
                rectCenterPos[i].x,
                rectCenterPos[i].x * 2.0f,
                EASE_OUT_QUINT
            ),
            Ease::Auto(
                animationCount_ - animationWaitTimeBefore_,
                animationCountMax_,
                rectCenterPos[i].y,
                rectCenterPos[i].y * 2.0f,
                EASE_OUT_QUINT
            )
        };

        leftTop = Transform({ rectDrawPos[i].x - 960.0f, rectDrawPos[i].y + 960.0f }, rotateMatrix);
        rightTop = Transform({ rectDrawPos[i].x + 960.0f, rectDrawPos[i].y + 960.0f }, rotateMatrix);
        leftBottom = Transform({ rectDrawPos[i].x - 960.0f, rectDrawPos[i].y - 960.0f }, rotateMatrix);
        rightBottom = Transform({ rectDrawPos[i].x + 960.0f, rectDrawPos[i].y - 960.0f }, rotateMatrix);

        CustomNovice::DrawQuad(
            leftTop.x,
            leftTop.y,
            rightTop.x,
            rightTop.y,
            leftBottom.x,
            leftBottom.y,
            rightBottom.x,
            rightBottom.y,
            0, 0, 1, 1,
            -1,
            BLACK
        );
    }
}

void SceneChange::DrawFadeOutRotateRectAndTitle() {
    static Matrix3x3 rotateMatrix;
    static Vector2 rectCenterPos[4] = {
        { 960.0f, 0.0f },
        { -960.0f, 0.0f },
        { 0.0f, 960.0f },
        { 0.0f, -960.0f }
    };
    static Vector2 rectDrawPos[4];
    static Vector2 leftTop;
    static Vector2 rightTop;
    static Vector2 leftBottom;
    static Vector2 rightBottom;

    if (animationCount_ - animationWaitTimeBefore_ < animationCountMax_ / 6) {
        //--------- 矩形にくりぬかれた形がくるくる回りながら出てくる ---------//
        rotateMatrix = MakeAffineMatrix(
            { 1.0f, 1.0f },
            ConvertDeg2Rad(
                Ease::Auto(
                    animationCount_ - animationWaitTimeBefore_,
                    animationCountMax_ / 6,
                    0.0f,
                    360.0f,
                    EASE_OUT_QUINT
                )
            ),
            { CustomNovice::WinWidth() / 2.0f, CustomNovice::WinHeight() / 2.0f }
        );
        for (int i = 0; i < 4; i++) {
            rectDrawPos[i] = {
            Ease::Auto(
                animationCount_ - animationWaitTimeBefore_,
                animationCountMax_ / 6,
                rectCenterPos[i].x,
                rectCenterPos[i].x + (rectCenterPos[i].x / 7.5f),
                EASE_OUT_QUINT
            ),
            Ease::Auto(
                animationCount_ - animationWaitTimeBefore_,
                animationCountMax_ / 6,
                rectCenterPos[i].y,
                rectCenterPos[i].y + (rectCenterPos[i].y / 7.5f),
                EASE_OUT_QUINT
            )
            };
        }

    } else if (animationCount_ - animationWaitTimeBefore_ < animationCountMax_ / 6 * 2) {
        //--------- 左右にある矩形だけが画面外に移動してタイトルがフェードで出てくる ---------//
        for (int i = 0; i < 2; i++) {
            rectDrawPos[i] = {
                Ease::Auto(
                    animationCount_ - animationWaitTimeBefore_ - animationCountMax_ / 6,
                    animationCountMax_ / 6,
                    rectCenterPos[i].x + (rectCenterPos[i].x / 7.5f),
                    rectCenterPos[i].x * 2.0f,
                    EASE_OUT_QUINT
                ),
                0.0f
            };
        }
        stageManager_->DrawStageName(
            SceneGame::GetStage()->GetPlayNowStageID(),
            { CustomNovice::WinWidth() / 2.0f, 64.0f },
            static_cast<unsigned int>(Ease::Auto(
                animationCount_ - animationWaitTimeBefore_ - animationCountMax_ / 6,
                animationCountMax_ / 6,
                0.0f,
                255.0f,
                EASE_LINER
            ))
        );
    
    } else if (animationCount_ - animationWaitTimeBefore_ < animationCountMax_ / 6 * 5) {
        //--------- ステージタイトルを描画 ---------//
        stageManager_->DrawStageName(
            SceneGame::GetStage()->GetPlayNowStageID(),
            { CustomNovice::WinWidth() / 2.0f, 64.0f },
            BLACK
        );

    } else if (animationCount_ - animationWaitTimeBefore_ < animationCountMax_) {
        //--------- タイトルをフェードで消して上下の矩形を画面外に移動 ---------//
        stageManager_->DrawStageName(
            SceneGame::GetStage()->GetPlayNowStageID(),
            { CustomNovice::WinWidth() / 2.0f, 64.0f },
            static_cast<unsigned int>(Ease::Auto(
                animationCount_ - animationWaitTimeBefore_ - animationCountMax_ / 6 * 5,
                animationCountMax_ / 6,
                255.0f,
                0.0f,
                EASE_LINER
            ))
        );
        for (int i = 2; i < 4; i++) {
            rectDrawPos[i] = {
                0.0f,
                Ease::Auto(
                    animationCount_ - animationWaitTimeBefore_ - animationCountMax_ / 6 * 5,
                    animationCountMax_ / 6,
                    rectCenterPos[i].y + (rectCenterPos[i].y / 7.5f),
                    rectCenterPos[i].y * 1.6f,
                    EASE_OUT_QUINT
                )
            };
        }
    }

    for (int i = 0; i < 4; i++) {
        leftTop = Transform({ rectDrawPos[i].x - 960.0f, rectDrawPos[i].y + 960.0f }, rotateMatrix);
        rightTop = Transform({ rectDrawPos[i].x + 960.0f, rectDrawPos[i].y + 960.0f }, rotateMatrix);
        leftBottom = Transform({ rectDrawPos[i].x - 960.0f, rectDrawPos[i].y - 960.0f }, rotateMatrix);
        rightBottom = Transform({ rectDrawPos[i].x + 960.0f, rectDrawPos[i].y - 960.0f }, rotateMatrix);

        CustomNovice::DrawQuad(
            leftTop.x,
            leftTop.y,
            rightTop.x,
            rightTop.y,
            leftBottom.x,
            leftBottom.y,
            rightBottom.x,
            rightBottom.y,
            0, 0, 1, 1,
            -1,
            BLACK
        );
    }
}

void SceneChange::Reset() {
    animationCountMax_ = 60;
    animationWaitTimeBefore_ = 30;
    animationWaitTimeAfter_ = 30;
	animationCount_ = -1;
	isChanging_ = false;
	isChanged_ = false;
}

void SceneChange::Start(SceneChangeAnimationType sceneChangeAnimationType, int animationCountMax, int animationWaitTimeBefore, int animationWaitTimeAfter) {
    Reset();
	sceneChangeAnimationType_ = sceneChangeAnimationType;
    animationCountMax_ = animationCountMax;
    animationWaitTimeBefore_ = animationWaitTimeBefore;
    animationWaitTimeAfter_ = animationWaitTimeAfter;
    isChanging_ = true;
}

void SceneChange::SetStageManager(StageManager *stageManager) {
    sStageManager = stageManager;
}

void SceneChange::Update() {
    if (!isChanging_) {
        return;
    }

    // 最大値 + 待ち時間までカウントを進める
    if (animationCount_ < animationCountMax_ + animationWaitTimeBefore_ + animationWaitTimeAfter_) {
        animationCount_++;
    } else {
        // シーンチェンジが終わったらフラグを立てる
        if (!isChanged_) {
            isChanged_ = true;
        } else {
            // 2回目のループでここを通ったらフラグを下げる
            isChanged_ = false;
            isChanging_ = false;
        }
    }
}

void SceneChange::Draw() {
    if (!isChanging_) {
        return;
    }

    switch (sceneChangeAnimationType_) {
        case SCA_FADE_IN_BLACKOUT:
            DrawFadeInBlackout();
            break;
        case SCA_FADE_OUT_BLACKOUT:
            DrawFadeOutBlackout();
            break;
        case SCA_FADE_IN_MANY_CIRCLES:
            DrawFadeInManyCircles();
            break;
        case SCA_FADE_OUT_MANY_CIRCLES:
            DrawFadeOutManyCircles();
            break;
        case SCA_FADE_IN_ROTATE_RECT:
            DrawFadeInRotateRect();
            break;
        case SCA_FADE_OUT_ROTATE_RECT:
            DrawFadeOutRotateRect();
            break;
        case SCA_FADE_OUT_ROTATE_RECT_AND_TITLE:
            DrawFadeOutRotateRectAndTitle();
            break;
        default:
            break;
    }
}
