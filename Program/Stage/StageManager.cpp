#include "StageManager.h"
#include <Common/CommonFunctions.h>
#include <Blocks/BlockManager.h>
#include <Common/Easings.h>
#include <Common/CustomNovice.h>
#include <Common/GraphHandle.h>
#include <Common/SoundHandle.h>
#include <Common/GetInput.h>

namespace {

// ブロックのデータ
auto *blockManager = BlockManager::GetInstance();
// GetInputのインスタンス
auto *sGetInput = GetInput::GetInstance();

} // namespace

StageManager::StageManager(const std::vector<std::string> &stageFileName) {
    // ステージデータの読み込み
    for (const auto &fileName : stageFileName) {
        if (fileName.empty() || !IsFileExists(fileName)) {
            continue;
        }
        LoadStageData(fileName);
    }
}

bool StageManager::IsHitTopBottom(Vector2 pos, float width) {
    // 渡された座標がマイナスなら false を返して終了
    if (pos.y < 0.0f) {
        return false;
    }

    // 渡された値をそれぞれint型にする
    static Vector2Int arrayPos;
    static Vector2Int posInt;
    static int range;
    static int repeatNum;

    posInt.x = static_cast<int>(pos.x);
    posInt.y = static_cast<int>(pos.y);
    range = static_cast<int>(width) - 1;
    repeatNum = range / kMapChipSize + 1;
    arrayPos.x = 0;
    arrayPos.y = 0;

    //--------- 判定 ---------//
    for (int i = 0; i <= repeatNum; i++) {
        // i の値によって参照する位置の計算を変える
        if (i == 0) {
            // i が 0 のとき
            if (posInt.x < 0) {
                continue;
            }
            arrayPos.x = posInt.x / kMapChipSize;

        } else if (i == repeatNum) {
            // i が 最後の値のとき
            if (posInt.x + range < 0) {
                continue;
            }
            arrayPos.x = (posInt.x + range) / kMapChipSize;

        } else {
            // それ以外(中間)
            if (posInt.x + (kMapChipSize * i - 1) < 0) {
                continue;
            }
            arrayPos.x = (posInt.x + (kMapChipSize * i - 1)) / kMapChipSize;
        }

        arrayPos.y = posInt.y / kMapChipSize;

        // 参照する位置が配列の中なら判定する
        if (arrayPos.x >= 0 && arrayPos.y >= 0 && arrayPos.x < stageData_[currentStageID_].stageSize && arrayPos.y < stageData_[currentStageID_].stageSize) {
            // 当たり判定があるブロックなら true を返す
            if (GetBlockData(stageDataCurrent_.stage[LAYER_RASTER]->GetBlockID(arrayPos.y, arrayPos.x))->IsCollision()) {
                return true;
            }
        }
    }

    // ここまで通ったら false を返す
    return false;
}

bool StageManager::IsHitLeftRight(Vector2 pos, float height) {
    // 渡された座標がマイナスなら false を返して終了
    if (pos.x < 0.0f) {
        return false;
    }

    // 渡された値をそれぞれint型にする
    static Vector2Int arrayPos;
    static Vector2Int posInt;
    static int range;
    static int repeatNum;

    posInt.x = static_cast<int>(pos.x);
    posInt.y = static_cast<int>(pos.y);
    range = static_cast<int>(height) - 1;
    repeatNum = range / kMapChipSize + 1;
    arrayPos.x = 0;
    arrayPos.y = 0;

    //--------- 判定 ---------//
    for (int i = 0; i <= repeatNum; i++) {
        // i の値によって参照する位置の計算を変える
        if (i == 0) {
            // i が 0 のとき
            if (posInt.y < 0) {
                continue;
            }
            arrayPos.y = posInt.y / kMapChipSize;

        } else if (i == repeatNum) {
            // i が 最後の値のとき
            if (posInt.y - range < 0) {
                continue;
            }
            arrayPos.y = (posInt.y - range) / kMapChipSize;

        } else {
            // それ以外(中間)
            if (posInt.y - (kMapChipSize * i + 1) < 0) {
                continue;
            }
            arrayPos.y = (posInt.y - (kMapChipSize * i + 1)) / kMapChipSize;
        }

        arrayPos.x = posInt.x / kMapChipSize;

        // 参照する位置が配列の中なら判定する
        if (arrayPos.x >= 0 && arrayPos.y >= 0 && arrayPos.x < stageData_[currentStageID_].stageSize && arrayPos.y < stageData_[currentStageID_].stageSize) {
            // 当たり判定があるブロックなら true を返す
            if (GetBlockData(stageDataCurrent_.stage[LAYER_RASTER]->GetBlockID(arrayPos.y, arrayPos.x))->IsCollision()) {
                return true;
            }
        }
    }

    // ここまで通ったら false を返す
    return false;
}

void StageManager::UpdateRotateLeft(int x, int y, int range) {
    // 範囲が0のときは全体の回転をする
    if (range <= 0) {
        range = stageData_[currentStageID_].stageSize;
        x = 0;
        y = 0;
    }

    // 回転させる分だけの配列を用意
    static std::vector<std::vector<int>> rotateArr[2];
    for (int i = 0; i < 2; i++) {
        rotateArr[i].resize(range);
        for (int j = 0; j < range; j++) {
            rotateArr[i][j].resize(range);
        }
    }

    // 回転
    for (int i = 0; i < range; i++) {
        for (int j = 0; j < range; j++) {
            rotateArr[0][i][j] = stageDataCurrent_.stage[LAYER_FRONT]->GetBlockID(y + ((range - 1) - j), x + i);
            rotateArr[1][i][j] = stageDataCurrent_.stage[LAYER_SWITCH_ON]->GetBlockID(y + ((range - 1) - j), x + i);
        }
    }

    // 元の配列に代入
    for (int i = 0; i < range; i++) {
        for (int j = 0; j < range; j++) {
            stageDataCurrent_.stage[LAYER_FRONT]->SetBlockID(y + i, x + j, rotateArr[0][i][j]);
            stageDataCurrent_.stage[LAYER_SWITCH_ON]->SetBlockID(y + i, x + j, rotateArr[1][i][j]);
        }
    }

    // レイヤーをラスタライズする
    UpdateRasterize();
}

void StageManager::UpdateRotateRight(int x, int y, int range) {
    // 範囲が0のときは全体の回転をする
    if (range <= 0) {
        range = stageData_[currentStageID_].stageSize;
        x = 0;
        y = 0;
    }

    // 回転させる分だけの配列を用意
    static std::vector<std::vector<int>> rotateArr[2];
    for (int i = 0; i < 2; i++) {
        rotateArr[i].resize(range);
        for (int j = 0; j < range; j++) {
            rotateArr[i][j].resize(range);
        }
    }

    // 回転
    for (int i = 0; i < range; i++) {
        for (int j = 0; j < range; j++) {
            rotateArr[0][i][j] = stageDataCurrent_.stage[LAYER_FRONT]->GetBlockID(y + j, x + ((range - 1) - i));
            rotateArr[1][i][j] = stageDataCurrent_.stage[LAYER_SWITCH_ON]->GetBlockID(y + j, x + ((range - 1) - i));
        }
    }

    // 元の配列に代入
    for (int i = 0; i < range; i++) {
        for (int j = 0; j < range; j++) {
            stageDataCurrent_.stage[LAYER_FRONT]->SetBlockID(y + i, x + j, rotateArr[0][i][j]);
            stageDataCurrent_.stage[LAYER_SWITCH_ON]->SetBlockID(y + i, x + j, rotateArr[1][i][j]);
        }
    }

    // レイヤーをラスタライズする
    UpdateRasterize();
}

void StageManager::LoadStageData(const std::string &fileName)
{
}

void StageManager::UpdateCameraScale(Camera &camera) {
    if (!isPuzzleMode_) {
        // カメラを縮小
        if (cameraEaseCount_ < cameraEaseMaxCount_) {
            cameraEaseCount_++;
            camera.SetScale(
                {
                    Ease::Auto(cameraEaseCount_, cameraEaseMaxCount_, cameraDefaultScale_.x + 0.2f, cameraDefaultScale_.x, EASE_OUT_QUINT),
                    Ease::Auto(cameraEaseCount_, cameraEaseMaxCount_, cameraDefaultScale_.y + 0.2f, cameraDefaultScale_.y, EASE_OUT_QUINT)
                }
            );
            camera.SetCamera();
        }
        return;

    } else {
        // カメラを拡大
        if (cameraEaseCount_ < cameraEaseMaxCount_) {
            cameraEaseCount_++;
            camera.SetScale(
                {
                    Ease::Auto(cameraEaseCount_, cameraEaseMaxCount_, cameraDefaultScale_.x, cameraDefaultScale_.x + 0.2f, EASE_OUT_QUINT),
                    Ease::Auto(cameraEaseCount_, cameraEaseMaxCount_, cameraDefaultScale_.y, cameraDefaultScale_.y + 0.2f, EASE_OUT_QUINT)
                }
            );
            camera.SetCamera();
        }
    }
}

void StageManager::UpdateSelectSection2Mouse(Camera &camera) {
    if (sGetInput->NowInputType() != InputType::KEYBOARD &&
        sGetInput->NowInputType() != InputType::MOUSE &&
        !sGetInput->IsMouseMove()) {
        return;
    }

    for (auto &section : stageData_[currentStageID_].section) {
        if (!IsHitMouse2Section(section, camera)) {
            continue;
        }
        selectSection_ = &section;
        return;
    }

    preSelectSection_ = selectSection_;
    selectSection_ = nullptr;
}

void StageManager::UpdateSelectSection2Controller()
{
}

void StageManager::UpdateRotateSection()
{
}

void StageManager::UpdateRasterize() {
    // 手前のレイヤーを最優先にしてラスタライズする
    for (int i = 0; i < stageData_[currentStageID_].stageSize; i++) {
        for (int j = 0; j < stageData_[currentStageID_].stageSize; j++) {
            stageDataCurrent_.stage[LAYER_RASTER]->SetBlockID(i, j, BLOCK_NONE);

            if (stageDataCurrent_.stage[LAYER_SWITCH_ON]->GetBlockID(i, j) != BLOCK_NONE) {
                stageDataCurrent_.stage[LAYER_RASTER]->SetBlockID(i, j, stageDataCurrent_.stage[LAYER_SWITCH_ON]->GetBlockID(i, j));

            } else if (stageDataCurrent_.stage[LAYER_FRONT]->GetBlockID(i, j) != BLOCK_NONE) {
                stageDataCurrent_.stage[LAYER_RASTER]->SetBlockID(i, j, stageDataCurrent_.stage[LAYER_FRONT]->GetBlockID(i, j));

            } else if (stageDataCurrent_.stage[LAYER_BACK]->GetBlockID(i, j) != BLOCK_NONE) {
                stageDataCurrent_.stage[LAYER_RASTER]->SetBlockID(i, j, stageDataCurrent_.stage[LAYER_BACK]->GetBlockID(i, j));
            }
        }
    }
}

bool StageManager::IsHitMouse2Section(ArrayRange section, Camera &camera) {
    Vector2 pos = {
        static_cast<float>(section.pos.x * kMapChipSize),
        static_cast<float>(section.pos.y * kMapChipSize)
    };
    Vector2 mousePos = { static_cast<float>(sGetInput->MouseX()), static_cast<float>(sGetInput->MouseY()) };
    mousePos = Transform(mousePos, InverseMatrix(camera.GetWVPVPMatrix()));
    float range = static_cast<float>(section.range * kMapChipSize);

    if (IsPos2RectHit(mousePos.x, mousePos.y, pos.x, pos.y, range, range)) {
        return true;
    }

    return false;
}