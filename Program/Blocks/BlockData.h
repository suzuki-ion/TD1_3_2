#pragma once
#include "BlockDataBase.h"
#include <Common/GraphHandle.h>

/// @brief 当たり判定のある白のブロック
class BlockWhite : public BlockDataBase {
public:
    BlockWhite() {
        textureID_ = TX_TILEMAP_NORMAL;
        isCollision_ = true;
        isDrawing_ = true;
        isConnectTexture_ = true;
    }
};

/// @brief 当たり判定のない黒のブロック
class BlockBlack : public BlockDataBase {
public:
    BlockBlack() {
        textureID_ = TX_TILEMAP_BRAILLE;
        isCollision_ = false;
        isDrawing_ = true;
        isConnectTexture_ = true;
    }
};

/// @brief ゴールブロック
class BlockGoal : public BlockDataBase {
public:
    BlockGoal() {
        textureID_ = TX_BLOCK_GOAL;
        isCollision_ = false;
        isDrawing_ = true;
    }
};

/// @brief スイッチ
class BlockSwitch : public BlockDataBase {
public:
    BlockSwitch() {
        textureID_ = TX_BLOCK_SWITCH;
        isCollision_ = false;
        isDrawing_ = true;
    }
    void Update() override;
};

/// @brief スイッチで動くブロック(オン)
class BlockSwitchingOn : public BlockDataBase {
public:
    BlockSwitchingOn() {
        textureID_ = TX_TILEMAP_ON;
        isCollision_ = true;
        isDrawing_ = true;
    }
};

/// @brief スイッチで動くブロック(オフ)
class BlockSwitchingOff : public BlockDataBase {
public:
    BlockSwitchingOff() {
        textureID_ = TX_TILEMAP_OFF;
        isCollision_ = true;
        isDrawing_ = true;
    }
};

/// @brief レーザー
class BlockLaser : public BlockDataBase {
public:
    BlockLaser() {
        textureID_ = TX_TILEMAP_NORMAL;
        isCollision_ = false;
        isDrawing_ = true;
    }
};

/// @brief レーザーで壊れるブロック
class BlockLaserBreak : public BlockDataBase {
public:
    BlockLaserBreak() {
        textureID_ = TX_TILEMAP_NORMAL;
        isCollision_ = true;
        isDrawing_ = true;
    }
};