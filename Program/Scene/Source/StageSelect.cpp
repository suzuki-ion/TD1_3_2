#include <Scene/StageSelect.h>
#include <Common/Easings.h>
#include <Common/CustomNovice.h>
#include <Common/GraphHandle.h>
#include <Common/SoundHandle.h>
#include <map>
#include <functional>

namespace {

// 入力のインスタンス
auto sGetInput = sGetInput->GetInstance();

} // namespace

//
StageClass *SceneStageSelect::stage_ = SceneGame::GetStage();
int SceneStageSelect::isStage_ = 0;
Camera SceneStageSelect::cameraSSS_;
float SceneStageSelect::scaleSSS_ = 1.6f;
int SceneStageSelect::selectStageID_ = 0;

float SceneStageSelect::degree_ = 0;
int SceneStageSelect::count_ = 0;
int SceneStageSelect::maxCount_ = 30;
bool SceneStageSelect::isRotate_ = false;
int SceneStageSelect::which_ = 0;

int SceneStageSelect::transitionCount_ = 0;
int SceneStageSelect::transitionCountMax_ = 90;

Vector2 SceneStageSelect::posPre_ = { -1300,2360 };
Vector2 SceneStageSelect::posNext_ = { 1300 + 1024,2360 };

float SceneStageSelect::rad_ = 512.0f;
float SceneStageSelect::radMin_ = 64.0f;
float SceneStageSelect::radMax_ = 512.0f;

Vector2 SceneStageSelect::wid_ = { 128.0f,128.0f };
Vector2 SceneStageSelect::player_ = { 500,980 - wid_.y / 2 };
Vector2 SceneStageSelect::playerScale_ = { 1.0f,1.0f };
float SceneStageSelect::playerRotate_ = 0.0f;
Vector2 SceneStageSelect::leftTop_ = { player_.x - wid_.x,player_.y - wid_.y };
Vector2 SceneStageSelect::rightTop_ = { player_.x + wid_.x,player_.y - wid_.y };
Vector2 SceneStageSelect::leftBottom_ = { player_.x - wid_.x,player_.y - wid_.y };
Vector2 SceneStageSelect::rightBottom_ = { player_.x + wid_.x,player_.y - wid_.y };

int SceneStageSelect::isMove_ = 0;
int SceneStageSelect::moveCount_ = 0;
Vector2 SceneStageSelect::cloudBig_ = { 1000 - 48 + (800.0f - 48.0f) / 2,180 + 48 + (800.0f - 48.0f) / 2 };//着地点（基本固定）

//タイプ
int SceneStageSelect::isSelectStage_ = 1;

void StageSelect::Update() {

	SoundStop(BGM_TITLE);
	SoundStop(BGM_GAME);

	/*TODO
	* 間を作る□　□　□　□　□みたいなの
	*
	*/

	//三つVer
	if (isSelectStage_ == 1) {
		//キャラの動き
		if (isMove_ == 0) {
			stage_->SetStage(selectStageID_);
			namePos_.x = CustomNovice::WinWidth() / 2.0f;
			//初期化
			player_.y = 980 - wid_.y / 2;
			moveCount_ += 1;
			scaleSSS_ = 1.6f * (StageClass::GetSizeIsSix(selectStageID_) / 16);

			cloudDegree_ = 0;
			cloudScale_ = { 1.0f,1.0f };

			for (int i = 0; i < 2; i++) {
				selectViewPos_[i] = { 1000.0f - 32.0f - 24 - 48 + 868.0f * i,636.0f - 24 };
				selectViewDegree_[i] = 0;
				selectViewScale_[i] = { 0.5f,1.0f };
				selectViewWid_[i] = { static_cast<float>(GraphHandle::Width(TX_SELECTVIEWSC)),static_cast<float>(GraphHandle::Height(TX_SELECTVIEWSC)) };
			}
			/*for (int i = 0; i < 10;i++) {
				thinkPos_[i] = { 260.0f + 55 * powf(1.325f,(float)i), 860.0f - i * 25};
				thinkDegree_[i] = 0;
				thinkScale_[i] = { 1.0f,1.0f };
				thinkWid_[i] = { 16.0f,16.0f };
			}*/
			if (moveCount_ >= 0) {
				//アニメーションへ
				isMove_ = 2;
				moveCount_ = 0;
			}
		}
		//アニメーションの動き
		if (isMove_ == 1) {
			//player_.y = Ease::Auto(moveCount_, 60, -128, 980 - wid_.y / 2, EASE_IN_SINE);
			//player_.y = Ease::Auto(moveCount_, 60, 980 - wid_.y / 2, 980 - wid_.y / 2, EASE_IN_SINE);
			moveCount_ += 1;
			if (moveCount_ > 0) {
				moveCount_ = 0;
				isMove_ = 2;//次のアニメーションでもいい（ロープするのを防ぐため）
			}
		}
		if (isMove_ == 2) {
			//一つ目の雲
			moveCount_ += 1;
			if (moveCount_ >= 0) {
				isMove_ = 3;
				moveCount_ = 0;
			}
		}
		if (isMove_ == 3) {
			//二つ目の雲
			moveCount_ += 1;
			if (moveCount_ >= 0) {
				isMove_ = 4;
				moveCount_ = 0;
			}
		}
		if (isMove_ == 4) {
			//大きな雲
			moveCount_ += 1;
			if (moveCount_ >= 0) {
				isMove_ = 5;
				moveCount_ = 0;
			}
		}
		if (isMove_ == 5) {
			//roop
			moveCount_ += 1 * 1;
			//ネームの動き
			if (moveCount_ <= 20 * 3) {
				namePos_.y = Ease::Auto(moveCount_, 20 * 3, 480.0f, 480.0f + 15.0f, EASE_OUT_SINE);
			} else if (moveCount_ <= 60 * 3) {
				namePos_.y = Ease::Auto(moveCount_ - 21 * 3, 40 * 3, 480.0f + 15.0f, 480.0f - 15.0f, EASE_IN_OUT_SINE);
			} else if (moveCount_ <= 80 * 3) {
				namePos_.y = Ease::Auto(moveCount_ - 61 * 3, 20 * 3, 480.0f - 15.0f, 480.0f, EASE_IN_SINE);
			}
			//ボタンの動き
			if (moveCount_ <= 120) {
				selectViewPos_[0].x = Ease::Auto(moveCount_, 120, 1000.0f - 32.0f - 24 - 48 + 868.0f * 0, 1000.0f - 32.0f - 24 - 48 + 868.0f * 0 - 30.0f, EASE_OUT_SINE);
				selectViewPos_[1].x = Ease::Auto(moveCount_, 120, 1000.0f - 32.0f - 24 - 48 + 868.0f * 1, 1000.0f - 32.0f - 24 - 48 + 868.0f * 1 + 30.0f, EASE_OUT_SINE);


			} else if (moveCount_ > 120) {
				selectViewPos_[0].x = Ease::Auto(moveCount_ - 120, 120, 1000.0f - 32.0f - 24 - 48 + 868.0f * 0 - 30.0f, 1000.0f - 32.0f - 24 - 48 + 868.0f * 0, EASE_IN_SINE);
				selectViewPos_[1].x = Ease::Auto(moveCount_ - 120, 120, 1000.0f - 32.0f - 24 - 48 + 868.0f * 1 + 30.0f, 1000.0f - 32.0f - 24 - 48 + 868.0f * 1, EASE_IN_SINE);

			}
			if (moveCount_ <= 8 && moveCount_ > 0) {
				if (transitionCount_ == 0) {
					playerScale_.x = Ease::Auto(moveCount_, 8, 1.0f, 1.1f, EASE_OUT_SINE);
					playerScale_.y = Ease::Auto(moveCount_, 8, 1.0f, 0.9f, EASE_OUT_SINE);
				}
			} else if (moveCount_ > 8 && moveCount_ > 0) {
				if (transitionCount_ == 0) {
					playerScale_.x = Ease::Auto(moveCount_ - 8, 8, 1.1f, 1.0f, EASE_IN_SINE);
					playerScale_.y = Ease::Auto(moveCount_ - 8, 8, 0.9f, 1.0f, EASE_OUT_SINE);
				}
			}

			if (moveCount_ <= 8 + 110 && moveCount_ >= 0 + 110) {
				if (transitionCount_ == 0) {
					playerScale_.x = Ease::Auto(moveCount_ - 110, 8, 1.0f, 1.1f, EASE_OUT_SINE);
					playerScale_.y = Ease::Auto(moveCount_ - 110, 8, 1.0f, 0.9f, EASE_OUT_SINE);
				}
			} else if (moveCount_ > 8 + 110 && moveCount_ >= 0 + 110) {
				if (transitionCount_ == 0) {
					playerScale_.x = Ease::Auto(moveCount_ - 8 - 110, 8, 1.1f, 1.0f, EASE_IN_SINE);
					playerScale_.y = Ease::Auto(moveCount_ - 8 - 110, 8, 0.9f, 1.0f, EASE_OUT_SINE);
				}
			}

			if (moveCount_ > 240) {
				moveCount_ = 0;
			}

			//for (int i = 0;i < 10;i++) {
			//	
			//	//if (moveCount_ >= 20 * i && moveCount_ <= 20 * (i + 1)) {
			//	//	if (moveCount_ <= 10 * (2 * i + 1)) {
			//	//		thinkScale_[i].x = Ease::Auto(moveCount_ - 20 * i, 20 / 2, 0.5f, 1.5f/*0.5f * powf(1.25f, (float)i)*/, EASE_OUT_SINE);
			//	//		thinkScale_[i].y = thinkScale_[i].x;
			//	//		thinkDegree_[i] = Ease::Auto(moveCount_ - 20 * i, 20 / 2, 0, 180, EASE_OUT_SINE);
			//	//	}
			//	//	else if (moveCount_ > 10 * (2 * i + 1)) {
			//	//		thinkScale_[i].x = Ease::Auto(moveCount_ - 20 * i - 20 / 2, 20 / 2, 1.5f/*0.5f * powf(1.25f, (float)i)*/, 0.5f, EASE_IN_SINE);
			//	//		thinkScale_[i].y = thinkScale_[i].x;
			//	//		thinkDegree_[i] = Ease::Auto(moveCount_ - 20 * i - 20 / 2, 20 / 2, 180, 360, EASE_IN_SINE);
			//	//	}
			//	//	else {
			//	//		thinkDegree_[i] = 0;
			//	//	}
			//	//}
			//	//if (moveCount_ > 200) {
			//	//	moveCount_ = 0;
			//	//}
			//	//if (moveCount_ >= 10 * i && moveCount_ <= 10 * (i + 1)) {
			//	//	if (moveCount_ <= 10 * (1 * i + 1)) {
			//	//		thinkScale_[i].x = Ease::Auto(moveCount_ - 10 * i, 20 / 2, 2.00f, 0.5f/*0.5f * powf(1.25f, (float)i)*/, EASE_OUT_SINE);
			//	//		thinkScale_[i].y = thinkScale_[i].x;
			//	//		thinkDegree_[i] = Ease::Auto(moveCount_ - 10 * i, 20 / 2, 0, 90, EASE_OUT_SINE);
			//	//	}
			//	//	else if (moveCount_ > 10 * (1 * i + 1)) {
			//	//		thinkScale_[i].x = Ease::Auto(moveCount_ - 10 * i - 20 / 2, 20 / 2, 0.5f/*0.5f * powf(1.25f, (float)i)*/, 2.00f, EASE_IN_SINE);
			//	//		thinkScale_[i].y = thinkScale_[i].x;
			//	//		thinkDegree_[i] = Ease::Auto(moveCount_ - 10 * i - 20 / 2, 20 / 2, 90, 180, EASE_IN_SINE);
			//	//	}
			//	//	else {
			//	//		thinkDegree_[i] = 0;
			//	//	}
			//	//}
			//	//if (moveCount_ > 110) {
			//	//	moveCount_ = 0;
			//	}
			//}

		}
		//キー入力
		if (!isRotate_ && transitionCount_ == 0 && isMove_ >= 5) {
			degree_ = 0;
			if ((GetInput::Keys({ DIK_A, DIK_LEFT }) || GetInput::JoystickPushButton(0, { DIXC_LEFT, DIXC_LB })) && !GetInput::IsMouseMove() ||
				GetInput::JoystickAnalogLeftX(0) < 0) {
				isRotate_ = true;
				which_ = DIK_RIGHT;
				if (degree_ == 0) {
					degree_ = 360;
				}
				SoundPlay(SE_SELECT);
			}
			if (IsPos2RectHit((float)GetInput::MouseX(), (float)GetInput::MouseY(), selectViewPos_[0].x - selectViewWid_[0].x / 2 * selectViewScale_[0].x,
				selectViewPos_[0].y - selectViewWid_[0].y / 2 * selectViewScale_[0].y, selectViewWid_[0].x * selectViewScale_[0].x, selectViewWid_[0].y * selectViewScale_[0].y)) {
				if (GetInput::MousePushButton(DIC_LEFT)) {
					isRotate_ = true;
					which_ = DIK_RIGHT;
					if (degree_ == 0) {
						degree_ = 360;
					}
					SoundPlay(SE_SELECT);
				}

			}

			if ((GetInput::Keys({ DIK_D, DIK_RIGHT }) || GetInput::JoystickPushButton(0, { DIXC_RIGHT, DIXC_RB })) && !GetInput::IsMouseMove() ||
				GetInput::JoystickAnalogLeftX(0) > 0) {
				isRotate_ = true;
				which_ = DIK_LEFT;
				SoundPlay(SE_SELECT);
			}
			if (IsPos2RectHit((float)GetInput::MouseX(), (float)GetInput::MouseY(), selectViewPos_[1].x - selectViewWid_[1].x / 2 * selectViewScale_[1].x,
				selectViewPos_[1].y - selectViewWid_[1].y / 2 * selectViewScale_[1].y, selectViewWid_[1].x * selectViewScale_[1].x, selectViewWid_[1].y * selectViewScale_[1].y)) {
				if (GetInput::MousePushButton(DIC_LEFT)) {
					isRotate_ = true;
					which_ = DIK_LEFT;
					SoundPlay(SE_SELECT);
				}

			}
		}
		if (isRotate_) {
			//アニメーションはこっち
			/*moveCount_ = 0;
			for (int i = 0;i < 10;i++) {
				thinkScale_[i] = {0.5f,0.5f};
				thinkDegree_[i] = 0;
			}*/
			for (int i = 0; i < 2; i++) {
				selectViewPos_[i] = { 1000.0f - 32.0f - 24 - 48 + 868.0f * i,636.0f - 24 };
			}
			moveCount_ = 0;
			if (count_ <= maxCount_ / 2) {
				player_.y = Ease::Auto(count_, maxCount_ / 2, 980 - wid_.y / 2, CustomNovice::WinHeight() - 75 - 145 - 300, EASE_OUT_SINE);
				playerScale_.x = Ease::Auto(count_, maxCount_ / 2, 1.0f, 0.7f, EASE_OUT_QUINT);
				playerScale_.y = Ease::Auto(count_, maxCount_ / 2, 0.9f, 1.2f, EASE_OUT_QUINT);
				scaleSSS_ = Ease::Auto(count_, maxCount_ / 2, 1.6f * (StageClass::GetSizeIsSix(selectStageID_) / 16.0f), 2.4f, EASE_OUT_CUBIC);
			} else if (count_ > maxCount_ / 2 && count_ <= maxCount_) {
				player_.y = Ease::Auto(count_ - maxCount_ / 2, maxCount_ / 2, CustomNovice::WinHeight() - 75 - 145 - 300, 980 - wid_.y / 2, EASE_IN_SINE);
				/*playerScale_.x = Ease::Auto(count_ - maxCount_ / 2, maxCount_ / 2, 0.7f, 1.5f, EASE_OUT_BACK,10.00f);
				playerScale_.y = Ease::Auto(count_ - maxCount_ / 2, maxCount_ / 2, 1.2f, 0.75f, EASE_OUT_BACK,0.8f);*/
				scaleSSS_ = Ease::Auto(count_ - maxCount_ / 2, maxCount_ / 2, 2.4f, 1.6f * (StageClass::GetSizeIsSix(selectStageID_) / 16.0f), EASE_IN_OUT_CUBIC);
				if (count_ <= maxCount_ - 1) {
					playerScale_.x = Ease::Auto(count_ - maxCount_ / 2, maxCount_ / 2 - 1, 0.7f, 1.0f, EASE_OUT_BACK, 10.00f);
					playerScale_.y = Ease::Auto(count_ - maxCount_ / 2, maxCount_ / 2 - 1, 1.2f, 1.0f, EASE_OUT_BACK, 0.8f);
				} else {
					playerScale_.x = 1.5f;
					playerScale_.y = 0.25f;
				}
			} else if (count_ > maxCount_) {
				playerScale_.x = 1.0f;
				playerScale_.y = 1.0f;
			}


			if (which_ == DIK_LEFT) {
				//play
				if (count_ <= maxCount_) {
					playerRotate_ = Ease::Auto(count_, maxCount_ / 2, 0, 360, EASE_OUT_SINE);
				}

				//セレクトビュー
				if (count_ <= maxCount_ / 2) {
					selectViewPos_[1].x = Ease::Auto(count_, maxCount_ / 2, 1000.0f - 32.0f - 24 - 48 + 868.0f, 1000.0f - 32.0f - 24 - 48 + 868.0f + 64, EASE_OUT_SINE);
					selectViewScale_[1].x = Ease::Auto(count_, maxCount_ / 2, 0.5f, 1.0f, EASE_OUT_CUBIC);
				} else if (count_ > maxCount_ / 2) {
					selectViewPos_[1].x = Ease::Auto(count_ - maxCount_ / 2, maxCount_ / 2, 1000.0f - 32.0f - 24 - 48 + 868.0f + 64, 1000.0f - 32.0f - 24 - 48 + 868.0f, EASE_IN_SINE);
					selectViewScale_[1].x = Ease::Auto(count_ - maxCount_ / 2, maxCount_ / 2, 1.0f, 0.5f, EASE_IN_OUT_CUBIC);
				}
				//VIEWの回転
				if (count_ <= maxCount_) {
					selectViewDegree_[1] = Ease::Auto(count_, maxCount_ / 2, 0, 360, EASE_OUT_SINE);
				}
				//BOX
				/*for (int i = 0;i < 10;i++) {
					thinkDegree_[i] = Ease::Auto(count_, maxCount_ / 2, 0, 360, EASE_OUT_SINE);
				}*/
				//stage
				if (count_ <= maxCount_) {
					degree_ = Ease::Auto(count_, maxCount_, 0, 360, EASE_OUT_BACK);
					count_ += 1;
					if (count_ == maxCount_ / 3) {
						selectStageID_++;
						if (selectStageID_ >= StageClass::GetStageDataSize()) {
							selectStageID_ = 0;
						}
						stage_->SetStage(selectStageID_);
					}
					if (count_ > maxCount_ / 3) {
						if (GetInput::Keys({ DIK_D, DIK_RIGHT }) && GetInput::PreKeys({ DIK_D, DIK_RIGHT }) || GetInput::JoystickPushButton(0, { DIXC_RIGHT, DIXC_RB }) && GetInput::JoystickPrePushButton(0, { DIXC_RIGHT, DIXC_RB })) {
							count_ += 1;
						}
					}
				} else if (count_ > maxCount_) {
					isRotate_ = false;
					count_ = 0;
					//selectStageID_++;

				}
			}
			if (which_ == DIK_RIGHT) {
				//play
				if (count_ <= maxCount_) {
					playerRotate_ = Ease::Auto(count_, maxCount_ / 2, 360, 0, EASE_OUT_SINE);
				}
				//BOX
				/*for (int i = 0;i < 10;i++) {
					thinkDegree_[i] = Ease::Auto(count_, maxCount_ / 2, 360, 0, EASE_OUT_SINE);
				}*/
				//セレクトビュー
				if (count_ <= maxCount_ / 2) {
					selectViewPos_[0].x = Ease::Auto(count_, maxCount_ / 2, 1000.0f - 32.0f - 24 - 48, 1000.0f - 32.0f - 24 - 48 - 64, EASE_OUT_SINE);
					selectViewScale_[0].x = Ease::Auto(count_, maxCount_ / 2, 0.5f, 1.0f, EASE_OUT_CUBIC);
				} else if (count_ > maxCount_ / 2) {
					selectViewPos_[0].x = Ease::Auto(count_ - maxCount_ / 2, maxCount_ / 2, 1000.0f - 32.0f - 24 - 48 - 64, 1000.0f - 32.0f - 24 - 48, EASE_IN_SINE);
					selectViewScale_[0].x = Ease::Auto(count_ - maxCount_ / 2, maxCount_ / 2, 1.0f, 0.5f, EASE_IN_OUT_CUBIC);
				}
				//VIEWの回転
				if (count_ <= maxCount_) {
					selectViewDegree_[0] = Ease::Auto(count_, maxCount_ / 2, 360, 0, EASE_OUT_SINE);
				}
				//stage
				if (count_ <= maxCount_) {
					degree_ = Ease::Auto(count_, maxCount_, 360, 0, EASE_OUT_BACK);

					count_ += 1;
					if (count_ == maxCount_ / 3) {
						selectStageID_--;
						if (selectStageID_ < 0) {
							selectStageID_ = StageClass::GetStageDataSize() - 1;
						}
						stage_->SetStage(selectStageID_);
					}
					if (count_ > maxCount_ / 3) {
						if (GetInput::Keys({ DIK_A, DIK_LEFT }) && GetInput::PreKeys({ DIK_A, DIK_LEFT }) || GetInput::JoystickPushButton(0, { DIXC_LEFT, DIXC_LB }) && GetInput::JoystickPrePushButton(0, { DIXC_LEFT, DIXC_LB })) {
							count_ += 1;
						}
					}
				} else if (count_ > maxCount_) {
					isRotate_ = false;
					count_ = 0;
					//selectStageID_--;

				}
			}
		}
		cameraSSS_.SetRotate(ConvertDeg2Rad(degree_));
		//ないとキモイ挙動do
		cameraSSS_.SetCamera();
		//動いてるときに押せないようにするため
		if (!isRotate_ && isMove_ >= 5) {
			// ENTER・SPACE・コントローラーAボタンでゲームシーンに移動
			if (GetInput::TriggerKeys({ DIK_RETURN, DIK_SPACE }) || GetInput::JoystickTriggerButton(0, DIXC_A)) {
				if (stage_->IsClear(4) == false && transitionCount_ == 0) {
					if (selectStageID_ >= 1 && stage_->IsClear(selectStageID_ - 1) == 1) {
						transitionCount_ += 1;
						SoundPlay(SE_DECIDE);
					} else if (selectStageID_ == 0) {
						transitionCount_ += 1;
						SoundPlay(SE_DECIDE);
					} else {
						shakeTime_ = 1;
					}
				} else if (stage_->IsClear(4) == true && transitionCount_ == 0) {
					if (!stage_->IsClear(selectStageID_) || stage_->IsClear(selectStageID_)) {
						transitionCount_ += 1;
						SoundPlay(SE_DECIDE);
					}
				}

			}
			if (IsPos2RectHit((float)GetInput::MouseX(), (float)GetInput::MouseY(), cloudBig_.x - (800.0f - 48.0f) / 2,
				cloudBig_.y - (800.0f - 48.0f) / 2, (800.0f - 48.0f), (800.0f - 48.0f))) {
				if (GetInput::MousePushButton(DIC_LEFT)) {
					if (stage_->IsClear(4) == false && transitionCount_ == 0) {
						if (selectStageID_ >= 1 && stage_->IsClear(selectStageID_ - 1) == 1) {
							transitionCount_ += 1;
							SoundPlay(SE_DECIDE);
						} else if (selectStageID_ == 0) {
							transitionCount_ += 1;
							SoundPlay(SE_DECIDE);
						} else {
							shakeTime_ = 1;
						}

					} else if (stage_->IsClear(4) == true && transitionCount_ == 0) {
						if (!stage_->IsClear(selectStageID_) || stage_->IsClear(selectStageID_)) {
							transitionCount_ += 1;
							SoundPlay(SE_DECIDE);
						}
					}
				}

			}
		}
		if (shakeTime_ >= 1) {
			shakeTime_ += 1;
			shake_ = rand() % static_cast<int>((1.0f - (shakeTime_ / 20.0f)) * 16.0f * 2.0f + 1.0f) - ((1.0f - (shakeTime_ / 20.0f)) * 16.0f);
			if (shakeTime_ >= 20) {
				shakeTime_ = 0;
			}
		}
	}


}

void StageSelect::Draw() {
	//三つver
	if (isSelectStage_ == 1) {
		//グリッド線の処理
		if (1) {
			cameraSSS_.SetScale({ 1.0f,1.0f });
			cameraSSS_.SetViewport(0, 0, CustomNovice::WinWidth(), CustomNovice::WinHeight());
			cameraSSS_.SetTranslate({ 0.0f,0.0f });
			cameraSSS_.SetRotate(0.0f);
			cameraSSS_.SetCamera();
			SceneClass::DrawGrid(cameraSSS_);
			cameraSSS_.SetRotate(ConvertDeg2Rad(degree_));
			cameraSSS_.SetScale({ scaleSSS_,scaleSSS_ });
			cameraSSS_.SetTranslate(
				{
					static_cast<float>(stage_->GetSize() * StageClass::GetMapChipSize()) / 2.0f,
					static_cast<float>(stage_->GetSize() * StageClass::GetMapChipSize()) / 2.0f
					/*static_cast<float>(stage_->GetSize() * StageClass::GetMapChipSize()) / 2.0f,
					static_cast<float>(stage_->GetSize() * StageClass::GetMapChipSize()) / 2.0f + 100.0f + 1080.0f + 620.0f*/
				});
			cameraSSS_.SetViewport(440 - 64, 50 + 24, CustomNovice::WinWidth(), CustomNovice::WinHeight());
			cameraSSS_.SetCamera();
		}
		//プレイヤーの処理？
		leftTop_ = { -wid_.x / 2, wid_.y / 2 };
		rightTop_ = { +wid_.x / 2, wid_.y / 2 };
		leftBottom_ = { -wid_.x / 2, -wid_.y / 2 };
		rightBottom_ = { +wid_.x / 2, -wid_.y / 2 };
		CustomNovice::DrawQuad(
			PlayerView(player_, leftTop_, ConvertDeg2Rad(playerRotate_), playerScale_).x, PlayerView(player_, leftTop_, ConvertDeg2Rad(playerRotate_), { 1.0f,1.0f }).y,
			PlayerView(player_, rightTop_, ConvertDeg2Rad(playerRotate_), playerScale_).x, PlayerView(player_, rightTop_, ConvertDeg2Rad(playerRotate_), { 1.0f,1.0f }).y,
			PlayerView(player_, leftBottom_, ConvertDeg2Rad(playerRotate_), playerScale_).x, PlayerView(player_, leftBottom_, ConvertDeg2Rad(playerRotate_), playerScale_).y,
			PlayerView(player_, rightBottom_, ConvertDeg2Rad(playerRotate_), playerScale_).x, PlayerView(player_, rightBottom_, ConvertDeg2Rad(playerRotate_), playerScale_).y,
			GraphHandle::Width(TX_PLAYER) / 3, 0, GraphHandle::Width(TX_PLAYER) / 3, GraphHandle::Height(TX_PLAYER), GraphHandle::ID(TX_PLAYER), 0xffff8bff
		);
		if (transitionCount_ <= transitionCountMax_ / 2) {
			/*CustomNovice::DrawBox(
				0, 1080, 1960, -100, 0x000000FF, 0.0f, kFillModeWireFrame
			);*/
			CustomNovice::DrawQuad(0, 1030 - 50, 0 + CustomNovice::WinWidth(), 1030 - 50.0f,
				0, 1030 + 50.0f, CustomNovice::WinWidth(), 1030 + 50.0f,
				0, 0, 64, 64, GraphHandle::ID(TX_TILEMAP_NORMAL), 0xaaaaaaFF);
			//雲の発生位置の印付け
			if (isMove_ >= 2) {
				//a
			}
			if (isMove_ >= 3) {
			}

			if (1) {
				//遊べるかORクリアしているか

			//最初の条件aa
				if (stage_->IsClear(4) == false) {
					if (stage_->IsClear(selectStageID_) == 0 && selectStageID_ == 0) {
						//周りのやつ
						leftTop_ = { -(800.0f - 48.0f) / 2, (800.0f - 48.0f) / 2 };
						rightTop_ = { +(800.0f - 48.0f) / 2, (800.0f - 48.0f) / 2 };
						leftBottom_ = { -(800.0f - 48.0f) / 2, -(800.0f - 48.0f) / 2 };
						rightBottom_ = { +(800.0f - 48.0f) / 2, -(800.0f - 48.0f) / 2 };
						CustomNovice::DrawQuad(
							PlayerView(cloudBig_, leftTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
							PlayerView(cloudBig_, rightTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
							PlayerView(cloudBig_, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
							PlayerView(cloudBig_, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
							0, 0, GraphHandle::Width(TX_TITLEBOX), GraphHandle::Height(TX_TITLEBOX), GraphHandle::ID(TX_TITLEBOX), 0xd81f35ff
						);
						if (IsPos2RectHit((float)GetInput::MouseX(), (float)GetInput::MouseY(), cloudBig_.x - (800.0f - 48.0f) / 2,
							cloudBig_.y - (800.0f - 48.0f) / 2, (800.0f - 48.0f), (800.0f - 48.0f))) {
							CustomNovice::DrawQuad(
								PlayerView(cloudBig_, leftTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
								PlayerView(cloudBig_, rightTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
								PlayerView(cloudBig_, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
								PlayerView(cloudBig_, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
								0, 0, GraphHandle::Width(TX_TITLEBOX), GraphHandle::Height(TX_TITLEBOX), GraphHandle::ID(TX_TITLEBOX), 0xff0000ff
							);
						}
						//プレイヤーの処理？
						for (int i = 0; i < 2; i++) {
							leftTop_ = { -selectViewWid_[i].x / 2, selectViewWid_[i].y / 2 };
							rightTop_ = { +selectViewWid_[i].x / 2, selectViewWid_[i].y / 2 };
							leftBottom_ = { -selectViewWid_[i].x / 2, -selectViewWid_[i].y / 2 };
							rightBottom_ = { +selectViewWid_[i].x / 2, -selectViewWid_[i].y / 2 };
							CustomNovice::DrawQuad(
								PlayerView(selectViewPos_[i], leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								PlayerView(selectViewPos_[i], rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								PlayerView(selectViewPos_[i], leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								PlayerView(selectViewPos_[i], rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								i * GraphHandle::Width(TX_SELECTVIEWSC) / 2, 0, GraphHandle::Width(TX_SELECTVIEWSC) / 2, GraphHandle::Height(TX_SELECTVIEWSC), GraphHandle::ID(TX_SELECTVIEWSC), 0xd81f35ff
							);
							if (IsPos2RectHit((float)GetInput::MouseX(), (float)GetInput::MouseY(), selectViewPos_[i].x - selectViewWid_[i].x / 2 * selectViewScale_[i].x,
								selectViewPos_[i].y - selectViewWid_[i].y / 2 * selectViewScale_[i].y, selectViewWid_[i].x * selectViewScale_[i].x, selectViewWid_[i].y * selectViewScale_[i].y)) {
								CustomNovice::DrawQuad(
									PlayerView(selectViewPos_[i], leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									PlayerView(selectViewPos_[i], rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									PlayerView(selectViewPos_[i], leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									PlayerView(selectViewPos_[i], rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									i * GraphHandle::Width(TX_SELECTVIEWSC) / 2, 0, GraphHandle::Width(TX_SELECTVIEWSC) / 2, GraphHandle::Height(TX_SELECTVIEWSC), GraphHandle::ID(TX_SELECTVIEWSC), 0xff0000ff
								);
							}
						}
					}
					//前ができていないので挑戦できない
					else if (stage_->IsClear(selectStageID_) == 0 && stage_->IsClear(selectStageID_ - 1) == 1) {
						//周りのやつ
						leftTop_ = { -(800.0f - 48.0f) / 2, (800.0f - 48.0f) / 2 };
						rightTop_ = { +(800.0f - 48.0f) / 2, (800.0f - 48.0f) / 2 };
						leftBottom_ = { -(800.0f - 48.0f) / 2, -(800.0f - 48.0f) / 2 };
						rightBottom_ = { +(800.0f - 48.0f) / 2, -(800.0f - 48.0f) / 2 };
						CustomNovice::DrawQuad(
							PlayerView(cloudBig_, leftTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
							PlayerView(cloudBig_, rightTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
							PlayerView(cloudBig_, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
							PlayerView(cloudBig_, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
							0, 0, GraphHandle::Width(TX_TITLEBOX), GraphHandle::Height(TX_TITLEBOX), GraphHandle::ID(TX_TITLEBOX), 0xd81f35ff
						);
						if (IsPos2RectHit((float)GetInput::MouseX(), (float)GetInput::MouseY(), cloudBig_.x - (800.0f - 48.0f) / 2,
							cloudBig_.y - (800.0f - 48.0f) / 2, (800.0f - 48.0f), (800.0f - 48.0f))) {
							CustomNovice::DrawQuad(
								PlayerView(cloudBig_, leftTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
								PlayerView(cloudBig_, rightTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
								PlayerView(cloudBig_, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
								PlayerView(cloudBig_, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
								0, 0, GraphHandle::Width(TX_TITLEBOX), GraphHandle::Height(TX_TITLEBOX), GraphHandle::ID(TX_TITLEBOX), 0xff0000ff
							);
						}
						//プレイヤーの処理？
						for (int i = 0; i < 2; i++) {
							leftTop_ = { -selectViewWid_[i].x / 2, selectViewWid_[i].y / 2 };
							rightTop_ = { +selectViewWid_[i].x / 2, selectViewWid_[i].y / 2 };
							leftBottom_ = { -selectViewWid_[i].x / 2, -selectViewWid_[i].y / 2 };
							rightBottom_ = { +selectViewWid_[i].x / 2, -selectViewWid_[i].y / 2 };
							CustomNovice::DrawQuad(
								PlayerView(selectViewPos_[i], leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								PlayerView(selectViewPos_[i], rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								PlayerView(selectViewPos_[i], leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								PlayerView(selectViewPos_[i], rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								i * GraphHandle::Width(TX_SELECTVIEWSC) / 2, 0, GraphHandle::Width(TX_SELECTVIEWSC) / 2, GraphHandle::Height(TX_SELECTVIEWSC), GraphHandle::ID(TX_SELECTVIEWSC), 0xd81f35ff
							);
							if (IsPos2RectHit((float)GetInput::MouseX(), (float)GetInput::MouseY(), selectViewPos_[i].x - selectViewWid_[i].x / 2 * selectViewScale_[i].x,
								selectViewPos_[i].y - selectViewWid_[i].y / 2 * selectViewScale_[i].y, selectViewWid_[i].x * selectViewScale_[i].x, selectViewWid_[i].y * selectViewScale_[i].y)) {
								CustomNovice::DrawQuad(
									PlayerView(selectViewPos_[i], leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									PlayerView(selectViewPos_[i], rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									PlayerView(selectViewPos_[i], leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									PlayerView(selectViewPos_[i], rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									i * GraphHandle::Width(TX_SELECTVIEWSC) / 2, 0, GraphHandle::Width(TX_SELECTVIEWSC) / 2, GraphHandle::Height(TX_SELECTVIEWSC), GraphHandle::ID(TX_SELECTVIEWSC), 0xff0000ff
								);
							}
						}
					}
					//クリアしたら
					else if (stage_->IsClear(selectStageID_) == 1) {
						//周りのやつ
						leftTop_ = { -(800.0f - 48.0f) / 2, (800.0f - 48.0f) / 2 };
						rightTop_ = { +(800.0f - 48.0f) / 2, (800.0f - 48.0f) / 2 };
						leftBottom_ = { -(800.0f - 48.0f) / 2, -(800.0f - 48.0f) / 2 };
						rightBottom_ = { +(800.0f - 48.0f) / 2, -(800.0f - 48.0f) / 2 };
						CustomNovice::DrawQuad(
							PlayerView(cloudBig_, leftTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
							PlayerView(cloudBig_, rightTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
							PlayerView(cloudBig_, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
							PlayerView(cloudBig_, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
							0, 0, GraphHandle::Width(TX_TITLEBOX), GraphHandle::Height(TX_TITLEBOX), GraphHandle::ID(TX_TITLEBOX), 0xb0deb8ff
						);
						if (IsPos2RectHit((float)GetInput::MouseX(), (float)GetInput::MouseY(), cloudBig_.x - (800.0f - 48.0f) / 2,
							cloudBig_.y - (800.0f - 48.0f) / 2, (800.0f - 48.0f), (800.0f - 48.0f))) {
							CustomNovice::DrawQuad(
								PlayerView(cloudBig_, leftTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
								PlayerView(cloudBig_, rightTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
								PlayerView(cloudBig_, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
								PlayerView(cloudBig_, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
								0, 0, GraphHandle::Width(TX_TITLEBOX), GraphHandle::Height(TX_TITLEBOX), GraphHandle::ID(TX_TITLEBOX), 0x00ff00ff
							);
						}
						//プレイヤーの処理？
						for (int i = 0; i < 2; i++) {
							leftTop_ = { -selectViewWid_[i].x / 2, selectViewWid_[i].y / 2 };
							rightTop_ = { +selectViewWid_[i].x / 2, selectViewWid_[i].y / 2 };
							leftBottom_ = { -selectViewWid_[i].x / 2, -selectViewWid_[i].y / 2 };
							rightBottom_ = { +selectViewWid_[i].x / 2, -selectViewWid_[i].y / 2 };
							CustomNovice::DrawQuad(
								PlayerView(selectViewPos_[i], leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								PlayerView(selectViewPos_[i], rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								PlayerView(selectViewPos_[i], leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								PlayerView(selectViewPos_[i], rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								i * GraphHandle::Width(TX_SELECTVIEWSC) / 2, 0, GraphHandle::Width(TX_SELECTVIEWSC) / 2, GraphHandle::Height(TX_SELECTVIEWSC), GraphHandle::ID(TX_SELECTVIEWSC), 0xb0deb8ff
							);
							if (IsPos2RectHit((float)GetInput::MouseX(), (float)GetInput::MouseY(), selectViewPos_[i].x - selectViewWid_[i].x / 2 * selectViewScale_[i].x,
								selectViewPos_[i].y - selectViewWid_[i].y / 2 * selectViewScale_[i].y, selectViewWid_[i].x * selectViewScale_[i].x, selectViewWid_[i].y * selectViewScale_[i].y)) {
								CustomNovice::DrawQuad(
									PlayerView(selectViewPos_[i], leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									PlayerView(selectViewPos_[i], rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									PlayerView(selectViewPos_[i], leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									PlayerView(selectViewPos_[i], rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									i * GraphHandle::Width(TX_SELECTVIEWSC) / 2, 0, GraphHandle::Width(TX_SELECTVIEWSC) / 2, GraphHandle::Height(TX_SELECTVIEWSC), GraphHandle::ID(TX_SELECTVIEWSC), 0x00ff00ff
								);
							}
						}
					}
					//前ができていないので挑戦できない
					else if (stage_->IsClear(selectStageID_) == 0 && stage_->IsClear(selectStageID_ - 1) == 0) {
						//周りのやつ
						leftTop_ = { -(800.0f - 48.0f) / 2, (800.0f - 48.0f) / 2 };
						rightTop_ = { +(800.0f - 48.0f) / 2, (800.0f - 48.0f) / 2 };
						leftBottom_ = { -(800.0f - 48.0f) / 2, -(800.0f - 48.0f) / 2 };
						rightBottom_ = { +(800.0f - 48.0f) / 2, -(800.0f - 48.0f) / 2 };
						CustomNovice::DrawQuad(
							PlayerView({ cloudBig_.x + shake_,cloudBig_.y }, leftTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
							PlayerView({ cloudBig_.x + shake_,cloudBig_.y }, rightTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
							PlayerView({ cloudBig_.x + shake_,cloudBig_.y }, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
							PlayerView({ cloudBig_.x + shake_,cloudBig_.y }, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
							0, 0, GraphHandle::Width(TX_TITLEBOX), GraphHandle::Height(TX_TITLEBOX), GraphHandle::ID(TX_TITLEBOX), 0x333333ff
						);
						if (IsPos2RectHit((float)GetInput::MouseX(), (float)GetInput::MouseY(), cloudBig_.x - (800.0f - 48.0f) / 2,
							cloudBig_.y - (800.0f - 48.0f) / 2, (800.0f - 48.0f), (800.0f - 48.0f))) {
							CustomNovice::DrawQuad(
								PlayerView({ cloudBig_.x + shake_,cloudBig_.y }, leftTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
								PlayerView({ cloudBig_.x + shake_,cloudBig_.y }, rightTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
								PlayerView({ cloudBig_.x + shake_,cloudBig_.y }, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
								PlayerView({ cloudBig_.x + shake_,cloudBig_.y }, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
								0, 0, GraphHandle::Width(TX_TITLEBOX), GraphHandle::Height(TX_TITLEBOX), GraphHandle::ID(TX_TITLEBOX), 0x777777ff
							);
						}
						//プレイヤーの処理？
						for (int i = 0; i < 2; i++) {
							leftTop_ = { -selectViewWid_[i].x / 2, selectViewWid_[i].y / 2 };
							rightTop_ = { +selectViewWid_[i].x / 2, selectViewWid_[i].y / 2 };
							leftBottom_ = { -selectViewWid_[i].x / 2, -selectViewWid_[i].y / 2 };
							rightBottom_ = { +selectViewWid_[i].x / 2, -selectViewWid_[i].y / 2 };
							CustomNovice::DrawQuad(
								PlayerView({ selectViewPos_[i].x + shake_,selectViewPos_[i].y }, leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								PlayerView({ selectViewPos_[i].x + shake_,selectViewPos_[i].y }, rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								PlayerView({ selectViewPos_[i].x + shake_,selectViewPos_[i].y }, leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								PlayerView({ selectViewPos_[i].x + shake_,selectViewPos_[i].y }, rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								i * GraphHandle::Width(TX_SELECTVIEWSC) / 2, 0, GraphHandle::Width(TX_SELECTVIEWSC) / 2, GraphHandle::Height(TX_SELECTVIEWSC), GraphHandle::ID(TX_SELECTVIEWSC), 0x333333ff
							);
							if (IsPos2RectHit((float)GetInput::MouseX(), (float)GetInput::MouseY(), selectViewPos_[i].x - selectViewWid_[i].x / 2 * selectViewScale_[i].x,
								selectViewPos_[i].y - selectViewWid_[i].y / 2 * selectViewScale_[i].y, selectViewWid_[i].x * selectViewScale_[i].x, selectViewWid_[i].y * selectViewScale_[i].y)) {
								CustomNovice::DrawQuad(
									PlayerView({ selectViewPos_[i].x + shake_,selectViewPos_[i].y }, leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									PlayerView({ selectViewPos_[i].x + shake_,selectViewPos_[i].y }, rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									PlayerView({ selectViewPos_[i].x + shake_,selectViewPos_[i].y }, leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									PlayerView({ selectViewPos_[i].x + shake_,selectViewPos_[i].y }, rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									i * GraphHandle::Width(TX_SELECTVIEWSC) / 2, 0, GraphHandle::Width(TX_SELECTVIEWSC) / 2, GraphHandle::Height(TX_SELECTVIEWSC), GraphHandle::ID(TX_SELECTVIEWSC), 0x777777FF
								);
							}
						}
					}
				} else if (stage_->IsClear(4) == true) {
					if (stage_->IsClear(selectStageID_) == false) {
						//周りのやつ
						leftTop_ = { -(800.0f - 48.0f) / 2, (800.0f - 48.0f) / 2 };
						rightTop_ = { +(800.0f - 48.0f) / 2, (800.0f - 48.0f) / 2 };
						leftBottom_ = { -(800.0f - 48.0f) / 2, -(800.0f - 48.0f) / 2 };
						rightBottom_ = { +(800.0f - 48.0f) / 2, -(800.0f - 48.0f) / 2 };
						CustomNovice::DrawQuad(
							PlayerView(cloudBig_, leftTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
							PlayerView(cloudBig_, rightTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
							PlayerView(cloudBig_, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
							PlayerView(cloudBig_, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
							0, 0, GraphHandle::Width(TX_TITLEBOX), GraphHandle::Height(TX_TITLEBOX), GraphHandle::ID(TX_TITLEBOX), 0xd81f35ff
						);
						if (IsPos2RectHit((float)GetInput::MouseX(), (float)GetInput::MouseY(), cloudBig_.x - (800.0f - 48.0f) / 2,
							cloudBig_.y - (800.0f - 48.0f) / 2, (800.0f - 48.0f), (800.0f - 48.0f))) {
							CustomNovice::DrawQuad(
								PlayerView(cloudBig_, leftTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
								PlayerView(cloudBig_, rightTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
								PlayerView(cloudBig_, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
								PlayerView(cloudBig_, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
								0, 0, GraphHandle::Width(TX_TITLEBOX), GraphHandle::Height(TX_TITLEBOX), GraphHandle::ID(TX_TITLEBOX), 0xff0000ff
							);
						}
						//プレイヤーの処理？
						for (int i = 0; i < 2; i++) {
							leftTop_ = { -selectViewWid_[i].x / 2, selectViewWid_[i].y / 2 };
							rightTop_ = { +selectViewWid_[i].x / 2, selectViewWid_[i].y / 2 };
							leftBottom_ = { -selectViewWid_[i].x / 2, -selectViewWid_[i].y / 2 };
							rightBottom_ = { +selectViewWid_[i].x / 2, -selectViewWid_[i].y / 2 };
							CustomNovice::DrawQuad(
								PlayerView(selectViewPos_[i], leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								PlayerView(selectViewPos_[i], rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								PlayerView(selectViewPos_[i], leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								PlayerView(selectViewPos_[i], rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								i * GraphHandle::Width(TX_SELECTVIEWSC) / 2, 0, GraphHandle::Width(TX_SELECTVIEWSC) / 2, GraphHandle::Height(TX_SELECTVIEWSC), GraphHandle::ID(TX_SELECTVIEWSC), 0xd81f35ff
							);
							if (IsPos2RectHit((float)GetInput::MouseX(), (float)GetInput::MouseY(), selectViewPos_[i].x - selectViewWid_[i].x / 2 * selectViewScale_[i].x,
								selectViewPos_[i].y - selectViewWid_[i].y / 2 * selectViewScale_[i].y, selectViewWid_[i].x * selectViewScale_[i].x, selectViewWid_[i].y * selectViewScale_[i].y)) {
								CustomNovice::DrawQuad(
									PlayerView(selectViewPos_[i], leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									PlayerView(selectViewPos_[i], rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									PlayerView(selectViewPos_[i], leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									PlayerView(selectViewPos_[i], rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									i * GraphHandle::Width(TX_SELECTVIEWSC) / 2, 0, GraphHandle::Width(TX_SELECTVIEWSC) / 2, GraphHandle::Height(TX_SELECTVIEWSC), GraphHandle::ID(TX_SELECTVIEWSC), 0xff0000ff
								);
							}
						}
					} else if (stage_->IsClear(selectStageID_) == true) {
						//周りのやつ
						leftTop_ = { -(800.0f - 48.0f) / 2, (800.0f - 48.0f) / 2 };
						rightTop_ = { +(800.0f - 48.0f) / 2, (800.0f - 48.0f) / 2 };
						leftBottom_ = { -(800.0f - 48.0f) / 2, -(800.0f - 48.0f) / 2 };
						rightBottom_ = { +(800.0f - 48.0f) / 2, -(800.0f - 48.0f) / 2 };
						CustomNovice::DrawQuad(
							PlayerView(cloudBig_, leftTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
							PlayerView(cloudBig_, rightTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
							PlayerView(cloudBig_, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
							PlayerView(cloudBig_, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
							0, 0, GraphHandle::Width(TX_TITLEBOX), GraphHandle::Height(TX_TITLEBOX), GraphHandle::ID(TX_TITLEBOX), 0xb0deb8ff
						);
						if (IsPos2RectHit((float)GetInput::MouseX(), (float)GetInput::MouseY(), cloudBig_.x - (800.0f - 48.0f) / 2,
							cloudBig_.y - (800.0f - 48.0f) / 2, (800.0f - 48.0f), (800.0f - 48.0f))) {
							CustomNovice::DrawQuad(
								PlayerView(cloudBig_, leftTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
								PlayerView(cloudBig_, rightTop_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightTop_, ConvertDeg2Rad(cloudDegree_), { 1.0f,1.0f }).y,
								PlayerView(cloudBig_, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, leftBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
								PlayerView(cloudBig_, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).x, PlayerView(cloudBig_, rightBottom_, ConvertDeg2Rad(cloudDegree_), cloudScale_).y,
								0, 0, GraphHandle::Width(TX_TITLEBOX), GraphHandle::Height(TX_TITLEBOX), GraphHandle::ID(TX_TITLEBOX), 0x00ff00ff
							);
						}
						//プレイヤーの処理？
						for (int i = 0; i < 2; i++) {
							leftTop_ = { -selectViewWid_[i].x / 2, selectViewWid_[i].y / 2 };
							rightTop_ = { +selectViewWid_[i].x / 2, selectViewWid_[i].y / 2 };
							leftBottom_ = { -selectViewWid_[i].x / 2, -selectViewWid_[i].y / 2 };
							rightBottom_ = { +selectViewWid_[i].x / 2, -selectViewWid_[i].y / 2 };
							CustomNovice::DrawQuad(
								PlayerView(selectViewPos_[i], leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								PlayerView(selectViewPos_[i], rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								PlayerView(selectViewPos_[i], leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								PlayerView(selectViewPos_[i], rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
								i * GraphHandle::Width(TX_SELECTVIEWSC) / 2, 0, GraphHandle::Width(TX_SELECTVIEWSC) / 2, GraphHandle::Height(TX_SELECTVIEWSC), GraphHandle::ID(TX_SELECTVIEWSC), 0xb0deb8ff
							);
							if (IsPos2RectHit((float)GetInput::MouseX(), (float)GetInput::MouseY(), selectViewPos_[i].x - selectViewWid_[i].x / 2 * selectViewScale_[i].x,
								selectViewPos_[i].y - selectViewWid_[i].y / 2 * selectViewScale_[i].y, selectViewWid_[i].x * selectViewScale_[i].x, selectViewWid_[i].y * selectViewScale_[i].y)) {
								CustomNovice::DrawQuad(
									PlayerView(selectViewPos_[i], leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									PlayerView(selectViewPos_[i], rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightTop_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									PlayerView(selectViewPos_[i], leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], leftBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									PlayerView(selectViewPos_[i], rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).x, PlayerView(selectViewPos_[i], rightBottom_, ConvertDeg2Rad(selectViewDegree_[i]), selectViewScale_[i]).y,
									i * GraphHandle::Width(TX_SELECTVIEWSC) / 2, 0, GraphHandle::Width(TX_SELECTVIEWSC) / 2, GraphHandle::Height(TX_SELECTVIEWSC), GraphHandle::ID(TX_SELECTVIEWSC), 0x00ff00ff
								);
							}
						}
					}
				}
			}

			stage_->DrawStageName(selectStageID_, namePos_);
			if (isMove_ >= 5) {


			}
		}
		//シーン遷移の処理
		if (transitionCount_ >= 1) {
			playerScale_ = { 1.0f,1.0f };
			transitionCount_ += 1;
			//ここにはシーン遷移の処理を書く
			if (transitionCount_ <= transitionCountMax_ / 3) {
				player_.y = Ease::Auto(transitionCount_, transitionCountMax_ / 3, 980 - wid_.y / 2, 700, EASE_OUT_SINE);
			} else if (transitionCount_ > transitionCountMax_ / 3) {
				player_.y = Ease::Auto(transitionCount_ - transitionCountMax_ / 3, transitionCountMax_ / 3 * 2, 700, 1500, EASE_IN_SINE);
			}

			cameraSSS_.SetTranslate(
				{
					Ease::Auto(transitionCount_, transitionCountMax_, static_cast<float>(stage_->GetSize() * StageClass::GetMapChipSize()) / 2.0f,
					static_cast<float>(stage_->GetSize() * StageClass::GetMapChipSize()) / 2.0f, EASE_IN_SINE),
					Ease::Auto(transitionCount_, transitionCountMax_, static_cast<float>(stage_->GetSize() * StageClass::GetMapChipSize()) / 2.0f,
					static_cast<float>(stage_->GetSize() * StageClass::GetMapChipSize()) / 2.0f,EASE_IN_SINE)
				}
			);
			cameraSSS_.SetScale(
				{
					Ease::Auto(transitionCount_, transitionCountMax_, scaleSSS_,
					1.0f, EASE_IN_SINE),
					Ease::Auto(transitionCount_, transitionCountMax_, scaleSSS_,
					1.0f,EASE_IN_SINE)
				}
			);
			cameraSSS_.SetViewport(
				Ease::Auto(transitionCount_, transitionCountMax_, 440.0f - 64.0f, 0, EASE_IN_SINE),
				Ease::Auto(transitionCount_, transitionCountMax_, 50.0f + 24.0f, 0, EASE_IN_SINE),
				CustomNovice::WinWidth(), CustomNovice::WinHeight()
			);
			cameraSSS_.SetCamera();
		}
		//ステージの描画
		if (isMove_ >= 5) {
			stage_->DrawStage(cameraSSS_, selectStageID_);
		}
		//DRAWのカメラ変換に取られる（グリッド線を表示したため）
		if (transitionCount_ >= transitionCountMax_) {
			cameraSSS_.ResetCamera();
			// ステージの中心にカメラが来るよう平行移動
			cameraSSS_.SetTranslate(
				{
					static_cast<float>(stage_->GetSize() * StageClass::GetMapChipSize()) / 2.0f,
					static_cast<float>(stage_->GetSize() * StageClass::GetMapChipSize()) / 2.0f
				}
			);
			cameraSSS_.SetCamera();
			SceneGame::Reset(selectStageID_);
			SceneClass::SetScene(GAME);
			transitionCount_ = 0;
			isMove_ = 0;
			//BGM
			SoundPlay(BGM_GAME);
		}
	}

}

void StageSelect::Init() {

	cameraSSS_.ResetCamera();
	cameraSSS_.SetTranslate({
		static_cast<float>(stage_->GetSize() * StageClass::GetMapChipSize()) / 2.0f,
		static_cast<float>(stage_->GetSize() * StageClass::GetMapChipSize()) / 2.0f + 100.0f
		}
	);
	cameraSSS_.SetScale({ scaleSSS_,scaleSSS_ });
	cameraSSS_.SetCamera();

}

Vector2 StageSelect::PlayerView(Vector2 pos, Vector2 posVer, float rotate, Vector2 scale) {
	Vector2 viewPos = posVer;
	Matrix3x3 affine = MakeAffineMatrix(scale, rotate, pos);
	viewPos = Transform(viewPos, affine);
	return viewPos;
}

