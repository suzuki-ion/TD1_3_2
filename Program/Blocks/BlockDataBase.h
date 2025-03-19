#pragma once
#include <Common/Camera.h>
#include <Stage/StageManager.h>

/// @brief ブロックデータの基底クラス
class BlockDataBase {
protected:
    int textureID_ = -1;
    bool isCollision_ = false;
    bool isDrawing_ = false;
    bool isConnectTexture_ = false;
    Matrix3x3 affineMatrix_ = Matrix3x3::InitialValue();

public:
    /// @brief アフィン行列の設定
    /// @param affineMatrix アフィン行列
    void SetAffineMatrix(const Matrix3x3 &affineMatrix) {
        affineMatrix_ = affineMatrix;
    }

    /// @brief テクスチャIDの取得
    /// @return テクスチャID
    int GetTextureID() const {
        return textureID_;
    }

    /// @brief 当たり判定フラグの取得
    /// @return 当たり判定フラグ
    bool IsCollision() const {
        return isCollision_;
    }

    /// @brief 描画フラグの取得
    /// @return 描画フラグ
    bool IsDrawing() const {
        return isDrawing_;
    }

    /// @brief 繋がるテクスチャフラグの取得
    /// @return 繋がるテクスチャフラグ
    bool IsConnectTexture() const {
        return isConnectTexture_;
    }

    /// @brief アフィン行列の取得
    /// @return アフィン行列
    Matrix3x3 GetAffineMatrix() const {
        return affineMatrix_;
    }

    /// @brief 更新処理
    /// @param stage ステージデータ
    virtual void Update(StageData &stageData) {
        return;
        static_cast<void>(stageData);
    }

    /// @brief 指定座標での更新処理
    /// @param stage ステージデータ
    /// @param x X座標
    /// @param y Y座標
    virtual void Update(StageData &stageData, int x, int y) {
        return;
        static_cast<void>(stageData);
        static_cast<void>(x);
        static_cast<void>(y);
    }

    /// @brief 描画処理
    /// @param x ステージ上でのX座標
    /// @param y ステージ上でのY座標
    /// @param tilemap タイルマップ
    virtual void Draw(int x, int y, Vector2Int tilemap[4]) {
        return;
        static_cast<void>(x);
        static_cast<void>(y);
        static_cast<void>(tilemap);
    };

    /// @brief カメラを使用した描画処理
    /// @param x ステージ上でのX座標
    /// @param y ステージ上でのY座標
    /// @param tilemap タイルマップ
    /// @param camera カメラ
    virtual void Draw(int x, int y, Vector2Int tilemap[4], Camera &camera) {
        return;
        static_cast<void>(x);
        static_cast<void>(y);
        static_cast<void>(tilemap);
        static_cast<void>(camera);
    };
};