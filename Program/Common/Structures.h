#pragma once
#include <windows.h>
#include <Novice.h>
#include <vector>
#include <string>
#include <Common/Math/Vector2.h>
#include <Common/Math/Vector2Int.h>
#include <Common/Math/Matrix3x3.h>

// 配列の範囲
struct ArrayRange {
    Vector2Int pos;
    int range = 0;
};

// マップチップの当たり判定専用構造体
struct IsMapChipHit {
    bool top = false;
    bool bottom = false;
    bool left = false;
    bool right = false;
};

// アニメーション用の円
struct AnimCircle {
    // 座標
    Vector2 pos;
    // 半径
    float radius = 0.0f;
    // アニメーション開始カウント
    int startCount = 0;
    // アニメーション終了カウント
    int endCount = 0;
};

// アニメーション用の四角形
struct AnimRect {
    // ローカル行列
    Matrix3x3 localMatrix = {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    // 中心座標
    Vector2 centerPos;
    // 左上座標
    Vector2 leftTop;
    // 右上座標
    Vector2 rightTop;
    // 左下座標
    Vector2 leftBottom;
    // 右下座標
    Vector2 rightBottom;
    // 横幅
    float width = 0;
    // 縦幅
    float height = 0;
    // 回転角度
    float degree = 0.0f;
    // アニメーション開始カウント
    int startCount = 0;
    // アニメーション終了カウント
    int endCount = 0;
    // 色
    unsigned int color = WHITE;
};

// アニメーション用構造体群
#pragma region illust_animation

// イラストのアニメーションデータ
typedef struct IllustObjAnim {
    // 平行移動開始値
    Vector2 translate;
    // 平行移動に使うイージング
    Vector2Int translateEaseType;
    // 拡縮開始値
    Vector2 scale;
    // 拡縮に使うイージング
    Vector2Int scaleEaseType;
    // 回転開始値
    float degree = 0.0f;
    // 回転に使うイージング
    int degreeEaseType = 0;
    // アニメーションを始めるカウントの値
    int startCount = 0;
} IllustObjAnim;

// イラストのアニメーション用オブジェクト
typedef struct IllustObj {
    // オブジェクトの名前
    std::string name = "root";
    // 名前のハッシュ値
    size_t nameHash = 0;
    // 原点((0, 0)を左上としたスクリーン系のローカル座標)
    Vector2 pivot;
    // 左上座標
    Vector2 leftTop;
    // 右上座標
    Vector2 rightTop;
    // 左下座標
    Vector2 leftBottom;
    // 右下座標
    Vector2 rightBottom;
    // 平行移動
    Vector2 translate;
    // 拡縮
    Vector2 scale = { 1.0f, 1.0f };
    // 回転角(deg)
    float degree = 0.0f;
    // イラストの横幅
    float width = 0.0f;
    // イラストの縦幅
    float height = 0.0f;
    // テクスチャ(イラストのグラフハンドル)
    int texture = -1;
    // ワールド行列
    Matrix3x3 worldMatrix;
    // ローカル行列
    Matrix3x3 localMatrix;
    // アニメーション情報
    std::vector<IllustObjAnim> illustObjAnim;
    // 子オブジェクト
    std::vector<IllustObj> childrenObj;
    // 親オブジェクト(ポインタ)
    IllustObj *parentObj = nullptr;
} IllustObj;

// イラストのアニメーション用構造体
struct RootObj {
    // アニメーションのカウント
    int animationCount = 0;
    // アニメーションのカウントの最大値
    int animationCountMax = 1;
    // アニメーション用オブジェクト
    IllustObj illustObj;
};

#pragma endregion