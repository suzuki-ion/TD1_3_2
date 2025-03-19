#pragma once
#include <vector>
#include <Common/Math/Vector2Int.h>

const int kMaxStageWidth = 128;
const int kMaxStageHeight = 128;

// タイルマップのテクスチャ参照位置
enum Tilemap {
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT
};

// ステージ上の1ブロックごとのデータ
struct Stage1BlockData {
    // ブロックの種類
    int blockID = 0;
    // 汎用的カウンター
    int counter = 0;
    // タイルマップの参照位置(テクスチャが繋がるブロック用)
    Vector2Int tilemap[4] = {
        { 0, 0 },
        { 1, 0 },
        { 0, 1 },
        { 1, 1 }
    };
};

class Stage {
private:
    Stage1BlockData stage_[kMaxStageHeight][kMaxStageWidth];
public:
    int &operator[](const Vector2Int &pos) {
        return stage_[pos.y][pos.x].blockID;
    }

    /// @brief ステージのセット
    /// @param setStage ステージのデータ
    void SetStage(const int (&setStage)[kMaxStageHeight][kMaxStageWidth]) {
        for (int y = 0; y < kMaxStageHeight; y++) {
            for (int x = 0; x < kMaxStageWidth; x++) {
                stage_[y][x].blockID = setStage[y][x];
            }
        }
    }

    /// @brief ブロックの種類の設定
    /// @param x X座標
    /// @param y Y座標
    /// @param blockID ブロックの種類
    void SetBlockID(int x, int y, int blockID) {
        stage_[y][x].blockID = blockID;
    }

    /// @brief ブロックの種類の取得
    /// @param x X座標
    /// @param y Y座標
    /// @return ブロックの種類
    int GetBlockID(int x, int y) {
        return stage_[y][x].blockID;
    }

    /// @brief 指定座標のブロックデータの取得
    /// @param x X座標
    /// @param y Y座標
    /// @return ブロックデータへのポインタ
    Stage1BlockData *GetBlockData(int x, int y) {
        return &stage_[y][x];
    }

    /// @brief 繋がるテクスチャに対してのタイルマップの更新
    void UpdateTilemap();

    /// @brief ステージのリセット
    void Reset() {
        for (int y = 0; y < kMaxStageHeight; y++) {
            for (int x = 0; x < kMaxStageWidth; x++) {
                stage_[y][x].blockID = 0;
                stage_[y][x].tilemap[0] = { 0, 0 };
                stage_[y][x].tilemap[1] = { 1, 0 };
                stage_[y][x].tilemap[2] = { 0, 1 };
                stage_[y][x].tilemap[3] = { 1, 1 };
            }
        }
    }
};