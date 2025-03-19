#pragma once
#include <Common/Math/Vector2.h>
#include <Common/Camera.h>
#include "SceneBase.h"

class Title : public SceneBase {
public:
    Title(const Title &) = delete;
    Title &operator=(const Title &) = delete;
    Title(Title &&) = delete;
    Title &operator=(Title &&) = delete;

    void Initialize() override;
    void Update() override;
    void Draw() override;

private:
    Title() = default;
    ~Title() = default;

    //最初のカラー
    unsigned int colorTop_;
    int isFirstTitle_;

    //タイトル
    //く・る・く・る・I・ノ・ノ・I・＋・ノ・ー・ー
    Vector2 titlePos_[12] = {};
    float titleDegree_[12] = {};
    Vector2 titleScale_[12] = {};
    Vector2 shake_;

    int moveCount_ = 0;

    //inline int map_[16][16] = {0};
    const int width_ = 48;
    const int height_ = 48;

    Camera cameraT_;
    float preRotate_;//
    float rotate_;
    float degree_;//
    int count_;//
    int maxCount_;//
    bool isRotate_;
    Vector2 scale_;
    Vector2 translate_;
    float changeSum_;
    int which_;

    int color_[4] = { 0 };
    int isColor_;
    Vector2 pos_;
    float colorTeach_;

    int isTitle_ = 100;
    int isSelect_ = 0;

    int toSelectView_;
    Vector2 stagePos_;
    Vector2 transitionPos_;

    Vector2 wid_;
    Vector2 player_;
    Vector2 playerScale_;
    float playerRotate_;
    Vector2 leftTop_;
    Vector2 rightTop_;
    Vector2 leftBottom_;
    Vector2 rightBottom_;
    int titleColor_;
};