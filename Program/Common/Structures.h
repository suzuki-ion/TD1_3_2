#pragma once
#include <windows.h>
#include <Novice.h>
#include <vector>
#include <string>
#include <Common/Math/Vector2.h>
#include <Common/Math/Vector2Int.h>
#include <Common/Math/Matrix3x3.h>

struct Sound {
    // Noviceでの再生用のID
    int id = -1;
    // 音声の再生音量
    float volume = 1.0f;
    // 音声のループフラグ
    bool isLoop = false;
};

// ブロックの構造体
struct Block {
    // ブロックのテクスチャID
    int textureID = -1;
    // ギミックを動かすときの操作方法
    int gimmickOperateType = 0;
    // 歩いたときに鳴る音
    int sound = 0;
    // 隣り合う同ブロックと繋がるテクスチャか否か
    bool isConnectTexture = false;
    // 当たり判定をするか否か
    bool isCollision = false;
    // 描画するか否か
    bool isDrawing = false;
    // 背景のブロックを描画するか否かのフラグ
    bool isDrawingBackBlock = false;
    // 下から通り抜けられるかのフラグ
    bool isThrouth = false;
};

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

// Novice用ボタンの構造体
struct NoviceButton {
    // ボタン描画位置
    Vector2 pos;
    // ボタンの横幅
    float width = 0;
    // ボタンの縦幅
    float height = 0;
    // ボタンの識別番号
    int id = 0;
    // ボタン通常時に描画する画像
    // (不使用なら -1 に設定しておく)
    int graphHandle2Usually = -1;
    // ボタン選択時に描画する画像
    // (不使用なら -1 に設定しておく。ちなみにその場合、通常時の画像が使われる。)
    int graphHandle2Select = -1;
    // ボタン決定時に描画する画像
    // (不使用なら -1 に設定しておく。ちなみにその場合、選択時の画像が使われる。)
    int graphHandle2Pushed = -1;
    // ボタン選択時の音
    // (不使用なら -1 に設定しておく)
    int soundHandle2Select = -1;
    // ボタン決定時の音
    // (不使用なら -1 に設定しておく)
    int soundHandle2Pushed = -1;
    // 文字描画時に使用するフォント
    // (不使用なら -1 に設定しておく)
    int fontGh = -1;
    // 文字の横幅
    int fontWidth = 1;
    // 文字の縦幅
    int fontHeight = 1;
    // 文字描画時の横幅
    int fontDrawWidth = 1;
    // 文字描画時の縦幅
    int fontDrawHeight = 1;
    // 文字の表示方法
    int fontDrawMethod = 0;
    // 文字の描画時のずらし座標
    Vector2 fontDrawShift;
    // 文字間のマージン
    Vector2Int fontMargin;
    // ボタン通常時の描画色
    unsigned int color2Usually = 0xFFFFFF80;
    // ボタン選択時の描画色
    unsigned int color2Select = WHITE;
    // ボタン決定時の描画色
    unsigned int color2Pushed = 0xFF8080FF;
    // ボタンに表示する文字
    std::string str = "\0";
    // 個別の選択用キー
    std::vector<int> selectKeys;
    // 個別の決定用キー
    std::vector<int> pushedKeys;
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