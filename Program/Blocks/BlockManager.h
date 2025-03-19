#pragma once
#include "BlockData.h"

enum BlockType {
    // 無し
    BLOCK_NONE,

    /// 
    /// ↓ここからブロックID記述
    /// 

    // 当たり判定のある白のブロック
    BLOCK_WHITE,
    // 当たり判定のない黒のブロック
    BLOCK_BLACK,

    // ゴールブロック
    BLOCK_GOAL,

    // スイッチ
    BLOCK_SWITCH,

    // スイッチで動くブロック(オン)
    BLOCK_SWITCHING_ON,
    // スイッチで動くブロック(オフ)
    BLOCK_SWITCHING_OFF,

    // レーザー
    BLOCK_LASER,
    // レーザーで壊れるブロック
    BLOCK_LASER_BREAK,

    /// 
    /// ↑ここまでブロックID記述
    /// 

    // ブロックの総数
    BLOCKS
};

/// @brief ブロック管理クラス
class BlockManager final {
public:
    BlockManager(const BlockManager &) = delete;
    BlockManager &operator=(const BlockManager &) = delete;
    BlockManager(BlockManager &&) = delete;
    BlockManager &operator=(BlockManager &&) = delete;

    /// @brief ブロック管理クラスのインスタンス取得
    /// @return ブロック管理クラスのインスタンス
    static BlockManager *GetInstance() {
        static BlockManager instance;
        return &instance;
    }

    /// @brief 初期化処理
    void Initialize() {
        blockData_[BLOCK_NONE] = BlockDataBase();
        blockData_[BLOCK_WHITE] = BlockWhite();
        blockData_[BLOCK_BLACK] = BlockBlack();
        blockData_[BLOCK_GOAL] = BlockGoal();
        blockData_[BLOCK_SWITCH] = BlockSwitch();
        blockData_[BLOCK_SWITCHING_ON] = BlockSwitchingOn();
        blockData_[BLOCK_SWITCHING_OFF] = BlockSwitchingOff();
        blockData_[BLOCK_LASER] = BlockLaser();
        blockData_[BLOCK_LASER_BREAK] = BlockLaserBreak();
    }

    /// @brief ブロックのデータ取得
    /// @param blockID ブロックのID
    /// @return ブロックのデータへのポインタ
    BlockDataBase *GetBlockData(int blockID) { return &blockData_[blockID]; }

private:
    BlockManager() = default;
    ~BlockManager() = default;

    // ブロックのデータ
    BlockDataBase blockData_[BLOCKS];
};

/// @brief ブロックのデータ取得
/// @param blockID ブロックのID
/// @return ブロックのデータへのポインタ
BlockDataBase *GetBlockData(int blockID) {
    return BlockManager::GetInstance()->GetBlockData(blockID);
}