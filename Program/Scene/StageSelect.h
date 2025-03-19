#pragma once
#include "SceneBase.h"
#include <Common/Math/Vector2.h>
#include <Common/Camera.h>
#include <Stage/StageManager.h>

class StageSelect : public SceneBase {
public:
    StageSelect(const StageSelect &) = delete;
    StageSelect &operator=(const StageSelect &) = delete;
    StageSelect(StageSelect &&) = delete;
    StageSelect &operator=(StageSelect &&) = delete;

    Vector2 PlayerView(Vector2 pos, Vector2 posVer, float rotate, Vector2 scale);
    int GetStageID() { return selectStageID_; }
    void Init();
    void Update();
    void Draw();

private:

    StageManager *stage_;
    //回転用
    float degree_;//
    int count_;//
    int maxCount_;//
    bool isRotate_;
    int which_;

    Camera cameraSSS_;
    float scaleSSS_;
    int isStage_;

    Vector2 posPre_;
    Vector2 posNext_;

    int selectStageID_;
    int transitionCount_;
    int transitionCountMax_;
    int isSelectStage_;

    float rad_;
    float radMax_;
    float radMin_;

    int isTransition_;

    Vector2 player_;
    Vector2 playerScale_;
    float playerRotate_;
    Vector2 leftTop_;
    Vector2 rightTop_;
    Vector2 leftBottom_;
    Vector2 rightBottom_;

    int isMove_;
    int moveCount_;
    Vector2 wid_;

    Vector2 cloudBig_;
    Vector2 cloudScale_ = {};
    float cloudDegree_ = 0;

    Vector2 namePos_ = { CustomNovice::WinWidth() / 2.0f, 480.0f };

    Vector2 selectViewPos_[2] = {};
    Vector2 selectViewScale_[2] = {};
    float selectViewDegree_[2] = {};
    Vector2 selectViewWid_[2] = {};

    int shakeTime_ = 0;
    float shake_ = 0;

    /*inline Vector2 thinkPos_[10] = {};
    inline Vector2 thinkScale_[10] = {};
    inline float thinkDegree_[10] = {};
    inline Vector2 thinkWid_[10] = {};*/
};