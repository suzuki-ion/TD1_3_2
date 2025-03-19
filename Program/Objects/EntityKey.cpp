#include <json.hpp>
#include <fstream>
#include <math.h>
#include "EntityKey.h"
#include "Textures.h"
#include "Player.h"
#include "CommonFunctions.h"
#include "SceneClass.h"
#include "SceneChangeAnimations.h"
#include "SoundHandle.h"

using Json = nlohmann::json;

void EntityKey::BlockHitPixelCalc() {
    int blockHitPixelNum = 0;
    blockHitPixelNum_ = 0;

    if (isUnlockAnimation_) {
        return;
    }

    // 上下左右の当たり判定を取得
    isMapChipHit_.top = stage_->IsMapChip2RectYHit(
        pos_.x,
        pos_.y + height_ / 2.0f,
        1.0f,
        true
    );
    isMapChipHit_.bottom = stage_->IsMapChip2RectYHit(
        pos_.x,
        pos_.y - height_ / 2.0f + 1.0f,
        1.0f
    );
    isMapChipHit_.left = stage_->IsMapChip2RectXHit(
        pos_.x - width_ / 2.0f,
        pos_.y,
        1.0f
    );
    isMapChipHit_.right = stage_->IsMapChip2RectXHit(
        pos_.x + width_ / 2.0f - 1.0f,
        pos_.y,
        1.0f
    );

    // 各方向の当たってるピクセル数を計算
    if (isMapChipHit_.top) {
        blockHitPixelNum = abs(static_cast<int>(pos_.y + height_ / 2.0f) % StageClass::GetMapChipSize());
        // 計算したピクセル数のほうが大きければ代入
        if (blockHitPixelNum_ < blockHitPixelNum) {
            blockHitPixelNum_ = blockHitPixelNum;
        }
        if (SceneGame::GetStage()->IsPuzzleMode()) {
            // パズルモードから戻った際に押し戻されるようにvelocityを1にする
            velocity_.y = acceleration_.y * 2.0f;
        }
    }
    if (isMapChipHit_.bottom) {
        blockHitPixelNum_ = StageClass::GetMapChipSize() - abs(static_cast<int>(pos_.y - height_ / 2.0f + 1.0f) % StageClass::GetMapChipSize());
        // 計算したピクセル数のほうが大きければ代入
        if (blockHitPixelNum_ < blockHitPixelNum) {
            blockHitPixelNum_ = blockHitPixelNum;
        }
        if (SceneGame::GetStage()->IsPuzzleMode()) {
            // パズルモードから戻った際に押し戻されるようにvelocityを1にする
            velocity_.y = -(acceleration_.y * 2.0f);
        }
    }
    if (isMapChipHit_.left) {
        blockHitPixelNum = StageClass::GetMapChipSize() - abs(static_cast<int>(pos_.x - width_ / 2.0f) % StageClass::GetMapChipSize());
        // 計算したピクセル数のほうが大きければ代入
        if (blockHitPixelNum_ < blockHitPixelNum) {
            blockHitPixelNum_ = blockHitPixelNum;
        }
        if (SceneGame::GetStage()->IsPuzzleMode()) {
            // パズルモードから戻った際に押し戻されるようにvelocityを1にする
            velocity_.x = -(acceleration_.x * 2.0f);
        }
    }
    if (isMapChipHit_.right) {
        blockHitPixelNum = abs(static_cast<int>(pos_.x + width_ / 2.0f - 1.0f) % StageClass::GetMapChipSize());
        // 計算したピクセル数のほうが大きければ代入
        if (blockHitPixelNum_ < blockHitPixelNum) {
            blockHitPixelNum_ = blockHitPixelNum;
        }
        if (SceneGame::GetStage()->IsPuzzleMode()) {
            // パズルモードから戻った際に押し戻されるようにvelocityを1にする
            velocity_.x = acceleration_.x * 2.0f;
        }
    }
}

void EntityKey::TopBottomProc() {
    velocity_.y -= acceleration_.y;

    // 速度を制限
    velocity_.y = Clamp(
        velocity_.y,
        minVelocity_.y,
        maxVelocity_.y
    );

    pos_.y += velocity_.y;

    // Y方向の速度がプラスなら top の当たり判定をする
    if (velocity_.y > 0.0f) {
        isMapChipHit_.bottom = false;
        isMapChipHit_.top = stage_->IsMapChip2RectYHit(
            pos_.x - width_ / 2.0f,
            pos_.y + height_ / 2.0f + velocity_.y,
            width_,
            true
        );
        // top のフラグが立ったらY速度を0にして下にずらす
        if (isMapChipHit_.top) {
            pos_.y = static_cast<float>((static_cast<int>(pos_.y + height_ / 2.0f + velocity_.y) / StageClass::GetMapChipSize()) * StageClass::GetMapChipSize()) - height_ / 2.0f;
            velocity_.y = 0.0f;
        }
    }

    // Y方向の速度がマイナスなら bottom の当たり判定をする
    if (velocity_.y < 0.0f) {
        isMapChipHit_.top = false;
        // bottom のフラグが下がっていて
        if (!isMapChipHit_.bottom) {
            isMapChipHit_.bottom = stage_->IsMapChip2RectYHit(
                pos_.x - width_ / 2.0f,
                pos_.y - height_ / 2.0f + 1.0f + velocity_.y,
                width_
            );
            // 当たり判定を行ってフラグが立ったら着地音を鳴らす
            if (isMapChipHit_.bottom) {
                //PlaySounds(soundHandle[SE_PLAYER_LANDED], playHandle[SE_PLAYER_LANDED]);
            }

        } else {
            isMapChipHit_.bottom = stage_->IsMapChip2RectYHit(
                pos_.x - width_ / 2.0f,
                pos_.y - height_ / 2.0f + 1.0f + velocity_.y,
                width_
            );
        }

        // bottom のフラグが立ったらY速度を0にして上にずらす
        if (isMapChipHit_.bottom) {
            pos_.y = static_cast<float>((static_cast<int>(pos_.y - height_ / 2.0f + 1.0f + velocity_.y) / StageClass::GetMapChipSize() + 1) * StageClass::GetMapChipSize()) + height_ / 2.0f;
            velocity_.y = 0.0f;
        }
    }
}

void EntityKey::PlayerHitProc() {
    static Player *player = SceneGame::GetPlayer();
    if (!isExist_ || isDelete_ || isUnlockAnimation_) {
        return;
    }

    if (pos_.x - width_ / 2.0f < player->GetPos().x + player->GetWidth() / 2.0f &&
        pos_.x + width_ / 2.0f > player->GetPos().x - player->GetWidth() / 2.0f &&
        pos_.y - height_ / 2.0f < player->GetPos().y + player->GetHeight() / 2.0f &&
        pos_.y + height_ / 2.0f > player->GetPos().y - player->GetHeight() / 2.0f) {
        isUnlockAnimation_ = true;
        getPos_ = pos_;
        SoundHandle::Play(SE_KEY_GET);
    }
}

void EntityKey::Respawn() {
    if (!isDelete_) {
        // キーが埋まるもしくは下に落ちたら消す
        if (pos_.y < -128.0f || blockHitPixelNum_ >= 16) {
            isDelete_ = true;
            if (blockHitPixelNum_ >= 16) {
                respawnAnimationCount_ = 0;
                particlePos_ = pos_;
            }

        } else {
            return;
        }
    }

    respawnCount_++;
    if (respawnCount_ >= 60) {
        pos_ = stage_->GetKeyPos();
        velocity_ = { 0.0f, 0.0f };
        isDelete_ = false;
        respawnCount_ = 0;
        respawnAnimationCount_ = 0;
        particlePos_ = pos_;
    }
}

void EntityKey::UpdateUnlockAnimation() {
    if (!isUnlockAnimation_) {
        return;
    }

    unlockAnimationCount_++;
    if (unlockAnimationCount_ < unlockAnimationMaxCount_ / 3) {
        pos_.y = Ease::Auto(
            unlockAnimationCount_,
            unlockAnimationMaxCount_ / 3,
            getPos_.y,
            getPos_.y + 128.0f,
            EASE_OUT_BACK
        );

    } else if (unlockAnimationCount_ <= unlockAnimationMaxCount_) {
        pos_.x = Ease::Auto(
            unlockAnimationCount_ - unlockAnimationMaxCount_ / 3,
            unlockAnimationMaxCount_ / 3 * 2,
            getPos_.x,
            goalPos_.x,
            EASE_IN_BACK
        );
        pos_.y = Ease::Auto(
            unlockAnimationCount_ - unlockAnimationMaxCount_ / 3,
            unlockAnimationMaxCount_ / 3 * 2,
            getPos_.y + 128.0f,
            goalPos_.y,
            EASE_IN_BACK
        );

    } else {
        isExist_ = false;
        isUnlockAnimation_ = false;
        unlockAnimationCount_ = 0;
        respawnAnimationCount_ = 0;
        particlePos_ = goalPos_;
        SoundHandle::Play(SE_KEY_UNLOCK);
    }
}

void EntityKey::UpdateParticle() {
    static Vector2 easePos;
    static float degreeVector = 0.0f;
    static float degreeRotate = 0.0f;

    if (respawnAnimationCount_ >= respawnAnimationMaxCount_) {
        return;
    }

    respawnAnimationCount_++;

    for (int i = 0; i < 8; i++) {
        degreeVector = (360.0f / 8.0f) * static_cast<float>(i);
        easePos = {
            Ease::Auto(
                respawnAnimationCount_,
                respawnAnimationMaxCount_,
                particlePos_.x,
                particlePos_.x + std::cos(ConvertDeg2Rad(degreeVector)) * 256.0f,
                EASE_OUT_CUBIC
            ),
            Ease::Auto(
                respawnAnimationCount_,
                respawnAnimationMaxCount_,
                particlePos_.y,
                particlePos_.y + std::sin(ConvertDeg2Rad(degreeVector)) * 256.0f,
                EASE_OUT_CUBIC
            )
        };
        particle_[i]->SetLocalCenterPos(easePos);
        degreeRotate += 2.0f;
        particle_[i]->SetRotate(ConvertDeg2Rad(degreeRotate));
        particle_[i]->SetColor(
            0xffff8b00 + static_cast<unsigned int>(Ease::Auto(
                respawnAnimationCount_,
                respawnAnimationMaxCount_,
                255.0f,
                0.0f,
                EASE_LINER
            ))
        );
    }
}

void EntityKey::DrawParticle() {
    for (int i = 0; i < 8; i++) {
        if (respawnAnimationCount_ < respawnAnimationMaxCount_) {
            particle_[i]->Draw(*camera_);
        }
    }
}

EntityKey::EntityKey() {
    // ステータスをプレイヤーと同じにする
    std::ifstream playerDataFile("PlayerStatus.json");
    Json playerData;
    playerDataFile >> playerData;
    playerDataFile.close();
    minVelocity_.x = playerData["PlayerStatus"]["minVelocity"]["x"];
    minVelocity_.y = playerData["PlayerStatus"]["minVelocity"]["y"];
    maxVelocity_.x = playerData["PlayerStatus"]["maxVelocity"]["x"];
    maxVelocity_.y = playerData["PlayerStatus"]["maxVelocity"]["y"];
    acceleration_.x = playerData["PlayerStatus"]["acceleration"]["x"];
    acceleration_.y = playerData["PlayerStatus"]["acceleration"]["y"];
    width_ = playerData["PlayerStatus"]["width"];
    height_ = playerData["PlayerStatus"]["height"];

    camera_ = SceneGame::GetCamera();
    stage_ = SceneGame::GetStage();
    for (int i = 0; i < 8; i++) {
        particle_[i] = std::make_unique<RectObject>();
        dynamic_cast<RectObject *>(particle_[i].get())->SetWidth(32.0f);
        dynamic_cast<RectObject *>(particle_[i].get())->SetHeight(32.0f);
        particle_[i]->SetColor(0xffff8bff);
    }
}

void EntityKey::Reset() {
    pos_ = stage_->GetKeyPos();
    velocity_ = { 0.0f, 0.0f };
    blockHitPixelNum_ = 0;
    isExist_ = stage_->GetKeyIsExist();
    goalPos_ = stage_->GetGoalPos();
    isDelete_ = false;
    isUnlockAnimation_ = false;
    respawnCount_ = 0;
    respawnAnimationCount_ = respawnAnimationMaxCount_;
    unlockAnimationCount_ = 0;
}

void EntityKey::Update() {
    if (!isExist_ || SceneChange::IsChanging()) {
        goto THROW;
    }

    BlockHitPixelCalc();
    if (!SceneGame::GetStage()->IsPuzzleMode()) {
        TopBottomProc();
        PlayerHitProc();
        Respawn();
    }
    UpdateUnlockAnimation();
    THROW:
    UpdateParticle();
}

void EntityKey::Draw() {
    static float animationDegree = 0.0f;
    static float animationDegreeSpeed = 4.0f;
    static float theta = 0.0f;

    if (!isExist_ || isDelete_) {
        goto THROW;
    }

    animationDegree_ = fmodf(animationDegree_ + animationDegreeSpeed_, 360.0f);
    theta_ = ConvertDeg2Rad(animationDegree_);

    CustomNovice::DrawQuad(
        *camera_,
        pos_.x - width_ / 2.0f,
        pos_.y + height_ / 2.0f + std::sin(theta_) * 8.0f,
        pos_.x + width_ / 2.0f,
        pos_.y + height_ / 2.0f + std::sin(theta_) * 8.0f,
        pos_.x - width_ / 2.0f,
        pos_.y - height_ / 2.0f + std::sin(theta_) * 8.0f,
        pos_.x + width_ / 2.0f,
        pos_.y - height_ / 2.0f + std::sin(theta_) * 8.0f,
        0, 0,
        GraphHandle::Width(TX_KEY),
        GraphHandle::Height(TX_KEY),
        GraphHandle::ID(TX_KEY)
    );
    THROW:
    DrawParticle();
}

void EntityKey::Draw(Camera &camera) {
    if (!isExist_) {
        return;
    }

    animationDegree_ = fmodf(animationDegree_ + animationDegreeSpeed_, 360.0f);
    theta_ = ConvertDeg2Rad(animationDegree_);

    CustomNovice::DrawQuad(
        camera,
        pos_.x - width_ / 2.0f,
        pos_.y + height_ / 2.0f + std::sin(theta_) * 8.0f,
        pos_.x + width_ / 2.0f,
        pos_.y + height_ / 2.0f + std::sin(theta_) * 8.0f,
        pos_.x - width_ / 2.0f,
        pos_.y - height_ / 2.0f + std::sin(theta_) * 8.0f,
        pos_.x + width_ / 2.0f,
        pos_.y - height_ / 2.0f + std::sin(theta_) * 8.0f,
        0, 0,
        GraphHandle::Width(TX_KEY),
        GraphHandle::Height(TX_KEY),
        GraphHandle::ID(TX_KEY)
    );
}