#pragma once
#include <json.hpp>
#include "Structures.h"
#include "StageClass.h"
#include "SceneClass.h"
#include "Objects.h"

using Json = nlohmann::json;

class Player {
    StageClass *stage_ = SceneGame::GetStage();
    Vector2 cameraDefaultTranslate_;
    Vector2 pos_= { 256.0f, 256.0f };
    Vector2Int posMap_ = { 0, 0 };
    Vector2 prePos_ = pos_;
    Vector2 particlePos_ = pos_;
    Vector2 acceleration_;
    Vector2 velocity_;
    Vector2 minVelocity_;
    Vector2 maxVelocity_;
    IsMapChipHit isMapChipHit_;
    float width_ = static_cast<float>(StageClass::GetMapChipSize());
    float height_ = static_cast<float>(StageClass::GetMapChipSize());
    float addHitWidth_ = 0.0f;
    float jumpPower_ = 18.5f;
    bool isAlive_ = true;
    bool isUnderSwitch_ = false;

    int direction_ = 1;
    int blockHitPixelNum_ = 0;
    int hitGoalBlockIndex_ = 0;
    std::vector<HitBlock> hitBlocks_;

    //--------- パーティクル ---------//

    std::unique_ptr<Object> goalParticle_[8];
    std::unique_ptr<Object> landingParticle_[2];

    //--------- アニメーション用 ---------//

    bool isMove_ = false;
    bool isSleep_ = false; // 寝てますか？
    bool isScared_ = false;
    bool isGoal_ = false;
    int bounceTime_ = 0; // アニメーションを管理する時間の変数
    int goalCount_ = 0;
    int landingCount_ = 0;
    float addWidth_ = 0.0f;
    float bounceWidth_ = 0.0f; // アニメーションさせる横幅
    float addHeight_ = 2.0f;
    float bounceHeight_ = 0.0f; //　アニメーションさせる縦幅

    Vector2Int preShake_;
    Vector2 shake_;

    int deathTimer_ = 0;
    Vector2 deathPos_;
    Vector2 deathVelocity_ = { 0.0f, 0.0f };
    
    int deathAnimaitonCount_ = 0;

    //UI
    struct ComicSign {
        //bool isActive = false;
        Vector2 pos_;
        Vector2 speed_;
    };

    std::vector<ComicSign> zzz_;
    int zzzFrameCounter_ = 0;

    void Move();
    void GetHitBlock();
    void GoalProc();
    void GoalParticleProc();
    void LandingParticleProc();
    void TopBottomProc();
    void LeftRightProc();

    void BlockHitPixelCalc();

    void Animation();

    void Death();
    void DeathAnimation();

    void DrawGoalParticle(Camera &camera);
    void DrawLandingParticle(Camera &camera);

public:
    Player();
    void Reset();

    Vector2 GetPos() { return pos_; };
    float GetWidth() { return width_; };
    float GetHeight() { return height_; };

    void SetCameraDefaultTranslate(const Vector2 &translate) { cameraDefaultTranslate_ = translate; };
    
    void Update();
    void Draw(Camera &camera);
};