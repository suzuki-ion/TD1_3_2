#include <Scene/Title.h>
#include <Common/Easings.h>
#include <Common/CustomNovice.h>
#include <Common/GetInput.h>
#include <Common/SoundHandle.h>

namespace {

// 入力のインスタンス
auto sGetInput = sGetInput->GetInstance();

} // namespace

void Title::Initialize() {
	cameraT_.ResetCamera();
	cameraT_.SetTranslate(
		{ 384, 384 - 48 }
		/*{ CustomNovice::WinWidth()/2, 1200}*/
	);
	cameraT_.SetScale(scale_);
	cameraT_.SetViewport(0, -1200, CustomNovice::WinWidth(), CustomNovice::WinHeight());
	cameraT_.SetCamera();

	for (int i = 0; i < 4; i++) {
		color_[i] = 0x20202011;
	}
	pos_ = { 384.0f,336.0f };
	color_[0] = 0xFFFFFF11;
}

void Title::Update() {

	SoundStop(BGM_STAGE_SELECT);
	SoundStop(BGM_GAME);

	/*
	* 右から左に移動
	* 先頭が止まる->詰まる->はじける->
	*/
	//最初の黒のフェードアウト
	if (isTitle_ == 100) {
		//colorTop_ = static_cast<unsigned int>(Ease::Auto(count_, 120, 0.0f, 255.0f, EASE_IN_SINE));
		if (count_ >= 255)
			colorTop_ -= 1;
		count_ += 1;
		if (count_ > 500) {
			count_ = 0;
			isTitle_ = 0;
			isFirstTitle_ = 0;
			colorTop_ = 0x00000000;
			colorTeach_ = static_cast<float>(0xFFFFFFFF);
			titleColor_ = 0xFFFFFF00;
			//タイトルの初期化処理
			for (int i = 0; i < 12; i++) {
				titlePos_[i] = { /*196.0f / 2 * 3 + i * 196*/CustomNovice::WinWidth() + 196.0f, 196 * 2 };
				titleDegree_[i] = 0;
				titleScale_[i] = { 1.0f,1.0f };
			}
			/*titlePos_[8]  = titlePos_[4];
			titlePos_[9]  = titlePos_[5];
			titlePos_[10] = titlePos_[6];
			titlePos_[11] = titlePos_[7];*/
		}
		//飛ばすため
		if (sGetInput->TriggerKeys({ DIK_RETURN, DIK_SPACE }) || sGetInput->JoystickTriggerButton(0, DIXC_A) || sGetInput->MouseTriggerButton({ DIC_LEFT })) {
			count_ = 499;
		}
	}
	//最初のタイトル
	if (isTitle_ == 0) {
		//ドンっ
		if (isFirstTitle_ == 0) {
			translate_.y = Ease::Auto(count_, 120, -1200.0f, 100.0f, EASE_OUT_ELASTIC, 1.0f);
			cameraT_.SetViewport(0, translate_.y, CustomNovice::WinWidth(), CustomNovice::WinHeight());
			cameraT_.SetCamera();

			//○   <----    ○
			if (count_ <= 20) {
				titlePos_[0].x = Ease::Auto(count_, 20, CustomNovice::WinWidth() + 196.0f, 294.0f, EASE_OUT_EXPO);
			}
			//○  ○  <---    ○
			if (count_ >= 10 && count_ <= 30) {
				titlePos_[1].x = Ease::Auto(count_ - 10, 20, CustomNovice::WinWidth() + 196.0f, 294.0f + 196.0f * 1.0f, EASE_OUT_QUART);
			}
			if (count_ >= 10 + 3 + 3 * 2 && count_ <= 30 + 3 + 3 * 2) {
				titlePos_[2].x = Ease::Auto(count_ - 10 - (3 + 3 * 2), 20, CustomNovice::WinWidth() + 196.0f, 294.0f + 196.0f * 2.0f, EASE_OUT_QUINT);
			}
			if (count_ >= 10 + 6 + 3 * 2 && count_ <= 30 + 6 + 3 * 2) {
				titlePos_[3].x = Ease::Auto(count_ - 10 - (6 + 3 * 2), 20, CustomNovice::WinWidth() + 196.0f, 294.0f + 196.0f * 3.0f, EASE_OUT_QUINT);
			}

			if (count_ >= 10 + 9 + 3 * 2 && count_ <= 30 + 9 + 3 * 2) {
				titlePos_[4].x = Ease::Auto(count_ - 10 - (9 + 3 * 2), 20, CustomNovice::WinWidth() + 196.0f, 294.0f + 196.0f * 4.0f, EASE_OUT_QUINT);
				titlePos_[4 + 4].x = Ease::Auto(count_ - 10 - (9 + 3 * 2), 20, CustomNovice::WinWidth() + 196.0f, 294.0f + 196.0f * 4.0f, EASE_OUT_QUINT);
			}

			if (count_ >= 10 + 12 + 3 * 2 && count_ <= 30 + 12 + 3 * 2) {
				titlePos_[5].x = Ease::Auto(count_ - 10 - (12 + 3 * 2), 20, CustomNovice::WinWidth() + 196.0f, 294.0f + 196.0f * 5.0f, EASE_OUT_QUINT);
				titlePos_[5 + 4].x = Ease::Auto(count_ - 10 - (12 + 3 * 2), 20, CustomNovice::WinWidth() + 196.0f, 294.0f + 196.0f * 5.0f, EASE_OUT_QUINT);
			}
			if (count_ >= 10 + 15 + 3 * 2 && count_ <= 30 + 15 + 3 * 2) {
				titlePos_[6].x = Ease::Auto(count_ - 10 - (15 + 3 * 2), 20, CustomNovice::WinWidth() + 196.0f, 294.0f + 196.0f * 6.0f, EASE_OUT_QUINT);
				titlePos_[6 + 4].x = Ease::Auto(count_ - 10 - (15 + 3 * 2), 20, CustomNovice::WinWidth() + 196.0f, 294.0f + 196.0f * 6.0f, EASE_OUT_QUINT);
			}


			if (count_ >= 70 && count_ <= 100) {
				titlePos_[7].x = Ease::Auto(count_ - 70 - (0), 20, CustomNovice::WinWidth() + 196.0f, 294.0f + 196.0f * 7.0f / 2.0f, EASE_OUT_EXPO);
				titlePos_[7 + 4].x = Ease::Auto(count_ - 70 - (0), 20, CustomNovice::WinWidth() + 196.0f, 294.0f + 196.0f * 7.0f / 2.0f, EASE_OUT_EXPO);
			}

			/*if (IsCircle2CircleHit(titlePos_[6].x, titlePos_[6].y, 98.0f * titleScale_[6].x, titlePos_[6 + 1].x, titlePos_[6 + 1].y, 98.0f * titleScale_[6 + 1].x)) {
				titlePos_[6].x = titlePos_[6 + 1].x - 98.0f * titleScale_[6 + 1].x - 98.0f * titleScale_[6].x;
			}*///例↑
			if (count_ >= 70 && count_ <= 100) {
				for (int i = 1; i < 7; i++) {
					if (IsCircle2CircleHit(titlePos_[i].x, titlePos_[i].y, 98.0f * titleScale_[i].x, titlePos_[i + 1].x, titlePos_[i + 1].y, 98.0f * titleScale_[i + 1].x)) {
						titlePos_[i].x = titlePos_[i + 1].x - (98.0f * titleScale_[i + 1].x) / 1.5f - (98.0f * titleScale_[i].x) / 1.5f;
						titleScale_[i].x = titleScale_[i + 1].x - 0.075f;
						titleScale_[i].y = titleScale_[i + 1].y + 0.02f;
					}
				}
				titlePos_[8] = titlePos_[4];
				titlePos_[9] = titlePos_[5];
				titlePos_[10] = titlePos_[6];
				titlePos_[11] = titlePos_[7];
			}
			//残り時間はプルプル
			if (count_ > 100) {
				shake_.x = rand() % static_cast<int>((1.0f - (count_ / 120.0f)) * 200.0f * 2.0f + 1.0f) - ((1.0f - (count_ / 120.0f)) * 200.0f);
			}
			count_ += 1;
			if (count_ > 120) {
				count_ = 0;
				shake_ = { 0,0 };
				isFirstTitle_ += 1;
			}
			//飛ばすため
			if (sGetInput->TriggerKeys({ DIK_RETURN, DIK_SPACE }) || sGetInput->JoystickTriggerButton(0, DIXC_A) || sGetInput->MouseTriggerButton({ DIC_LEFT })) {
				count_ += 20;
			}
		}
		//くるくる小さく
		else if (isFirstTitle_ == 1) {
			scale_.x = Ease::Auto(count_, 120, 0.8f, 5.2f * 2, EASE_IN_SINE);
			scale_.y = Ease::Auto(count_, 120, 0.8f, 5.2f * 2, EASE_IN_SINE);
			degree_ = Ease::Auto(count_, 120, 0, 1080, EASE_IN_OUT_QUINT, 2.0f);

			if (count_ >= 0 && count_ <= 30) {

				for (int i = 8; i < 12; i++) {
					titleDegree_[i] = Ease::Auto(count_, 30, 0, 1440 + (i * 6.0f), EASE_IN_SINE);
				}
				if (count_ <= 15) {
					titleScale_[0].x = Ease::Auto(count_, 15, titleScale_[0].x, 2.6f, EASE_OUT_SINE);
				}
				if (count_ > 15) {
					titleScale_[0].x = Ease::Auto(count_ - 15, 15, 2.6f, 1.0f, EASE_IN_SINE);
				}

				titlePos_[1].x = Ease::Auto(count_ - (0), 30 + (0), 300.0f, 300.0f + 196.0f * 5.0f / 2.0f, EASE_OUT_BACK);
				for (int i = 1; i < 7; i++) {
					if (IsCircle2CircleHit(titlePos_[i].x, titlePos_[i].y, 98.0f * titleScale_[i].x, titlePos_[i + 1].x, titlePos_[i + 1].y, 98.0f * titleScale_[i + 1].x)) {
						titlePos_[i + 1].x = titlePos_[i].x + (98.0f * titleScale_[i].x) / 1.5f + (98.0f * titleScale_[i + 1].x) * 1.25f;
						titleScale_[i + 0].x = titleScale_[i + 1].x + 0.075f;
						titleScale_[i + 0].y = titleScale_[i + 1].y - 0.02f;
					}
				}
				titlePos_[8] = titlePos_[4];
				titlePos_[9] = titlePos_[5];
				titlePos_[10] = titlePos_[6];
				titlePos_[11] = titlePos_[7];
			}
			if (count_ >= 26 + (0) && count_ <= 46 + (0)) {
				titlePos_[1].x = Ease::Auto(count_ - (30), 20 + (0), titlePos_[1].x, 300.0f + 196.0f * 1.0f, EASE_OUT_SINE);
				titleScale_[1].x = Ease::Auto(count_ - (30), 20 + (0), titleScale_[1].x, 1.0f, EASE_OUT_BACK);
				titleScale_[1].y = Ease::Auto(count_ - (30), 20 + (0), titleScale_[1].y, 1.0f, EASE_OUT_BACK);
			}
			if (count_ >= 26 + (2) && count_ <= 46 + (2)) {
				titlePos_[2].x = Ease::Auto(count_ - (30), 20 + (0), titlePos_[2].x, 300.0f + 196.0f * 2.0f, EASE_OUT_SINE);
				titleScale_[2].x = Ease::Auto(count_ - (2), 20 + (0), titleScale_[2].x, 1.0f, EASE_OUT_BACK);
				titleScale_[2].y = Ease::Auto(count_ - (2), 20 + (0), titleScale_[2].y, 1.0f, EASE_OUT_BACK);
			}
			if (count_ >= 26 + (5 + 3) && count_ <= 46 + (5 + 3)) {
				titlePos_[3].x = Ease::Auto(count_ - (30 + 5 + 3), 20 + (0), titlePos_[3].x, 300.0f + 196.0f * 3.0f, EASE_OUT_SINE);
				titleScale_[3].x = Ease::Auto(count_ - (30 + 5 + 3), 20 + (0), titleScale_[3].x, 1.0f, EASE_OUT_BACK);
				titleScale_[3].y = Ease::Auto(count_ - (30 + 5 + 3), 20 + (0), titleScale_[3].y, 1.0f, EASE_OUT_BACK);
			}
			if (count_ >= 26 + (9 + 3) && count_ <= 46 + (9 + 3)) {
				titlePos_[4].x = Ease::Auto(count_ - (30 + (9 + 3)), 20, titlePos_[4].x, 300.0f + 196.0f * 4.0f, EASE_OUT_SINE);
				titleScale_[4].x = Ease::Auto(count_ - (30 + (9 + 3)), 20, titleScale_[4].x, 1.0f, EASE_OUT_BACK);
				titleScale_[4].y = Ease::Auto(count_ - (30 + (9 + 3)), 20, titleScale_[4].y, 1.0f, EASE_OUT_BACK);
			}
			if (count_ >= 26 + (14 + 3) && count_ <= 46 + (14 + 3)) {
				titlePos_[5].x = Ease::Auto(count_ - (30 + (14 + 3)), 20, titlePos_[5].x, 300.0f + 196.0f * 5.0f, EASE_OUT_SINE);
				titleScale_[5].x = Ease::Auto(count_ - (30 + (14 + 3)), 20, titleScale_[5].x, 1.0f, EASE_OUT_BACK);
				titleScale_[5].y = Ease::Auto(count_ - (30 + (14 + 3)), 20, titleScale_[5].y, 1.0f, EASE_OUT_BACK);
			}
			if (count_ >= 26 + (20 + 3) && count_ <= 46 + (20 + 3)) {
				titlePos_[6].x = Ease::Auto(count_ - (30 + (20 + 3)), 20, titlePos_[6].x, 300.0f + 196.0f * 6.0f, EASE_OUT_SINE);
				titleScale_[6].x = Ease::Auto(count_ - (30 + (20 + 3)), 20, titleScale_[6].x, 1.0f, EASE_OUT_BACK);
				titleScale_[6].y = Ease::Auto(count_ - (30 + (20 + 3)), 20, titleScale_[6].y, 1.0f, EASE_OUT_BACK);
			}
			if (count_ >= 26 + (27 + 3) && count_ <= 46 + (27 + 3)) {
				titlePos_[7].x = Ease::Auto(count_ - (30 + (27 + 3)), 20, titlePos_[7].x, 300.0f + 196.0f * 7.0f, EASE_OUT_SINE);
				titleScale_[7].x = Ease::Auto(count_ - (30 + (27 + 3)), 20, titleScale_[7].x, 1.0f, EASE_OUT_BACK);
				titleScale_[7].y = Ease::Auto(count_ - (30 + (27 + 3)), 20, titleScale_[7].y, 1.0f, EASE_OUT_BACK);
			}

			if (count_ >= 90) {
				for (int i = 8; i < 12; i++) {
					titlePos_[i].x = Ease::Auto(count_ - (90 + (i - 8) * 2), 15, titlePos_[i].x, titlePos_[i - 4].x, EASE_OUT_BACK, 2.0f);
				}
			}

			count_ += 1;
			if (count_ >= 120) {
				for (int i = 0; i < 12; i++) {
					titlePos_[i] = { 196.0f / 2 * 3 + i * 196, 196 * 2 };
				}
				titlePos_[8] = titlePos_[4];
				titlePos_[9] = titlePos_[5];
				titlePos_[10] = titlePos_[6];
				titlePos_[11] = titlePos_[7];
				isFirstTitle_ += 1;
				/*scale_ = { 1.0f,1.0f };*/
				scale_ = { 5.2f * 2,5.2f * 2 };
				count_ = 0;
				degree_ = 0;
			}
			cameraT_.SetScale(scale_);
			cameraT_.SetRotate(ConvertDeg2Rad(degree_));
			cameraT_.SetCamera();
			//飛ばすため
			if (sGetInput->TriggerKeys({ DIK_RETURN, DIK_SPACE }) || sGetInput->JoystickTriggerButton(0, DIXC_A) || sGetInput->MouseTriggerButton({ DIC_LEFT })) {
				count_ += 15;
			}
		}
		//くるくる大きく
		else if (isFirstTitle_ == 2) {
			scale_.x = Ease::Auto(count_, 60, 5.2f * 2, 0.8f, EASE_OUT_BACK);
			scale_.y = Ease::Auto(count_, 60, 5.2f * 2, 0.8f, EASE_OUT_BACK);
			degree_ = Ease::Auto(count_, 60, 0, -1080, EASE_IN_OUT_BACK, 1.0f);

			if (count_ >= 0 && count_ <= 10) {
				titleDegree_[8] = Ease::Auto(count_, 10, 8 * 6, 360, EASE_OUT_BACK);
			}
			if (count_ >= 0 + 5 && count_ <= 10 + 5) {
				titleDegree_[9] = Ease::Auto(count_ - 5, 10, 9 * 6, 360, EASE_OUT_BACK);
			}
			if (count_ >= 0 + 10 && count_ <= 10 + 10) {
				titleDegree_[10] = Ease::Auto(count_ - 10, 10, 10 * 6, 360, EASE_OUT_BACK);
			}
			if (count_ >= 0 + 15 && count_ <= 10 + 15) {
				titleDegree_[11] = Ease::Auto(count_ - 15, 10, 11 * 6, 360, EASE_OUT_BACK);
			}


			if (count_ >= 0 && count_ <= 30) {
				for (int i = 0; i < 12; i++) {
					titlePos_[i].y = Ease::Auto(count_, 30, 196 * 2, 196 * 2 - 96, EASE_OUT_SINE);
					titleScale_[i].x = Ease::Auto(count_, 30, 1.0f, 0.75f, EASE_OUT_SINE);
					titleScale_[i].y = titleScale_[i].x;
				}
			}
			if (count_ >= 30 && count_ <= 60) {
				for (int i = 0; i < 12; i++) {
					titlePos_[i].y = Ease::Auto(count_ - 30, 30, 196 * 2 - 64, 196 * 2 - 16, EASE_IN_SINE);
					titleScale_[i].x = Ease::Auto(count_ - 30, 30, 0.75f, 1.00f, EASE_OUT_BACK);
					titleScale_[i].y = titleScale_[i].x;
				}
			}

			count_ += 1;
			if (count_ >= 60) {
				isFirstTitle_ += 1;
				/*scale_ = { 1.0f,1.0f };*/
				scale_ = { 0.8f,0.8f };
				count_ = 0;
				degree_ = 0;
			}
			cameraT_.SetScale(scale_);
			cameraT_.SetRotate(ConvertDeg2Rad(degree_));
			cameraT_.SetCamera();
			//飛ばすため
			if (sGetInput->TriggerKeys({ DIK_RETURN, DIK_SPACE }) || sGetInput->JoystickTriggerButton(0, DIXC_A) || sGetInput->MouseTriggerButton({ DIC_LEFT })) {
				count_ += 30;
			}
		} else if (isFirstTitle_ == 3) {
			count_ += 1;
			titleColor_ += static_cast<int>(255.0f / 50.0f);
			if (count_ >= 50) {
				isFirstTitle_ += 1;
				count_ = 0;
				titleColor_ = 0xFFFFFFFF;
			}
		}
		//全て終了
		else if (isFirstTitle_ == 4) {
			//イージング処理
			if (1) {
				if (count_ <= 20 * 2) {
					translate_.y = Ease::Auto(count_, 20 * 2, 100.0f, 130.0f, EASE_OUT_SINE);
				} else if (count_ <= 60 * 2) {
					translate_.y = Ease::Auto(count_ - 21 * 2, 40 * 2, 130.0f, 100 - 30.0f, EASE_IN_OUT_SINE);
				} else if (count_ <= 80 * 2) {
					translate_.y = Ease::Auto(count_ - 61 * 2, 20 * 2, 100 - 30.0f, 100.0f, EASE_IN_SINE);
				}
			}
			//鯛とルの処理
			if (1) {
				if (count_ <= 20 + 5 && count_ >= 0 + 5) {
					titleDegree_[0] = Ease::Auto(count_ - 5, 20, 0, 360, EASE_OUT_BACK);
				}
				if (count_ <= 30 + 5 && count_ >= 10 + 5) {
					titleDegree_[2] = Ease::Auto(count_ - 10 - 5, 20, 0, 360, EASE_OUT_BACK);
				}
				if (count_ <= 40 + 5 && count_ >= 20 + 5) {
					titleDegree_[8] = Ease::Auto(count_ - 20 - 5, 20, 0, 360, EASE_OUT_BACK);
				}
				if (count_ <= 50 + 5 && count_ >= 30 + 5) {
					titleDegree_[9] = Ease::Auto(count_ - 30 - 5, 20, 0, 360, EASE_OUT_BACK);
				}
				if (count_ <= 60 + 5 && count_ >= 40 + 5) {
					titleDegree_[10] = Ease::Auto(count_ - 40 - 5, 20, 0, 360, EASE_OUT_BACK);
				}
				if (count_ <= 70 + 5 && count_ >= 50 + 5) {
					titleDegree_[11] = Ease::Auto(count_ - 50 - 5, 20, 0, 360, EASE_OUT_BACK);
				}
				if (count_ <= 140 && count_ >= 120) {
					titleDegree_[0] = Ease::Auto(count_ - 120, 20, 0, 360, EASE_OUT_BACK);
					titleDegree_[2] = Ease::Auto(count_ - 120, 20, 0, 360, EASE_OUT_BACK);
					titleDegree_[8] = Ease::Auto(count_ - 120, 20, 0, 360, EASE_OUT_BACK);
					titleDegree_[9] = Ease::Auto(count_ - 120, 20, 0, 360, EASE_OUT_BACK);
					titleDegree_[10] = Ease::Auto(count_ - 120, 20, 0, 360, EASE_OUT_BACK);
					titleDegree_[11] = Ease::Auto(count_ - 120, 20, 0, 360, EASE_OUT_BACK);
				}
			}
			count_ += 1;
			if (count_ > 160) {
				count_ = 0;
				//translate_.y = 0.0f;
			}
			cameraT_.SetViewport(translate_.x, translate_.y, CustomNovice::WinWidth(), CustomNovice::WinHeight());
			cameraT_.SetCamera();
			//Game　OR　EXIT
			if (1) {
				if (sGetInput->TriggerKeys({ DIK_W, DIK_UP }) || sGetInput->JoystickTriggerButton(0, DIXC_UP)) {
					isSelect_ -= 1;
					SoundPlay(SE_SELECT);
				} else if (sGetInput->TriggerKeys({ DIK_S, DIK_DOWN }) || sGetInput->JoystickTriggerButton(0, DIXC_DOWN)) {
					isSelect_ += 1;
					SoundPlay(SE_SELECT);
				}

				if (isSelect_ < 0) {
					isSelect_ = 1;
				} else if (isSelect_ > 1) {
					isSelect_ = 0;
				}
			}
			//START
			if (isSelect_ == 0) {
				if (sGetInput->TriggerKeys({ DIK_RETURN, DIK_SPACE }) || sGetInput->JoystickTriggerButton(0, DIXC_A) || sGetInput->MouseTriggerButton({ DIC_LEFT })) {
					isTitle_ = 10;
					count_ = 0;
					//位置の調整
					translate_ = { 1280.0f + 200.0f,640.0f + 200.0f };
					cameraT_.SetViewport(translate_.x, translate_.y, CustomNovice::WinWidth(), CustomNovice::WinHeight());
					cameraT_.SetCamera();
					//ここまで
					SoundPlay(SE_DECIDE);
				}
			}
			//EXIT
			else if (isSelect_ == 1) {
				if (sGetInput->TriggerKeys({ DIK_RETURN, DIK_SPACE }) || sGetInput->JoystickTriggerButton(0, DIXC_A) || sGetInput->MouseTriggerButton({ DIC_LEFT })) {
					/*isTitle_ = 20;*/
					SceneClass::SetClose();
					SoundPlay(SE_DECIDE);
				}
			}
		}
	}
	//小さくなる処理(大きくするか)
	else if (isTitle_ == 10) {

		//プレイヤーの登場
		if (count_ <= 30) {
			player_.y = Ease::Auto(count_, 30, 2060, CustomNovice::WinHeight() - 75 - 100 - 300, EASE_OUT_SINE);
		} else if (count_ > 30) {
			player_.y = Ease::Auto(count_ - 30, 30, CustomNovice::WinHeight() - 75 - 100 - 300, 980 - wid_.y / 2, EASE_IN_SINE);
		}

		stagePos_.y = Ease::Auto(count_, 60, CustomNovice::WinHeight() + 100, /*CustomNovice::WinHeight() - 75*/1030, EASE_IN_OUT_BACK);
		//下の説明のカラーについて
		colorTeach_ = static_cast<float>(Ease::Auto(count_, 60, static_cast<float>(0x000000FF - 60), static_cast<float>(0x000000FF), EASE_LINER));
		scale_.x = Ease::Auto(count_, 60, 0.8f, 0.6f, EASE_IN_SINE);
		scale_.y = Ease::Auto(count_, 60, 0.8f, 0.6f, EASE_IN_SINE);
		/*translate_.x = Ease::Auto(count_, 60, 0.0f, -CustomNovice::WinWidth() / 2, EASE_IN_SINE,1.0f);
		translate_.y = Ease::Auto(count_, 60, 0.0f, -CustomNovice::WinHeight() / 2, EASE_IN_SINE,1.0f);*/
		translate_.x = Ease::Auto(count_, 60, 1280.0f + 200.0f, -CustomNovice::WinWidth() / 2, EASE_IN_SINE, 1.0f);
		translate_.y = Ease::Auto(count_, 60, 640.0f + 200.0f, -CustomNovice::WinHeight() / 2, EASE_IN_SINE, 1.0f);
		degree_ = Ease::Auto(count_, 60, 0, 360, EASE_IN_OUT_BACK, 1.0f);
		count_ += 1;
		if (count_ >= 60) {
			isTitle_ = 1;
			/*scale_ = { 1.0f,1.0f };*/
			player_.y = 980 - wid_.y / 2;
			scale_ = { 0.6f,0.6f };
			count_ = 0;
			degree_ = 0;
			transitionPos_ = { CustomNovice::WinWidth() / 2,-CustomNovice::WinHeight() / 2 };
		}
		cameraT_.SetViewport(translate_.x, translate_.y, CustomNovice::WinWidth(), CustomNovice::WinHeight());
		cameraT_.SetScale(scale_);
		cameraT_.SetRotate(ConvertDeg2Rad(degree_));
		cameraT_.SetCamera();

	}//選択画面の処理
	//タイトルの選択画面
	else if (isTitle_ == 1) {
		moveCount_ += 1;
		if (moveCount_ <= 8 && moveCount_ > 0) {
			if (count_ == 0) {
				playerScale_.x = Ease::Auto(moveCount_, 8, 1.0f, 1.1f, EASE_OUT_SINE);
				playerScale_.y = Ease::Auto(moveCount_, 8, 1.0f, 0.9f, EASE_OUT_SINE);
			}
		} else if (moveCount_ > 8 && moveCount_ > 0) {
			if (count_ == 0) {
				playerScale_.x = Ease::Auto(moveCount_ - 8, 8, 1.1f, 1.0f, EASE_IN_SINE);
				playerScale_.y = Ease::Auto(moveCount_ - 8, 8, 0.9f, 1.0f, EASE_IN_SINE);
			}
		}
		if (moveCount_ <= 8 + 110 && moveCount_ >= 0 + 110) {
			if (count_ == 0) {
				playerScale_.x = Ease::Auto(moveCount_ - 110, 8, 1.0f, 1.1f, EASE_OUT_SINE);
				playerScale_.y = Ease::Auto(moveCount_ - 110, 8, 1.0f, 0.9f, EASE_OUT_SINE);
			}
		} else if (moveCount_ > 8 + 110 && moveCount_ >= 0 + 110) {
			if (count_ == 0) {
				playerScale_.x = Ease::Auto(moveCount_ - 8 - 110, 8, 1.1f, 1.0f, EASE_IN_SINE);
				playerScale_.y = Ease::Auto(moveCount_ - 8 - 110, 8, 0.9f, 1.0f, EASE_IN_SINE);
			}
		}
		if (moveCount_ > 240) {
			moveCount_ = 0;
		}
		//回転処理のボタン / ボタン押したら動かないようにするため
		if (!isRotate_ && toSelectView_ == 0) {
			if (sGetInput->Keys({ DIK_D, DIK_RIGHT, DIK_X }) || sGetInput->JoystickPushButton(0, { DIXC_RIGHT, DIXC_RB }) || sGetInput->JoystickAnalogLeftX(0) > 0) {
				which_ = DIK_RIGHT;
				isRotate_ = true;
				SoundPlay(SE_SELECT);
				if (degree_ == 0) {
					degree_ = 360;
				}
			} else if (sGetInput->Keys({ DIK_A, DIK_LEFT, DIK_Z }) || sGetInput->JoystickPushButton(0, { DIXC_LEFT, DIXC_LB }) || sGetInput->JoystickAnalogLeftX(0) < 0
				) {
				which_ = DIK_LEFT;
				isRotate_ = true;
				SoundPlay(SE_SELECT);
				if (degree_ == 360) {
					degree_ = 0;
				}
			}
		}
		//回転処理
		if (isRotate_) {

			//右左に関係ない処理
			if (count_ <= maxCount_ / 2) {
				player_.y = Ease::Auto(count_, maxCount_ / 2, 980 - wid_.y / 2, CustomNovice::WinHeight() - 75 - 145 - 300, EASE_OUT_SINE);
				playerScale_.x = Ease::Auto(count_, maxCount_ / 2, 1.0f, 0.7f, EASE_OUT_QUINT);
				playerScale_.y = Ease::Auto(count_, maxCount_ / 2, 0.9f, 1.2f, EASE_OUT_QUINT);
			} else if (count_ > maxCount_ / 2 && count_ <= maxCount_) {
				player_.y = Ease::Auto(count_ - maxCount_ / 2, maxCount_ / 2, CustomNovice::WinHeight() - 75 - 145 - 300, 980 - wid_.y / 2, EASE_IN_SINE);
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
				player_.y = 980 - wid_.y / 2;
			}

			if (which_ == DIK_RIGHT) {

				//プレイヤー
				if (count_ <= maxCount_) {
					playerRotate_ = Ease::Auto(count_, maxCount_ / 2, 0, 360, EASE_OUT_SINE);
				}

				/*if (count_ <= maxCount_ / 2) {
					player_.y = Ease::Auto(count_, maxCount_ / 2, stagePos_.y - 50 - 64, CustomNovice::WinHeight() - 75 - 145 - 300, EASE_OUT_SINE);
				}
				else if (count_ > maxCount_ / 2) {
					player_.y = Ease::Auto(count_ - maxCount_ / 2, maxCount_ / 2, CustomNovice::WinHeight() - 75 - 145 - 300, stagePos_.y - 50 - 64, EASE_IN_SINE);
				}*/

				if (count_ <= maxCount_) {
					if (isColor_ == 2) {
						degree_ = Ease::Auto(count_, maxCount_, 0, 90, EASE_OUT_BACK);
						//degree_ = Ease::Auto(count_, maxCount_, 360, 270);
					} else if (isColor_ == 3) {
						degree_ = Ease::Auto(count_, maxCount_, 270, 360, EASE_OUT_BACK);
						//degree_ = Ease::Auto(count_, maxCount_, 270, 180);
					} else if (isColor_ == 0) {
						//degree_ = Ease::Auto(count_, maxCount_, 180, 90);
						degree_ = Ease::Auto(count_, maxCount_, 180, 270, EASE_OUT_BACK);
					} else if (isColor_ == 1) {
						//degree_ = Ease::Auto(count_, maxCount_, 90, 360);
						degree_ = Ease::Auto(count_, maxCount_, 90, 180, EASE_OUT_BACK);
					}
					count_ += 1;
				} else if (count_ > maxCount_) {
					isRotate_ = false;
					count_ = 0;
					isColor_ -= 1;
					if (isColor_ < 0) {
						isColor_ = 3;
					}
				}
			} else if (which_ == DIK_LEFT) {

				//プレイヤー
				if (count_ <= maxCount_) {
					playerRotate_ = Ease::Auto(count_, maxCount_ / 2, 360, 0, EASE_OUT_SINE);
				}

				/*if (count_ <= maxCount_ / 2) {
					player_.y = Ease::Auto(count_, maxCount_ / 2, stagePos_.y - 50 - 64, CustomNovice::WinHeight() - 75 - 145 - 300, EASE_OUT_SINE);
				}
				else if (count_ > maxCount_ / 2) {
					player_.y = Ease::Auto(count_ - maxCount_ / 2, maxCount_ / 2, CustomNovice::WinHeight() - 75 - 145 - 300, stagePos_.y - 50 - 64, EASE_IN_SINE);
				}*/

				if (count_ <= maxCount_) {
					if (isColor_ == 2) {
						//degree_ = Ease::Auto(count_, maxCount_, 0, 90);
						degree_ = Ease::Auto(count_, maxCount_, 360, 270, EASE_OUT_BACK);
					} else if (isColor_ == 3) {
						//degree_ = Ease::Auto(count_, maxCount_, 90, 180);
						degree_ = Ease::Auto(count_, maxCount_, 270, 180, EASE_OUT_BACK);
					} else if (isColor_ == 0) {
						degree_ = Ease::Auto(count_, maxCount_, 180, 90, EASE_OUT_BACK);
						//degree_ = Ease::Auto(count_, maxCount_, 180, 270);
					} else if (isColor_ == 1) {
						degree_ = Ease::Auto(count_, maxCount_, 90, 0, EASE_OUT_BACK);
						//degree_ = Ease::Auto(count_, maxCount_, 270, 360);
					}
					count_ += 1;
				} else if (count_ > maxCount_) {
					isRotate_ = false;
					count_ = 0;
					isColor_ += 1;
					if (isColor_ > 3) {
						isColor_ = 0;
					}
				}
			}
		}
		//画面に行く処理
		if (isColor_ == 1 || isColor_ == 3) {
			if (sGetInput->TriggerKeys({ DIK_RETURN, DIK_SPACE }) || sGetInput->JoystickTriggerButton(0, DIXC_A) || sGetInput->MouseTriggerButton({ DIC_LEFT })) {
				if (isRotate_ == false) {
					isTitle_ = 11;
					SoundPlay(SE_DECIDE);
				}
			}
		}
		if (isColor_ == 2 || isColor_ == 0) {
			if (sGetInput->TriggerKeys({ DIK_RETURN, DIK_SPACE }) || sGetInput->JoystickTriggerButton(0, DIXC_A) || sGetInput->MouseTriggerButton({ DIC_LEFT })) {
				if (isRotate_ == false) {
					toSelectView_ = 1;
					SoundPlay(SE_DECIDE);
				}
			}
			if (toSelectView_ == 1) {
				//シーン切り替え
				colorTeach_ = static_cast<float>(Ease::Auto(count_, 60, static_cast<float>(0x000000FF), static_cast<float>(0x00000000), EASE_LINER));
				player_.x = Ease::Auto(count_, 60, 1200, 500, EASE_OUT_BACK);
				cameraT_.SetViewport(
					Ease::Auto(count_, 60, -CustomNovice::WinWidth() / 2, 440 - 64, EASE_OUT_BACK),
					Ease::Auto(count_, 60, -CustomNovice::WinHeight() / 2, 74, EASE_OUT_BACK),
					CustomNovice::WinWidth(), CustomNovice::WinHeight()
				);
				cameraT_.SetCamera();
				count_ += 1;
				if (count_ >= 60) {
					cameraT_.SetViewport(440 - 64, 74, CustomNovice::WinWidth(), CustomNovice::WinHeight());
					cameraT_.SetCamera();
				}
			}
		}
		/*if (isColor_ == 0) {
			if (sGetInput->TriggerKeys({ DIK_RETURN, DIK_SPACE }) || sGetInput->JoystickTriggerButton(0, DIXC_A) || sGetInput->MouseTriggerButton({ DIC_LEFT })) {
				CustomNovice::ChangeWindowMode();
			}
		}*/
		//色について
		for (int i = 0; i < 4; i++) {
			if (i == isColor_) {
				color_[i] = 0xFFFFFFFF;
			} else {
				color_[i] = 0xA0A0A0FF;
			}
		}
	}
	//大きくなる処理
	else if (isTitle_ == 11) {

		if (count_ <= 30) {
			player_.y = Ease::Auto(count_, 30, 980 - wid_.y / 2, CustomNovice::WinHeight() - 75 - 100 - 300, EASE_OUT_SINE);
		} else if (count_ > 30) {
			player_.y = Ease::Auto(count_ - 30, 30, CustomNovice::WinHeight() - 75 - 100 - 300, 2060, EASE_IN_SINE);
		}

		stagePos_.y = Ease::Auto(count_, 60, /*CustomNovice::WinHeight() - 75*/1030, CustomNovice::WinHeight() + 100, EASE_IN_SINE);
		//イージング SIZE and TRANSLATE
		scale_.x = Ease::Auto(count_, 60, 1.0f, 0.8f, EASE_IN_SINE);
		scale_.y = Ease::Auto(count_, 60, 1.0f, 0.8f, EASE_IN_SINE);
		/*translate_.x = Ease::Auto(count_, 60, -CustomNovice::WinWidth() / 2, 0.0f,  EASE_IN_SINE);
		translate_.y = Ease::Auto(count_, 60,-CustomNovice::WinHeight() / 2, 0.0f,  EASE_IN_SINE);*/
		translate_.x = Ease::Auto(count_, 60, -CustomNovice::WinWidth() / 2, 1280 + 200.0f, EASE_IN_SINE);
		translate_.y = Ease::Auto(count_, 60, -CustomNovice::WinHeight() / 2, 640.0f + 200.0f, EASE_IN_SINE);
		degree_ = Ease::Auto(count_, 60, 0, -360, EASE_IN_OUT_BACK, 1.0f);
		count_ += 1;
		if (count_ >= 60) {
			scale_ = { 0.8f,0.8f };
			count_ = 0;
			isTitle_ = 0;
			degree_ = 0;
			isColor_ = 2;



		}

		cameraT_.SetViewport(translate_.x, translate_.y, CustomNovice::WinWidth(), CustomNovice::WinHeight());
		cameraT_.SetScale(scale_);
		cameraT_.SetRotate(ConvertDeg2Rad(degree_));
		cameraT_.SetCamera();
	}
	//ゲーム終了の処理
	else if (isTitle_ == 20) {

	}
	cameraT_.SetRotate(ConvertDeg2Rad(degree_));
	cameraT_.SetCamera();
}

void Title::Draw() {
	//背景を動かさないための処理(グリッド線)
	if (1) {
		if (isTitle_ == 0) {
			preRotate_ = cameraT_.GetRotate();
			cameraT_.SetRotate(ConvertDeg2Rad(0));
			cameraT_.SetScale({ 0.8f,0.8f });
			cameraT_.SetViewport(0, 0, CustomNovice::WinWidth(), CustomNovice::WinHeight());
			cameraT_.SetTranslate({ 0.0f,0.0f });
			cameraT_.SetCamera();
			SceneClass::DrawGrid(cameraT_);
			cameraT_.SetRotate(preRotate_);
			cameraT_.SetScale(scale_);
			cameraT_.SetViewport(0, translate_.y, CustomNovice::WinWidth(), CustomNovice::WinHeight());
			cameraT_.SetTranslate({ 384.0f,384.0f - 48.0f });
			cameraT_.SetCamera();
		} else {
			preRotate_ = cameraT_.GetRotate();
			cameraT_.SetRotate(ConvertDeg2Rad(0));
			cameraT_.SetScale({ 1.0f,1.0f });
			cameraT_.SetViewport(0, 0, CustomNovice::WinWidth(), CustomNovice::WinHeight());
			cameraT_.SetTranslate({ 0.0f,0.0f });
			cameraT_.SetCamera();
			SceneClass::DrawGrid(cameraT_);
			cameraT_.SetRotate(preRotate_);
			cameraT_.SetScale(scale_);
			cameraT_.SetViewport(translate_.x, translate_.y, CustomNovice::WinWidth(), CustomNovice::WinHeight());
			cameraT_.SetTranslate({ 384.0f,384.0f - 48.0f });
			cameraT_.SetCamera();
		}
	}
	//説明のやつ
	//最初は後ろ
	if (isTitle_ == 10 || isTitle_ == 1) {
		//プレイヤーの処理？
		leftTop_ = { -wid_.x / 2, wid_.y / 2 };
		rightTop_ = { +wid_.x / 2, wid_.y / 2 };
		leftBottom_ = { -wid_.x / 2, -wid_.y / 2 };
		rightBottom_ = { +wid_.x / 2, -wid_.y / 2 };
		CustomNovice::DrawQuad(
			SceneStageSelect::PlayerView(player_, leftTop_, ConvertDeg2Rad(playerRotate_), playerScale_).x, SceneStageSelect::PlayerView(player_, leftTop_, ConvertDeg2Rad(playerRotate_), { 1.0f,1.0f }).y,
			SceneStageSelect::PlayerView(player_, rightTop_, ConvertDeg2Rad(playerRotate_), playerScale_).x, SceneStageSelect::PlayerView(player_, rightTop_, ConvertDeg2Rad(playerRotate_), { 1.0f,1.0f }).y,
			SceneStageSelect::PlayerView(player_, leftBottom_, ConvertDeg2Rad(playerRotate_), playerScale_).x, SceneStageSelect::PlayerView(player_, leftBottom_, ConvertDeg2Rad(playerRotate_), playerScale_).y,
			SceneStageSelect::PlayerView(player_, rightBottom_, ConvertDeg2Rad(playerRotate_), playerScale_).x, SceneStageSelect::PlayerView(player_, rightBottom_, ConvertDeg2Rad(playerRotate_), playerScale_).y,
			GraphHandle::Width(TX_PLAYER) / 3, 0, GraphHandle::Width(TX_PLAYER) / 3, GraphHandle::Height(TX_PLAYER), GraphHandle::ID(TX_PLAYER), 0xffff8bff
		);
	}
	if (isTitle_ == 1 || isTitle_ == 10 || isTitle_ == 11) {
		/*CustomNovice::DrawBox(0, stagePos_.y - 50, CustomNovice::WinWidth() - 200 + 200, 100.0f, BLACK,0.0f,kFillModeWireFrame);*/
		CustomNovice::DrawQuad(0, stagePos_.y - 50, 0 + CustomNovice::WinWidth(), stagePos_.y - 50.0f,
			0, stagePos_.y + 50.0f, CustomNovice::WinWidth(), stagePos_.y + 50.0f,
			0, 0, 64, 64, GraphHandle::ID(TX_TILEMAP_NORMAL), 0xaaaaaaFF);
	}
	if (isColor_ == 2 || isColor_ == 0) {
		if (toSelectView_ == 1) {
			cameraT_.SetViewport(
				Ease::Auto(count_, 50, -CustomNovice::WinWidth() / 2, 440 - 64, EASE_OUT_BACK),
				Ease::Auto(count_, 50, -CustomNovice::WinHeight() / 2, 50 + 24, EASE_OUT_BACK),
				CustomNovice::WinWidth(), CustomNovice::WinHeight()
			);
			scale_.x = Ease::Auto(count_, 50, 0.6f, 1.0f, EASE_IN_SINE);
			scale_.y = scale_.x;
			degree_ = Ease::Auto(count_, 40, 0, 360, EASE_IN_SINE);
			cameraT_.SetRotate(ConvertDeg2Rad(degree_));
			cameraT_.SetScale(scale_);
			cameraT_.SetCamera();
			if (count_ >= 60) {
				cameraT_.SetViewport(440 - 64, 74, CustomNovice::WinWidth(), CustomNovice::WinHeight());
				cameraT_.SetCamera();
				count_ = 0;
				toSelectView_ = 0;
				colorTop_ = 0x000000FF;
				isTitle_ = 100;
				SceneClass::SetScene(STAGE_SELECT);
				SoundPlay(BGM_STAGE_SELECT);

			}
		}
	}
	//周りのやつ
	if (isTitle_ != 0 && isTitle_ != 100) {
		leftTop_ = { -width_ * 16 / 2, -height_ * 16 / 2 };
		rightTop_ = { +width_ * 16 / 2, -height_ * 16 / 2 };
		leftBottom_ = { -width_ * 16 / 2, height_ * 16 / 2 };
		rightBottom_ = { +width_ * 16 / 2, height_ * 16 / 2 };
		CustomNovice::DrawQuad(cameraT_,
			pos_.x + leftTop_.x, pos_.y + leftTop_.y,
			pos_.x + rightTop_.x, pos_.y + rightTop_.y,
			pos_.x + leftBottom_.x, pos_.y + leftBottom_.y,
			pos_.x + rightBottom_.x, pos_.y + rightBottom_.y,
			0, 0, GraphHandle::Width(TX_TITLEBOX), GraphHandle::Height(TX_TITLEBOX), GraphHandle::ID(TX_TITLEBOX), 0xffffffff
		);
	}

	//タイトル画面
	if (isTitle_ == 0) {
		if (isSelect_ == 0) {
			CustomNovice::DrawQuad(cameraT_,
				pos_.x - 224.0f, pos_.y + 224.0f,
				pos_.x + 224.0f, pos_.y + 224.0f,
				pos_.x - 224.0f, pos_.y - 224.0f,
				pos_.x + 224.0f, pos_.y - 224.0f,
				896 * 4, 0, 896, 896, GraphHandle::ID(TX_SELECTELLLIPSE), titleColor_
			);
		} else if (isSelect_ == 1) {
			CustomNovice::DrawQuad(cameraT_,
				pos_.x - 224.0f, pos_.y + 224.0f,
				pos_.x + 224.0f, pos_.y + 224.0f,
				pos_.x - 224.0f, pos_.y - 224.0f,
				pos_.x + 224.0f, pos_.y - 224.0f,
				896 * 5, 0, 896, 896, GraphHandle::ID(TX_SELECTELLLIPSE), titleColor_
			);
		}
		if (/*(isFirstTitle_ == 2 && count_ >= 30) || isFirstTitle_ >= 3*/1) {
			leftTop_ = { -196 / 2, -196 / 2 };
			rightTop_ = { +196 / 2, -196 / 2 };
			leftBottom_ = { -196 / 2, 196 / 2 };
			rightBottom_ = { +196 / 2, 196 / 2 };
			for (int i = 0; i < 4; i++) {
				//タイトル
				CustomNovice::DrawQuad(
					SceneStageSelect::PlayerView(titlePos_[i] + shake_, leftTop_, ConvertDeg2Rad(titleDegree_[i]), titleScale_[i]).x, SceneStageSelect::PlayerView(titlePos_[i], leftTop_, ConvertDeg2Rad(titleDegree_[i]), { 1.0f,1.0f }).y,
					SceneStageSelect::PlayerView(titlePos_[i] + shake_, rightTop_, ConvertDeg2Rad(titleDegree_[i]), titleScale_[i]).x, SceneStageSelect::PlayerView(titlePos_[i], rightTop_, ConvertDeg2Rad(titleDegree_[i]), { 1.0f,1.0f }).y,
					SceneStageSelect::PlayerView(titlePos_[i] + shake_, leftBottom_, ConvertDeg2Rad(titleDegree_[i]), titleScale_[i]).x, SceneStageSelect::PlayerView(titlePos_[i], leftBottom_, ConvertDeg2Rad(titleDegree_[i]), titleScale_[i]).y,
					SceneStageSelect::PlayerView(titlePos_[i] + shake_, rightBottom_, ConvertDeg2Rad(titleDegree_[i]), titleScale_[i]).x, SceneStageSelect::PlayerView(titlePos_[i], rightBottom_, ConvertDeg2Rad(titleDegree_[i]), titleScale_[i]).y,
					GraphHandle::Width(TX_TITLEROTATE) / 4 * i, 0, GraphHandle::Width(TX_TITLEROTATE) / 4, GraphHandle::Height(TX_TITLEROTATE), GraphHandle::ID(TX_TITLEROTATE), 0xffffffff
				);
			}
			for (int i = 4; i < 8; i++) {
				//タイトル
				CustomNovice::DrawQuad(
					SceneStageSelect::PlayerView(titlePos_[i] + shake_, leftTop_, ConvertDeg2Rad(titleDegree_[i]), titleScale_[i]).x, SceneStageSelect::PlayerView(titlePos_[i], leftTop_, ConvertDeg2Rad(titleDegree_[i]), { 1.0f,1.0f }).y,
					SceneStageSelect::PlayerView(titlePos_[i] + shake_, rightTop_, ConvertDeg2Rad(titleDegree_[i]), titleScale_[i]).x, SceneStageSelect::PlayerView(titlePos_[i], rightTop_, ConvertDeg2Rad(titleDegree_[i]), { 1.0f,1.0f }).y,
					SceneStageSelect::PlayerView(titlePos_[i] + shake_, leftBottom_, ConvertDeg2Rad(titleDegree_[i]), titleScale_[i]).x, SceneStageSelect::PlayerView(titlePos_[i], leftBottom_, ConvertDeg2Rad(titleDegree_[i]), titleScale_[i]).y,
					SceneStageSelect::PlayerView(titlePos_[i] + shake_, rightBottom_, ConvertDeg2Rad(titleDegree_[i]), titleScale_[i]).x, SceneStageSelect::PlayerView(titlePos_[i], rightBottom_, ConvertDeg2Rad(titleDegree_[i]), titleScale_[i]).y,
					GraphHandle::Width(TX_TITLEROTATE) / 4 * (i - 4), 0, GraphHandle::Width(TX_TITLEROTATE) / 4, GraphHandle::Height(TX_TITLEROTATE), GraphHandle::ID(TX_TITLEBLUE), 0xffffffff
				);
			}
			for (int i = 8; i < 12; i++) {
				//タイトル
				CustomNovice::DrawQuad(
					SceneStageSelect::PlayerView(titlePos_[i] + shake_, leftTop_, ConvertDeg2Rad(titleDegree_[i]), titleScale_[i]).x, SceneStageSelect::PlayerView(titlePos_[i], leftTop_, ConvertDeg2Rad(titleDegree_[i]), { 1.0f,1.0f }).y,
					SceneStageSelect::PlayerView(titlePos_[i] + shake_, rightTop_, ConvertDeg2Rad(titleDegree_[i]), titleScale_[i]).x, SceneStageSelect::PlayerView(titlePos_[i], rightTop_, ConvertDeg2Rad(titleDegree_[i]), { 1.0f,1.0f }).y,
					SceneStageSelect::PlayerView(titlePos_[i] + shake_, leftBottom_, ConvertDeg2Rad(titleDegree_[i]), titleScale_[i]).x, SceneStageSelect::PlayerView(titlePos_[i], leftBottom_, ConvertDeg2Rad(titleDegree_[i]), titleScale_[i]).y,
					SceneStageSelect::PlayerView(titlePos_[i] + shake_, rightBottom_, ConvertDeg2Rad(titleDegree_[i]), titleScale_[i]).x, SceneStageSelect::PlayerView(titlePos_[i], rightBottom_, ConvertDeg2Rad(titleDegree_[i]), titleScale_[i]).y,
					GraphHandle::Width(TX_TITLERED) / 4 * (i - 8), 0, GraphHandle::Width(TX_TITLERED) / 4, GraphHandle::Height(TX_TITLERED), GraphHandle::ID(TX_TITLERED), 0xffffffff
				);
			}
		}

	}


	//タイトル（２）の画面
	for (int i = 0; i < 4; i++) {
		if (isTitle_ == 1 && toSelectView_ == 0) {
			CustomNovice::DrawQuad(cameraT_,
				pos_.x - 224.0f * 1.2f, pos_.y + 224.0f * 1.2f,
				pos_.x + 224.0f * 1.2f, pos_.y + 224.0f * 1.2f,
				pos_.x - 224.0f * 1.2f, pos_.y - 224.0f * 1.2f,
				pos_.x + 224.0f * 1.2f, pos_.y - 224.0f * 1.2f,
				896 * i, 0, 896, 896, GraphHandle::ID(TX_SELECTELLLIPSE), color_[i]
			);
		}
	}

	if (isTitle_ == 1 && toSelectView_ == 0) {
		//中心に置くキーの表示
		if (1) {
			preRotate_ = cameraT_.GetRotate();
			cameraT_.SetRotate(ConvertDeg2Rad(0));
			cameraT_.SetCamera();
			CustomNovice::DrawQuad(cameraT_,
				pos_.x - 224.0f, pos_.y + 224.0f,
				pos_.x + 224.0f, pos_.y + 224.0f,
				pos_.x - 224.0f, pos_.y - 224.0f,
				pos_.x + 224.0f, pos_.y - 224.0f,
				896 * 6, 0, 896, 896, GraphHandle::ID(TX_SELECTELLLIPSE),
				static_cast<int>(colorTeach_)
			);
			cameraT_.SetRotate(preRotate_);
			cameraT_.SetCamera();
		}
	}
	if (isTitle_ == 1) {
		//シーン遷移のやつ
		if (toSelectView_ == 1) {

		}
	}
	//フェードアウトのやつ
	if (isTitle_ == 100) {
		CustomNovice::DrawBox(0.0f, 0.0f, CustomNovice::WinWidth(), CustomNovice::WinHeight(), colorTop_);
	}
	//降りるときは前
	if (isTitle_ == 11) {
		//プレイヤーの処理？
		leftTop_ = { -wid_.x / 2, wid_.y / 2 };
		rightTop_ = { +wid_.x / 2, wid_.y / 2 };
		leftBottom_ = { -wid_.x / 2, -wid_.y / 2 };
		rightBottom_ = { +wid_.x / 2, -wid_.y / 2 };
		CustomNovice::DrawQuad(
			SceneStageSelect::PlayerView(player_, leftTop_, ConvertDeg2Rad(playerRotate_), playerScale_).x, SceneStageSelect::PlayerView(player_, leftTop_, ConvertDeg2Rad(playerRotate_), { 1.0f,1.0f }).y,
			SceneStageSelect::PlayerView(player_, rightTop_, ConvertDeg2Rad(playerRotate_), playerScale_).x, SceneStageSelect::PlayerView(player_, rightTop_, ConvertDeg2Rad(playerRotate_), { 1.0f,1.0f }).y,
			SceneStageSelect::PlayerView(player_, leftBottom_, ConvertDeg2Rad(playerRotate_), playerScale_).x, SceneStageSelect::PlayerView(player_, leftBottom_, ConvertDeg2Rad(playerRotate_), playerScale_).y,
			SceneStageSelect::PlayerView(player_, rightBottom_, ConvertDeg2Rad(playerRotate_), playerScale_).x, SceneStageSelect::PlayerView(player_, rightBottom_, ConvertDeg2Rad(playerRotate_), playerScale_).y,
			GraphHandle::Width(TX_PLAYER) / 3, 0, GraphHandle::Width(TX_PLAYER) / 3, GraphHandle::Height(TX_PLAYER), GraphHandle::ID(TX_PLAYER), 0xffff8bff
		);
	}
}
