#include <cmath>
#include <fstream>
#include "Structures.h"
#include "StageClass.h"
#include "Player.h"
#include "GetInput.h"
#include "CommonFunctions.h"
#include "SceneClass.h"
#include "Textures.h"
#include "SoundHandle.h"
#include "Easings.h"
#include "SceneChangeAnimations.h"
#include "EntityKey.h"
#include "KeyConfig.h"

void Player::Update() {
    LandingParticleProc();
	if (isGoal_) {
        GoalParticleProc();
		return;
	}

	BlockHitPixelCalc();
	
	if (!SceneChange::IsChanging()){
		if (GetInput::TriggerKeys(KEY_CONFIG_GET(KEY_CHANGE_MODE)) ||
			GetInput::JoystickTriggerButton(0, CONTROLLER_CONFIG_GET(KEY_CHANGE_MODE)) ||
			GetInput::MouseTriggerButton(DIC_LEFT)) {
			if (isAlive_) {
				stage_->ChangeMode();
			}
		}
	}

    if (!stage_->IsPuzzleMode()) {
		if ((blockHitPixelNum_ > 16) || (pos_.y <= -96.0f)) {
			Death();
			//SceneGame::Reset(StageClass::GetPlayNowStageID());

		} else {
			if (!SceneChange::IsChanging()) {
				// パズルモードでなければ通常通り処理
				Move();
				GetHitBlock();
				TopBottomProc();
				LeftRightProc();
                posMap_ = {
					static_cast<int>(pos_.x / StageClass::GetMapChipSize()),
					static_cast<int>(pos_.y / StageClass::GetMapChipSize())
				};
				GoalProc();
			}
		}
    }
	
	//アニメーション
	Animation();
}

void Player::Move() {
	//==================================================
	//
	// キーボードの場合
	// ADで移動、SPACEでジャンプ、ENTERでモード切り替え
	//
	// コントローラーの場合
	// 左スティックで移動、Aでジャンプ、Xでモード切り替え
	//
	//==================================================

	// AとDどちらも押されていなければ移動
	// ついでにコントローラーの十字キー左右でも移動できるようにしとく
	if ((GetInput::Keys({ DIK_A, DIK_LEFT }) || GetInput::JoystickPushButton(0, DIXC_LEFT)) != (GetInput::Keys({ DIK_D, DIK_RIGHT }) || GetInput::JoystickPushButton(0, DIXC_RIGHT))) {
		if (GetInput::Keys({ DIK_A, DIK_LEFT }) || GetInput::JoystickPushButton(0, DIXC_LEFT)) {
			velocity_.x -= acceleration_.x;
			direction_ = -1;
		}
		if (GetInput::Keys({ DIK_D, DIK_RIGHT }) || GetInput::JoystickPushButton(0, DIXC_RIGHT)) {
			velocity_.x += acceleration_.x;
			direction_ = 1;
		}
		// 速度を制限
		velocity_.x = Clamp(
			velocity_.x,
			minVelocity_.x,
			maxVelocity_.x
		);
        addHitWidth_ = 32.0f;
        isMove_ = true;
        goto MOVE_PROC_THROUGH;

	} else {
		// 入力がされてない、またはAとDどちらも入力されていたらX方向の速度を減算する
		if (velocity_.x < 0.0f) {
			velocity_.x += acceleration_.x;
			if (velocity_.x > 0.0f) {
				velocity_.x = 0.0f;
			}

		} else if (velocity_.x > 0.0f) {
			velocity_.x -= acceleration_.x;
			if (velocity_.x < 0.0f) {
				velocity_.x = 0.0f;
			}
		}
        addHitWidth_ = 0.0f;
        isMove_ = false;
	}

	// コントローラーの場合左スティックのX方向入力をそのまま移動に適応させる
	if (GetInput::JoystickAnalogLeftX(0) != 0) {
		velocity_.x = (static_cast<float>(GetInput::JoystickAnalogLeftX(0)) / 32768.0f) * maxVelocity_.x;
		if (velocity_.x < 0.0f) {
			direction_ = -1;
		} else if (velocity_.x > 0.0f) {
			direction_ = 1;
		}
		addHitWidth_ = 32.0f;
		isMove_ = true;
	} else {
		addHitWidth_ = 0.0f;
		isMove_ = false;
	}

MOVE_PROC_THROUGH:;

	// ジャンプ
	if (GetInput::TriggerKeys({ DIK_SPACE, DIK_W }) || GetInput::JoystickTriggerButton(0, DIXC_A)) {
		// bottomのフラグが立ってるときのみジャンプ可能にする
		if (isMapChipHit_.bottom) {
			velocity_.y += jumpPower_;
			isMapChipHit_.bottom = false;
			if (isSleep_) {
				isSleep_ = false;
				bounceTime_ = 0;
				zzz_.clear();
				zzzFrameCounter_ = 0;
				//bounceHeight_ = 0.0f;
				//addHeight_ = 2.0f;
			}
			SoundHandle::Play(SE_JUMP);
		}
	}

    isUnderSwitch_ = false;
	for (const auto &block : hitBlocks_) {
		if (block.blockID != BLOCK_SWITCH) {
			continue;
		}
		// プレイヤーよりも下にスイッチがある場合
		if (block.y < static_cast<int>(pos_.y - height_ / 2.0f + 1.0f) / StageClass::GetMapChipSize()) {
			// 下入力されてたらスイッチを押す
			if (GetInput::TriggerKeys(DIK_S) || GetInput::JoystickTriggerButton(0, DIXC_DOWN) ||
				(GetInput::JoystickAnalogLeftY(0) >= 16384 && GetInput::JoystickAnalogLeftPreY(0) < 16384)) {
				stage_->SwitchOn();
				bounceWidth_ = 12.0f;
				bounceHeight_ = -12.0f;
				bounceTime_ = 0;
				zzz_.clear();
				zzzFrameCounter_ = 0;
				isSleep_ = false;
			}
            isUnderSwitch_ = true;
		}
	}
}

void Player::GetHitBlock() {
	hitBlocks_ = stage_->GetObjectHitBlockID(
		pos_.x - width_ / 2.0f - 1.0f,
		pos_.y + height_ / 2.0f + 1.0f,
		width_ + 3.0f,
		height_ + 3.0f
	);
}

void Player::GoalProc() {
	static int tmp = 0;
	if (SceneGame::GetEntityKey()->IsExist()) {
        return;
	}
	
	tmp = 0;
    for (const auto &block : hitBlocks_) {
		if (block.blockID == BLOCK_GOAL) {
            // ゴールの位置が斜めの場合は無視
            if (block.x - posMap_.x != 0 && block.y - posMap_.y != 0) {
				tmp++;
                continue;
            }

            // ゴールのブロックに触れたらゴール処理
            isGoal_ = true;
			hitGoalBlockIndex_ = tmp;
			for (int i = 0; i < 8; i++) {
				goalParticle_[i]->SetLocalCenterPos({
					static_cast<float>(hitBlocks_[hitGoalBlockIndex_].x * StageClass::GetMapChipSize() + StageClass::GetMapChipSize() / 2),
                    static_cast<float>(hitBlocks_[hitGoalBlockIndex_].y * StageClass::GetMapChipSize() + StageClass::GetMapChipSize() / 2)
				});
			}
            goalCount_ = 0;
            prePos_ = pos_;
			SceneGame::Clear();
            break;
        }
        tmp++;
    }
}

void Player::GoalParticleProc() {
    static Vector2 easePos;
	static float degreeVector = 0.0f;
    static float degreeRotate = 0.0f;

	if (!isGoal_) {
		return;
	}
	if (goalCount_ >= 60) {
		return;
	}

    goalCount_++;

	if (goalCount_ < 30) {
        pos_.x = Ease::Auto(
			goalCount_, 30,
			prePos_.x,
			static_cast<float>(hitBlocks_[hitGoalBlockIndex_].x * StageClass::GetMapChipSize() + StageClass::GetMapChipSize() / 2),
			EASE_OUT_ELASTIC
		);
        pos_.y = Ease::Auto(
            goalCount_, 30,
            prePos_.y,
            static_cast<float>(hitBlocks_[hitGoalBlockIndex_].y * StageClass::GetMapChipSize() + StageClass::GetMapChipSize() / 2),
            EASE_OUT_ELASTIC
        );

    } else if (goalCount_ < 60) {
		if (goalCount_ == 30) {
			SoundHandle::Play(SE_GOAL);
		}
        for (int i = 0; i < 8; i++) {
            degreeVector = (360.0f / 8.0f) * static_cast<float>(i);
            easePos = {
                Ease::Auto(
                    goalCount_ - 30, 30,
					static_cast<float>(hitBlocks_[hitGoalBlockIndex_].x * StageClass::GetMapChipSize() + StageClass::GetMapChipSize() / 2),
                    pos_.x + std::cos(ConvertDeg2Rad(degreeVector)) * 128.0f,
                    EASE_OUT_QUINT
                ),
                Ease::Auto(
                    goalCount_ - 30, 30,
					static_cast<float>(hitBlocks_[hitGoalBlockIndex_].y * StageClass::GetMapChipSize() + StageClass::GetMapChipSize() / 2),
                    pos_.y + std::sin(ConvertDeg2Rad(degreeVector)) * 128.0f,
                    EASE_OUT_QUINT
                )
            };
            goalParticle_[i]->SetLocalCenterPos(easePos);
            degreeRotate += 2.0f;
            goalParticle_[i]->SetRotate(ConvertDeg2Rad(degreeRotate));
        }

	} else {
		SceneGame::StartClearAnimation();
	}
}

void Player::LandingParticleProc() {
	static Vector2 easePos;
	static float degreeVector = 0.0f;
	static float degreeRotate = 0.0f;

	if (landingCount_ >= 30) {
		return;
	}

	landingCount_++;

	for (int i = 0; i < 2; i++) {
		degreeVector = 180.0f * static_cast<float>(i);
		easePos = {
			Ease::Auto(
				landingCount_, 30,
                particlePos_.x,
				particlePos_.x + std::cos(ConvertDeg2Rad(degreeVector)) * 128.0f,
				EASE_OUT_CUBIC
            ),
            particlePos_.y
		};
		landingParticle_[i]->SetLocalCenterPos(easePos);
        landingParticle_[i]->SetColor(
            0xffff8b00 + static_cast<unsigned int>(Ease::Auto(
				landingCount_, 30,
				255.0f,
				0.0f,
				EASE_IN_CUBIC
			))
		);
	}

	degreeRotate += 4.0f;
	landingParticle_[0]->SetRotate(ConvertDeg2Rad(degreeRotate));
    landingParticle_[1]->SetRotate(ConvertDeg2Rad(-degreeRotate));
}

void Player::TopBottomProc() {
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
			pos_.x - width_ / 2.0f + (16.0f - addHitWidth_ / 2.0f),
			pos_.y + height_ / 2.0f + velocity_.y,
			width_ - (32.0f - addHitWidth_),
			true
		);
		// top のフラグが立ったらY速度を0にしてプレイヤーを下にずらす
		if (isMapChipHit_.top) {
			pos_.y = static_cast<float>((static_cast<int>(pos_.y + height_ / 2.0f + velocity_.y) / StageClass::GetMapChipSize()) * StageClass::GetMapChipSize()) - height_ / 2.0f;
			velocity_.y = 0.0f;
		}
	}

	// プレイヤーのY方向の速度がマイナスなら bottom の当たり判定をする
	if (velocity_.y < 0.0f) {
		isMapChipHit_.top = false;
		// bottom のフラグが下がっていて
		if (!isMapChipHit_.bottom) {
			isMapChipHit_.bottom = stage_->IsMapChip2RectYHit(
				pos_.x - width_ / 2.0f + (16.0f - addHitWidth_ / 2.0f),
				pos_.y - height_ / 2.0f + 1.0f + velocity_.y,
                width_ - (32.0f - addHitWidth_)
			);
			// 当たり判定を行ってフラグが立ったら着地音を鳴らす
			if (isMapChipHit_.bottom) {
				//PlaySounds(soundHandle[SE_PLAYER_LANDED], playHandle[SE_PLAYER_LANDED]);
				bounceWidth_ = 12.0f;
				bounceHeight_ = -12.0f;
                particlePos_ = pos_;
				particlePos_.y -= height_ / 2.0f;
                landingCount_ = 0;
			}

		} else {
			isMapChipHit_.bottom = stage_->IsMapChip2RectYHit(
				pos_.x - width_ / 2.0f + (16.0f - addHitWidth_ / 2.0f),
				pos_.y - height_ / 2.0f + 1.0f + velocity_.y,
				width_ - (32.0f - addHitWidth_)
			);
		}

		// bottom のフラグが立ったらY速度を0にしてプレイヤーを上にずらす
		if (isMapChipHit_.bottom) {
			pos_.y = static_cast<float>((static_cast<int>(pos_.y - height_ / 2.0f + 1.0f + velocity_.y) / StageClass::GetMapChipSize() + 1) * StageClass::GetMapChipSize()) + height_ / 2.0f;
			velocity_.y = 0.0f;
		}
	}
}

void Player::LeftRightProc() {
	pos_.x += velocity_.x;

	// プレイヤーのX方向の速度がマイナスなら left の当たり判定をする
	if (velocity_.x < 0.0f) {
		isMapChipHit_.right = false;
		isMapChipHit_.left = stage_->IsMapChip2RectXHit(
			pos_.x - width_ / 2.0f,
			pos_.y + height_ / 2.0f - 1.0f,
			height_
		);
		// left のフラグが立ったらX速度を0にしてプレイヤーを右にずらす
		if (isMapChipHit_.left) {
			velocity_.x = 0.0f;
			// 参照したX座標がマイナスでなければずらす位置を計算
			if ((pos_.x - width_ / 2.0f) >= 0.0f) {
				pos_.x = static_cast<float>((static_cast<int>(pos_.x - width_ / 2.0f) / StageClass::GetMapChipSize() + 1) * StageClass::GetMapChipSize()) + width_ / 2.0f;
			} else {
				// マイナスのときは width だけで座標を固定
				pos_.x = width_ / 2.0f;
			}
		}
	}

	// プレイヤーのX方向の速度がプラスなら right の当たり判定をする
	if (velocity_.x > 0.0f) {
		isMapChipHit_.left = false;
		isMapChipHit_.right = stage_->IsMapChip2RectXHit(
			pos_.x + width_ / 2.0f - 1.0f,
			pos_.y + height_ / 2.0f - 1.0f,
			height_
		);
		// right のフラグが立ったらX速度を0にしてプレイヤーを左にずらす
		if (isMapChipHit_.right) {
			velocity_.x = 0.0f;
			pos_.x = static_cast<float>((static_cast<int>(pos_.x + width_ / 2.0f - 1.0f) / StageClass::GetMapChipSize()) * StageClass::GetMapChipSize()) - width_ / 2.0f;
		}
	}
}

void Player::BlockHitPixelCalc() {
    static IsMapChipHit isMapChipHit;
    int blockHitPixelNum = 0;
    blockHitPixelNum_ = 0;

	// 上下左右の当たり判定を取得
	isMapChipHit.top = stage_->IsMapChip2RectYHit(
		pos_.x,
		pos_.y + height_ / 2.0f,
		1.0f,
		true
	);
	isMapChipHit.bottom = stage_->IsMapChip2RectYHit(
		pos_.x,
		pos_.y - height_ / 2.0f + 1.0f,
		1.0f
	);
	isMapChipHit.left = stage_->IsMapChip2RectXHit(
		pos_.x - width_ / 2.0f,
		pos_.y,
		1.0f
	);
	isMapChipHit.right = stage_->IsMapChip2RectXHit(
		pos_.x + width_ / 2.0f - 1.0f,
		pos_.y,
		1.0f
	);

    // 各方向の当たってるピクセル数を計算
    if (isMapChipHit.top) {
        blockHitPixelNum = abs(static_cast<int>(pos_.y + height_ / 2.0f) % StageClass::GetMapChipSize());
        // 計算したピクセル数のほうが大きければ代入
        if (blockHitPixelNum_ < blockHitPixelNum) {
            blockHitPixelNum_ = blockHitPixelNum;
        }
		if (stage_->IsPuzzleMode()) {
			// パズルモードから戻った際に押し戻されるようにvelocityを1にする
			velocity_.y = acceleration_.y * 2.0f;
		}
    }
    if (isMapChipHit.bottom) {
        blockHitPixelNum_ = StageClass::GetMapChipSize() - abs(static_cast<int>(pos_.y - height_ / 2.0f + 1.0f) % StageClass::GetMapChipSize());
		// 計算したピクセル数のほうが大きければ代入
		if (blockHitPixelNum_ < blockHitPixelNum) {
			blockHitPixelNum_ = blockHitPixelNum;
		}
		if (stage_->IsPuzzleMode()) {
			// パズルモードから戻った際に押し戻されるようにvelocityを1にする
			velocity_.y = -(acceleration_.y * 2.0f);
		}
    }
	if (isMapChipHit.left) {
		blockHitPixelNum = StageClass::GetMapChipSize() - abs(static_cast<int>(pos_.x - width_ / 2.0f) % StageClass::GetMapChipSize());
		// 計算したピクセル数のほうが大きければ代入
		if (blockHitPixelNum_ < blockHitPixelNum) {
			blockHitPixelNum_ = blockHitPixelNum;
		}
		if (stage_->IsPuzzleMode()) {
			// パズルモードから戻った際に押し戻されるようにvelocityを1にする
			velocity_.x = -(acceleration_.x * 2.0f);
		}
	}
    if (isMapChipHit.right) {
        blockHitPixelNum = abs(static_cast<int>(pos_.x + width_ / 2.0f - 1.0f) % StageClass::GetMapChipSize());
        // 計算したピクセル数のほうが大きければ代入
        if (blockHitPixelNum_ < blockHitPixelNum) {
            blockHitPixelNum_ = blockHitPixelNum;
        }
		if (stage_->IsPuzzleMode()) {
			// パズルモードから戻った際に押し戻されるようにvelocityを1にする
			velocity_.x = acceleration_.x * 2.0f;
		}
    }
	
    // デバッグ用にピクセル数を表示
#ifdef _DEBUG
    Novice::ScreenPrintf(128, 16, "blockHitPixelNum_:%d", blockHitPixelNum_);
#endif
}

void Player::Animation(){
	
	// 現在の横幅によってアニメーションさせる方向を変える
	if (bounceHeight_ <= -4) {
		addHeight_ = 2.0f;
	}
	else if (bounceHeight_ >= 4) {
		addHeight_ = -2.0f;
	}

	if (bounceWidth_ > 0) {
		if (!isSleep_) {
			bounceWidth_ -= 2.0f;
		}
	}
	
	if (!stage_->IsPuzzleMode()) {
		if (!isMapChipHit_.bottom) {
			if (bounceHeight_ < 4.0f) {
				bounceHeight_ += 1.0f;
			}
			if (bounceWidth_ > -4.0f) {
				bounceWidth_ -= 1.0f;
			}
		}
		// 地面にいるかつ動いているとき
		else if (isMapChipHit_.bottom && isMove_) {
			if (isSleep_) {
				isSleep_ = false;
				bounceHeight_ = 0.0f;
				addHeight_ = 2.0f;
				bounceWidth_ = 0.0f;
				addWidth_ = 0.0f;
				zzz_.clear();
				zzzFrameCounter_ = 0;
			}
			bounceHeight_ += addHeight_;
			bounceTime_ = 0;
			// 動いていない時
		}else if (isMapChipHit_.bottom && !isMove_) {
			// 寝てない時
			if (!isSleep_) {
				if (bounceHeight_ > 0.0f) {
					bounceHeight_ -= 2.0f;
				}
				else if (bounceHeight_ < 0.0f) {
					bounceHeight_ += 2.0f;
				}
			}
			bounceTime_++;
			// 3秒動いてなかったら寝る
			if (bounceTime_ > 120) {
				if (!isSleep_) {
					isSleep_ = true;
					addHeight_ = 0.0f;
				}
			}
			// 寝てたら
			if (isSleep_) {
				zzzFrameCounter_++;
				addHeight_ += 0.05f;
				bounceHeight_ = 4 * std::sin(addHeight_);
				addWidth_ -= 0.05f;
				bounceWidth_ = 4 * std::sin(addWidth_);

				//UI
				if (zzzFrameCounter_ >= 20) {
					zzz_.push_back({ {pos_.x + 16.0f, pos_.y + 16.0f}, { 1.0f, 1.0f } });
					zzzFrameCounter_ = 0;
				}
				for (auto& zzz : zzz_) {
					zzz.pos_.x += zzz.speed_.x;
					zzz.pos_.y += zzz.speed_.y;
				}
				if (zzz_.size() > 3) {
					zzz_.erase(zzz_.begin());
				}
			}
		}
	}
	else {
		if (!isScared_) {
			if (blockHitPixelNum_ > 16) {
				isScared_ = true;
				addHeight_ = 0.0f;
			}
		}else if (isScared_) {
			if (blockHitPixelNum_ <= 16) {
				isScared_ = false;
				addHeight_ = 2.0f;
				bounceHeight_ = 0.0f;
			}
		}

		if (isScared_) {
			addHeight_ += 1.0f;
			bounceHeight_ = 4 * std::sin(addHeight_);
		}

	}

}

void Player::Death() {
	if (isAlive_) {
		bounceHeight_ = 0.0f;
		addHeight_ = 2.0f;
		bounceWidth_ = 0.0f;
		addWidth_ = 0.0f;
		isAlive_ = false;
		preShake_ = { 12,12 };
		deathPos_ = pos_;
		deathVelocity_ = { 0 };
		bounceTime_ = 0;
		zzz_.clear();
		SoundHandle::Play(SE_DEATH);
	}
	DeathAnimation();
}

void Player::DeathAnimation() {

	shake_ = { static_cast<float>(CustomRangeRand(-preShake_.x, preShake_.y)), static_cast<float>(CustomRangeRand(-preShake_.x, preShake_.y)) };
	if (pos_.y <= -96.0f) {
		SceneGame::GetCamera()->SetTranslate(
			cameraDefaultTranslate_ + shake_
		);
		SceneGame::GetCamera()->SetCamera();
	}

	if (preShake_.x > 0) {
		preShake_.x -= 1;
		preShake_.y -= 1;
	}

	if (deathTimer_ == 30) {
		deathVelocity_.y = jumpPower_;
	}
	else if (deathTimer_ > 30) {
		deathVelocity_.y -= acceleration_.y;
		deathPos_.y += deathVelocity_.y;
	}

	if (deathTimer_ >= 120) {
		if (!SceneChange::IsChanging()) {
			SceneChange::Start(SCA_FADE_IN_ROTATE_RECT, 30, 0, 30);
		}
		if (SceneChange::IsChanging() && !SceneChange::IsChanged()) {
			return;
		}
        SceneChange::Start(SCA_FADE_OUT_ROTATE_RECT, 30, 0, 0);
		SceneGame::Reset(stage_->GetPlayNowStageID());
		deathTimer_ = 0;
		isAlive_ = true;
	} else {
		deathTimer_++;
	}
}

void Player::DrawGoalParticle(Camera &camera) {
	for (int i = 0; i < 8; i++) {
		if (isGoal_) {
			goalParticle_[i]->Draw(camera);
		}
	}
}

void Player::DrawLandingParticle(Camera &camera) {
    for (int i = 0; i < 2; i++) {
        landingParticle_[i]->Draw(camera);
    }
}

Player::Player() {
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
    jumpPower_ = playerData["PlayerStatus"]["jumpPower"];
    for (int i = 0; i < 8; i++) {
        goalParticle_[i] = std::make_unique<RectObject>();
        dynamic_cast<RectObject *>(goalParticle_[i].get())->SetWidth(32.0f);
        dynamic_cast<RectObject *>(goalParticle_[i].get())->SetHeight(32.0f);
        if (i % 2 == 0) {
            goalParticle_[i]->SetColor(0xffff8bff);
		} else {
			goalParticle_[i]->SetColor(0xff8b8bff);
		}
    }
    for (int i = 0; i < 2; i++) {
        landingParticle_[i] = std::make_unique<RectObject>();
        dynamic_cast<RectObject *>(landingParticle_[i].get())->SetWidth(32.0f);
        dynamic_cast<RectObject *>(landingParticle_[i].get())->SetHeight(32.0f);
        landingParticle_[i]->SetColor(0xffff8bff);
    }
	landingCount_ = 30;
}

void Player::Reset() {
    pos_ = stage_->GetPlayerStartPos();
    direction_ = stage_->GetPlayerDirection();
    velocity_ = { 0.0f, 0.0f };
    blockHitPixelNum_ = 0;
    hitBlocks_.clear();
    isMapChipHit_.bottom = true;
    isMove_ = false;
    isAlive_ = true;
    isGoal_ = false;
    isSleep_ = false;
    isScared_ = false;
    bounceTime_ = 0;
    goalCount_ = 0;
}

void Player::Draw(Camera &camera) {
	static int animationCount = 0;
	int direction = direction_;
    if (isGoal_) {
		if (goalCount_ < 30) {
			CustomNovice::DrawQuad(
				camera,
				pos_.x - width_ / 2.0f,
				pos_.y + height_ / 2.0f,
				pos_.x + width_ / 2.0f,
				pos_.y + height_ / 2.0f,
				pos_.x - width_ / 2.0f,
				pos_.y - height_ / 2.0f,
				pos_.x + width_ / 2.0f,
				pos_.y - height_ / 2.0f,
				0,
				0,
				GraphHandle::Width(TX_CLEAR_PLAYER),
				GraphHandle::Height(TX_CLEAR_PLAYER),
				GraphHandle::ID(TX_CLEAR_PLAYER), 0xffff8bff
			);
		} else if (goalCount_ < 60) {
			DrawGoalParticle(camera);
		}
        goto THROW;
    }

	if (direction == -1) {
		direction = 0;
	}

	if (!isAlive_) {
		CustomNovice::DrawQuad(
			camera,
			deathPos_.x - width_ / 2.0f - bounceWidth_ + shake_.x,
			deathPos_.y + height_ / 2.0f + bounceHeight_ + shake_.y,
			deathPos_.x + width_ / 2.0f + bounceWidth_ + shake_.x,
			deathPos_.y + height_ / 2.0f + bounceHeight_ + shake_.y,
			deathPos_.x - width_ / 2.0f - bounceWidth_ + shake_.x,
			deathPos_.y - height_ / 2.0f + shake_.y,
			deathPos_.x + width_ / 2.0f + bounceWidth_ + shake_.x,
			deathPos_.y - height_ / 2.0f + shake_.y,
			0,
			0,
			GraphHandle::Width(TX_DEATH_PLAYER),
			GraphHandle::Height(TX_DEATH_PLAYER),
			GraphHandle::ID(TX_DEATH_PLAYER), 0xffff8bff
		);
        return;

	}else if (blockHitPixelNum_ > 16) {
		CustomNovice::DrawQuad(
			camera,
			pos_.x - width_ / 2.0f - bounceWidth_,
			pos_.y + height_ / 2.0f + bounceHeight_,
			pos_.x + width_ / 2.0f + bounceWidth_,
			pos_.y + height_ / 2.0f + bounceHeight_,
			pos_.x - width_ / 2.0f - bounceWidth_,
			pos_.y - height_ / 2.0f,
			pos_.x + width_ / 2.0f + bounceWidth_,
			pos_.y - height_ / 2.0f,
			0,
			0,
			GraphHandle::Width(TX_SCARED_PLAYER),
			GraphHandle::Height(TX_PLAYER),
			GraphHandle::ID(TX_SCARED_PLAYER), WHITE
		);
	}else if (isSleep_) {
		CustomNovice::DrawQuad(
			camera,
			pos_.x - width_ / 2.0f - bounceWidth_,
			pos_.y + height_ / 2.0f + bounceHeight_,
			pos_.x + width_ / 2.0f + bounceWidth_,
			pos_.y + height_ / 2.0f + bounceHeight_,
			pos_.x - width_ / 2.0f - bounceWidth_,
			pos_.y - height_ / 2.0f,
			pos_.x + width_ / 2.0f + bounceWidth_,
			pos_.y - height_ / 2.0f,
			GraphHandle::Width(TX_PLAYER) / 3 * 2,
			0,
			GraphHandle::Width(TX_PLAYER) / 3,
			GraphHandle::Height(TX_PLAYER),
			GraphHandle::ID(TX_PLAYER), 0xffff8bff
		);
		// zzzテクスチャを描画
		for (const auto& zzz : zzz_) {
			CustomNovice::DrawQuad(
				camera,
				zzz.pos_.x - 16.0f,
				zzz.pos_.y + 16.0f,
				zzz.pos_.x + 16.0f,
				zzz.pos_.y + 16.0f,
				zzz.pos_.x - 16.0f,
				zzz.pos_.y - 16.0f,
				zzz.pos_.x + 16.0f,
				zzz.pos_.y - 16.0f,
				0,
				0,
				32,
				32,
				GraphHandle::ID(TX_COMICSIGN_ZZZ), WHITE
			);
		}
	}else {
		CustomNovice::DrawQuad(
			camera,
			pos_.x - width_ / 2.0f - bounceWidth_,
			pos_.y + height_ / 2.0f + bounceHeight_,
			pos_.x + width_ / 2.0f + bounceWidth_,
			pos_.y + height_ / 2.0f + bounceHeight_,
			pos_.x - width_ / 2.0f - bounceWidth_,
			pos_.y - height_ / 2.0f,
			pos_.x + width_ / 2.0f + bounceWidth_,
			pos_.y - height_ / 2.0f,
			GraphHandle::Width(TX_PLAYER) / 3 * direction,
			0,
			GraphHandle::Width(TX_PLAYER) / 3,
			GraphHandle::Height(TX_PLAYER),
			GraphHandle::ID(TX_PLAYER), 0xffff8bff
		);
	}

	if (!isUnderSwitch_) {
		if (GetInput::NowInputType() == InputType::KEYBOARD ||
			GetInput::NowInputType() == InputType::MOUSE) {
			animationCount = (animationCount + 1) % 60;
			CustomNovice::DrawQuad(
				camera,
				pos_.x - width_ / 2.0f,
				pos_.y + height_ / 2.0f + height_,
				pos_.x + width_ / 2.0f,
				pos_.y + height_ / 2.0f + height_,
				pos_.x - width_ / 2.0f,
				pos_.y - height_ / 2.0f + height_,
				pos_.x + width_ / 2.0f,
				pos_.y - height_ / 2.0f + height_,
				64 + (64 * (animationCount / 30)),
				0,
				64,
				64,
				GraphHandle::ID(TX_INPUT_PAZZLE_UI)
			);
		} else if (GetInput::NowInputType() == InputType::JOYSTICK) {
			CustomNovice::DrawQuad(
				camera,
				pos_.x - width_ / 2.0f,
				pos_.y + height_ / 2.0f + height_,
				pos_.x + width_ / 2.0f,
				pos_.y + height_ / 2.0f + height_,
				pos_.x - width_ / 2.0f,
				pos_.y - height_ / 2.0f + height_,
				pos_.x + width_ / 2.0f,
				pos_.y - height_ / 2.0f + height_,
				0,
				0,
				64,
				64,
				GraphHandle::ID(TX_INPUT_PAZZLE_UI)
			);
		}

	} else {
		CustomNovice::DrawQuad(
			camera,
			pos_.x - width_,
			pos_.y + height_ / 2.0f + height_,
			pos_.x + width_,
			pos_.y + height_ / 2.0f + height_,
			pos_.x - width_,
			pos_.y - height_ / 2.0f + height_,
			pos_.x + width_,
			pos_.y - height_ / 2.0f + height_,
			0,
			0,
			128,
			64,
			GraphHandle::ID(TX_SWITCH_UI)
		);
	}

THROW:;
	if (landingCount_ < 30) {
		DrawLandingParticle(camera);
	}

	// デバッグ用
#ifdef _DEBUG
	Novice::ScreenPrintf(16, 16, "x:%.2f, y:%.2f", pos_.x, pos_.y);
	
#endif
}
