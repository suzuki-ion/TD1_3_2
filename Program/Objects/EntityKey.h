#include <memory>
#include "Structures.h"
#include "StageClass.h"
#include "Camera.h"
#include "Objects.h"

class EntityKey {
    StageClass *stage_;
    Camera *camera_;

    std::unique_ptr<Object> particle_[8];
    Vector2 goalPos_;

    Vector2 pos_;
    Vector2 getPos_;
    Vector2 particlePos_;
    Vector2 acceleration_;
    Vector2 velocity_;
    Vector2 minVelocity_;
    Vector2 maxVelocity_;
    IsMapChipHit isMapChipHit_;
    float width_ = static_cast<float>(StageClass::GetMapChipSize());
    float height_ = static_cast<float>(StageClass::GetMapChipSize());
    float animationDegree_ = 0.0f;
    float animationDegreeSpeed_ = 4.0f;
    float theta_ = 0.0f;
    int blockHitPixelNum_ = 0;
    int respawnCount_ = 0;
    int respawnMaxCount_ = 60;
    int respawnAnimationCount_ = 0;
    int respawnAnimationMaxCount_ = 30;
    int unlockAnimationCount_ = 0;
    int unlockAnimationMaxCount_ = 90;
    bool isExist_ = false;
    bool isDelete_ = false;
    bool isUnlockAnimation_ = false;

    void BlockHitPixelCalc();
    void TopBottomProc();
    void PlayerHitProc();
    void Respawn();
    void UpdateUnlockAnimation();
    void UpdateParticle();
    void DrawParticle();

public:
    EntityKey();
    void Reset();

    bool IsExist() { return isExist_; }

    void Update();
    void Draw();
    void Draw(Camera &camera);
};