#include <Stage/Stage.h>
#include <Common/CommonFunctions.h>
#include <Blocks/BlockManager.h>

namespace {

// ブロックのデータ
BlockManager *blockManager = BlockManager::GetInstance();

} // namespace

void Stage::UpdateTilemap() {
    // 参照位置
    int x = 0;
    int y = 0;
    // デフォルトのタイルの値
    static Vector2Int defaultTile[4] = {
        { 0, 0 },
        { 1, 0 },
        { 0, 1 },
        { 1, 1 }
    };

    // 配列の大きさ分繰り返し
    for (int i = 0; i < kMaxStageHeight; i++) {
        for (int j = 0; j < kMaxStageWidth; j++) {
            // 値をリセット
            for (int k = 0; k < 4; k++) {
                stage_[i][j].tilemap[k] = defaultTile[k];
            }

            // 参照してる位置にブロックがあって
            if (stage_[i][j].blockID == BLOCK_NONE) {
                continue;
            }
            // タイルマップを用いるブロックならテクスチャを計算
            if (blockManager->GetBlockData(stage_[i][j].blockID)->IsConnectTexture()) {
                continue;
            }

            //--------- 上 ---------//

            // 参照する位置を設定
            y = i + 1;
            // 判定する方向に同じ種類のブロックがあったら繋げる
            if (y < kMaxStageHeight && stage_[i][j].blockID == stage_[y][j].blockID) {
                stage_[i][j].tilemap[TOP_LEFT].x = 0;
                stage_[i][j].tilemap[TOP_LEFT].y = 4;
                stage_[i][j].tilemap[TOP_RIGHT].x = 3;
                stage_[i][j].tilemap[TOP_RIGHT].y = 4;
            }

            //--------- 下 ---------//

            // 参照する位置を設定
            y = i - 1;
            // 判定する方向に同じ種類のブロックがあったら繋げる
            if (y >= 0 && stage_[i][j].blockID == stage_[y][j].blockID) {
                stage_[i][j].tilemap[BOTTOM_LEFT].x = 0;
                stage_[i][j].tilemap[BOTTOM_LEFT].y = 3;
                stage_[i][j].tilemap[BOTTOM_RIGHT].x = 3;
                stage_[i][j].tilemap[BOTTOM_RIGHT].y = 3;
            }

            //--------- 左 ---------//

            // 参照する位置を設定
            x = j - 1;
            // 判定する方向に同じ種類のブロックがあったら繋げる
            if (x >= 0 && stage_[i][j].blockID == stage_[i][x].blockID) {
                // 既に上に繋がってたら別のテクスチャにする
                if (stage_[i][j].tilemap[TOP_LEFT].x == 0 && stage_[i][j].tilemap[TOP_LEFT].y == 4) {
                    stage_[i][j].tilemap[TOP_LEFT].x = 2;
                    stage_[i][j].tilemap[TOP_LEFT].y = 0;
                } else {
                    stage_[i][j].tilemap[TOP_LEFT].x = 2;
                    stage_[i][j].tilemap[TOP_LEFT].y = 2;
                }
                // 既に下に繋がってたら別のテクスチャにする
                if (stage_[i][j].tilemap[BOTTOM_LEFT].x == 0 && stage_[i][j].tilemap[BOTTOM_LEFT].y == 3) {
                    stage_[i][j].tilemap[BOTTOM_LEFT].x = 2;
                    stage_[i][j].tilemap[BOTTOM_LEFT].y = 1;
                } else {
                    stage_[i][j].tilemap[BOTTOM_LEFT].x = 2;
                    stage_[i][j].tilemap[BOTTOM_LEFT].y = 5;
                }
            }

            //--------- 右 ---------//

            // 参照する位置を設定
            x = j + 1;
            // 判定する方向に同じ種類のブロックがあったら繋げる
            if (x < stageData_[playNowStageID_].stageSize && stage_[i][j].blockID == stage_[i][x].blockID) {
                // 既に上に繋がってたら別のテクスチャにする
                if (stage_[i][j].tilemap[TOP_RIGHT].x == 3 && stage_[i][j].tilemap[TOP_RIGHT].y == 4) {
                    stage_[i][j].tilemap[TOP_RIGHT].x = 3;
                    stage_[i][j].tilemap[TOP_RIGHT].y = 0;
                } else {
                    stage_[i][j].tilemap[TOP_RIGHT].x = 1;
                    stage_[i][j].tilemap[TOP_RIGHT].y = 2;
                }
                // 既に下に繋がってたら別のテクスチャにする
                if (stage_[i][j].tilemap[BOTTOM_RIGHT].x == 3 && stage_[i][j].tilemap[BOTTOM_RIGHT].y == 3) {
                    stage_[i][j].tilemap[BOTTOM_RIGHT].x = 3;
                    stage_[i][j].tilemap[BOTTOM_RIGHT].y = 1;
                } else {
                    stage_[i][j].tilemap[BOTTOM_RIGHT].x = 1;
                    stage_[i][j].tilemap[BOTTOM_RIGHT].y = 5;
                }
            }

            //--------- 左上 ---------//

            // 左と上に繋がってたら左上を参照する
            if (stage_[i][j].tilemap[TOP_LEFT].x == 2 && stage_[i][j].tilemap[TOP_LEFT].y == 0) {
                // 参照する位置を設定
                x = j - 1;
                y = i + 1;
                // 判定する方向に同じ種類のブロックがあったら繋げる
                if (x >= 0 && y < stageData_[playNowStageID_].stageSize && stage_[i][j].blockID == stage_[y][x].blockID) {
                    stage_[i][j].tilemap[TOP_LEFT].x = 2;
                    stage_[i][j].tilemap[TOP_LEFT].y = 4;
                }
            }

            //--------- 右上 ---------//

            // 右と上に繋がってたら左上を参照する
            if (stage_[i][j].tilemap[TOP_RIGHT].x == 3 && stage_[i][j].tilemap[TOP_RIGHT].y == 0) {
                // 参照する位置を設定
                x = j + 1;
                y = i + 1;
                // 判定する方向に同じ種類のブロックがあったら繋げる
                if (x < stageData_[playNowStageID_].stageSize && y < stageData_[playNowStageID_].stageSize && stage_[i][j].blockID == stage_[y][x].blockID) {
                    stage_[i][j].tilemap[TOP_RIGHT].x = 1;
                    stage_[i][j].tilemap[TOP_RIGHT].y = 4;
                }
            }

            //--------- 左下 ---------//

            // 左と下に繋がってたら左上を参照する
            if (stage_[i][j].tilemap[BOTTOM_LEFT].x == 2 && stage_[i][j].tilemap[BOTTOM_LEFT].y == 1) {
                // 参照する位置を設定
                x = j - 1;
                y = i - 1;
                // 判定する方向に同じ種類のブロックがあったら繋げる
                if (x >= 0 && y >= 0 && stage_[i][j].blockID == stage_[y][x].blockID) {
                    stage_[i][j].tilemap[BOTTOM_LEFT].x = 2;
                    stage_[i][j].tilemap[BOTTOM_LEFT].y = 3;
                }
            }

            //--------- 右下 ---------//

            // 右と下に繋がってたら左上を参照する
            if (stage_[i][j].tilemap[BOTTOM_RIGHT].x == 3 && stage_[i][j].tilemap[BOTTOM_RIGHT].y == 1) {
                // 参照する位置を設定
                x = j + 1;
                y = i - 1;
                // 判定する方向に同じ種類のブロックがあったら繋げる
                if (x < stageData_[playNowStageID_].stageSize && y >= 0 && stage_[i][j].blockID == stage_[y][x].blockID) {
                    stage_[i][j].tilemap[BOTTOM_RIGHT].x = 1;
                    stage_[i][j].tilemap[BOTTOM_RIGHT].y = 3;
                }
            }
        }
    }
}